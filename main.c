#include <stdio.h>
#include "vector.h"
#include "matrix.h"

#define Y_N 57

#define X_N Y_N
#define X_M 6

#define A_N X_M

// Матрица целевойго признака y (57x1)
const double Y[Y_N] =
{
	3.8,
	0.8,
	5.4,
	1.4,
	4.6,
	3.8,
	1.6,
	3.1,
	5.7,
	3.5,
	6.5,
	4.9,
	0.9,
	2.7,
	1.1,
	0.6,
	1.7,
	1.4,
	1.1,
	0.9,
	0.7,
	0.5,
	1.6,
	1.8,
	0.3,
	0.6,
	1.0,
	4.7,
	1.9,
	4.8,
	7.6,
	1.2,
	3.5,
	1.0,
	2.4,
	1.6,
	2.0,
	1.9,
	1.8,
	1.4,
	6.0,
	3.0,
	3.4,
	2.7,
	1.7,
	1.3,
	1.4,
	1.5,
	2.4,
	1.1,
	0.6,
	1.3,
	1.6,
	0.4,
	1.4,
	2.4,
	0.04
};

// Матрица независимых признаков X (57x6) с фиктивным столбцом
const double X[X_N][X_M] =
{
	{ 14.2,	1.9,	114.2,	125.7,	119.3,	1.0 },
	{ 8.6,	4.6,	111.7,	126.8,	115.5,	1.0 },
	{ 15.9,	3.3,	111.5,	127.8,	128.7,	1.0 },
	{ 9.9,	0.9,	107.8,	129.7,	120.3,	1.0 },
	{ 7.3,	1.6,	111,	125.4,	119.3,	1.0 },
	{ 9,	1.3,	110.7,	120.6,	121.7,	1.0 },
	{ 8.2,	0.9,	116,	126.6,	126,	1.0 },
	{ 10.6,	2.9,	112.3,	129.9,	112.6,	1.0 },
	{ 7.1,	1.3,	121.6,	124.8,	123.6,	1.0 },
	{ 6.5,	1.8,	100.2,	127.3,	117.3,	1.0 },
	{ 9.3,	0.5,	116.8,	128,	122,	1.0 },
	{ 9.4,	3.6,	112.1,	123.3,	120.6,	1.0 },
	{ 2.6,	0.2,	125.8,	121.3,	118.2,	1.0 },
	{ 7.1,	0.4,	123.9,	128.5,	127.8,	1.0 },
	{ 9.3,	3.3,	114.1,	117.9,	121.2,	1.0 },
	{ 6.6,	0.7,	120.1,	125.6,	124,	1.0 },
	{ 5.9,	2.3,	107.3,	120.3,	108.3,	1.0 },
	{ 5.1,	0.3,	100.8,	127.3,	120.7,	1.0 },
	{ 3.8,	0.7,	109.3,	124.7,	115.4,	1.0 },
	{ 2.4,	0.7,	108,	120.7,	111.1,	1.0 },
	{ 1.7,	0.5,	102.4,	127.9,	134.2,	1.0 },
	{ 2.4,	0.3,	96.7,	125.9,	121.3,	1.0 },
	{ 4.1,	0.8,	104.3,	128.9,	114,	1.0 },
	{ 3.5,	0.7,	104.4,	125.9,	114.5,	1.0 },
	{ 2.2,	0.4,	110.7,	122.2,	121.7,	1.0 },
	{ 0.6,	0.8,	102.8,	128.7,	106.4,	1.0 },
	{ 2.4,	0.2,	116.9,	126.5,	117,	1.0 },
	{ 10.1,	2.2,	118.4,	122.6,	125.5,	1.0 },
	{ 2.7,	1.3,	114.8,	121,	115.8,	1.0 },
	{ 5.1,	3.3,	111.2,	115,	118.2,	1.0 },
	{ 0.9,	3.3,	116.8,	107.3,	126.9,	1.0 },
	{ 1.3,	0.3,	116.6,	123.1,	116.5,	1.0 },
	{ 4.7,	1,		123.2,	122.6,	124.2,	1.0 },
	{ 2.9,	0.2,	104.2,	121.7,	121.8,	1.0 },
	{ 3.2,	0.7,	106.7,	120.4,	122,	1.0 },
	{ 3.3,	3,		121.8,	116.6,	110.7,	1.0 },
	{ 7,	1.9,	108.2,	125.3,	120.2,	1.0 },
	{ 10.2,	2.6,	96.8,	119,	116.7,	1.0 },
	{ 7.1,	6,		107.5,	131.5,	131.1,	1.0 },
	{ 8.5,	2.1,	94.7,	126.4,	117.5,	1.0 },
	{ 3.5,	2.7,	105.8,	122.7,	126.4,	1.0 },
	{ 14.3,	3.7,	112,	128.3,	113.6,	1.0 },
	{ 11.2,	2.1,	110.4,	126.8,	121.7,	1.0 },
	{ 7.3,	1.3,	113,	125.7,	116.7,	1.0 },
	{ 5.7,	1.3,	106.4,	119.4,	118.2,	1.0 },
	{ 8.2,	1.9,	115.2,	128,	119.1,	1.0 },
	{ 2.9,	0.7,	108.5,	131.4,	116.9,	1.0 },
	{ 4.8,	1.6,	121.3,	131.1,	125.2,	1.0 },
	{ 4.5,	2.4,	115.8,	123.9,	119.9,	1.0 },
	{ 10.8,	0.6,	118.2,	132.1,	127.6,	1.0 },
	{ 4.6,	1.6,	110,	127.8,	114.2,	1.0 },
	{ 7,	3.1,	116.3,	125.6,	134.2,	1.0 },
	{ 7.3,	1.2,	103.7,	132.9,	110.9,	1.0 },
	{ 4.4,	1.6,	114.9,	128.7,	126.6,	1.0 },
	{ 3.6,	1.7,	105.8,	121.4,	111.9,	1.0 },
	{ 5.7,	1.8,	108.2,	127.5,	120.1,	1.0 },
	{ 5.5,	0.5,	109.9,	116.9,	112.8,	1.0 }
};

