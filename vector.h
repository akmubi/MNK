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
		printf("%3.2f\t", vec->array[i]);
	printf("\n\n");
}

#endif // _VECTOR_H_