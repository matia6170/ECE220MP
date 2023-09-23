#include <stdio.h>

int is_prime(int number) {
    int i;
    if (number == 1) {
        return 0;
    } else if (number == 2) {
        return 1;
    }
    for (i = 2; i < number; i++) {  // for each number smaller than it
        if (number % i == 0) {      // check if the remainder is 0
            return 0;
        }
    }
    return 1;
}
int print_semiprimes(int a, int b) {
    int i, j, k;
    int ret = 0;
    int prevJ = 0;
    for (i = a; i <= b; i++) {  // for each item in interval
        // check if semiprime
        for (j = 2; j <= i; j++) {
            if (i % j == 0) {
                if (is_prime(j)) {
                    k = i / j;
                    if (is_prime(k) && prevJ != k) {
                        prevJ = j;
                        printf("%d ", i);
                    }
                }
            }
        }
    }
    printf("\n");
    return ret;
}
int main() {
    int in;
    // scanf("%d", &in);

    print_semiprimes(30, 40);

        return 1;
}