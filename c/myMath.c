#include "myMath.h"

int absoluteValueOf(int val) { return (val > 0) ? val : -val; }

// calculate x^n
long powerOf(int x, int n) {
	int xOrig = x;

	if (n == 0)
		return x = 1;

	while (--n > 0) {
		x *= xOrig;
	}

	return x;
}
