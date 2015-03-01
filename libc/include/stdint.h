#ifndef _STDINT_H_
#define _STDINT_H_

#ifndef __UINT8_TYPE__
#ifndef __INT8_TYPE__
#define __INT8_TYPE__ char
#endif
#define __UINT8_TYPE__ unsigned __INT8_TYPE__
#endif
#ifndef __INT16_TYPE__
#define __INT16_TYPE__ short
#endif
#ifndef __UINT16_TYPE__
#define __UINT16_TYPE__ unsigned __INT16_TYPE__
#endif
#ifndef __UINT32_TYPE__
#ifndef __INT32_TYPE__
#define __INT32_TYPE__ int
#endif
#define __UINT32_TYPE__ unsigned __INT32_TYPE__
#endif
#ifndef __UINT64_TYPE__
#ifndef __INT64_TYPE_
#if __SIZEOF_LONG__ == 4
#define __INT64_TYPE__ long long
#else
#define __INT64_TYPE__ long
#endif
#endif
#define __UINT64_TYPE__ unsigned __INT64_TYPE__
#endif
#ifndef __UINTPTR_TYPE__
#ifndef __INTPTR_TYPE_
#define __INTPTR_TYPE __PTRDIFF_TYPE__
#endif
#define __UINTPTR_TYPE__ unsigned __INTPTR_TYPE__
#endif

typedef __INT8_TYPE__ int8_t;
typedef __UINT8_TYPE__ uint8_t;
typedef __INT16_TYPE__ int16_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __INT32_TYPE__ int32_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __INT64_TYPE__ int64_t;
typedef __UINT64_TYPE__ uint64_t;
typedef __INTPTR_TYPE__ intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;

#endif
