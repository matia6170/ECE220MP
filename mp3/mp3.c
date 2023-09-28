/*
    ========================================
    MP3
    partners: awinick2, hyunwoo6, crjung2
    ========================================

    The program reads which line from the pascal triangle the user wants to see.
    Then the program iterates by the inputted number of times where it calls the nCr() function to print the next column of the given row.
    The nCr function uses the formula given from the mp3 assignment page.
    It calculates the denominator and the numerator seperately, and computes the final answer by returning (numerator/denominator).

*/
#include <stdio.h>
#include <stdlib.h>

//combinations function. calculates "n choose r" and returns it
unsigned long nCr(int n, int r) {
    unsigned long a = 1, b = 1; //a: neumerator, b:denominator
    //calculates "n choose r" based on the formula given on the mp3 assignment page.
    for (int i = 1; i < r + 1; i++) { //loop through the loop r times starting index from 1
        a *= (n + 1 - i);   //keep on multiplying (n+1-i) on to a, the neumerator
        b *= i;             //keep on multiplying (i) on to b, the denominator
    }
    return a / b; //returns a/b (the final calculated value)
}

int main() {
    int row; //initialize row 

    printf("Enter a row index: ");
    //reads the row index
    scanf("%d", &row);
    if (row < 0) {
	    printf("Input row must be greater than or equal to 0!!!");
	    return -1; //returns -1 if row index is less than 0
    }

    // Write your code here
    // iterates through the column of the given pascal's triangle row.
    for (int i = 0; i <= row; i++) printf("%lu ", nCr(row, i)); //prints each column of the given row

    return 0;
}
