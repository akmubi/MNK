#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <assert.h>
#include <stdlib.h>
#include <math.h>

// Перестановка
#define MAT_SWAP(A, B) { (A) ^= (B); (B) ^= (A); (A) ^= (B); }

typedef struct
{
	double	*array;
	size_t	rows;
	size_t	columns;
} Matrix;

void mat_init			(Matrix *mat, size_t rows, size_t columns);
void mat_init_array		(Matrix *mat, const double *array, size_t rows, size_t columns);
void mat_transpose		(Matrix *mat);
void mat_print			(Matrix *mat);
void mat_mul			(Matrix *first, Matrix *second, Matrix *result);
void mat_mul_vec		(Matrix *mat, Vector *vec, Vector *result);
void mat_mul_s			(Matrix *mat, double scalar);
void mat_inverse		(Matrix *mat);
double mat_minor		(Matrix *mat, size_t row_index, size_t column_index);
double mat_determinant	(Matrix *mat);
void mat_destroy		(Matrix *mat);
static void static_minor(Matrix *mat, size_t row_index, size_t column_index, Matrix *result);

// Создание матрицы, заполненного нулями
void mat_init(Matrix *mat, size_t rows, size_t columns)
{
	assert(mat != NULL);
	mat->rows = rows;
	mat->columns = columns;
	mat->array = (double *)malloc(rows * columns * sizeof(*mat->array));
	//
	//
	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < columns; j++)
			mat->array[i * columns + j] = 0.0;
}

// Создание матрицы, заполненного значениями из массива
void mat_init_array(Matrix *mat, const double *array, size_t rows, size_t columns)
{
	assert(mat != NULL && array != NULL);
	mat->rows = rows;
	mat->columns = columns;
	mat->array = (double *)malloc(rows * columns * sizeof(*mat->array));
	//
	//
	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < columns; j++)
			mat->array[i * columns + j] = array[i * columns + j];
}

// Транспонирование матрицы
void mat_transpose(Matrix *mat)
{
	assert(mat != NULL);
	//
	//
	double *temp_array = (double *)malloc(mat->rows * mat->columns * sizeof(*temp_array));
	for (size_t i = 0; i < mat->rows; i++)
		for (size_t j = 0; j < mat->columns; j++)
			temp_array[j * mat->rows + i] = mat->array[i * mat->columns + j];

	for (size_t i = 0; i < mat->rows; i++)
		for (size_t j = 0; j < mat->columns; j++)
			mat->array[i * mat->columns + j] = temp_array[i * mat->columns + j];
	
	MAT_SWAP(mat->columns, mat->rows);
	//
	//
	free(temp_array);
}

// Вывод матрицы
void mat_print(Matrix *mat)
{
	assert(mat != NULL);
	//
	//
	for (size_t i = 0; i < mat->rows; i++)
	{
		for (size_t j = 0; j < mat->columns; j++)
			printf("%3.10f\t", mat->array[i * mat->columns + j]);
		printf("\n");
	}
	printf("\n");
}

// Умножение матриц
void mat_mul(Matrix *first, Matrix *second, Matrix *result)
{
	assert(first != NULL && second != NULL);
	assert(result->rows == first->rows && result->columns == second->columns);
	//
	//
	for (size_t i = 0; i < first->rows; i++)
		for (size_t j = 0; j < second->columns; j++)
		{
			double accum = 0.0;
			for (size_t k = 0; k < second->rows; k++)
				accum += first->array[i * first->columns + k] * second->array[k * second->columns + j];
			result->array[i * result->columns + j] = accum;
		}
}

