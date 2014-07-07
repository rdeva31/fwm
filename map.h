#include "compat.h"

#ifndef FWM_MAP
#define FWM_MAP

#define map(__array, __length, __mapper) ({					\
	typeof(*__array) *__array_copy = (__array);				\
	typeof((__mapper)((typeof(*__array))0)) *__mapped =			\
					FWM_MALLOC(FWM_MALLOC_FMT(		\
					sizeof(*__mapped) * (__length)));	\
	for (int c = 0; c < (__length); ++c)					\
		__mapped[c] = (__mapper)(__array_copy[c]);			\
	__mapped;								\
})

#endif
