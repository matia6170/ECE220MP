/*
 *
 * Partners: hyunwoo6,
 * the is_prime() function had a bug where it would not return 1 if 2 was put as
 * an argument for the function. We fixed the issue by adding a specific test
 * case just for 2. We also swapped 1 and 0.
 * 
 * the print_semi
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number) {
    int i;
    if (number == 1) {
        return 0;
    } else if (number == 2) {  // we added this line that checks if the number is 2
        return 1; // then return 1
    }                               
    for (i = 2; i < number; i++) {  // for each number smaller than it
        if (number % i == 0) {      // check if the remainder is 0
            return 0;
        }
    }
    return 1;
}

/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b) {
    int i, j, k;
    int ret = 0;

    for (i = a; i <= b; i++) {  // for each item in interval
        // check if semiprime
        for (j = 2; j <= i; j++) {
            if (i % j == 0) {
                if (is_prime(j)) {
                    k = i / j; //divide i by j so that k can be used to check k is a prime.
                    if (is_prime(k)) {
                        printf("%d ", i);
                        ret = 1; // sets ret to 1 so that the function returns 1 when there is a semiprime
                        break; // break so that there is no duplicaiton prints of the same number.
                    }
                }
            }
        }
    }
    printf("\n");
    return ret; // returns 0 when there is no semiprime
}
