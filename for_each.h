#include "compat.h"

#ifndef FWM_EACH
#define FWM_EACH

#define for_each(__array, __length, __var)					\
	for (typeof(*__array) __var = *(__array), *__curr = (__array);		\
			(__var = *__curr) && (__curr < __array + __length);	\
			__curr++)

#endif
