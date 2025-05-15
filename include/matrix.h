#ifndef MATRIX_H
#define MATRIX_H

typedef struct
{
	double **data;
	int nrows;
	int ncols;
} Matrix;

Matrix read_dims();
Matrix alloc_matrix(int r, int c);
void read_matrix(Matrix *m);
void print_matrix(Matrix *m);
Matrix identity_matrix(int n);
Matrix zero_matrix(int r, int c);
Matrix add_matrix(Matrix *m, Matrix *n);
Matrix subtract_matrix(Matrix *m, Matrix *n);
Matrix scale_matrix(Matrix *m, double k);
Matrix multiply_matrix(Matrix *m, Matrix *n);
Matrix transpose_matrix(Matrix *m);
void scale_row(Matrix *m, int i, double k);
void add_scaled_row(Matrix *m, int i, int j, double k);
void swap_rows(Matrix *m, int i, int j);
int find_pivot_row(Matrix *m, int i, int j);
void row_echelon_form(Matrix *m);
void free_matrix(Matrix *m);

#endif
