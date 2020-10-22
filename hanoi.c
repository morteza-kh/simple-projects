/* in the name of Allah */

#include <stdio.h>

#define say(from, to)                                                                                        \
	do {                                                                                                     \
		printf("move from %c to %c\n", from, to);                                                            \
		fflush(stdout);                                                                                      \
	} while (0)

void move(int num, int from, int to, int tmp) {
	if (num == 1) {
		say(from, to);
	}
	else {
		move(num - 1, from, tmp, to);
		move(1, from, to, tmp);
		move(num - 1, tmp, to, from);
	}
}