// Нахождение МНК-оценки
void MNK_rate(Vector *y_vec, Matrix *x_mat, Vector *result);

// Среднее значение расчетных и фактических данных зависимых переменных
bool check_average_equality(Matrix *x_mat, Vector *a_vec, Vector *y_vec_calulated);

// Вычисление коэффициента детерминации
double det_coef(Vector *y_vec, Vector *y_vec_calculated);

int main(void)
{
	Matrix x_mat;
	Vector y_vec, a_vec;

	// double x_array[5][2] =
	// {
	// 	{ 12, 20 },
	// 	{ 11, 18 },
	// 	{ 18, 27 },
	// 	{ 17, 11 },
	// 	{ 15, 14 }
	// };
	// double y_array[5] =	{ 1.8, 0.3, 0.6, 1.0, 4.7 };
	// mat_init_array(&x_mat, &x_array[0][0], 5, 2);
	// vec_init_array(&y_vec, &y_array[0], 5);
	// vec_init(&a_vec, 2);
	mat_init_array(&x_mat, &X[0][0], X_N, X_M);
	vec_init_array(&y_vec, &Y[0], Y_N);
	vec_init(&a_vec, A_N);

	MNK_rate(&y_vec, &x_mat, &a_vec);
	
	printf("Vector A:\n");
	vec_print(&a_vec);

	check_average_equality(&x_mat, &a_vec, &y_vec);
	vec_destroy(&a_vec);
	vec_destroy(&y_vec);
	mat_destroy(&x_mat);
	return 0;
}

void MNK_rate(Vector *y_vec, Matrix *x_mat, Vector *a_vec)
{
	assert(x_mat != NULL && a_vec != NULL && y_vec != NULL);
	// X^t, X^t
	Matrix x_transposed, x_transposed2;
	Matrix multiplication, multiplication2;
	
	// X -> [X^t]
	mat_init_array(&x_transposed, x_mat->array, x_mat->rows, x_mat->columns);
	mat_init_array(&x_transposed2, x_mat->array, x_mat->rows, x_mat->columns);

	// [X^t] -> X^t
	mat_transpose(&x_transposed);
	mat_transpose(&x_transposed2);

	// X^t * X
	mat_init(&multiplication, x_transposed.rows, x_mat->columns);
	mat_mul(&x_transposed, x_mat, &multiplication);
	
	// (X^t * X)^-1
	mat_inverse(&multiplication);
	
	// (X^t * X)^-1 * X^t
	mat_init(&multiplication2, multiplication.rows, x_transposed2.columns);
	mat_mul(&multiplication, &x_transposed2, &multiplication2);
	// (X^t * X)^-1 * X^t * y = a
	mat_mul_vec(&multiplication2, y_vec, a_vec);

	mat_destroy(&x_transposed);
	mat_destroy(&x_transposed2);
	mat_destroy(&multiplication);
	mat_destroy(&multiplication2);
}

bool check_average_equality(Matrix *x_mat, Vector *a_vec, Vector *y_vec)
{
	assert(x_mat != NULL && a_vec != NULL && y_vec != NULL);
	Vector y_vec_calculated;
	vec_init(&y_vec_calculated, y_vec->size);
	//
	//
	mat_mul_vec(x_mat, a_vec, &y_vec_calculated);

	double average = vec_average(y_vec);
	printf("average for y1 = %3.15f\n", average);
	double average_calculated = vec_average(&y_vec_calculated);
	printf("average for y2 = %3.15f\n", average_calculated);

	double coef = det_coef(y_vec, &y_vec_calculated);
	printf("det coef - %3.15f\n", coef);
	//
	//
	vec_destroy(&y_vec_calculated);
	//
	//
	return average - average_calculated;
}

double det_coef(Vector *y_vec, Vector *y_vec_calculated)
{
	assert(y_vec->size == y_vec_calculated->size);
	Vector e_vec;
	vec_init(&e_vec, y_vec->size);
	//
	//
	vec_sub(y_vec, y_vec_calculated, &e_vec);
	
	double e_sqr_sum = 0.0;
	for (size_t i = 0; i < e_vec.size; i++)
		e_sqr_sum += e_vec.array[i] * e_vec.array[i];

	double y_average = vec_average(y_vec);
	double y_sqr_sum = 0.0;
	for (size_t i = 0; i < y_vec->size; i++)
		y_sqr_sum += (y_vec->array[i] - y_average) * (y_vec->array[i] - y_average);
	//
	//
	vec_destroy(&e_vec);
	return 1 - e_sqr_sum / y_sqr_sum;
}