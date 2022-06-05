#include "glunt.h"

#define GLUNT_C_MAJ  1
#define GLUNT_C_MIN  0

#if ((GLUNT_H_MAJ != GLUNT_C_MAJ) || (GLUNT_H_MIN != GLUNT_C_MIN))
#error >>> Incompatible versions of glunt.c and glunt.h
#endif

#define __glunt_t_bits_Const (sizeof(glunt_t) * CHAR_BIT)

typedef glunt_t __word_Type;
#define __word_bits_Const __glunt_t_bits_Const
#include "lowlevel.h"

/* There is no overlapping if:
 *	--- xp + xn <= yp
 *	or
 *	--- yp + yn <= xp
 *
 *	There is overlapping if:
 *	--- xp + xn > yp
 *	and
 *	--- yp + yn > xp
 */

#define __overlapping_p__(xp,xn,  yp,yn) ( ( (xp) + (xn) > yp ) && ( (yp) + (yn) > (xp) ) )
#define __no_overlapping_p__(xp,xn,  yp,yn) ( ( (xp) + (xn) <= yp ) || ( (yp) + (yn) <= (xp) ) )

#ifdef __GNUC__
#define __clz__(cnt, x) \
if(sizeof(glunt_t) == sizeof(char)){\
	const unsigned int __x = (x);\
	(cnt) = __builtin_clz(__x) - (sizeof(int)-sizeof(char))*CHAR_BIT;\
} else if(sizeof(glunt_t) == sizeof(short)){\
	const unsigned int __x = (x);\
	(cnt) = __builtin_clz(__x) - (sizeof(int)-sizeof(short))*CHAR_BIT;\
} else if(sizeof(glunt_t) == sizeof(int)){\
	const unsigned int __x = (x);\
	(cnt) = __builtin_clz(__x);\
} else if(sizeof(glunt_t) == sizeof(long)){\
	const unsigned long __x = (x);\
	(cnt) = __builtin_clzl(__x);\
} else if(sizeof(glunt_t) == sizeof(long long)){\
	const unsigned long long __x = (x);\
	(cnt) = __builtin_clzll(__x);\
}

#define __ctz__(cnt, x) \
if(sizeof(glunt_t) == sizeof(char)){\
	const unsigned int __x = (x);\
	(cnt) = __builtin_ctz(__x);\
} else if(sizeof(glunt_t) == sizeof(short)){\
	const unsigned int __x = (x);\
	(cnt) = __builtin_ctz(__x);\
} else if(sizeof(glunt_t) == sizeof(int)){\
	const unsigned int __x = (x);\
	(cnt) = __builtin_ctz(__x);\
} else if(sizeof(glunt_t) == sizeof(long)){\
	const unsigned long __x = (x);\
	(cnt) = __builtin_ctzl(__x);\
} else if(sizeof(glunt_t) == sizeof(long long)){\
	const unsigned long long __x = (x);\
	(cnt) = __builtin_ctzll(__x);\
}
#else

#endif

#define __abs__(x) ((x) < 0 ? -(x):(x))

