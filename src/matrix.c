#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Matrix read_dims()
{
	Matrix m;
	printf("\nNUMBER OF ROWS: ");
	scanf("%d", &m.nrows);
	printf("NUMBER OF COLUMNS: ");
	scanf("%d", &m.ncols);
	m.data = NULL;
	return m;
}

Matrix alloc_matrix(int nrows, int ncols)
{
	Matrix m;
	m.nrows = nrows;
	m.ncols = ncols;
	m.data = malloc(nrows * sizeof(double *));
	for (int i = 0; i < nrows; ++i)
		m.data[i] = malloc(ncols * sizeof(double));
	return m;
}

void read_matrix(Matrix *m)
{
	for (int i = 0; i < m->nrows; ++i)
		for (int j = 0; j < m->ncols; ++j)
			scanf("%lf", &m->data[i][j]);
}

void print_matrix(Matrix *m)
{
	int border = 2 + m->ncols * 9;
	printf("\nMATRIX (%d x %d):\n", m->nrows, m->ncols);
	for (int i = 0; i < border; ++i)
		printf("+");
	printf("\n");
	for (int i = 0; i < m->nrows; ++i)
	{
		printf("| ");
		for (int j = 0; j < m->ncols; ++j)
			printf("%8.2lf ", m->data[i][j]);
		printf("|\n");
	}
	for (int i = 0; i < border; ++i)
		printf("+");
	printf("\n\n");
}

Matrix identity_matrix(int n)
{
	Matrix id;
	id = alloc_matrix(n, n);	
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i == j) 
				id.data[i][j] = 1;
			else 
				id.data[i][j] = 0;
		}
	}
	return id;
}

Matrix zero_matrix(int r, int c)
{
	Matrix z;
	z = alloc_matrix(r, c);
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
			z.data[i][j] = 0;
	return z;
			
}

Matrix add_matrix(Matrix *m, Matrix *n)
{
	if (m->nrows != n->nrows || m->ncols != n->ncols)
	{
		fprintf(stderr, "ERROR: MATRIX DIMS MUST MATCH\n");
		exit(EXIT_FAILURE);
	}
	Matrix result = alloc_matrix(m->nrows, m->ncols);
	for (int i = 0; i < m->nrows; ++i)
		for (int j = 0; j < m->ncols; ++j)
			result.data[i][j] = m->data[i][j] + n->data[i][j];
	return result;
}

Matrix subtract_matrix(Matrix *m, Matrix *n)
{
	if (m->ncols != n->ncols || m->nrows != n->nrows)
	{
		fprintf(stderr, "ERROR: MATRIX DIMS MUST MATCH\n");
		exit(EXIT_FAILURE);
	}
	Matrix result = alloc_matrix(m->nrows, m->ncols);
	for (int i = 0; i < m->nrows; ++i)
		for (int j = 0; j < m->ncols; ++j)
			result.data[i][j] = m->data[i][j] - n->data[i][j];
	return result;
}

Matrix multiply_matrix(Matrix *m, Matrix *n)
{
    if (m->ncols != n->nrows)
    {
        fprintf(stderr, "ERROR: NUMBER OF COLUMNS OF MATRIX 1 "
			"MUST BE EQUAL TO NUMBER OF ROWS OF MATRIX 2\n");
        exit(EXIT_FAILURE);
    }

    Matrix r = alloc_matrix(m->nrows, n->ncols);
    for (int i = 0; i < m->nrows; ++i)
    {
        for (int j = 0; j < n->ncols; ++j)
        {
            r.data[i][j] = 0;
            for (int k = 0; k < m->ncols; ++k)
            {
                r.data[i][j] += m->data[i][k] * n->data[k][j];
            }
        }
    }

    return r;
}

Matrix transpose_matrix(Matrix* m)
{
	Matrix r = alloc_matrix(m->ncols, m->nrows);
	for (int i = 0; i < r.nrows; ++i)
		for (int j = 0; j < r.ncols; ++j)
			r.data[i][j] = m->data[j][i];
	return r;
}

Matrix scale_matrix(Matrix *m, double k)
{
	Matrix result = alloc_matrix(m->nrows, m->ncols);
	for (int i = 0; i < m->nrows; ++i)
		for (int j = 0; j < m->ncols; ++j)
			result.data[i][j] = m->data[i][j] * k;
	return result;
}

void scale_row(Matrix *m, int i, double k)
{
	if (k == 1.0)
		return;
	if (i >= m->nrows || i < 0)
	{
		fprintf(stderr, "ERROR: ROW INDEX OUT OF BOUNDS\n");
		exit(EXIT_FAILURE);
	}
	for (int j = 0; j < m->ncols; ++j)
		m->data[i][j] *= k;
}

void add_scaled_row(Matrix *m, int i, int src, double k)
{
	if (k == 0.0)
		return;
	if (i < 0 || i >= m->nrows || src < 0 || src >= m->nrows)
	{
		fprintf(stderr, "ERROR: ROW INDEX OUT OF BOUNDS");
		exit(EXIT_FAILURE);
	}
	for (int j = 0; j < m->ncols; ++j)
		m->data[i][j] += k * m->data[src][j];
}

void swap_rows(Matrix *m, int i, int j)
{
	double *tmp_row = m->data[i];
	m->data[i] = m->data[j];
	m->data[j] = tmp_row;
}

int find_pivot_row(Matrix *m, int col, int start_row)
{
	for (int i = start_row; i < m->nrows; ++i)
		if (fabs(m->data[i][col]) > 1e-9)
			return i;
	return -1;
}

void row_echelon_form(Matrix *m)
{
	int row = 0;
	for (int col = 0; col < m->ncols && row < m->nrows; ++col)
	{
		int pivot = find_pivot_row(m, col, row);
		if (pivot == -1)
			continue;
		if (pivot != row)
			swap_rows(m, row, pivot);
		scale_row(m, row, 1.0 / m->data[row][col]);
		for (int i = row + 1; i < m->nrows; ++i)
		{
			double factor = -m->data[i][col];
			add_scaled_row(m, i, row, factor);
		}
		++row;
	}
}

void free_matrix(Matrix *m)
{
	for (int i = 0; i < m->nrows; ++i)
		free(m->data[i]);
	free(m->data);
}
