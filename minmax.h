#include "compat.h"

#ifndef FWM_MINMAX
#define FWM_MINMAX

#define minmax(__array, __length, __comparator) ({				\
	struct {								\
			typeof(*array) min, max;				\
	} __minmax;								\
	typeof(*(__array)) __min, __max, *__array_copy = (__array);		\
										\
	__min = __max = __array_copy[0];					\
										\
	for (int __curr = 1; __curr < (__length); ++__curr) {			\
		if ((__comparator)(__array_copy[__curr], __min) < 0)		\
			__min = __array_copy[__curr];				\
										\
		if ((__comparator)(__array_copy[__curr], __max) > 0)		\
			__max = __array_copy[__curr]; \
	}									\
										\
	__minmax.min = __min;							\
	__minmax.max = __max;							\
	__minmax;								\
})

#endif
