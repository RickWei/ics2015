#include "trap.h"

#define N 100

int a[N] = {81, 37, 64, 23, 38, 65, 56, 15, 8, 33, 85, 39, 71, 12, 77, 6, 82, 89, 80, 35, 0, 59, 73, 4, 61, 30, 74, 69, 13, 42, 68, 63, 9, 29, 47, 36, 99, 25, 21, 14, 60, 3, 2, 18, 26, 83, 53, 5, 43, 67, 88, 70, 76, 92, 94, 48, 34, 49, 66, 95, 78, 62, 32, 52, 16, 72, 27, 28, 22, 40, 84, 91, 96, 57, 87, 51, 98, 1, 10, 11, 24, 20, 19, 31, 7, 97, 50, 86, 79, 17, 75, 55, 93, 44, 58, 54, 45, 41, 90, 46};

void bubble_sort() {
	int i, j, t;
	for(j = 0; j < N; j ++) {
		for(i = 0; i < N - 1 - j; i ++) {
			if(a[i] > a[i + 1]) {
				t = a[i];
				a[i] = a[i + 1];
				a[i + 1] = t;
			}
		}
	}

}

int main() {
	bubble_sort();
	int i;
	for(i = 0; i < N; i ++) {
		nemu_assert(a[i] == i);
	}

	nemu_assert(i == N);

	bubble_sort();

	for(i = 0; i < N; i ++) {
		nemu_assert(a[i] == i);
	}

	nemu_assert(i == N);

	HIT_GOOD_TRAP;

	return 0;
}