// Умножение матрицы на вектор
void mat_mul_vec(Matrix *mat, Vector *vec, Vector *result)
{
	assert(vec != NULL && mat != NULL && result != NULL);
	// Количество столбцов/строк матрицы и размерность вектора должны быть одинаковыми
	assert(mat->columns == vec->size || mat->rows == vec->size);
	//
	//
	if (mat->columns == vec->size)
		for (size_t i = 0; i < mat->rows; i++)
		{
			double accum = 0.0;
			for (size_t j = 0; j < mat->columns; j++)
				accum += mat->array[i * mat->columns + j] * vec->array[j];
			result->array[i] = accum;
		}
	else
		for (size_t i = 0; i < mat->rows; i++)
			for (size_t j = 0; j < mat->columns; j++)
				result->array[i] += mat->array[j * mat->rows + i] * vec->array[j];
}

// Умножение матрицы на скаляр
void mat_mul_s(Matrix *mat, double scalar)
{
	assert(mat != NULL);
	//
	//
	for (size_t i = 0; i < mat->rows; i++)
		for (size_t j = 0; j < mat->columns; j++)
				mat->array[i * mat->columns + j] *= scalar;
}

// A^-1 = 1 / det * ~A, где ~A - союзна матрица
// ~A = B^T, где B - матрица, состоящая из алгебраических дополнений матрицы A
// Нахождение обратной матрицы
void mat_inverse(Matrix *mat)
{
	assert(mat != NULL);
	// Матрица должна быть квадратной
	assert(mat->rows == mat->columns);
	//
	//
	size_t size = mat->rows;

	double determinant = mat_determinant(mat);

	// Определитель не должен быть 0
	assert(determinant != 0);

	// Транспонирование
	mat_transpose(mat);

	// Создание союзной матрицы
	// Заполнение алгебраическими дополнениями
	Matrix additions;
	mat_init(&additions, size, size);
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			additions.array[i * size + j] = mat_minor(mat, i, j);
	//
	//
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			mat->array[i * size + j] = additions.array[i * size + j];
	mat_destroy(&additions);
	//
	//

	// Деление на определитель союзной матрицы
	mat_mul_s(mat, 1 / determinant);
}

// Нахождение определителя
double mat_determinant(Matrix *mat)
{
	assert(mat != NULL);
	assert(mat->columns == mat->rows);

	size_t size = mat->columns;
	//
	//
	if (size == 1) return mat->array[0];
	if (size == 2) return mat->array[0] * mat->array[size + 1] - mat->array[1] * mat->array[size];

	double sum = 0.0;
	for (size_t i = 0; i < size; i++)
	{
		//
		//
		Matrix temp_mat;
		mat_init(&temp_mat, size - 1, size - 1);
		//
		//

		// По первой строке
		static_minor(mat, 0, i, &temp_mat);

		sum += mat->array[i] * ((i & 1) ? -1 : 1) * mat_determinant(&temp_mat);
		//
		//
		mat_destroy(&temp_mat);
		//
		//
	}
	return sum;
}

void static_minor(Matrix *mat, size_t row_index, size_t column_index, Matrix *result)
{
	assert(mat != NULL && result != NULL);
	assert(mat->columns == mat->rows);
	size_t size = mat->columns;
	//
	//
	size_t iter = 0;
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
		{
			if (i == row_index || j == column_index)
				continue;
			result->array[iter++] = mat->array[i * size + j];
		}
}

// Алгебраическое дополнение
double mat_minor(Matrix *mat, size_t row_index, size_t column_index)
{
	assert(mat != NULL);
	assert(mat->rows == mat->columns);
	size_t size = mat->columns;

	Matrix temp_mat;
	mat_init(&temp_mat, size - 1, size - 1);
	//
	//
	static_minor(mat, row_index, column_index, &temp_mat);
	double determinant = mat_determinant(&temp_mat);
	determinant *= ((row_index + column_index) & 1) ? -1 : 1;
	//
	//
	mat_destroy(&temp_mat);
	return determinant;
}

// Освобождение ресурсов
void mat_destroy(Matrix *mat)
{
	assert(mat != NULL);
	if (mat->array != NULL) free(mat->array);
	mat->array = NULL;
	mat->rows = 0;
	mat->columns = 0;
}
#endif // _MATRIX_H_