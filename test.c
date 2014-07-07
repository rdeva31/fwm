#include <assert.h>
#include <alloca.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "fold_right.h"
#include "for_each.h"
#include "minmax.h"
#include "map.h"

int fibbonacci(int a, int b)
{
	return a + b;
}

int combinatorial(int a, int b)
{
	return a * b;
}

int minus(int a, int b)
{
	return a - b;
}

int last(int a, int b)
{
	return b;
}

int first(int a, int b)
{
	return a;
}

bool test_fold_right(void)
{
	const int array[] = {4, 3, 2, 1};
	int size = sizeof(array)/sizeof(*array);
	int reference = 0;

	/* Simple sum */
	for (int c = 0; c < size; ++c)
		reference += array[c];

	assert(reference == fold_right(array, size));
	assert(reference == fold_right(array, size, fibbonacci));

	/* Minus */
	reference = array[0];
	for (int c = 1; c < size; ++c)
		reference -= array[c];
	assert(reference == fold_right(array, size, minus));

	/* Combinatorial! */
	reference = 1;
	for (int c = 0; c < size; ++c)
		reference *= array[c];

	assert(reference == fold_right(array, size, combinatorial));

	/* Last */
	reference = array[size - 1];
	assert(reference == fold_right(array, size, last));

	/* First */
	reference = array[0];
	assert(reference == fold_right(array, size, first));

	return true;
}

bool test_each(void)
{
	const char *array[] = {"a", "bb", "ccc", "dddd"};
	int size = sizeof(array)/sizeof(*array);

	/* Max str size */
	int guess = 0, max = strlen(array[size - 1]);

	for_each(array, size, curr) {
		int len = strlen(curr);

		if (guess < len)
			guess = len;
	}

	assert(guess == max);

	/* Same thing, but use pointers instead */
	guess = 0, max = strlen(array[size - 1]);

	for_each_as_ptr(array, size, curr) {
		int len = strlen(*curr);

		if (guess < len)
			guess = len;
	}

	assert(guess == max);

	return true;
}

struct my_int {
	int i;
};

int my_int_comparator(struct my_int a, struct my_int b)
{
	return a.i - b.i;
}

bool test_minmax(void)
{
	const struct my_int array[] = {
		{4}, {3}, {2}, {1}
	};
	int size = sizeof(array)/sizeof(*array);

	assert(4 == minmax(array, size, my_int_comparator).max.i);
	assert(1 == minmax(array, size, my_int_comparator).min.i);
	return true;
}

double half(int a)
{
	return a / 2.0;
}

char *stringify(double a)
{
	char *temp = malloc(32 /*32 digits ought to be enough for anyone*/);

	sprintf(temp, "%.1f", a);
	return temp;
}

struct timeval timevalify(double a)
{
	struct timeval tv;

	tv.tv_sec = (int)a;
	tv.tv_usec = a - (int)a;

	return tv;
}

bool test_map(void)
{
	const int array[] = {4, 3, 2, 1};
	int size = sizeof(array)/sizeof(*array);

	/* Half */
	double float_reference[] = {2.0, 1.5, 1.0, 0.5};
	double *halved = map(array, size, half);

	assert(memcmp(float_reference, halved, sizeof(float_reference)) == 0);
	free(halved);

	/* Timeval */
	struct timeval tv_reference[] = {
		{2, 0}, {1, 5}, {1, 0}, {0, 5}
	};
	struct timeval *timevaled = map(array, size, timevalify);

	assert(memcmp(tv_reference, timevaled, sizeof(tv_reference)) == 0);

	/* Stringify */
	char *str_reference[] = {"4.0", "3.0", "2.0", "1.0"};
	char **stringified = map(array, size, stringify);

	for (int c = 0; c < size; ++c) {
		assert(strcmp(stringified[c], str_reference[c]) == 0);
		free(stringified[c]);
	}
	free(stringified);

	return true;
}

int main(void)
{
#define test(x) do { \
	printf("Running " #x "..."); \
	if (x) {\
		printf(" passed!\n"); \
	} else { \
		printf(" failed!\n"); \
	} \
} while (0)

	test(test_fold_right());
	test(test_each());
	test(test_minmax());
	test(test_map());

	return 0;
}
