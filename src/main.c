#include "matrix.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	Matrix *matrices = NULL;
	int size = 0;

	handle_menu(&matrices, &size);

	for (int i = 0; i < size; ++i)
		free_matrix(&matrices[i]);
	free(matrices);

	return 0;
}
