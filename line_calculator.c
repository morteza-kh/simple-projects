/* in the name of Allah */

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void const *memdup(void const *, size_t, size_t);
long long get_digit(char const **);
long long next_opd(char const **);
long long calculate(char const **);

#define is_opr(c) (c == '+' || c == '-' || c == '*' || c == '/')

#define __skip(ptr, cond)                                                                                      \
	do {                                                                                                     \
		for (; cond(*(ptr)); (ptr)++)                                                                        \
			;                                                                                                \
	} while (0)

#define skip_white(ptr) __skip(ptr, isspace)

#define skip_digit(ptr) __skip(ptr, isdigit)

#define ptr_advance(ptr) ++(ptr)

#define next(ptr) (*(ptr_advance(*ptr) - 1))

#define str_dup(data, length) (char const *)memdup((char const *)data, length, sizeof(char))

void const *memdup(void const *data, size_t size, size_t size_of) {
	void *dptr = calloc(size, sizeof(size_of));
	assert(dptr != NULL);

	return memcpy(dptr, data, size * size_of);
}

long long get_digit(char const **sptr) {
	char const *dummy = *sptr;
	skip_digit(*sptr);
	char const *dptr = str_dup(dummy, *sptr - dummy);
	long long digit = atoll(dptr);

	return free((char *)dptr), digit;
}

long long calculate(char const **sptr) {
	long long opd = 0;

	if (**sptr == ')') {
		return opd;
	}
	if (**sptr != 0) {
		opd = next_opd(sptr);
		skip_white(*sptr);

		if (is_opr(**sptr)) {
			int opr = next(sptr);
			switch (opr) {
				case '*': return opd * next_opd(sptr);
				case '/': {
					long long op2 = next_opd(sptr);
					assert(op2 != 0);
					return opd / op2;
				}
				case '+': return opd + calculate(sptr);
				case '-': return opd - calculate(sptr);
			}
		}
		return opd + calculate(sptr);
	}
	return opd;
}

long long next_opd(char const **sptr) {
	long long opd = 0;

	skip_white(*sptr);
	if (isdigit(**sptr)) {
		opd = get_digit(sptr);
	}
	else if (**sptr == '(') {
		(void)(next(sptr));
		opd = calculate(sptr);
		skip_white(*sptr);
		assert(next(sptr) == ')');
	}
	return opd;
}

int main() {
	char const *testexpr = str_dup("13+5*(((8+9)*(4*6))+7)", 22);
	char line[1024];
	
	assert(calculate(&testexpr) == 2088LL);
	
	while (fgets(line, 1024, stdin)) {
		char const *lineptr = str_dup(line, strlen(line));
		printf("result: %lld\n", calculate(&lineptr));
	}
}
