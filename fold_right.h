#include "compat.h"

#ifndef FWM_FOLD_RIGHT
#define FWM_FOLD_RIGHT

#define fold_right_simple(__array, __length) ({					\
	typeof(*(__array)) __accum = (__array)[0];				\
	int __curr = 1;								\
										\
	for (;__curr < (__length); ++__curr) {					\
		__accum = __accum + (__array)[__curr];				\
	}									\
										\
	__accum;								\
})

#define fold_right_complex(__array, __length, __functor) ({			\
	typeof(*(__array)) __accum = (__array)[0];				\
	int __curr = 1;								\
										\
	for (;__curr < (__length); ++__curr) {					\
		__accum = (__functor)(__accum, (__array)[__curr]);		\
	}									\
										\
	__accum;								\
})

#define fold_right_polymorph(__1, __2, __3, __4, ...) __4
#define fold_right(...) fold_right_polymorph(__VA_ARGS__,			\
		fold_right_complex, fold_right_simple)(__VA_ARGS__)

#endif
