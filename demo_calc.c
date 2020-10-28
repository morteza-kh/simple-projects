/* in the name of Allah */

#include <assert.h>
#include <stdio.h>
#include "line_calculator.h"

int main() {
	char const expr[] = "13 + 5 * (((8 + 9) * (4 * 6)) + 7)";

	// assert(calculate(expr) == 2088LL);
	fprintf(stderr, "%lld\n", calculate(expr));

	return 0;
}
