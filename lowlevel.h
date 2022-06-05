#include <limits.h>
typedef unsigned short __ushort_Type;
typedef unsigned int __uint_Type;
typedef unsigned long __ulong_Type;
typedef unsigned long long __ulonglong_Type;

#define __ushort_bits_Const (sizeof(__ushort_Type) * CHAR_BIT)
#define __uint_bits_Const (sizeof(__uint_Type) * CHAR_BIT)
#define __ulong_bits_Const (sizeof(__ulong_Type) * CHAR_BIT)
#define __ulonglong_bits_Const (sizeof(__ulonglong_Type) * CHAR_BIT)

#define __get_hi_word_Func(ww) ((ww) >> (__word_bits_Const/2))
#define __get_lo_word_Func(ww) ((ww) && (((__word_Type) 1 << (__word_bits_Const/2)) - 1))

/* w1w0 = x + y */
#define __add_Func(w1, w0,  x, y) \
do{\
	if(__word_bits_Const * 2 <= __ushort_bits_Const){\
		const __ushort_Type __ww = (x) + (y);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __uint_bits_Const){\
		const __uint_Type __ww = (x) + (y);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulong_bits_Const){\
		const __ulong_Type __ww = (x) + (y);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulonglong_bits_Const){\
		const __ulonglong_Type __ww = (x) + (y);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else {\
		const __word_Type __y = (y);\
		const __word_Type __w0 = (x) + __y;\
		const __word_Type __w1 = (__w0 < __y);\
		(w1) = __w1;\
		(w0) = __w0;\
	}\
}while(0)

/* w1w0 = x - y */
#define __sub_Func(w1, w0,  x, y) \
do{\
	if(__word_bits_Const * 2 <= __ushort_bits_Const){\
		const __ushort_Type __ww = (x) - (y);\
		(w1) = (__word_Type) ((__ww >> __word_bits_Const) & 1U);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __uint_bits_Const){\
		const __uint_Type __ww = (x) - (y);\
		(w1) = (__word_Type) ((__ww >> __word_bits_Const) & 1U);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulong_bits_Const){\
		const __ulong_Type __ww = (x) - (y);\
		(w1) = (__word_Type) ((__ww >> __word_bits_Const) & 1U);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulonglong_bits_Const){\
		const __ulonglong_Type __ww = (x) - (y);\
		(w1) = (__word_Type) ((__ww >> __word_bits_Const) & 1U);\
		(w0) = (__word_Type) __ww;\
	} else {\
		const __word_Type __x = (x);\
		const __word_Type __y = (y);\
		const __word_Type __w0 = __x - __y;\
		const __word_Type __w1 = (__x < __y);\
		(w1) = __w1;\
		(w0) = __w0;\
	}\
}while(0)

/* w1w0 = x + y + c */
#define __addc_Func(w1, w0,  x, y, c) \
do{\
	if(__word_bits_Const * 2 <= __ushort_bits_Const){\
		const __ushort_Type __ww = (x) + (y) + (c);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __uint_bits_Const){\
		const __uint_Type __ww = (x) + (y) + (c);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulong_bits_Const){\
		const __ulong_Type __ww = (x) + (y) + (c);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulonglong_bits_Const){\
		const __ulonglong_Type __ww = (x) + (y) + (c);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else {\
		const __word_Type __x = (x);\
		const __word_Type __y = (y);\
		__word_Type __c = (c);\
		__word_Type __w0 = __y + __c;\
		__word_Type __w1 = (__w0 < __c);\
		__w0 = __w0 + __x;\
		__w1 = __w1 + (__w0 < __x);\
		(w1) = __w1;\
		(w0) = __w0;\
	}\
}while(0)

/* w1w0 = x - y - c */
#define __subc_Func(w1, w0,  x, y, c) \
do{\
	if(__word_bits_Const * 2 <= __ushort_bits_Const){\
		const __ushort_Type __ww = (x) - (y) - (c);\
		(w1) = (__word_Type) ((__ww >> __word_bits_Const) & 1U);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __uint_bits_Const){\
		const __uint_Type __ww = (x) - (y) - (c);\
		(w1) = (__word_Type) ((__ww >> __word_bits_Const) & 1U);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulong_bits_Const){\
		const __ulong_Type __ww = (x) - (y) - (c);\
		(w1) = (__word_Type) ((__ww >> __word_bits_Const) & 1U);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulonglong_bits_Const){\
		const __ulonglong_Type __ww = (x) - (y) - (c);\
		(w1) = (__word_Type) ((__ww >> __word_bits_Const) & 1U);\
		(w0) = (__word_Type) __ww;\
	} else {\
		const __word_Type __x = (x);\
		const __word_Type __y = (y);\
		const __word_Type __c = (c);\
		__word_Type __w0 = __y + __c;\
		const __word_Type __w1 = (__w0 < __c) + (__x < __y);\
		__w0 = __x - __w0;\
		(w1) = __w1;\
		(w0) = __w0;\
	}\
}while(0)

/* w1w0 = x * y */
#define __mul_Func(w1, w0,  x, y) \
do{\
	if(__word_bits_Const * 2 <= __ushort_bits_Const){\
		const __ushort_Type __ww = (x) * (y);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __uint_bits_Const){\
		const __uint_Type __ww = (x) * (y);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulong_bits_Const){\
		const __ulong_Type __ww = (x) * (y);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulonglong_bits_Const){\
		const __ulonglong_Type __ww = (x) * (y);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else {\
		const __word_Type __x = (x);\
		const __word_Type __y = (y);\
		const __word_Type __xl = __get_lo_word_Func(__x);\
		const __word_Type __xh = __get_hi_word_Func(__x);\
		const __word_Type __yl = __get_lo_word_Func(__y);\
		const __word_Type __yh = __get_hi_word_Func(__y);\
		/* Nomenclature assumes that __word_Type is 64 bits */\
		__word_Type __p00 = __xl * __yl;\
		__word_Type __p32 = __xl * __yh;\
		const __word_Type __q32 = __xh * __yl;\
		__word_Type __p64 = __xh * __yh;\
		__p32 += ( __p00 >> (__word_bits_Const/2) );\
		__p32 += __q32;\
		if(__p32 < __q32)\
			__p64 += ( (__word_Type) 1 << (__word_bits_Const/2) );\
		__p64 += __get_hi_word_Func(__p32);\
		__p00 = __get_lo_word_Func(__p00) + (__p32 << (__word_bits_Const/2));\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)

/* w1w0 = x^2 */
#define __sqr_Func(w1, w0,  x) \
do{\
	if(__word_bits_Const * 2 <= __ushort_bits_Const){\
		const __ushort_Type __ww = (x) * (x);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __uint_bits_Const){\
		const __uint_Type __ww = (x) * (x);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulong_bits_Const){\
		const __ulong_Type __ww = (x) * (x);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulonglong_bits_Const){\
		const __ulonglong_Type __ww = (x) * (x);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else {\
		const __word_Type __x = (x);\
		__word_Type __xl = __get_lo_word_Func(__x);\
		__word_Type __xh = __get_hi_word_Func(__x);\
		/* Nomenclature assumes that __word_Type is 64 bits */\
		__word_Type __p00 = __xl * __xl;\
		__word_Type __p32 = __xl * __xh;\
		const __word_Type __q32 = __p32;\
		__word_Type __p64 = __xh * __xh;\
		__p32 += __get_hi_word_Func(__p00);\
		__p32 <<= 1;\
		if(__p32 < __q32)\
			__p64 += ( (__word_Type) 1 << (__word_bits_Const/2) );\
		__p64 += (__p32 >> (__word_bits_Const/2));\
		__p00 = __get_lo_word_Func(__p00) + ( __p32 << (__word_bits_Const/2) );\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)

/* w1w0 = a + x * y */
#define __add_mul_Func(w1, w0,  a, x, y) \
do{\
	if(__word_bits_Const * 2 <= __ushort_bits_Const){\
		const __ushort_Type __ww = (x) * (y) + (a);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __uint_bits_Const){\
		const __uint_Type __ww = (x) * (y) + (a);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulong_bits_Const){\
		const __ulong_Type __ww = (x) * (y) + (a);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulonglong_bits_Const){\
		const __ulonglong_Type __ww = (x) * (y) + (a);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else {\
		const __word_Type __x = (x);\
		const __word_Type __y = (y);\
		const __word_Type __xl = __get_lo_word_Func(__x);\
		const __word_Type __xh = __get_hi_word_Func(__x);\
		const __word_Type __yl = __get_lo_word_Func(__y);\
		const __word_Type __yh = __get_hi_word_Func(__y);\
		/* Nomenclature assumes that __word_Type is 64 bits */\
		__word_Type __p00 = __xl * __yl;\
		__word_Type __p32 = __xl * __yh;\
		const __word_Type __q32 = __xh * __yl;\
		__word_Type __p64 = __xh * __yh;\
		__p32 += __get_hi_word_Func(__p00);\
		__p32 += __q32;\
		if(__p32 < __q32)\
			__p64 += ( (__word_Type) 1 << (__word_bits_Const/2) );\
		__p64 += __get_hi_word_Func(__p32);\
		__p00 = __get_lo_word_Func(__p00) + ( __p32 << (__word_bits_Const/2) );\
		const __word_Type __a = (a);\
		__p00 += __a;\
		if(__p00 < __a)\
			__p64++;\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)

/* w1w0 = a + x^2 */
#define __add_sqr_Func(w1, w0,  a, x) \
do{\
	if(__word_bits_Const * 2 <= __ushort_bits_Const){\
		const __ushort_Type __ww = (x) * (x) + (a);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __uint_bits_Const){\
		const __uint_Type __ww = (x) * (x) + (a);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulong_bits_Const){\
		const __ulong_Type __ww = (x) * (x) + (a);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulonglong_bits_Const){\
		const __ulonglong_Type __ww = (x) * (x) + (a);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else {\
		const __word_Type __x = (x);\
		const __word_Type __xl = __get_lo_word_Func(__x);\
		const __word_Type __xh = __get_hi_word_Func(__x);\
		/* Nomenclature assumes that __word_Type is 64 bits */\
		__word_Type __p00 = __xl * __xl;\
		__word_Type __p32 = __xl * __xh;\
		const __word_Type __q32 = __p32;\
		__word_Type __p64 = __xh * __xh;\
		__p32 += __get_hi_word_Func(__p00);\
		__p32 <<= 1;\
		if(__p32 < __q32)\
			__p64 += ( (__word_Type) 1 << (__word_bits_Const/2) );\
		__p64 += __get_hi_word_Func(__p32);\
		__p00 = __get_lo_word_Func(__p00) + ( __p32 << (__word_bits_Const/2) );\
		const __word_Type __a = (a);\
		__p00 += __a;\
		if(__p00 < __a)\
			__p64++;\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)

/* w1w0 = a + b + x * y */
#define __add_add_mul_Func(w1, w0,  a, b, x, y) \
do{\
	if(__word_bits_Const * 2 <= __ushort_bits_Const){\
		const __ushort_Type __ww = (x) * (y) + (a) + (b);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __uint_bits_Const){\
		const __uint_Type __ww = (x) * (y) + (a) + (b);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulong_bits_Const){\
		const __ulong_Type __ww = (x) * (y) + (a) + (b);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulonglong_bits_Const){\
		const __ulonglong_Type __ww = (x) * (y) + (a) + (b);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else {\
		const __word_Type __x = (x);\
		const __word_Type __y = (y);\
		const __word_Type __xl = __get_lo_word_Func(__x);\
		const __word_Type __xh = __get_hi_word_Func(__x);\
		const __word_Type __yl = __get_lo_word_Func(__y);\
		const __word_Type __yh = __get_hi_word_Func(__y);\
		/* Nomenclature assumes that __word_Type is 64 bits */\
		__word_Type __p00 = __xl * __yl;\
		__word_Type __p32 = __xl * __yh;\
		const __word_Type __q32 = __xh * __yl;\
		__word_Type __p64 = __xh * __yh;\
		__p32 += __get_hi_word_Func(__p00);\
		__p32 += __q32;\
		if(__p32 < __q32)\
			__p64 += ( (__word_Type) 1 << (__word_bits_Const/2) );\
		__p64 += __get_hi_word_Func(__p32);\
		__p00 = __get_lo_word_Func(__p00) + ( __p32 << (__word_bits_Const/2) );\
		const __word_Type __a = (a);\
		__p00 += __a;\
		if(__p00 < __a)\
			__p64++;\
		const __word_Type __b = (b);\
		__p00 += __b;\
		if(__p00 < __b)\
			__p64++;\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)

/* w1w0 = a + b + x^2 */
#define __add_add_sqr_Func(w1, w0,  a, b, x) \
do{\
	if(__word_bits_Const * 2 <= __ushort_bits_Const){\
		const __ushort_Type __ww = (x) * (x) + (a) + (b);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __uint_bits_Const){\
		const __uint_Type __ww = (x) * (x) + (a) + (b);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulong_bits_Const){\
		const __ulong_Type __ww = (x) * (x) + (a) + (b);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulonglong_bits_Const){\
		const __ulonglong_Type __ww = (x) * (x) + (a) + (b);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else {\
		const __word_Type __x = (x);\
		const __word_Type __xl = __get_lo_word_Func(__x);\
		const __word_Type __xh = __get_hi_word_Func(__x);\
		/* Nomenclature assumes that __word_Type is 64 bits */\
		__word_Type __p00 = __xl * __xl;\
		__word_Type __p32 = __xl * __xh;\
		const __word_Type __q32 = __p32;\
		__word_Type __p64 = __xh * __xh;\
		__p32 += __get_hi_word_Func(__p00);\
		__p32 <<= 1;\
		if(__p32 < __q32)\
			__p64 += ( (__word_Type) 1 << (__word_bits_Const/2) );\
		__p64 += __get_hi_word_Func(__p32);\
		__p00 = __get_lo_word_Func(__p00) + ( __p32 << (__word_bits_Const/2) );\
		const __word_Type __a = (a);\
		__p00 += __a;\
		if(__p00 < __a)\
			__p64++;\
		const __word_Type __b = (b);\
		__p00 += __b;\
		if(__p00 < __b)\
			__p64++;\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)

/* w1w0 = a + x * 2 */
#define __add_mulby2_Func(w1, w0,  a, x) \
do{\
	if(__word_bits_Const * 2 <= __ushort_bits_Const){\
		const __ushort_Type __ww = ((__ushort_Type)(x) << 1) + (a);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __uint_bits_Const){\
		const __uint_Type __ww = ((__uint_Type)(x) << 1) + (a);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulong_bits_Const){\
		const __ulong_Type __ww = ((__ulong_Type)(x) << 1) + (a);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulonglong_bits_Const){\
		const __ulonglong_Type __ww = ((__ulonglong_Type)(x) << 1) + (a);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else {\
		const __word_Type __a = (a);\
		const __word_Type __x = (x);\
		__word_Type __p00 = __x << 1;\
		__word_Type __p64 = 0;\
		if(__p00 < __x)\
			__p64++;\
		__p00 += __a;\
		if(__p00 < __a)\
			__p64++;\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)

/* w1w0 = a - x * y */
#define __sub_mul_Func(w1, w0,  a, x, y) \
do{\
	if(__word_bits_Const * 2 <= __ushort_bits_Const){\
		__ushort_Type __ww = (a) - (x) * (y);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __uint_bits_Const){\
		const __uint_Type __ww = (a) - (x) * (y);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulong_bits_Const){\
		const __ulong_Type __ww = (a) - (x) * (y);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulonglong_bits_Const){\
		const __ulonglong_Type __ww = (a) - (x) * (y);\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else {\
		const __word_Type __x = (x);\
		const __word_Type __y = (y);\
		const __word_Type __xl = __get_lo_word_Func(__x);\
		const __word_Type __xh = __get_hi_word_Func(__x);\
		const __word_Type __yl = __get_lo_word_Func(__y);\
		const __word_Type __yh = __get_hi_word_Func(__y);\
		/* Nomenclature assumes that __word_Type is 64 bits */\
		__word_Type __p00 = __xl * __yl;\
		__word_Type __p32 = __xl * __yh;\
		const __word_Type __q32 = __xh * __yl;\
		__word_Type __p64 = __xh * __yh;\
		__p32 += __get_hi_word_Func(__p00);\
		__p32 += __q32;\
		if(__p32 < __q32)\
			__p64 += ( (__word_Type) 1 << (__word_bits_Const/2) );\
		__p64 += __get_hi_word_Func(__p32);\
		__p00 = __get_lo_word_Func(__p00) + ( __p32 << (__word_bits_Const/2) );\
		const __word_Type __a = (a);\
		if(__p00 > __a)\
			__p64 = -(__p64+1);\
		__p00 = __a - __p00;\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)

/* w1w0 = a - b - x * y */
#define __sub_sub_mul_Func(w1, w0,  a, b, x, y) \
do{\
	if(__word_bits_Const * 2 <= __ushort_bits_Const){\
		const __ushort_Type __ww = (a) - ((x) * (y) + (b));\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __uint_bits_Const){\
		const __uint_Type __ww = (a) - ((x) * (y) + (b));\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulong_bits_Const){\
		const __ulong_Type __ww = (a) - ((x) * (y) + (b));\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else if(__word_bits_Const * 2 <= __ulonglong_bits_Const){\
		const __ulonglong_Type __ww = (a) - ((x) * (y) + (b));\
		(w1) = (__word_Type) (__ww >> __word_bits_Const);\
		(w0) = (__word_Type) __ww;\
	} else {\
		const __word_Type __x = (x);\
		const __word_Type __y = (y);\
		const __word_Type __xl = __get_lo_word_Func(__x);\
		const __word_Type __xh = __get_hi_word_Func(__x);\
		const __word_Type __yl = __get_lo_word_Func(__y);\
		const __word_Type __yh = __get_hi_word_Func(__y);\
		/* Nomenclature assumes that __word_Type is 64 bits */\
		__word_Type __p00 = __xl * __yl;\
		__word_Type __p32 = __xl * __yh;\
		const __word_Type __q32 = __xh * __yl;\
		__word_Type __p64 = __xh * __yh;\
		__p32 += __get_hi_word_Func(__p00);\
		__p32 += __q32;\
		if(__p32 < __q32)\
			__p64 += ( (__word_Type) 1 << (__word_bits_Const/2) );\
		__p64 += __get_hi_word_Func(__p32);\
		__p00 = __get_lo_word_Func(__p00) + ( __p32 << (__word_bits_Const/2) );\
		const __word_Type __b = (b);\
		__p00 += __b;\
		if(__p00 < __b)\
			__p64 = (__p64+1);\
		const __word_Type __a = (a);\
		if(__p00 > __a)\
			__p64 = -(__p64);\
		__p00 = __a - __p00;\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)
