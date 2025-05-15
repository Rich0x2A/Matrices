#include "menu.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void handle_menu(Matrix **matrices, int *n)
{
        char c;
        do 
        {
                printf("+-----------------------+\n");
                printf("|      MATRIX MENU      |\n");
                printf("+-----------------------+\n");
                printf("| (1) Print matrix      |\n");
                printf("| (2) Add two matrices  |\n");
                printf("| (3) Sub two matrices  |\n");
                printf("| (4) Mult two matrices |\n");
                printf("| (5) Scale matrix      |\n");
                printf("| (6) Row echelon form  |\n");
                printf("| (n) New matrix        |\n");
                printf("| (q) Quit              |\n");
                printf("+-----------------------+\n");
                scanf(" %c", &c);
                switch (c) {
                case '1':
                {
                        if (*n == 0) {
                                printf("ERROR: NO MATRICES EXIST\n");
                                break;
                        }
                        int ix;
                        printf("MATRIX INDEX (0 to %d): ", *n - 1);
                        scanf("%d", &ix);
                        if (ix < 0 || ix >= *n)
                        {
                                printf("ERROR: INVALID MATRIX INDEX\n");
                                break;
                        }
                        print_matrix(&(*matrices)[ix]);
                        break;
                }
                case '2':
                {
                        if (*n == 0) {
                                printf("ERROR: NO MATRICES EXIST\n");
                                break;
                        }
                        int ix, jx;
                        printf("MATRIX 1 INDEX (0 to %d): ", *n - 1);
                        scanf("%d", &ix);
                        printf("MATRIX 2 INDEX (0 to %d): ", *n - 1);
                        scanf("%d", &jx);
                        if (ix < 0 || ix >= *n || jx < 0 || jx >= *n) {
                                printf("ERROR: INVALID MATRIX INDICES\n");
                                break;
                        }
                        Matrix result = add_matrix(&(*matrices)[ix], &(*matrices)[jx]);
                        print_matrix(&result);
                        free_matrix(&result);
                        break;
                }
                case '3':
                {
                        if (*n == 0) {
                                printf("ERROR: NO MATRICES EXIST\n");
                                break;
                        }
                        int ix, jx;
                        printf("MATRIX 1 INDEX (0 to %d): ", *n - 1);
                        scanf("%d", &ix);
                        printf("MATRIX 2 INDEX (0 to %d): ", *n - 1);
                        scanf("%d", &jx);
                        if (ix < 0 || ix >= *n || jx < 0 || jx >= *n) {
                                printf("ERROR: INVALID MATRIX INDICES\n");
                                break;
                        }
                        Matrix result = subtract_matrix(&(*matrices)[ix], &(*matrices)[jx]);
                        print_matrix(&result);
                        free_matrix(&result);
                        break;
                }
                case '4':
                        if (*n == 0) {
                                printf("ERROR: NO MATRICES EXIST\n");
                                break;
                        }
			int ix, jx;
			printf("MATRIX 1 INDEX (0 to %d): ", *n - 1);
			scanf("%d", &ix);
			printf("MATRIX 2 INDEX (0 to %d): ", *n - 1);
			scanf("%d", &jx);
			if (ix < 0 || jx < 0 || ix >= *n || jx >= *n) {
				printf("ERROR: INVALID MATRIX INDICES\n");
				break;
			}             
			Matrix result = multiply_matrix(&(*matrices)[ix], &(*matrices)[jx]);
			print_matrix(&result);
			free_matrix(&result);           
                        break;
                case '5':
                {
                        if (*n == 0) {
                                printf("ERROR: NO MATRICES EXIST\n");
                                break;
                        }
                        int ix;
                        double k;
                        printf("MATRIX INDEX (0 to %d): ", *n - 1);
                        scanf("%d", &ix);
                        printf("SCALAR: ");
                        scanf("%lf", &k);
                        if (ix < 0 || ix >= *n) {
                                printf("ERROR: INVALID MATRIX INDEX\n");
                                break;
                        }
                        Matrix result = scale_matrix(&(*matrices)[ix], k);
                        print_matrix(&result);
                        free_matrix(&result);
                        break;
                }
                case '6':
                {
                        if (*n == 0) {
                                printf("ERROR: NO MATRICES EXIST\n");
                                break;
                        }
                        int ix;
                        printf("MATRIX INDEX FOR REF (0 to %d): ", *n - 1);
                        scanf("%d", &ix);
                        if (ix < 0 || ix >= *n) {
                                printf("ERROR: INVALID MATRIX INDEX\n");
                                break;
                        }
                        row_echelon_form(&(*matrices)[ix]);
                        print_matrix(&(*matrices)[ix]);
                        break;
                }
                case 'n':
                {
                        Matrix m = read_dims();
                        m = alloc_matrix(m.nrows, m.ncols);
                        read_matrix(&m);

                        Matrix *resized = realloc(*matrices, (*n + 1) * sizeof(Matrix));
                        if (!resized) {
                                printf("ERROR: MEMORY ALLOCATION FAILED\n");
                                break;
                        }
                        *matrices = resized;
                        (*matrices)[*n] = m;
                        (*n)++;
                        printf("Matrix #%d created.\n", *n);
                        break;
                }
                case 'q':
                        printf("QUITTING PROGRAM, TAKE CARE\n");
                        break;
                default:
                        printf("ERROR: INVALID CHOICE\n");
                }
        } while (c != 'q');
}
