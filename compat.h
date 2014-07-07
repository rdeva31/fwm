#ifndef FWM_COMPAT
#define FWM_COMPAT

#ifndef __GNUC__
#define __typeof__ typeof
#endif

/* Override FWM_MALLOC to use malloc implementation of choice e.g. xmalloc or
 * kmalloc.  This is used by map(), filter() to allocate new arrays. FWM_MALLOC
 * should resolve to a function.
 */
#ifndef FWM_MALLOC
#define FWM_MALLOC malloc
#endif

/* Override FWM_MALLOC_FMT if your malloc implementation of choice requires
 * arguments besides the size.  e.g. your customer malloc's prototype is
 *     void * my_malloc(size_t size, char *debug_string_to_track_allocations)
 * So if you
 *     #define FWM_MALLOC my_malloc
 *     #define FWM_MALLOC_FMT(size) (size, __func__)
 * all allocations made by map(), filter() etc, will call my_malloc(some_size,
 * __func__) during allocations.
 *
 * Of course this doesn't gracefully work if you want to vary the format
 * between allocations..but we'll cross that bridge when we reach it.
 */
#ifndef FWM_MALLOC_FMT
#define FWM_MALLOC_FMT(size) (size)
#endif

#endif
