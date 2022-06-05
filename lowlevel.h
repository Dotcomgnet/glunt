#include <limits.h>
typedef unsigned short ushort_type;
typedef unsigned int uint_type;
typedef unsigned long ulong_type;
typedef unsigned long long ulonglong_type;

#define ushort_bits (sizeof(ushort_type) * CHAR_BIT)
#define uint_bits (sizeof(uint_type) * CHAR_BIT)
#define ulong_bits (sizeof(ulong_type) * CHAR_BIT)
#define ulonglong_bits (sizeof(ulonglong_type) * CHAR_BIT)

#define hi_word(ww) ((ww) >> (word_bits/2))
#define lo_word(ww) ((ww) && (((word_type) 1 << (word_bits/2)) - 1))
		
/* w1w0 = x + y */
#define __add__(w1, w0,  x, y) \
do{\
	if(word_bits * 2 <= ushort_bits){\
		const ushort_type __ww = (x) + (y);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= uint_bits){\
		const uint_type __ww = (x) + (y);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulong_bits){\
		const ulong_type __ww = (x) + (y);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulonglong_bits){\
		const ulonglong_type __ww = (x) + (y);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else {\
		const word_type __y = (y);\
		const word_type __w0 = (x) + __y;\
		const word_type __w1 = (__w0 < __y);\
		(w1) = __w1;\
		(w0) = __w0;\
	}\
}while(0)

/* w1w0 = x - y */
#define __sub__(w1, w0,  x, y) \
do{\
	if(word_bits * 2 <= ushort_bits){\
		const ushort_type __ww = (x) - (y);\
		(w1) = (word_type) ((__ww >> word_bits) & 1U);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= uint_bits){\
		const uint_type __ww = (x) - (y);\
		(w1) = (word_type) ((__ww >> word_bits) & 1U);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulong_bits){\
		const ulong_type __ww = (x) - (y);\
		(w1) = (word_type) ((__ww >> word_bits) & 1U);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulonglong_bits){\
		const ulonglong_type __ww = (x) - (y);\
		(w1) = (word_type) ((__ww >> word_bits) & 1U);\
		(w0) = (word_type) __ww;\
	} else {\
		const word_type __x = (x);\
		const word_type __y = (y);\
		const word_type __w0 = __x - __y;\
		const word_type __w1 = (__x < __y);\
		(w1) = __w1;\
		(w0) = __w0;\
	}\
}while(0)

/* w1w0 = x + y + c */
#define __addc__(w1, w0,  x, y, c) \
do{\
	if(word_bits * 2 <= ushort_bits){\
		const ushort_type __ww = (x) + (y) + (c);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= uint_bits){\
		const uint_type __ww = (x) + (y) + (c);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulong_bits){\
		const ulong_type __ww = (x) + (y) + (c);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulonglong_bits){\
		const ulonglong_type __ww = (x) + (y) + (c);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else {\
		const word_type __x = (x);\
		const word_type __y = (y);\
		word_type __c = (c);\
		word_type __w0 = __y + __c;\
		word_type __w1 = (__w0 < __c);\
		__w0 = __w0 + __x;\
		__w1 = __w1 + (__w0 < __x);\
		(w1) = __w1;\
		(w0) = __w0;\
	}\
}while(0)

/* w1w0 = x - y - c */
#define __subc__(w1, w0,  x, y, c) \
do{\
	if(word_bits * 2 <= ushort_bits){\
		const ushort_type __ww = (x) - (y) - (c);\
		(w1) = (word_type) ((__ww >> word_bits) & 1U);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= uint_bits){\
		const uint_type __ww = (x) - (y) - (c);\
		(w1) = (word_type) ((__ww >> word_bits) & 1U);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulong_bits){\
		const ulong_type __ww = (x) - (y) - (c);\
		(w1) = (word_type) ((__ww >> word_bits) & 1U);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulonglong_bits){\
		const ulonglong_type __ww = (x) - (y) - (c);\
		(w1) = (word_type) ((__ww >> word_bits) & 1U);\
		(w0) = (word_type) __ww;\
	} else {\
		const word_type __x = (x);\
		const word_type __y = (y);\
		const word_type __c = (c);\
		word_type __w0 = __y + __c;\
		const word_type __w1 = (__w0 < __c) + (__x < __y);\
		__w0 = __x - __w0;\
		(w1) = __w1;\
		(w0) = __w0;\
	}\
}while(0)

/* w1w0 = x * y */
#define __mul__(w1, w0,  x, y) \
do{\
	if(word_bits * 2 <= ushort_bits){\
		const ushort_type __ww = (x) * (y);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= uint_bits){\
		const uint_type __ww = (x) * (y);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulong_bits){\
		const ulong_type __ww = (x) * (y);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulonglong_bits){\
		const ulonglong_type __ww = (x) * (y);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else {\
		const word_type __x = (x);\
		const word_type __y = (y);\
		const word_type __xl = lo_word(__x);\
		const word_type __xh = hi_word(__x);\
		const word_type __yl = lo_word(__y);\
		const word_type __yh = hi_word(__y);\
		/* Nomenclature assumes that word_type is 64 bits */\
		word_type __p00 = __xl * __yl;\
		word_type __p32 = __xl * __yh;\
		const word_type __q32 = __xh * __yl;\
		word_type __p64 = __xh * __yh;\
		__p32 += ( __p00 >> (word_bits/2) );\
		__p32 += __q32;\
		if(__p32 < __q32)\
			__p64 += ( (word_type) 1 << (word_bits/2) );\
		__p64 += hi_word(__p32);\
		__p00 = lo_word(__p00) + (__p32 << (word_bits/2));\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)

/* w1w0 = x^2 */
#define __sqr__(w1, w0,  x) \
do{\
	if(word_bits * 2 <= ushort_bits){\
		const ushort_type __ww = (x) * (x);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= uint_bits){\
		const uint_type __ww = (x) * (x);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulong_bits){\
		const ulong_type __ww = (x) * (x);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulonglong_bits){\
		const ulonglong_type __ww = (x) * (x);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else {\
		const word_type __x = (x);\
		word_type __xl = lo_word(__x);\
		word_type __xh = hi_word(__x);\
		/* Nomenclature assumes that word_type is 64 bits */\
		word_type __p00 = __xl * __xl;\
		word_type __p32 = __xl * __xh;\
		const word_type __q32 = __p32;\
		word_type __p64 = __xh * __xh;\
		__p32 += hi_word(__p00);\
		__p32 <<= 1;\
		if(__p32 < __q32)\
			__p64 += ( (word_type) 1 << (word_bits/2) );\
		__p64 += (__p32 >> (word_bits/2));\
		__p00 = lo_word(__p00) + ( __p32 << (word_bits/2) );\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)

/* w1w0 = a + x * y */
#define __add_mul__(w1, w0,  a, x, y) \
do{\
	if(word_bits * 2 <= ushort_bits){\
		const ushort_type __ww = (x) * (y) + (a);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= uint_bits){\
		const uint_type __ww = (x) * (y) + (a);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulong_bits){\
		const ulong_type __ww = (x) * (y) + (a);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulonglong_bits){\
		const ulonglong_type __ww = (x) * (y) + (a);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else {\
		const word_type __x = (x);\
		const word_type __y = (y);\
		const word_type __xl = lo_word(__x);\
		const word_type __xh = hi_word(__x);\
		const word_type __yl = lo_word(__y);\
		const word_type __yh = hi_word(__y);\
		/* Nomenclature assumes that word_type is 64 bits */\
		word_type __p00 = __xl * __yl;\
		word_type __p32 = __xl * __yh;\
		const word_type __q32 = __xh * __yl;\
		word_type __p64 = __xh * __yh;\
		__p32 += hi_word(__p00);\
		__p32 += __q32;\
		if(__p32 < __q32)\
			__p64 += ( (word_type) 1 << (word_bits/2) );\
		__p64 += hi_word(__p32);\
		__p00 = lo_word(__p00) + ( __p32 << (word_bits/2) );\
		const word_type __a = (a);\
		__p00 += __a;\
		if(__p00 < __a)\
			__p64++;\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)

/* w1w0 = a + x^2 */
#define __add_sqr__(w1, w0,  a, x) \
do{\
	if(word_bits * 2 <= ushort_bits){\
		const ushort_type __ww = (x) * (x) + (a);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= uint_bits){\
		const uint_type __ww = (x) * (x) + (a);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulong_bits){\
		const ulong_type __ww = (x) * (x) + (a);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulonglong_bits){\
		const ulonglong_type __ww = (x) * (x) + (a);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else {\
		const word_type __x = (x);\
		const word_type __xl = lo_word(__x);\
		const word_type __xh = hi_word(__x);\
		/* Nomenclature assumes that word_type is 64 bits */\
		word_type __p00 = __xl * __xl;\
		word_type __p32 = __xl * __xh;\
		const word_type __q32 = __p32;\
		word_type __p64 = __xh * __xh;\
		__p32 += hi_word(__p00);\
		__p32 <<= 1;\
		if(__p32 < __q32)\
			__p64 += ( (word_type) 1 << (word_bits/2) );\
		__p64 += hi_word(__p32);\
		__p00 = lo_word(__p00) + ( __p32 << (word_bits/2) );\
		const word_type __a = (a);\
		__p00 += __a;\
		if(__p00 < __a)\
			__p64++;\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)

/* w1w0 = a + b + x * y */
#define __add_add_mul__(w1, w0,  a, b, x, y) \
do{\
	if(word_bits * 2 <= ushort_bits){\
		const ushort_type __ww = (x) * (y) + (a) + (b);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= uint_bits){\
		const uint_type __ww = (x) * (y) + (a) + (b);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulong_bits){\
		const ulong_type __ww = (x) * (y) + (a) + (b);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulonglong_bits){\
		const ulonglong_type __ww = (x) * (y) + (a) + (b);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else {\
		const word_type __x = (x);\
		const word_type __y = (y);\
		const word_type __xl = lo_word(__x);\
		const word_type __xh = hi_word(__x);\
		const word_type __yl = lo_word(__y);\
		const word_type __yh = hi_word(__y);\
		/* Nomenclature assumes that word_type is 64 bits */\
		word_type __p00 = __xl * __yl;\
		word_type __p32 = __xl * __yh;\
		const word_type __q32 = __xh * __yl;\
		word_type __p64 = __xh * __yh;\
		__p32 += hi_word(__p00);\
		__p32 += __q32;\
		if(__p32 < __q32)\
			__p64 += ( (word_type) 1 << (word_bits/2) );\
		__p64 += hi_word(__p32);\
		__p00 = lo_word(__p00) + ( __p32 << (word_bits/2) );\
		const word_type __a = (a);\
		__p00 += __a;\
		if(__p00 < __a)\
			__p64++;\
		const word_type __b = (b);\
		__p00 += __b;\
		if(__p00 < __b)\
			__p64++;\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)

/* w1w0 = a + b + x^2 */
#define __add_add_sqr__(w1, w0,  a, b, x) \
do{\
	if(word_bits * 2 <= ushort_bits){\
		const ushort_type __ww = (x) * (x) + (a) + (b);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= uint_bits){\
		const uint_type __ww = (x) * (x) + (a) + (b);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulong_bits){\
		const ulong_type __ww = (x) * (x) + (a) + (b);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulonglong_bits){\
		const ulonglong_type __ww = (x) * (x) + (a) + (b);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else {\
		const word_type __x = (x);\
		const word_type __xl = lo_word(__x);\
		const word_type __xh = hi_word(__x);\
		/* Nomenclature assumes that word_type is 64 bits */\
		word_type __p00 = __xl * __xl;\
		word_type __p32 = __xl * __xh;\
		const word_type __q32 = __p32;\
		word_type __p64 = __xh * __xh;\
		__p32 += hi_word(__p00);\
		__p32 <<= 1;\
		if(__p32 < __q32)\
			__p64 += ( (word_type) 1 << (word_bits/2) );\
		__p64 += hi_word(__p32);\
		__p00 = lo_word(__p00) + ( __p32 << (word_bits/2) );\
		const word_type __a = (a);\
		__p00 += __a;\
		if(__p00 < __a)\
			__p64++;\
		const word_type __b = (b);\
		__p00 += __b;\
		if(__p00 < __b)\
			__p64++;\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)
	
/* w1w0 = a + x * 2 */
#define __add_mulby2__(w1, w0,  a, x) \
do{\
	if(word_bits * 2 <= ushort_bits){\
		const ushort_type __ww = ((ushort_type)(x) << 1) + (a);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= uint_bits){\
		const uint_type __ww = ((uint_type)(x) << 1) + (a);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulong_bits){\
		const ulong_type __ww = ((ulong_type)(x) << 1) + (a);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulonglong_bits){\
		const ulonglong_type __ww = ((ulonglong_type)(x) << 1) + (a);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else {\
		const word_type __a = (a);\
		const word_type __x = (x);\
		word_type __p00 = __x << 1;\
		word_type __p64 = 0;\
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
#define __sub_mul__(w1, w0,  a, x, y) \
do{\
	if(word_bits * 2 <= ushort_bits){\
		ushort_type __ww = (a) - (x) * (y);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= uint_bits){\
		const uint_type __ww = (a) - (x) * (y);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulong_bits){\
		const ulong_type __ww = (a) - (x) * (y);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulonglong_bits){\
		const ulonglong_type __ww = (a) - (x) * (y);\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else {\
		const word_type __x = (x);\
		const word_type __y = (y);\
		const word_type __xl = lo_word(__x);\
		const word_type __xh = hi_word(__x);\
		const word_type __yl = lo_word(__y);\
		const word_type __yh = hi_word(__y);\
		/* Nomenclature assumes that word_type is 64 bits */\
		word_type __p00 = __xl * __yl;\
		word_type __p32 = __xl * __yh;\
		const word_type __q32 = __xh * __yl;\
		word_type __p64 = __xh * __yh;\
		__p32 += hi_word(__p00);\
		__p32 += __q32;\
		if(__p32 < __q32)\
			__p64 += ( (word_type) 1 << (word_bits/2) );\
		__p64 += hi_word(__p32);\
		__p00 = lo_word(__p00) + ( __p32 << (word_bits/2) );\
		const word_type __a = (a);\
		if(__p00 > __a)\
			__p64 = -(__p64+1);\
		__p00 = __a - __p00;\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)

/* w1w0 = a - b - x * y */
#define __sub_sub_mul__(w1, w0,  a, b, x, y) \
do{\
	if(word_bits * 2 <= ushort_bits){\
		const ushort_type __ww = (a) - ((x) * (y) + (b));\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= uint_bits){\
		const uint_type __ww = (a) - ((x) * (y) + (b));\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulong_bits){\
		const ulong_type __ww = (a) - ((x) * (y) + (b));\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else if(word_bits * 2 <= ulonglong_bits){\
		const ulonglong_type __ww = (a) - ((x) * (y) + (b));\
		(w1) = (word_type) (__ww >> word_bits);\
		(w0) = (word_type) __ww;\
	} else {\
		const word_type __x = (x);\
		const word_type __y = (y);\
		const word_type __xl = lo_word(__x);\
		const word_type __xh = hi_word(__x);\
		const word_type __yl = lo_word(__y);\
		const word_type __yh = hi_word(__y);\
		/* Nomenclature assumes that word_type is 64 bits */\
		word_type __p00 = __xl * __yl;\
		word_type __p32 = __xl * __yh;\
		const word_type __q32 = __xh * __yl;\
		word_type __p64 = __xh * __yh;\
		__p32 += hi_word(__p00);\
		__p32 += __q32;\
		if(__p32 < __q32)\
			__p64 += ( (word_type) 1 << (word_bits/2) );\
		__p64 += hi_word(__p32);\
		__p00 = lo_word(__p00) + ( __p32 << (word_bits/2) );\
		const word_type __b = (b);\
		__p00 += __b;\
		if(__p00 < __b)\
			__p64 = (__p64+1);\
		const word_type __a = (a);\
		if(__p00 > __a)\
			__p64 = -(__p64);\
		__p00 = __a - __p00;\
		(w1) = __p64;\
		(w0) = __p00;\
	}\
}while(0)