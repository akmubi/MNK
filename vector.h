#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct
{
	double *array;
	size_t size;
} Vector;

void vec_init		(Vector *vec, size_t size);
void vec_init_array	(Vector *vec, const double *array, size_t size);
double vec_sub		(Vector *first, Vector *second, Vector *result);
double vec_average	(Vector *vec);
void vec_destroy	(Vector *vec);
void vec_print		(Vector *vec);

// Создание вектора, заполненного нулями
void vec_init(Vector *vec, size_t size)
{
	assert(vec != NULL);
	vec->array = (double *)malloc(size * sizeof(*vec->array));
	vec->size = size;
	//
	//
	for (size_t i = 0; i < size; i++)
		vec->array[i] = 0.0;
}

// Создание вектора, заполненного значениями из массива
void vec_init_array(Vector *vec, const double *array, size_t size)
{
	assert(vec != NULL);
	assert(array != NULL);
	vec->array = (double *)malloc(size * sizeof(*vec->array));
	vec->size = size;
	//
	//
	for (size_t i = 0; i < size; i++)
		vec->array[i] = array[i];
}

double vec_sub(Vector *first, Vector *second, Vector *result)
{
	assert(first != NULL && second != NULL && result != NULL);
	assert(first->size == second->size && first->size == result->size);
	size_t size = first->size;
	//
	//
	for (size_t i = 0; i < size; i++)
		result->array[i] = first->array[i] - second->array[i];
}

double vec_average(Vector *vec)
{
	assert(vec != NULL);
	assert(vec->size > 0);
	//
	//
	double sum = 0.0;
	for (size_t i = 0; i < vec->size; i++)
		sum += vec->array[i];
	return sum / vec->size;
}

void vec_destroy(Vector *vec)
{
	assert(vec != NULL);
	if (vec->array != NULL)	free(vec->array);
	vec->array = NULL;
	vec->size = 0;
}

void vec_print(Vector *vec)
{
	assert(vec != NULL);
	for (size_t i = 0; i < vec->size; i++)
		printf("%3.10f\t", vec->array[i]);
	printf("\n\n");
}

#endif // _VECTOR_H_