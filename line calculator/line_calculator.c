/* in the name of Allah */

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "line_calculator.h"

#define is_opr(c) (c == '+' || c == '-' || c == '*' || c == '/')
#define __skip(ptr, cond)                                                                                                        \
	do {                                                                                                                         \
		for (; cond(*(ptr)); (ptr)++)                                                                                            \
			;                                                                                                                    \
	} while (0)
#define skip_white(ptr)		  __skip(ptr, isspace)
#define skip_digit(ptr)		  __skip(ptr, isdigit)
#define ptr_advance(ptr)	  ++(ptr)
#define next(ptr)			  (*(ptr_advance(*ptr) - 1))
#define str_dup(data)		  (char const *)memdup((char const *)data, strlen(data), sizeof(char))
#define strndup(data, length) (char const *)memdup((char const *)data, length, sizeof(char))

static void const *memdup(void const *, size_t, size_t);
static long long getdigit(char const **);
static long long getoper(char const **);
static long long getresult(char const **);

static void const *memdup(void const *data, size_t size, size_t size_of) {
	void *dptr = calloc(size, sizeof(size_of));
	assert(dptr != NULL);

	return memcpy(dptr, data, size * size_of);
}

static long long getdigit(char const **sptr) {
	char const *dummy = *sptr;

	skip_digit(*sptr);

	char dptr[*sptr - dummy + 1];
	strncpy(dptr, dummy, *sptr - dummy);

	return atoll(dptr);
}

static long long getoper(char const **sptr) {
	long long opd = 0;

	if (isdigit(**sptr)) {
		opd = getdigit(sptr);
	} else if (**sptr == '(') {
		ptr_advance(*sptr);
		opd = getresult(sptr);
		assert(next(sptr) == ')');
	}
	return opd;
}

static long long getresult(char const **sptr) {
	long long opd = 0;

	if (**sptr == ')') { return opd; }
	if (**sptr != 0) {
		opd = getoper(sptr);
		if (is_opr(**sptr)) {
			int opr = next(sptr);

			switch (opr) {
				case '*': return opd * getoper(sptr);
				case '/': {
					long long op2 = getoper(sptr);
					assert(op2 != 0);
					return opd / op2;
				}
				case '+': return opd + getresult(sptr);
				case '-': return opd - getresult(sptr);
			}
		}
		return opd + getresult(sptr);
	}
	return opd;
}

static void rm_white(char const *str) {
	char *ptr = (char *)str;

	for (; *str; *ptr++ = *str++) {
		for (; isspace(*str); str++)
			;
	}
	*ptr = 0;
}

long long calculate(char const *str) {
	rm_white(str);
	return getresult(&str);
}
