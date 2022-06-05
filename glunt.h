#ifndef __GLUNT_H__
#define __GLUNT_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GLUNT_H_MAJ  1
#define GLUNT_H_MIN  0

#define GLUNT_MAJ GLUNT_H_MAJ
#define GLUNT_MIN GLUNT_H_MIN
#define GLUNT_VER ((GLUNT_H_MAJ << 8) + GLUNT_H_MIN)

typedef unsigned long glunt_t;
typedef unsigned long glize_t; /* size type */

typedef glunt_t * glunt_ptr;
typedef const glunt_t * glunt_srcptr;

void glunt_copy(glunt_ptr, glunt_srcptr, glize_t);
void glunt_copy_i(glunt_ptr, glunt_srcptr, glunt_srcptr const);
void glunt_copy_d(glunt_ptr, glunt_srcptr const, glunt_srcptr);
void glunt_zero_out(glunt_ptr, glunt_srcptr const);

glunt_t glunt_add_1(glunt_ptr, glunt_srcptr, glize_t, glunt_t);
glunt_t glunt_add_n(glunt_ptr, glunt_srcptr, glunt_srcptr, glize_t);
glunt_t glunt_add(glunt_ptr, glunt_srcptr, glize_t, glunt_srcptr, glize_t);

glunt_t glunt_sub_1(glunt_ptr, glunt_srcptr, glize_t, glunt_t);
glunt_t glunt_sub_n(glunt_ptr, glunt_srcptr, glunt_srcptr, glize_t);
glunt_t glunt_sub(glunt_ptr, glunt_srcptr, glize_t, glunt_srcptr, glize_t);

glunt_t glunt_mul_1(glunt_ptr, glunt_srcptr, glize_t, glunt_t);
glunt_t glunt_addmul_1(glunt_ptr, glunt_srcptr, glize_t, glunt_t);
glunt_t glunt_submul_1(glunt_ptr, glunt_srcptr, glize_t, glunt_t);

void glunt_mul(glunt_ptr, glunt_srcptr, glize_t, glunt_srcptr, glize_t);
void glunt_mul_n(glunt_ptr, glunt_srcptr, glunt_srcptr, glize_t);
void glunt_sqr(glunt_ptr, glunt_srcptr, glize_t);

glunt_t glunt_divqr_1(glunt_ptr, glunt_srcptr, glize_t, glunt_t);
void glunt_divqr(glunt_ptr, glunt_ptr, glize_t, glunt_srcptr, glize_t);

glunt_t glunt_divr_1(glunt_srcptr, glize_t, glunt_t);
void glunt_divr(glunt_ptr, glize_t, glunt_srcptr, glize_t);

void glunt_addr(glunt_ptr, glunt_srcptr, glize_t, glunt_srcptr, glize_t, glunt_srcptr, glize_t);
void glunt_subr(glunt_ptr, glunt_srcptr, glize_t, glunt_srcptr, glize_t, glunt_srcptr, glize_t);
void glunt_mulr(glunt_ptr, glunt_srcptr, glize_t, glunt_srcptr, glize_t, glunt_srcptr, glize_t);
void glunt_sqrr(glunt_ptr, glunt_srcptr, glize_t, glunt_srcptr, glize_t);
void glunt_expr_1(glunt_ptr, glunt_t, glunt_srcptr, glize_t, glunt_srcptr, glize_t);
void glunt_powr_1(glunt_ptr, glunt_srcptr, glize_t, glunt_t, glunt_srcptr, glize_t);
void glunt_powr(glunt_ptr, glunt_srcptr, glize_t, glunt_srcptr, glize_t, glunt_srcptr, glize_t);
int glunt_equr(glunt_srcptr, glize_t, glunt_srcptr, glize_t, glunt_srcptr, glize_t);

glunt_t glunt_shl(glunt_ptr, glunt_srcptr, glize_t, unsigned long);
glunt_t glunt_shr(glunt_ptr, glunt_srcptr, glize_t, unsigned long);
glunt_t glunt_shift(glunt_ptr, glunt_srcptr, glize_t, signed long);

void glunt_and_n(glunt_ptr, glunt_srcptr, glunt_srcptr, glize_t);
void glunt_ior_n(glunt_ptr, glunt_srcptr, glunt_srcptr, glize_t);
void glunt_xor_n(glunt_ptr, glunt_srcptr, glunt_srcptr, glize_t);
void glunt_com(glunt_ptr, glunt_srcptr, glize_t);
void glunt_neg(glunt_ptr, glunt_srcptr, glize_t);

int glunt_setbit(glunt_ptr, glize_t, unsigned long); /* ret (1): if bit at pos was already set; (0): if bit at pos was not set */
int glunt_toggle(glunt_ptr, glize_t, unsigned long); /* ret (1): if bit is set; (0) otherwise */
int glunt_testbit(glunt_srcptr, glize_t, unsigned long); /* ret (1): if bit at pos is set; (0): otherwise */
int glunt_clearbit(glunt_ptr, glize_t, unsigned long); /* ret (1): if bit at pos was set before deletion; (0): otherwise */
unsigned long glunt_bitsize(glunt_srcptr, glize_t);
glize_t glunt_size(unsigned long);

int glunt_cmp_1(glunt_srcptr, glize_t, glunt_t);
int glunt_cmp_n(glunt_srcptr, glunt_srcptr, glize_t);

int glunt_equ_1(glunt_srcptr, glize_t, glunt_t);
int glunt_equ_n(glunt_srcptr, glunt_srcptr, glize_t);

size_t glunt_size_in_base(glunt_srcptr, glize_t, int);
size_t glunt_get_s(unsigned char *, int, glunt_srcptr, glize_t);
glize_t glunt_set_s(glunt_srcptr, const unsigned char *, size_t, int);

void glunt_random(glunt_ptr, glize_t);
void glunt_random_bits(glunt_ptr, glize_t);

glunt_t glunt_gcd_1(glunt_srcptr, glize_t, glunt_t);
glize_t glunt_gcd(glunt_ptr, glunt_srcptr, glize_t, glunt_srcptr, glize_t);

glunt_t glunt_lcm_1(glunt_srcptr, glize_t, glunt_t);
glize_t glunt_lcm(glunt_ptr, glunt_srcptr, glize_t, glunt_srcptr, glize_t);

void glunt_dump(glunt_srcptr, glize_t);

typedef struct {
	glunt_t *_u;
	glize_t  _size;
	glize_t  _alloc;
} __mpn_struct;

typedef __mpn_struct mpn_t[1];

typedef __mpn_struct *mpn_ptr;
typedef const __mpn_struct *mpn_srcptr;

void mpn_init(mpn_ptr);
void mpn_init_n(mpn_ptr, unsigned long);
void mpn_init_bits(mpn_ptr, unsigned long);
void mpn_clear(mpn_ptr);

void mpn_set_ull(mpn_ptr, unsigned long long);
void mpn_set(mpn_ptr, mpn_srcptr);

void mpn_add(mpn_ptr, mpn_srcptr, mpn_srcptr);
glunt_t mpn_sub(mpn_ptr, mpn_srcptr, mpn_srcptr);
void mpn_mul(mpn_ptr, mpn_srcptr, mpn_srcptr);

#ifdef __cplusplus
}
#endif

#endif
