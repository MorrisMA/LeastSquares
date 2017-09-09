// PolyLeastSquares.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define     Nmax    (9)
#define     Rmax    (Nmax + 2)
#define     Cmax    (Rmax + 1)
#define     Mmax    (64)

void main(int argc, char* argv[])
{
    FILE    *in;
    char    ch;
    long    i, j, k, r, c, m, M, N, Nrow, Ncol;
    double  x[Mmax], y[Mmax], A[Rmax][Cmax], B[Rmax];
    double  pivot, tmp, sum; 

    ///////////////////////////////////////////////////////////////////////////
    
    printf("Polynomial Least Squares Fit\n");
    printf("Translated from \"Numerical Methods for the Personal Computer\", Terry E. Shoup\n");
	
    printf("\nComputes a polynomial least squares fit for tabular data using the normal\n");
    printf("equations and Cholesky decomposition. For a discussion regarding the use of \n");
    printf("the normal equations, see \"Numerical Methods for Scientists and Engineers\", \n");
    printf("R. W. Hamming.\n");

    if(argc < 2) {
        printf("\n\tProgram requires 2 arguments: N infile\n");
        printf("\tN\t: Order of the approx. polynomial, max(N)=%d\n", Nmax);
        printf("\tinfile\t: input [x, y] data in comma-separated columns\n");

        printf("\nEnter <CR> to continue: "); ch = getchar();
        exit(-1);
    } else {
        printf("\n");
        for(i = 1; i < argc; i++) {
            printf("argv[%d] = %s\n", i, argv[i]);
        }
        printf("\n");
    }

    N = atoi(argv[1]);

    if(Nmax < N) {
		fprintf(stderr, "Error: Polynomial order (N = argv[1]) exceeds allowable range. Maximum order = %d\n", Nmax);
    } else if((in = fopen(argv[2], "r")) == NULL) {
		fprintf(stderr, "Error: Cannot open input file: %s\n", argv[2]);
    } else {
        // Initialize A[][], B[], x[], and y[]

        for(r = 0; r <= Rmax; r++) {
            for(c = 0; c <= Cmax; c++) {
                A[r][c] = 0.0;
            }
        }

        for(r = 0; r <= Rmax; r++) {
            B[r] = 0.0;
        }

        for(r = 0; r <= Mmax; r++) {
            x[r] = y[r] = 0.0;
        }

        // Read input data from input file

        i = 1;
        while((EOF != fscanf(in, "%lf, %lf\n", &x[i], &y[i])) && (i <= Mmax)) {
            printf("%12.4le, %12.4le\n", x[i], y[i]);
            i++;
        }
		fclose(in);

        M    = (i - 1);     // Calculate input data length
        Nrow = (N + 1);     // Set number of rows based on polynomial order N
        Ncol = (Nrow + 1);  // Set number of columns based on polynomial order N

        printf("\nN = %d, Nrow = %d, Ncol = %d, M = %d\n", N, Nrow, Ncol, M);

        // Compute approximation polynomial using method of least squares
        //
        //  err_m = g(x_m) - y_m
        //  
        //  E = sum(err_m^2) = sum[(g(x_m) - y_m)^2]
        //
        //  g(x) = c1 * g1(x) + c2 * g2(x) + ... + ck * gk(x)
        //
        //  To minimize E, the partial derivatives with respect to the linear
        //  coefficients, ci, must be equal to 0. Thus,
        //
        //  E = sum(c1*g1(x_m)+c2*g2(x_m)+...+ ck*gk(x_m) - y_m]^2)
        //
        //  d(E)/d(c1) = 2*[c1*g1(x_m)+...+ck*gk(x_m) - y_m]*g1(x_m) = 0 
        //  d(E)/d(c2) = 2*[c1*g1(x_m)+...+ck*gk(x_m) - y_m]*g2(x_m) = 0 
        //
        //  d(E)/d(ck) = 2*[c1*g1(x_m)+...+ck*gk(x_m) - y_m]*gk(x_m) = 0
        //
        //  which can be arranged in the following matrix form
        //
        //  |sum[g1(x_m)*g1(x_m)]...sum[g1(x_m)*gk(x_m)||c1| |sum[g1(x_m)*y_m]|
        //  |sum[g2(x_m)*g1(x_m)]...sum[g2(x_m)*gk(x_m)||c2| |sum[g2(x_m)*y_m]|
        //  |sum[g3(x_m)*g1(x_m)]...sum[g3(x_m)*gk(x_m)||c3| |sum[g2(x_m)*y_m]|
        //  |                                          ||  |=|                |
        //  |sum[gk(x_m)*g1(x_m)]...sum[gk(x_m)*gk(x_m)||ck| |sum[gk(x_m)*y_m]|
        //
        //  The basis functions can be orthogonal: gi(x_m)gj(x_m) = 0, i <> j
        //  which would reduce the above A[]][] matrix into a diagonal form that
        //  can be solved directly: cj = sum[gj(x_m)*y_m] / sum[gj(x_m)^2].
        //  If this is the form, it is known as the normal equations for the
        //  method of least squares. A formulation using the normal equations
        //  can be susceptible to roundoff and other numerical instabilities.
        //
        //  Fortunately, any set of non-orthogonal basis functions that can form
        //  a linear combination can be used. For this application, the basis
        //  functions are: 1, x, x^2,...,x^k. these basis functions can be
        //  implemented as:
        //
        //  g1(x) = sum[x_m^0]
        //  g2(x) = sum[x_m^1]
        //
        //  gk(x) = sum[x_m^(k-1)]
        //
        //  Thus, gi(x)*gj(x) = sum[x_m^(i-1)*x_m^(j-1)]
        //
        // Set up the linear equations for the least squares decomposition
        
        for(r = 1; r <= Nrow; r++) {
            // Compute the elements of A[][]: A[r][c] = sum[gr(x_m) * gc(x_m)]
            for(c = 1; c <= Nrow; c++) {
                A[r][c] = 0; 
                for(m = 1; m <= M; m++) {
                    A[r][c] +=   pow(x[m], (double) (r - 1))
                               * pow(x[m], (double) (c - 1));
                }
            }
            // Augment A[][] with output vector: A[r][Ncol] = sum[gr(x_m) * y_m] 
            A[r][Ncol] = 0;
            for(m = 1; m <= M; m++) {
                A[r][Ncol] += pow(x[m], (double) (r - 1)) * y[m];
            }
        }

        printf("\n");
        for(k = 1; k <= Nrow; k++) {
            printf("|");
            for(j = 1; j <= Nrow; j++) {
                printf("%12.3le", A[k][j]);
            }
            printf("||%12.4le|\n", A[k][j]);
        }

        //  Use Cholesky's method for solution of a system of simultaneous
        //  linear equations to determine the coefficients of the approximating
        //  polynomial using the method of least sqaures.
        //
        //  A system of linear equations can be solved simultaneously using
        //  Cholesky's method if the system matrix A[][] can be reduced and/or
        //  transformed into an upper triangular form. If the augmented system
        //  matrix A[N][N+1] is operated on in the manner required, then back-
        //  substitution will provide the solution of the independent variable.
        //
        //  The system of linear equations has the form: Ax=b. Cholesky's method
        //  applies when A is positive definite. If A is also symmetric, then
        //  additional reduction in the complexity of the solution can be used.
        //  However, the mechanism used below does not assume a symmetric A.
        //
        //  Cholesky's method makes use of the fact that if A is positive 
        //  definite, then there will exist a lower triangular matrix L that
        //  can transform upper triangular matrix U by simple matrix multiplica-
        //  tion from the left into A: LU = A.
        //
        //  The form of L is as follows:
        //  
        //  | L[1][1]    0    ...     0   |
        //  | L[2][1] L[2][2] ...     0   |
        //  |                             |
        //  | L[N][1] L[N][2] ... L[N][N] |
        //
        //  The form of U is as follows:
        //
        //  |    1    L[1][2] ... L[1][N] |
        //  |    0       1    ... L[2][N] |
        //  |                             |
        //  |    0       0    ...     1   |
        //
        //  From these two matrices, it should be clear that L[1][1] = A[1][1].
        //  Even more, L[i][1] = A[i][1]. In other words, the first column of L
        //  equals the first column of A. With the first column of L determined,
        //  the first row of U can be determined:
        //
        //      U[1][j] = A[1][j]/L[1][1]; j = 2,3,...,(N+1)
        //
        //  for the augmented matrix. Next the second column of L can be deter-
        //  mined:
        //
        //      L[i][2] = (A[i][2]-L[2][1]*U[2][2]);         i = 2,3,...,N
        //
        //  the second row of U can be determined:
        //
        //      U[2][j] = (A[2][j]-L[2][1]*U[1][j])/L[2][2]; j = 3,4,...,(N+1)
        //
        //  This process can be followed to its logical conclusion. However, 
        //  the following recurrence relations can be used to solve for L and U,
        //  using an in-place algorithm because the zero and one terms of L and 
        //  U can be assumed, so the remaining terms of L and U can be stored 
        //  within the A[][] matrix.
        //
        //  After solving for the first row:
        //
        //  A[1][j] = A[1][j]/A[1][1]; j=2,3,...,(N+1)
        //
        //  Solve for the remaining m columns: m = 2,...,N
        //
        //  A[i][m] = A[i][m] - sum(A[i][k]*A[k][m]);
        //      i = m,...,N; and k = 1,2,...,(m-1)
        //
        //  and then for the m remaining rows in column-row order:
        //
        //  A[m][j] = (A[m][j] - sum(A[m][k]*A[k][j]))/A[m][m];
        //      j = (m+1)...(N+1) and k = 1,2,...,(m-1)
        //
        //  The coefficients are then available by back-substitution:
        //
        //  B[N] = A[N][N+1]
        //  
        //  and
        //  
        //  B[i] = A[i][N+1] - sum(A[i][k]*B[k]);
        //      i = (N-1),(N-2),...,1 and k = (i+1),...,N
        //
        //  A final note: the algorithm used/described is a 1-based matrix algo-
        //  rithm. Thus, the 0th row and column, although allocated, are not
        //  used, and the loops use a <= condition rather than a < condition.
        //
        // Improve numerical stability of solution by employing partial pivoting

        for(r = 1; r <= Nrow; r++) {
            pivot = A[r][r];                    // Select pivot on diagonal
            k = r;
            for(c = (r + 1); c <= Nrow; c++) {  // Find max value in column
                if(fabs(pivot) < fabs(A[r][c])) {
                    pivot = A[r][c];
                    k = c;
                }
            }

            if(k != r) {                        // if largest column value is
                for(c = 1; c <= Ncol; c++) {    // not largest diagonal value,
                    tmp    = A[r][c];           // do a row exchange to place it
                    A[r][c] = A[k][c];          // on the diagonal
                    A[k][c] = tmp;
                }
            }
        }

        // Compute first row of the upper triagular Cholesky solution matrix

        for(c = 2; c <= Ncol; c++) {
            A[1][c] = A[1][c] / A[1][1];
        }

        // Compute remaining rows/columns of the Cholesky solution matrix

        for(c = 2; c <= Nrow; c++) {
            // Compute column of the lower triangular Cholesky solution matrix
            for(r = c; r <= Nrow; r++) {
                sum = 0.0;
                for(k = 1; k <= (c - 1); k++) {
                    sum += A[r][k] * A[k][c];
                }
                A[r][c] = A[r][c] - sum;
            }
            // Compute row of the upper triagular Cholesky solution matrix
            for(j = (c + 1); j <= Ncol; j++) {
                sum = 0.0;
                for(k = 1; k <= (c - 1); k++) {
                    sum += A[c][k] * A[k][j];
                }
                A[c][j] = (A[c][j] - sum) / A[c][c];
            }
        }

        // Compute polynomial approximation's coefficients by back-substitution

        B[Nrow] = A[Nrow][Ncol];
        for(m = 1; m <= (Nrow - 1); m++) {
            i   = (Nrow - m);
            tmp = 0.0;
            for(j = (i + 1); j <= Nrow; j++) {
                tmp += A[i][j] * B[j];
            }
            B[i] = (A[i][Ncol] - tmp);
        }

		// Print polynomial approximation's coefficients: c[0],...,c[N]

		printf("\n");
		for(k = 1; k <= Nrow; k++) {
			printf("|%15.6le|\n", B[k]);
		}

		printf("\nEnter <CR> to continue: "); ch = getchar();
    }

    exit(0);
}

