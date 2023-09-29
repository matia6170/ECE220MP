/* ==============================
 * ============[MP5]=============
 * ==============================
 * 
 * =======[Group Memebers]=======
 * |||crjung2,hyunwoo6,awinick2|||
 * 
 * ==============================
 * We worked on the three functions that we were supposed to work on: set_seed, start_game, and make_guess.
 * In set_seed, we check if the user input for setting the seed is valid or not.
 * If valid, we set the seed and return 1. Else, we print an invalid seed mesesage and return 0.
 * In start_game, we used modulus to limit the random nuber between 0 an 7. Then we added 1 to make it 1 to 9.
 * Then we save eawch of the generated nubmer to each of the coresponding static solution variables so that we can access it later.
 * In make_guess, we check if input is valid. If invalid we print error and return 0 
 * Then we increment guess number, and we create arrays for the solutions, for the guess, and for keeping track of found perfect matches.
 * Then we create two loops to check for perfect and missed matches. We increment each counter coresspondingly. 
 * Then we print our output with the counter values.
 */


/*
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */

/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

#include "prog5.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;

/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the
 * code in main.c. This function should use the function sscanf to find the
 * integer seed value from the string seed_str, then initialize the random
 * number generator by calling srand with the integer seed value. To be valid,
 * exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user,
 * containing the random seed OUTPUTS: none RETURN VALUE: 0 if the given string
 * is invalid (string contains anything other than a single integer), or 1 if
 * string is valid (contains one integer) SIDE EFFECTS: initializes
 * pseudo-random number generation using the function srand. Prints "set_seed:
 * invalid seed\n" if string is invalid. Prints nothing if it is valid.
 */
int set_seed(const char seed_str[]) {
    //    Example of how to use sscanf to read a single integer and check for
    //    anything other than the integer "int seed" will contain the number
    //    typed by the user (if any) and the string "post" will contain anything
    //    after the integer The user should enter only an integer, and nothing
    //    else, so we will check that only "seed" is read. We declare int seed;
    //    char post[2];
    //    The sscanf statement below reads the integer into seed.
    //    sscanf (seed_str, "%d%1s", &seed, post)
    //    If there is no integer, seed will not be set. If something else is
    //    read after the integer, it will go into "post". The return value of
    //    sscanf indicates the number of items read succesfully. When the user
    //    has typed in only an integer, only 1 item should be read sucessfully.
    //    Check that the return value is 1 to ensure the user enters only an
    //    integer. Feel free to uncomment these statements, modify them, or
    //    delete these comments as necessary. You may need to change the return
    //    statement below

    int seed;
    char post[2];
    // we check if the use input seed value is invalid or not.
    if (sscanf(seed_str, "%d%1s", &seed, post) == 1) {
        //if valid we set seed and return 1
        srand(seed);
        return 1; 
    }
    
    // if not, we print error and return 0
    printf("set_seed: invalid seed\n");
    return 0;
}

/*
 * start_game -- This function is called by main.c after set_seed but before the
 * user makes guesses. This function creates the four solution numbers using the
 * approach described in the wiki specification (using rand()) The four solution
 * numbers should be stored in the static variables defined above. The values at
 * the pointers should also be set to the solution numbers. The guess_number
 * should be initialized to 1 (to indicate the first guess) INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use
 * by make_guess, set guess_number
 */
void start_game(int* one, int* two, int* three, int* four) {
    // your code here

    // We use modulus to limit the random number output from 0-7. Then we add 1 to make it 1 to 9

    *one = (rand() % 8) + 1;
    *two = (rand() % 8) + 1;
    *three = (rand() % 8) + 1;
    *four = (rand() % 8) + 1;

    // *one = 5;
    // *two = 4;
    // *three = 4;
    // *four = 4;

    // Then we save each of the generated number to each of the corresponding solutions.
    solution1 = *one;
    solution2 = *two;
    solution3 = *three;
    solution4 = *four;
}

/*
 * make_guess -- This function is called by main.c after the user types in a
 * guess. The guess is stored in the string guess_str. The function must
 * calculate the number of perfect and misplaced matches for a guess, given the
 * solution recorded earlier by start_game The guess must be valid (contain only
 * 4 integers, within the range 1-8). If it is valid the number of correct and
 * incorrect matches should be printed, using the following format "With guess
 * %d, you got %d perfect matches and %d misplaced matches.\n" If valid, the
 * guess_number should be incremented. If invalid, the error message
 * "make_guess: invalid guess\n" should be printed and 0 returned. For an
 * invalid guess, the guess_number is not incremented. INPUTS: guess_str -- a
 * string consisting of the guess typed by the user OUTPUTS: the following are
 * only valid if the function returns 1 (A valid guess) *one -- the first guess
 * value (between 1 and 8) *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and
 * increments guess_number(valid guess) or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki
 * writeup)
 */
int make_guess(const char guess_str[], int* one, int* two, int* three,
               int* four) {
    //  One thing you will need to read four integers from the string guess_str,
    //  using a process similar to set_seed The statement, given char post[2];
    //  and four integers w,x,y,z, sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y,
    //  &z, post) will read four integers from guess_str into the integers and
    //  read anything else present into post The return value of sscanf
    //  indicates the number of items sucessfully read from the string. You
    //  should check that exactly four integers were sucessfully read. You
    //  should then check if the 4 integers are between 1-8. If so, it is a
    //  valid guess Otherwise, it is invalid. Feel free to use this sscanf
    //  statement, delete these comments, and modify the return statement as
    //  needed

    int perfect = 0,
        missed = 0;  // counter for the perfect matches and the missed matches

    int ans[] = {solution1, solution2, solution3, solution4};  // create an array for the solutions for easy comparison
    int perfectMatch[] = {0, 0, 0, 0};  // array of length 4 to keep track indices with perfect matches
    int missMatch[] = {solution1, solution2, solution3, solution4};
    char post[2];  // to store the access input data

    // Here, return 0 and print error if the guess that we get from the user does not have exactly 4 items.
    if (sscanf(guess_str, "%d%d%d%d%1s", one, two, three, four, post) != 4) {
        printf("make_guess: invalid guess\n");
        return 0;
    }
    // we create another array to store the values of the guessed numbers. We use this array to compare.
    int guess[] = {*one, *two, *three, *four};

    // Here we check for another invalid input. We return 0 and print error if
    // any of the 4 integers in the guess is less than 1 or greater than 8
    for (int i = 0; i < 4; i++) {
        if ((guess[i] < 1 || guess[i] > 8)) {
            printf("make_guess: invalid guess\n");
            return 0;
        }
    }
    // increment the guess number. It is safe to increment it here since if there was an invalid input, function would have returned and ended.
    guess_number++;

    // Detect perfect matches
    for (int i = 0; i < 4; i++) {  // iterate through each of the 4 guess numbers
        if (guess[i] == ans[i]) {  // if we find that the guess number and the answer is equal on the same index
            perfect++;             // we increment the perfect match counter;
            perfectMatch[i] = 1;   // we also mark in our pefectMatch array that we found a perfect match in the i^th index.
        }
    }
    // Detect missed Matches
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {  // we iterate through the 4 answers
            // we first check if the current index of the guess is equal to any of the possible answers.
            // We also make sure to not check when the current answer we are comparing to is already a perfect match. This prevents double counting.
            if (guess[i] == missMatch[j] && perfectMatch[j] == 0) {
                missMatch[j] = 0; //
                missed++;               
                break; 
            }
        }
    }

    // print output
    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, missed);

    return 1;
}