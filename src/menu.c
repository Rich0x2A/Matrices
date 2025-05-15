#include "menu.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

static void handle_print(Matrix *matrices, int n) {
    if (n == 0) {
        printf("ERROR: NO MATRICES EXIST\n");
        return;
    }
    int ix;
    printf("MATRIX INDEX (0 to %d): ", n - 1);
    scanf("%d", &ix);
    if (ix < 0 || ix >= n) {
        printf("ERROR: INVALID MATRIX INDEX\n");
        return;
    }
    print_matrix(&matrices[ix]);
}

static void handle_add(Matrix **matrices, int *n) {
    if (*n == 0) {
        printf("ERROR: NO MATRICES EXIST\n");
        return;
    }
    int ix, jx;
    printf("MATRIX 1 INDEX (0 to %d): ", *n - 1);
    scanf("%d", &ix);
    printf("MATRIX 2 INDEX (0 to %d): ", *n - 1);
    scanf("%d", &jx);
    if (ix < 0 || jx < 0 || ix >= *n || jx >= *n) {
        printf("ERROR: INVALID MATRIX INDICES\n");
        return;
    }
    Matrix result = add_matrix(&(*matrices)[ix], &(*matrices)[jx]);
    print_matrix(&result);
    free_matrix(&result);
}

static void handle_subtract(Matrix **matrices, int *n) {
    if (*n == 0) {
        printf("ERROR: NO MATRICES EXIST\n");
        return;
    }
    int ix, jx;
    printf("MATRIX 1 INDEX (0 to %d): ", *n - 1);
    scanf("%d", &ix);
    printf("MATRIX 2 INDEX (0 to %d): ", *n - 1);
    scanf("%d", &jx);
    if (ix < 0 || jx < 0 || ix >= *n || jx >= *n) {
        printf("ERROR: INVALID MATRIX INDICES\n");
        return;
    }
    Matrix result = subtract_matrix(&(*matrices)[ix], &(*matrices)[jx]);
    print_matrix(&result);
    free_matrix(&result);
}

static void handle_multiply(Matrix **matrices, int *n) {
    if (*n == 0) {
        printf("ERROR: NO MATRICES EXIST\n");
        return;
    }
    int ix, jx;
    printf("MATRIX 1 INDEX (0 to %d): ", *n - 1);
    scanf("%d", &ix);
    printf("MATRIX 2 INDEX (0 to %d): ", *n - 1);
    scanf("%d", &jx);
    if (ix < 0 || jx < 0 || ix >= *n || jx >= *n) {
        printf("ERROR: INVALID MATRIX INDICES\n");
        return;
    }
    Matrix result = multiply_matrix(&(*matrices)[ix], &(*matrices)[jx]);
    print_matrix(&result);
    free_matrix(&result);
}

static void handle_scale(Matrix **matrices, int *n) {
    if (*n == 0) {
        printf("ERROR: NO MATRICES EXIST\n");
        return;
    }
    int ix;
    double k;
    printf("MATRIX INDEX (0 to %d): ", *n - 1);
    scanf("%d", &ix);
    printf("SCALAR: ");
    scanf("%lf", &k);
    if (ix < 0 || ix >= *n) {
        printf("ERROR: INVALID MATRIX INDEX\n");
        return;
    }
    Matrix result = scale_matrix(&(*matrices)[ix], k);
    print_matrix(&result);
    free_matrix(&result);
}

static void handle_ref(Matrix **matrices, int *n) {
    if (*n == 0) {
        printf("ERROR: NO MATRICES EXIST\n");
        return;
    }
    int ix;
    printf("MATRIX INDEX FOR REF (0 to %d): ", *n - 1);
    scanf("%d", &ix);
    if (ix < 0 || ix >= *n) {
        printf("ERROR: INVALID MATRIX INDEX\n");
        return;
    }
    row_echelon_form(&(*matrices)[ix]);
    print_matrix(&(*matrices)[ix]);
}

