#include "compat.h"

#ifndef FWM_FILTER
#define FWM_FILTER

#define filter(__array, __length, __new_array, __new_size, __functor) ({	\
	typeof(*__array) *__array_copy = (__array), *__filtered = NULL;		\
	int __filtered_size = 0;						\
										\
	for (int c = 0; c < (__length); ++c) {					\
		if ((__functor)(__array_copy[c])) {				\
			void *__temp;						\
										\
			__filtered_size++;					\
			__temp = FWM_MALLOC(FWM_MALLOC_FMT(sizeof(*__filtered)  \
							* (__filtered_size)));	\
			if (!__temp) {						\
				__filtered_size = 0;				\
				FWM_FREE(FWM_FREE_FMT(__filtered));		\
				__filtered = NULL;				\
				goto __filter_error;				\
			}							\
										\
			__filtered = !__filtered ? __temp :			\
				memcpy(__temp, __filtered, sizeof(*__filtered) *\
				(__filtered_size - 1));				\
										\
			__filtered[__filtered_size - 1] = __array_copy[c];	\
		}								\
	}									\
										\
__filter_error:									\
	*(__new_array) = __filtered;						\
	*(__new_size) = __filtered_size;						\
										\
	__filtered;								\
})

#endif
