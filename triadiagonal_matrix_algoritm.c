/* A solution of numerical numbers task from Georgy Semenyak, a 211 group student
 * of Faculty of Computational Mathematics and Cybernetics of Lomonosov Moscow State University */

/*Solve a system of linear algebraic equations
 * -gamma * y_(i - 1) + 2 * y_i + gamma * y_(i + 1) = f_i , i = 1, ... , N − 1;
 * y_0 = f_0;
 * y_n = f_n;
 * Where gamma is a constant from 0.2 to 1.
 * The right part of the system ( f_i ,i = 0, ... , N ) is given.
 *
 * In my version of this task, f(x) equals:
 * |0, i = 0, ... , 39;
 * |0.1, i = 40, ... ,60;
 * |0, i = 61, ... , N; */


#include <stdio.h>
#include <stdlib.h>

#define N 100 //the constant given by the task condition. Recommended set of values for analysis: 100; 1000
#define gamma 0.2 //the constant given by the task condition. Recommended set of values for analysis: 0.2; 0.5; 1

void f_column(long double *f) { //fill in the column of the right part of the system of equations with values
    for (int i = 0; i < 40; i++) {
        f[i] = 0;
    }

    for (int i = 40; i < 61; i++) {
        f[i] = 0.1;
    }
    for (int i = 61; i < N + 1; i++) {
        f[i] = 0;
    }
}

void diagonals(long double *a, long double *b, long double *c) { //fill in the values of three diagonals
    a[0] = 0;
    b[0] = 0;
    c[0] = 0;
    for (int i = 1; i < N; i++) {
        a[i] = 0 - gamma;
        c[i] = 2;
        b[i] = gamma;
    }
}

void all_free(long double *a, long double *b, long double *c, long double *y, long double *alpha, long double *betta, long double *f) { //free all
    // dynamically allocated memory
    free(f);
    free(a);
    free(b);
    free(c);
    free(y);
    free(alpha);
    free(betta);
}

void alpha_and_betta_coefficients(long double *alpha, long double *betta, long double *a, long double *b, long double *c, long double *f) { //finding all
    // alpha and betta coefficients in our interrelation
    for (int i = 1; i < N; i++) {
        alpha[i + 1] = 0 - b[i] / (a[i] * alpha[i] + c[i]);
        betta[i + 1] = (f[i] - betta[i] * a[i]) / (a[i] * alpha[i] + c[i]);
    }
}

void system_solution(long double *alpha, long double *betta, long double *y) { //finding the solution of our system
    for (int i = N - 1; i > 0; i--) {
        y[i] = alpha[i + 1] * y [i + 1] + betta[i + 1];
    }
}

void result_print(long double *y, long double *f) { //printing a result
    printf("Solution of a system of linear algebraic equations: \n");
    printf("-%.1f * y_(i - 1) + 2 * y_i + %.1f * y_(i + 1) = f_i , i = 1, ... , N − 1; \n", gamma, gamma);
    printf("y_0 = f_0; \n");
    printf("y_n = f_n; \n");
    printf("Where the vector f is such: \n");
    for (int i = 0; i < N + 1; i++) {
        printf("%.1Lf ", f[i]);
    }
    printf("\nAnd N equals %d \n", N);
    printf("Is the vector: \n");
    for (int i = 0; i < N + 1; i++) {
        printf("%Le ", y[i]);
    }
    printf("\nThe program was finished successfully\n");
}
int main() {
    long double *f = (long double *) malloc ((N + 2) * sizeof(long double)); //right part of the system
    f_column(f);
    long double *a = (long double *) malloc ((N) * sizeof(long double)); //lower diagonal
    long double *b = (long double *) malloc ((N) * sizeof(long double)); //upper diagonal
    long double *c = (long double *) malloc ((N) * sizeof(long double)); //middle diagonal
    diagonals(a, b, c);
    long double *y = (long double *) malloc ((N + 2) * sizeof(long double)); //the vector of solutions of our system of linear algebraic equations
    //suppose that the unknowns are connected by a repetitive interrelation: y_(i - 1) = alpha_(i - 1) * y_i + betta_(i - 1)
    long double *alpha = (long double *) malloc ((N + 2) * sizeof(long double));
    long double *betta = (long double *) malloc ((N + 2) * sizeof(long double));
    alpha[0] = 0;
    betta[0] = 0;
    alpha[1] = 0;
    betta[1] = f[0];
    alpha_and_betta_coefficients(alpha, betta, a, b, c, f);
    y[0] = f[0]; //equation from the task condition
    y[N] = f[N]; //equation from the task condition
    system_solution(alpha, betta, y);
    result_print(y, f);
    all_free(a, b, c, y, alpha, betta, f);
    return 0;
}