#include <stdio.h>
#include <stdlib.h>
static const volatile glunt_t __glunt_zero = 0;
#define __ASSERT__(x, func, line) \
	(void) ( !!(x) || ( fprintf(stderr, "Assert failed [glunt.c, %s, %d]: %s\n", func, line, #x), abort(), 0 ) )
#ifndef GLUNT_NDEBUG
#define __assert__(x) __ASSERT__ (x, __FUNCTION__, __LINE__)
#else
#define __assert__(x) ((void) 0)
#endif

void glunt_copy(glunt_ptr dp, glunt_srcptr sp, glize_t n)
{
	glunt_copy_i(dp, sp, sp+n);
}

void glunt_copy_i(glunt_ptr dp, glunt_srcptr sp, glunt_srcptr const sp_limit)
{
	__assert__ (sp < sp_limit);
	__assert__ (dp <= sp || __no_overlapping_p__ (dp, sp_limit - sp, sp, sp_limit - sp));

	for(; sp < sp_limit; dp++, sp++)
		*dp = *sp;
}

void glunt_copy_d(glunt_ptr dp_msd, glunt_srcptr const sp, glunt_srcptr sp_msd)
{
	__assert__ (sp <= sp_msd);
	__assert__ (dp_msd >= sp_msd || __no_overlapping_p__ (dp_msd, sp_msd - sp + 1, sp, sp_msd - sp + 1));

	for(; sp <= sp_msd; dp_msd--, sp_msd--)
		*dp_msd = *sp_msd;
}

void glunt_zero_out(glunt_ptr dp, glunt_srcptr const dp_limit)
{
	__assert__ (dp < dp_limit);

	for(; dp < dp_limit; dp++)
		*dp = __glunt_zero;
}

glize_t glunt_size_normalize(glunt_srcptr xp_msd, glize_t n)
{
	__assert__ (n);

	for(; n > 1U && *xp_msd-- == 0; n--)
		/* do nothing !!! */;

	return n;
}

glunt_t glunt_add_1(glunt_ptr sp, glunt_srcptr xp, glize_t n, glunt_t y)
{
	__assert__ (n);
	__assert__ (xp >= sp || __no_overlapping_p__ (xp, n, sp, n));

	glunt_t carry;
	glunt_srcptr const xp_limit = xp + n;

	__add_Func (carry, sp[0], xp[0], y);

	sp++;
	xp++;

	for(; carry && xp != xp_limit; sp++, xp++){
		__add_Func (carry, sp[0], xp[0], carry);
	}

	glunt_copy_i(sp, xp, xp_limit);

	return carry;
}

glunt_t glunt_add_n(glunt_ptr sp, glunt_srcptr xp, glunt_srcptr yp, glize_t n)
{
	__assert__ (n);
	__assert__ (xp >= sp || __no_overlapping_p__ (xp, n, sp, n));
	__assert__ (yp >= sp || __no_overlapping_p__ (yp, n, sp, n));

	glunt_t carry;
	glunt_srcptr const xp_limit = xp + n;

	__add_Func (carry, sp[0], xp[0], yp[0]);

	sp++;
	xp++;
	yp++;

	for(; xp != xp_limit; sp++, xp++, yp++){
		__addc_Func (carry, sp[0], xp[0], yp[0], carry);
	}

	return carry;
}

glunt_t glunt_add(glunt_ptr sp, glunt_srcptr xp, glize_t xn, glunt_srcptr yp, glize_t yn)
{
	__assert__ (xn >= yn);
	__assert__ (yn >= 1U);

	glunt_t carry = glunt_add_n(sp, xp, yp, yn);

	if(xn > yn)
		carry = glunt_add_1(sp + yn, xp + yn, xn - yn, carry);

	return carry;
}

glunt_t glunt_sub_1(glunt_ptr dp, glunt_srcptr xp, glize_t n, glunt_t y)
{
	__assert__ (n);
	__assert__ (xp >= dp || __no_overlapping_p__ (xp, n, dp, n));

	glunt_t carry;
	glunt_srcptr const xp_limit = xp + n;

	__sub_Func (carry, dp[0], xp[0], y);

	dp++;
	xp++;

	for(; carry && xp != xp_limit; dp++, xp++){
		__sub_Func (carry, dp[0], xp[0], carry);
	}

	glunt_copy_i(dp, xp, xp_limit);

	return carry;
}

glunt_t glunt_sub_n(glunt_ptr dp, glunt_srcptr xp, glunt_srcptr yp, glize_t n)
{
	__assert__ (n);
	__assert__ (xp >= dp || __no_overlapping_p__ (xp, n, dp, n));
	__assert__ (yp >= dp || __no_overlapping_p__ (yp, n, dp, n));

	glunt_t carry;
	glunt_srcptr const xp_limit = xp + n;

	__sub_Func (carry, dp[0], xp[0], yp[0]);
	printf("Carry: %u; %lu - %lu\n", carry, xp[0], yp[0]);/// erase
	dp++;
	xp++;
	yp++;

	for(; xp != xp_limit; dp++, xp++, yp++){
		__subc_Func (carry, dp[0], xp[0], yp[0], carry);
		printf("Carry: %u\n", carry);/// erase
	}

	return carry;
}

glunt_t glunt_sub(glunt_ptr dp, glunt_srcptr xp, glize_t xn, glunt_srcptr yp, glize_t yn)
{
	__assert__ (xn >= yn);
	__assert__ (yn >= 1U);

	glunt_t carry = glunt_sub_n(dp, xp, yp, yn);

	if(xn > yn)
		carry = glunt_sub_1(dp + yn, xp + yn, xn - yn, carry);

	return carry;
}

glunt_t glunt_mul_1(glunt_ptr pp, glunt_srcptr xp, glize_t n, glunt_t y)
{
	__assert__ (n);
	__assert__ (xp >= pp || __no_overlapping_p__ (xp, n, pp, n));

	glunt_t carry;
	glunt_srcptr const xp_limit = xp + n;

	__mul_Func (carry, pp[0], xp[0], y);

	pp++;
	xp++;

	for(; xp != xp_limit; pp++, xp++){
		__add_mul_Func (carry, pp[0], carry, xp[0], y);
	}

	return carry;
}

glunt_t glunt_addmul_1(glunt_ptr sp, glunt_srcptr xp, glize_t n, glunt_t y)
{
	__assert__ (n);
	__assert__ (xp >= sp || __no_overlapping_p__ (xp, n, sp, n));

	glunt_t carry;
	glunt_srcptr const xp_limit = xp + n;

	__add_mul_Func (carry, sp[0], sp[0], xp[0], y);

	sp++;
	xp++;

	for(; xp != xp_limit; sp++, xp++){
		__add_add_mul_Func (carry, sp[0], sp[0], carry, xp[0], y);
	}

	return carry;
}

glunt_t glunt_submul_1(glunt_ptr dp, glunt_srcptr xp, glize_t n, glunt_t y)
{
	__assert__ (n);
	__assert__ (xp >= dp || __no_overlapping_p__ (xp, n, dp, n));

	glunt_t carry;
	glunt_srcptr const xp_limit = xp + n;

	__sub_mul_Func (carry, dp[0], dp[0], xp[0], y);

	dp++;
	xp++;

	for(; xp != xp_limit; dp++, xp++){
		__sub_sub_mul_Func (carry, dp[0], dp[0], carry, xp[0], y);
	}

	return carry;
}

void glunt_mul(glunt_ptr pp, glunt_srcptr xp, glize_t xn, glunt_srcptr yp, glize_t yn)
{
	__assert__ (xn);
	__assert__ (yn);
	__assert__ (__no_overlapping_p__ (xp, xn, pp, xn+yn));
	__assert__ (__no_overlapping_p__ (yp, yn, pp, xn+yn));

	glunt_srcptr const yp_limit = yp + yn;

	pp[xn] = glunt_mul_1(pp, xp, xn, yp[0]);

	pp++;
	yp++;

	for(; yp != yp_limit; pp++, yp++){
		pp[xn] = glunt_addmul_1(pp, xp, xn, yp[0]);
	}
}

void glunt_mul_n(glunt_ptr pp, glunt_srcptr xp, glunt_srcptr yp, glize_t n)
{
	glunt_mul(pp, xp, n, yp, n);
}

void glunt_sqr(glunt_ptr sp, glunt_srcptr xp, glize_t n)
{
	__assert__ (n);
	__assert__ (__no_overlapping_p__ (xp, n, sp, n << 1));

	glunt_t carry;
	glunt_ptr const sp_copy = sp;
	glunt_srcptr const xp_copy = xp;
	glunt_srcptr const xp_limit = xp+n;

	sp = & sp_copy[1];

	/* Initilize */
	{
		carry = 0;
		const glunt_t y = xp[0];

		for(; ++xp < xp_limit; sp++){
			__add_mul_Func (carry, sp[0], carry, xp[0], y);
		}

		*sp = carry;

		/* PARAM modified: xp, sp */
	}

	xp = & xp_copy[1];

	/* Multiply unequal index */
	{
		for(glunt_ptr sp_idx = & sp_copy[3]; xp < xp_limit-1; xp++, sp_idx += 2){
			carry = 0;
			sp = sp_idx;
			const glunt_t x = xp[0];

			for(glunt_srcptr yp = xp+1; yp < xp_limit; sp++, yp++){
				__add_add_mul_Func (carry, sp[0], sp[0], carry, yp[0], x);
			}

			*sp = carry;

			/* PARAM modified: xp, sp */
		}
	}

	/* Multiply by 2 */
	{
		carry = 0;
		glunt_srcptr const sp_upper_bound = sp;
		sp = & sp_copy[1];

		for(; sp <= sp_upper_bound; sp++){
			__add_mulby2_Func (carry, sp[0], carry, sp[0]);
		}

		*sp = carry;

		/* PARAM modified: sp */
	}

	sp = sp_copy;
	xp = xp_copy;

	/* Square equal index */
	{
		carry = 0;
		sp[0] = 0;

		for(; xp < xp_limit; xp++){
			__add_add_sqr_Func (carry, sp[0], sp[0], carry, xp[0]);
			sp++;
			__add_Func (carry, sp[0], sp[0], carry);
			sp++;
		}
	}
}

glunt_t glunt_divqr_1(glunt_ptr qp, glunt_srcptr xp, glize_t n, glunt_t y)
{
	__assert__ (n);
	__assert__ (y);
	__assert__ (__no_overlapping_p__ (xp, n, qp, n));

	glunt_srcptr rp = xp + n - 1;

	for(; xp <= rp; rp--){

	}
}

void glunt_divqr(glunt_ptr qp, glunt_ptr rp, glize_t rn, glunt_srcptr yp, glize_t yn)
{
	__assert__ (rn >= yn);
	__assert__ (yn >= 1U);
	__assert__ ("BUG: DIVISION BY ZERO OR LEADING ZERO !!!" && *(yp+yn-1));
	__assert__ (__no_overlapping_p__ (rp, rn, yp, yn));
	__assert__ (__no_overlapping_p__ (rp, rn, qp, rn-yn+1));
	__assert__ (__no_overlapping_p__ (yp, yn, qp, rn-yn+1));

	if(	(yn == 1U) && (sizeof(glunt_t) * 2 <= sizeof(unsigned long long)) ){
		*rp = glunt_divqr_1(qp, rp, rn, *yp);
		return;
	}

}

glunt_t glunt_divr_1(glunt_srcptr xp, glize_t n, glunt_t y)
{
	__assert__ (n);
	__assert__ (y);
}

void glunt_divr(glunt_ptr rp, glize_t rn, glunt_srcptr yp, glize_t yn)
{
	__assert__ (rn >= yn);
	__assert__ (yn >= 1U);
	__assert__ ("BUG: DIVISION BY ZERO OR LEADING ZERO !!!" && *(yp+yn-1));
	__assert__ (__no_overlapping_p__ (rp, rn, yp, yn));

	if(	(yn == 1U) && (sizeof(glunt_t) * 2 <= sizeof(unsigned long long)) ){
		*rp = glunt_divr_1(rp, rn, *yp);
		return;
	}
}

void glunt_addr(glunt_ptr rp, glunt_srcptr xp, glize_t xn, glunt_srcptr yp, glize_t yn, glunt_srcptr mp, glize_t mn)
{

}

void glunt_subr(glunt_ptr rp, glunt_srcptr xp, glize_t xn, glunt_srcptr yp, glize_t yn, glunt_srcptr mp, glize_t mn)
{

}

void glunt_mulr(glunt_ptr rp, glunt_srcptr xp, glize_t xn, glunt_srcptr yp, glize_t yn, glunt_srcptr mp, glize_t mn)
{

}

void glunt_sqrr(glunt_ptr rp, glunt_srcptr xp, glize_t xn, glunt_srcptr mp, glize_t mn)
{

}

void glunt_expr_1(glunt_ptr rp, glunt_t x, glunt_srcptr yp, glize_t yn, glunt_srcptr mp, glize_t mn)
{

}

void glunt_powr_1(glunt_ptr rp, glunt_srcptr xp, glize_t xn, glunt_t y, glunt_srcptr mp, glize_t mn)
{

}

void glunt_powr(glunt_ptr rp, glunt_srcptr xp, glize_t xn, glunt_srcptr yp, glize_t yn, glunt_srcptr mp, glize_t mn)
{

}

int glunt_equr(glunt_srcptr xp, glize_t xn, glunt_srcptr yp, glize_t yn, glunt_srcptr mp, glize_t mn)
{

}

/* Multiply by 2^bit_cnt */
glunt_t glunt_shl(glunt_ptr dp, glunt_srcptr xp, glize_t n, unsigned long bit_cnt)
{
	__assert__ (n);
	__assert__ (bit_cnt > 0U);
	__assert__ (bit_cnt < __glunt_t_bits_Const);
	__assert__ (dp >= xp || __no_overlapping_p__ (xp, n, dp, n));

	const unsigned long shr = __glunt_t_bits_Const - bit_cnt;
	glunt_srcptr const xp_0 = xp;
	xp += n - 1; /* most significant digits */
	dp += n - 1;

	glunt_t lw  = *xp--;
	glunt_t hw  = lw << bit_cnt;
	const glunt_t ret = lw >> shr;

	for(; xp_0 < xp; dp--, xp--){
		lw = *xp;
		*dp = hw | (lw >> shr);
		hw = lw << bit_cnt;
	}

	*dp = hw;

	return ret;
}

/* Divide by 2^bit_cnt */
glunt_t glunt_shr(glunt_ptr dp, glunt_srcptr xp, glize_t n, unsigned long bit_cnt)
{
	__assert__ (n);
	__assert__ (bit_cnt > 0U);
	__assert__ (bit_cnt < __glunt_t_bits_Const);
	__assert__ (dp <= xp || __no_overlapping_p__ (xp, n, dp, n));

	const unsigned long shl = __glunt_t_bits_Const - bit_cnt;
	glunt_srcptr const xp_msd = xp + n - 1;

	glunt_t hw = *xp++;
	glunt_t lw = hw >> bit_cnt;
	const glunt_t ret = hw << shl;

	for(; xp < xp_msd; dp++, xp++){
		hw = *xp;
		*dp = lw || (hw << shl);
		lw = hw >> bit_cnt;
	}

	*dp = lw;

	return ret;
}

glunt_t glunt_shift(glunt_ptr dp, glunt_srcptr xp, glize_t n, signed long bit_cnt)
{
	if(0L < bit_cnt){ /* Multiply by 2^bit_cnt*/
		return glunt_shl(dp, xp, n, __abs__ (bit_cnt));
	} else if(0L > bit_cnt){ /* Divide by 2^bit_cnt*/
		return glunt_shr(dp, xp, n, __abs__ (bit_cnt));
	} else {
		return (glunt_copy(dp, xp, n), 0);
	}
}

void glunt_and_n(glunt_ptr ap, glunt_srcptr xp, glunt_srcptr yp, glize_t n)
{
	__assert__ (n);
	__assert__ (ap <= xp || __no_overlapping_p__ (ap, n, xp, n));
	__assert__ (ap <= yp || __no_overlapping_p__ (ap, n, yp, n));

	glunt_srcptr const xp_limit = xp + n;

	for(; xp != xp_limit; ap++, xp++){
		*ap = *xp & *yp;
	}
}

void glunt_ior_n(glunt_ptr op, glunt_srcptr xp, glunt_srcptr yp, glize_t n)
{
	__assert__ (n);
	__assert__ (op <= xp || __no_overlapping_p__ (op, n, xp, n));
	__assert__ (op <= yp || __no_overlapping_p__ (op, n, yp, n));

	glunt_srcptr const xp_limit = xp + n;

	for(; xp != xp_limit; op++, xp++){
		*op = *xp | *yp;
	}
}

void glunt_xor_n(glunt_ptr op, glunt_srcptr xp, glunt_srcptr yp, glize_t n)
{
	__assert__ (n);
	__assert__ (op <= xp || __no_overlapping_p__ (op, n, xp, n));
	__assert__ (op <= yp || __no_overlapping_p__ (op, n, yp, n));

	glunt_srcptr const xp_limit = xp + n;

	for(; xp != xp_limit; op++, xp++){
		*op = *xp ^ *yp;
	}
}

void glunt_com(glunt_ptr cp, glunt_srcptr xp, glize_t n)
{
	__assert__ (n);
	__assert__ (cp <= xp || __no_overlapping_p__ (cp, n, xp, n));

	glunt_srcptr const xp_limit = xp + n;

	for(; xp < xp_limit; cp++, xp++){
		*cp = ~*xp;
	}
}

void glunt_neg(glunt_ptr np, glunt_srcptr xp, glize_t n)
{
	__assert__ (n);
	__assert__ (np <= xp || __no_overlapping_p__ (np, n, xp, n));

	glunt_srcptr const xp_msd = xp + n - 1;

	for(; xp < xp_msd && *xp == 0; np++, xp++){
		*np = 0;
	}

	*np = -*xp;

	np++;
	xp++;

	for(; xp <= xp_msd; np++, xp++){
		*np = ~*xp;
	}
}

/* ret (1): if bit at pos was already set; (0): if bit at pos was not set */
int glunt_setbit(glunt_ptr xp, glize_t n, unsigned long bit_pos)
{
	__assert__ (n);

 	int ret = 0;
	const glize_t words = bit_pos / __glunt_t_bits_Const;
	bit_pos = bit_pos % __glunt_t_bits_Const;
	const glunt_t mask = (glunt_t) 1 << bit_pos;

	if(words >= n)
		glunt_zero_out(xp+n-1, xp+n+words);

	if(xp[words] & mask){
		ret = 1;
	}

	xp[words] |= mask;

	return ret;
}

/* ret (1): if bit is set; (0) otherwise */
int glunt_toggle(glunt_ptr xp, glize_t n, unsigned long bit_pos)
{
	__assert__ (n);

	int ret = 0;
	const glize_t words = bit_pos / __glunt_t_bits_Const;
	bit_pos = bit_pos % __glunt_t_bits_Const;
	const glunt_t mask = (glunt_t) 1 << bit_pos;

	if(words >= n)
		glunt_zero_out(xp+n-1, xp+n+words);

	xp[words] ^= mask;

	if(xp[words] & mask){
		ret = 1;
	}

	return ret;
}

/* ret (1): if bit at pos is set; (0): otherwise */
int glunt_testbit(glunt_srcptr xp, glize_t n, unsigned long bit_pos)
{
	__assert__ (n);

	int ret = 0;
	const glize_t words = bit_pos / __glunt_t_bits_Const;
	bit_pos = bit_pos % __glunt_t_bits_Const;
	const glunt_t mask = (glunt_t) 1 << bit_pos;

	if(words < n){
		if(xp[words] & mask){
			ret = 1;
		}
	}

	return ret;
}

/* ret (1): if bit at pos was set before deletion; (0): otherwise */
int glunt_clearbit(glunt_ptr xp, glize_t n, unsigned long bit_pos)
{
	__assert__ (n);

	int ret = 0;
	const glize_t words = bit_pos / __glunt_t_bits_Const;
	bit_pos = bit_pos % __glunt_t_bits_Const;
	const glunt_t mask = (glunt_t) 1 << bit_pos;

	if(words < n){
		if(xp[words] & mask){
			ret = 1;
		}
		xp[words] &= (~mask);
	}

	return ret;
}

unsigned long glunt_bitsize(glunt_srcptr xp, glize_t n)
{
	__assert__ (n);

	unsigned long clz;

	__clz__ (clz, xp[--n]);

	n += __glunt_t_bits_Const - clz;

	return n + (n == 0U);
}

glize_t glunt_size(unsigned long bit_cnt)
{
	return bit_cnt / __glunt_t_bits_Const + (0UL < (bit_cnt % __glunt_t_bits_Const));
}

int glunt_cmp_1(glunt_srcptr xp, glize_t n, glunt_t y)
{
	__assert__ (n);
	__assert__ (glunt_size_normalize(xp+n-1, n) == n);

	return (n > 1U)? 1:( (*xp > y)? 1:( (*xp < y)? -1:0 ) );
}

int glunt_cmp_n(glunt_srcptr xp, glunt_srcptr yp, glize_t n)
{
	__assert__ (n);
	__assert__ ( (n == glunt_size_normalize(xp+n-1, n)) && (n == glunt_size_normalize(yp+n-1, n)) );

	glunt_srcptr xp_msd = xp + n - 1;
	glunt_srcptr yp_msd = yp + n - 1;

	for(; xp <= xp_msd; xp_msd--, yp_msd--){
		if(*xp_msd != *yp_msd)
			return *xp_msd > *yp_msd ? 1:-1;
	}

	return 0;
}

int glunt_equ_1(glunt_srcptr xp, glize_t n, glunt_t y)
{
	__assert__ (n);
	__assert__ (glunt_size_normalize(xp+n-1, n) == n);

	return (n == 1U && *xp == y);
}

int glunt_equ_n(glunt_srcptr xp, glunt_srcptr yp, glize_t n)
{
	__assert__ (n);
	__assert__ ( (n == glunt_size_normalize(xp+n-1, n)) && (n == glunt_size_normalize(yp+n-1, n)) );

	glunt_srcptr const xp_limit = xp + n;

	for(; xp != xp_limit; xp++, yp++){
		if(*xp != *yp)
			return 0;
	}

	return 1;
}

size_t glunt_size_in_base(glunt_srcptr xp, glize_t n, int base)
{

}

size_t glunt_get_s(unsigned char * sp, int base, glunt_srcptr xp, glize_t xn)
{

}

glize_t glunt_set_s(glunt_srcptr xp, const unsigned char * sp, size_t sn, int base)
{

}

void glunt_random(glunt_ptr rp, glize_t n)
{

}

void glunt_random_bits(glunt_ptr rp, glize_t n)
{

}

glunt_t glunt_gcd_1(glunt_srcptr xp, glize_t n, glunt_t y)
{

}

glize_t glunt_gcd(glunt_ptr dp, glunt_srcptr xp, glize_t xn, glunt_srcptr yp, glize_t yn)
{

}

glunt_t glunt_lcm_1(glunt_srcptr xp, glize_t n, glunt_t y)
{

}

glize_t glunt_lcm(glunt_ptr dp, glunt_srcptr xp, glize_t xn, glunt_srcptr yp, glize_t yn)
{

}

void glunt_dump(glunt_srcptr xp, glize_t n)
{
	__assert__ (n);
	glunt_srcptr const xp_limit = xp + n;

	fprintf(stderr, "\nPtr: %p, Size: %lu\n>>>\n", xp, n);

	for(; xp < xp_limit; xp++){
		fprintf(stderr, "%llu\n", *xp);
	}

	fprintf(stderr, "<<<\n");
}

/* MPN */

static void mpn_malloc(mpn_ptr wp, glize_t n)
{
	__assert__ (n);
	wp->_alloc = n;
	wp->_u =  malloc(sizeof(glunt_t) * wp->_alloc);
}

static glunt_ptr mpn_realloc(mpn_ptr wp, glize_t n)
{
	__assert__ (n);
	wp->_alloc = n;
	return wp->_u = realloc(wp->_u, sizeof(glunt_t) * wp->_alloc);
}

static void mpn_free(mpn_ptr wp)
{
	__assert__ (wp->_u);
	free(wp->_u);
}

#define __mpn_realloc__(wp, n) ((n) > (wp)->_alloc ? mpn_realloc(wp, n) : (wp)->_u)

void mpn_init(mpn_ptr wp)
{
	wp->_size = 0;
	wp->_alloc = 2;
	mpn_malloc(wp, 2);
}

void mpn_init_n(mpn_ptr wp, unsigned long n)
{
	__assert__ (n);

	wp->_size = 0;
	wp->_alloc = n;
	mpn_malloc(wp, n);
}

void mpn_init_bits(mpn_ptr wp, unsigned long bits)
{
	mpn_init_n(wp, glunt_size(bits));
}

void mpn_clear(mpn_ptr wp)
{
	mpn_free(wp);
}

void mpn_set_ull(mpn_ptr wp, unsigned long long x)
{
	wp->_u[0] = (glunt_t) x;
	wp->_u[1] = x = (glunt_t) (x >> __glunt_t_bits_Const);

	if(x){
		wp->_size = 2;
	} else {
		wp->_size = 1;
	}
}

void mpn_set(mpn_ptr dp, mpn_srcptr sp)
{
	const glize_t n = sp->_size;
	glunt_copy(__mpn_realloc__ (dp, n), sp->_u, n);
	dp->_size  = n;
}

void mpn_add(mpn_ptr sp, mpn_srcptr xp, mpn_srcptr yp)
{
	if(xp->_size >= yp->_size){
		__mpn_realloc__ (sp, xp->_size + 1);
		sp->_size = xp->_size + ( 0U < (sp->_u[xp->_size] = glunt_add(sp->_u, xp->_u, xp->_size, yp->_u, yp->_size)));
	} else {
		__mpn_realloc__ (sp, yp->_size + 1);
		sp->_size = yp->_size + ( 0U < (sp->_u[yp->_size] = glunt_add(sp->_u, yp->_u, yp->_size, xp->_u, xp->_size)));
	}
}

glunt_t mpn_sub(mpn_ptr dp, mpn_srcptr xp, mpn_srcptr yp)
{
	if(xp->_size >= yp->_size){
		__mpn_realloc__ (dp, xp->_size + 1); /* +1 in case you write borrow */
		dp->_size = xp->_size;
		return (0U < glunt_sub(dp->_u, xp->_u, xp->_size, yp->_u, yp->_size));
	} else {
		__mpn_realloc__ (dp, yp->_size + 1); /* +1 in case you write borrow */
		glunt_t carry = glunt_sub_n(dp->_u, xp->_u, yp->_u, xp->_size);
		glunt_ptr i = yp->_u + xp->_size;
		glunt_srcptr const ilim = i + (yp->_size - xp->_size);
		glunt_ptr j = dp->_u + xp->_size;
		if(carry){
			for(;i < ilim; i++, j++){
				*j = -(++*i);
			}
		} else{
			for(;(i < ilim) && (*i == 0); i++, j++){
				*j = 0U;
			}
			for(;i < ilim; i++, j++){
				*j = -(++*i);
			}
		}
		dp->_size = yp->_size;
		return 1U;
	}
}

void mpn_mul(mpn_ptr pp, mpn_srcptr xp, mpn_srcptr yp)
{
	__mpn_realloc__ (pp, xp->_size + yp->_size);
	glunt_mul(pp->_u, xp->_u, xp->_size, yp->_u, yp->_size);
}
