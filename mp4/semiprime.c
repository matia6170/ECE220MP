#include <stdlib.h>
#include <stdio.h>
/*
 * Partners: crjung2,hyunwoo6,awinick2
 * is_prime had a bug where it couldn't check 2 since number starts at 2
 * and if statement checks if i<number.
 * Added a new if case where number == 2.
 * Also had a problem where it returns 0 when it is a prime and 1 when it isn't.
 * Swapped the 0 and 1.
 *
 * print_semiprime had k=i%j which is the wrong operation to check the other divisor
 * Must use div / to check the other divisor of the number
 * Return value wasn't returning 1 when it found a semiprime
 * So once we found semiprime, we set ret = 1.
 * Also the for loop to check semiprime of given i wasn't ending when we found a semiprime
 * thus printing duplication.
 * So we added a break after finding a semiprime.
*/

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    else if (number == 2) {return 1;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0; // Return 0 if not prime
        }
    }
    return 1; //Return 1 if prime
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;    //k is the other divisor
                    if (is_prime(k)) {
                        printf("%d ", i);
                        ret = 1; //Set return value to 1 if prime
                        break; //Break once sound semiprime
                    }
                }
            }
        }

    }
    //printf("return:%d",ret); Used to test return value
    printf("\n");
    return ret;

}