#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Перестановка
#define MAT_SWAP(A, B) { (A) ^= (B); (B) ^= (A); (A) ^= (B); }

typedef struct
{
	union
	{
		double *array;

		// Для операции с xor
		long long int *array_int;
	};
	
	size_t rows;
	size_t columns;
} Matrix;

void mat_init			(Matrix *mat, size_t rows, size_t columns);
void mat_init_array		(Matrix *mat, double *array, size_t rows, size_t columns);
void mat_transpose		(Matrix *mat);
void mat_print			(Matrix *mat);
void mat_mul			(Matrix *first, Matrix *second);
void mat_mul_vec		(Matrix *matrix, double *vector);
void mat_mul_s			(Matrix *mat, double scalar);
void mat_inverse		(Matrix *mat);
double mat_minor		(double *array, size_t row_index, size_t column_index, size_t size);
double mat_determinant	(double *array, size_t size);
void mat_destroy		(Matrix *mat);

static void static_minor(double *array, size_t row_index, size_t column_index, size_t size, double *result);

// Инициализация матрицы
void mat_init(Matrix *mat, size_t rows, size_t columns)
{
	mat->rows = rows;
	mat->columns = columns;
	mat->array = (double *)malloc(rows * columns * sizeof(*mat->array));
	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < columns; j++)
			mat->array[i * columns + j] = 0.0;
}

// Инициализация матрицы массивом
void mat_init_array(Matrix *mat, double *array, size_t rows, size_t columns)
{
	mat->rows = rows;
	mat->columns = columns;
	mat->array = array;
}

// Транспонирование матрицы
void mat_transpose(Matrix *mat)
{
	double *temp_array = (double *)malloc(mat->rows * mat->columns * sizeof(*temp_array));
	for (size_t i = 0; i < mat->rows; i++)
		for (size_t j = 0; j < mat->columns; j++)
			temp_array[j * mat->rows + i] = mat->array[i * mat->columns + j];

	for (size_t i = 0; i < mat->rows; i++)
		for (size_t j = 0; j < mat->columns; j++)
			mat->array[i * mat->columns + j] = temp_array[i * mat->columns + j];
	
	mat->columns ^= mat->rows;
	mat->rows ^= mat->columns;
	mat->columns ^= mat->rows;
#if !defined(__linux__)
	free(temp_array);
#endif
}

// Вывод матрицы
void mat_print(Matrix *mat)
{
	for (size_t i = 0; i < mat->rows; i++)
	{
		for (size_t j = 0; j < mat->columns; j++)
			printf("%3.1f\t", mat->array[i * mat->columns + j]);
		printf("\n");
	}
}

void mat_mul(Matrix *first, Matrix *second)
{
	for (size_t i = 0; i < first->rows; i++)
		for (size_t j = 0; j < first->columns; j++)
		{
			double accum;
			for (size_t k = 0; k < second->rows; k++)
				accum += first->array[i * first->columns + k] * second->array[k * second->columns + i];
			first->array[i * first->columns + j] = accum;
		}
}

void mat_mul_vec(Matrix *matrix, double *vector)
{
	double *temp_vector = (double *)malloc(matrix->rows * sizeof(*temp_vector));
	for (size_t i = 0; i < matrix->rows; i++)
		for (size_t j = 0; j < matrix->columns; j++)
			temp_vector[i] += matrix->array[i * matrix->columns + j] * vector[j];
#if !defined(__linux__)
	free(temp_vector);
#endif
}

// Умножение матрицы на скаляр
void mat_mul_s(Matrix *mat, double scalar)
{
	for (size_t i = 0; i < mat->rows; i++)
		for (size_t j = 0; j < mat->columns; j++)
				mat->array[i * mat->columns + j] *= scalar;
}

// A^-1 = 1 / det * ~A, где ~A - союзна матрица
// ~A = B^T, где B - матрица, состоящая из алгебраических дополнений матрицы A
// Нахождение обратной матрицы
void mat_inverse(Matrix *mat)
{
	// Матрица должна быть квадратной
	assert(mat->rows == mat->columns);

	size_t size = mat->rows;

	double determinant = mat_determinant(mat->array, size);

	// Определитель не должен быть 0
	assert(determinant != 0);

	// Создание союзной матрицы
	// Заполнение алгебраическими дополнениями
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			mat->array[i * size + j] = mat_minor(mat->array, i, j, size);
	
	// Транспонирование
	mat_transpose(mat);
	
	// Деление на определитель союзной матрицы
	mat_mul_s(mat, 1 / determinant);
}

// Нахождение определителя
double mat_determinant(double *array, size_t size)
{
	if (size == 1) return array[0];
	if (size == 2) return array[0] * array[size + 1] - array[1] * array[size];

	static double sum = 0.0;
	for (size_t i = 0; i < size; i++)
	{
		double *temp_array = (double *)malloc((size - 1) * (size - 1) * sizeof(*temp_array));
		static_minor(array, size + 1, i, size, temp_array);

		sum += array[i] * ((i % 2) ? 1 : -1) * mat_determinant(temp_array, size - 1);
#if !defined(__linux__)
		free(temp_array);
#endif
	}
	return sum;
}

void static_minor(double *array, size_t row_index, size_t column_index, size_t size, double *result)
{
	size_t iter = 0;
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
		{
			if (i == row_index || j == column_index)
				continue;
			result[iter++] = array[i * size + j];
		}
}

// Алгебраическое дополнение
double mat_minor(double *array, size_t row_index, size_t column_index, size_t size)
{
	double *temp_array = (double *)malloc((size - 1) * (size - 1) * sizeof(*temp_array));
	static_minor(array, row_index, column_index, size, temp_array);
	double determinant = mat_determinant(temp_array, size - 1);
#if !defined (__linux__)
	free(temp_array);
#endif
	return determinant;
}

// Освобождение ресурсов
void mat_destroy(Matrix *mat)
{
	mat->rows = 0;
	mat->columns = 0;
#if !defined (__linux__)
	if (mat->array != NULL) free(mat->array);
#endif
	mat->array = NULL;
}
#endif // _MATRIX_H_