static void handle_transpose(Matrix **matrices, int *n) {
    if (*n == 0) {
        printf("ERROR: NO MATRICES EXIST\n");
        return;
    }
    int ix;
    printf("MATRIX INDEX FOR TRANSPOSE (0 to %d): ", *n - 1);
    scanf("%d", &ix);
    if (ix < 0 || ix >= *n) {
        printf("ERROR: INVALID MATRIX INDEX\n");
        return;
    }
    Matrix result = transpose_matrix(&(*matrices)[ix]);
    print_matrix(&result);
    free_matrix(&result);
}

static void handle_new(Matrix **matrices, int *n) {
    Matrix m = read_dims();
    m = alloc_matrix(m.nrows, m.ncols);
    read_matrix(&m);

    Matrix *resized = realloc(*matrices, (*n + 1) * sizeof(Matrix));
    if (!resized) {
        printf("ERROR: MEMORY ALLOCATION FAILED\n");
        return;
    }
    *matrices = resized;
    (*matrices)[*n] = m;
    (*n)++;
    printf("SUCCESS: MATRIX #%d CREATED\n", *n);
}

static void handle_zero(Matrix **matrices, int *n) {
    Matrix z = read_dims();
    z = alloc_matrix(z.nrows, z.ncols);
    for (int i = 0; i < z.nrows; ++i)
        for (int j = 0; j < z.ncols; ++j)
            z.data[i][j] = 0.0;

    Matrix *resized = realloc(*matrices, (*n + 1) * sizeof(Matrix));
    if (!resized) {
        printf("ERROR: MEMORY ALLOCATION FAILED\n");
        return;
    }
    *matrices = resized;
    (*matrices)[*n] = z;
    (*n)++;
    printf("SUCCESS: MATRIX #%d CREATED\n", *n);
    print_matrix(&z);
}

static void handle_identity(Matrix **matrices, int *n) {
    int size;
    printf("IDENTITY MATRIX SIZE: ");
    scanf("%d", &size);
    if (size <= 0) {
        printf("ERROR: INVALID MATRIX SIZE\n");
        return;
    }
    Matrix i = identity_matrix(size);
    Matrix *resized = realloc(*matrices, (*n + 1) * sizeof(Matrix));
    if (!resized) {
        printf("ERROR: MEMORY ALLOCATION FAILED\n");
        return;
    }
    *matrices = resized;
    (*matrices)[*n] = i;
    (*n)++;
    printf("SUCCESS: MATRIX #%d CREATED\n", *n);
    print_matrix(&i);
}

void menu(Matrix **matrices, int *n) {
    char c;
    do {
        printf("+-----------------------+\n");
        printf("|      MATRIX MENU      |\n");
        printf("+-----------------------+\n");
        printf("| (1) Print matrix      |\n");
        printf("| (2) Add two matrices  |\n");
        printf("| (3) Sub two matrices  |\n");
        printf("| (4) Mult two matrices |\n");
        printf("| (5) Scale matrix      |\n");
        printf("| (6) Row echelon form  |\n");
        printf("| (7) Transpose matrix  |\n");
        printf("| (n) New matrix        |\n");
        printf("| (z) Zero matrix       |\n");
        printf("| (i) Identity matrix   |\n");
        printf("| (q) Quit              |\n");
        printf("+-----------------------+\n");
        scanf(" %c", &c);

        switch (c) {
            case '1': handle_print(*matrices, *n); break;
            case '2': handle_add(matrices, n); break;
            case '3': handle_subtract(matrices, n); break;
            case '4': handle_multiply(matrices, n); break;
            case '5': handle_scale(matrices, n); break;
            case '6': handle_ref(matrices, n); break;
            case '7': handle_transpose(matrices, n); break;
            case 'n': handle_new(matrices, n); break;
            case 'z': handle_zero(matrices, n); break;
            case 'i': handle_identity(matrices, n); break;
            case 'q': printf("QUITTING PROGRAM, TAKE CARE\n"); break;
            default: printf("ERROR: INVALID CHOICE\n");
        }
    } while (c != 'q');
}
