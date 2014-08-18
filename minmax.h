#include "compat.h"

#ifndef FWM_MINMAX
#define FWM_MINMAX

#define min(__array, __length, __comparator) ({					\
	typeof(*(__array)) __min, *__array_copy = (__array);			\
										\
	__min = __array_copy[0];						\
										\
	for (int __curr = 1; __curr < (__length); ++__curr) {			\
		if ((__comparator)(__array_copy[__curr], __min) < 0)		\
			__min = __array_copy[__curr];				\
	}									\
										\
	__min;									\
})

#define max(__array, __length, __comparator) ({					\
	typeof(*(__array)) __max, *__array_copy = (__array);			\
										\
	__max = __array_copy[0];						\
										\
	for (int __curr = 1; __curr < (__length); ++__curr) {			\
		if ((__comparator)(__array_copy[__curr], __max) > 0)		\
			__max = __array_copy[__curr];				\
	}									\
										\
	__max;									\
})
#endif
