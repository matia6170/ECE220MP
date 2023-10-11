#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

/*
 * partners: crjung2,hyunwoo6,awinick2
 * This program solves a sudoku puzzle.
 * It has three functions that checks if we can place a value or not:
 * is_val_in_row(), is_val_in_col(), is_val_in_3x3_zone() Each of them checks
 * for if it is valid to place the value in that given row, column, and 3x3
 * zone. is_val_valid() is then used to check if it is safe to place a value
 * using the aforementioned 3 functions. Then, solve_sudoku() recursively solves
 * the sudoku map by setting the base case as checking if the board is filled or
 * not using the function we wrote: check_sudoku_filled().
 * We also created a function called find_empty_cell() which finds the the first
 * empty cell. The rest of the solve_sudoku() iterates through the possible
 * values and checks if its okay to place. If yes, it will recursively call it
 * self.
 */

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
    assert(i >= 0 && i < 9);

    // BEG TODO
    for (int j = 0; j < 9; j++) {
        if (sudoku[i][j] ==
            val) {  // iterates through row, checks for duplicate value
            return 1;
        }
    }
    return 0;
    // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
    assert(j >= 0 && j < 9);

    // BEG TODO

    for (int i = 0; i < 9; i++) {
        if (sudoku[i][j] ==
            val) {  // iterates through col, checks for duplicate value
            return 1;
        }
    }

    return 0;
    // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j,
                       const int sudoku[9][9]) {
    assert(i >= 0 && i < 9);
    // BEG TODO
    // Divide the 9 sections into a 3x3 2d array
    int ib = i / 3;  // i_base
    int jb = j / 3;  // j_base
    // The actaul i and j (k,l) value will be the base*3 to base*3+2 (b*3 >= x >
    // b*3+3) with the given i,j base, offset k,l to convert 3x3 to 9x9
    for (int k = ib * 3; k < ib * 3 + 3; k++) {
        for (int l = jb * 3; l < jb * 3 + 3; l++) {
            if (sudoku[k][l] == val) {  // if value is already in 3x3 return 1
                return 1;
            }
        }
    }
    return 0;
    // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j,
                 const int sudoku[9][9]) {
    assert(i >= 0 && i < 9 && j >= 0 && j < 9);

    // BEG TODO
    if (is_val_in_row(val, i, sudoku) == 0 &&
        is_val_in_col(val, j, sudoku) == 0 &&
        is_val_in_3x3_zone(val, i, j, sudoku) == 0) {
        // If all 3 check found no duplicates, it is a valid value
        return 1;
    }
    return 0;
    // END TODO
}

// Helper function: check_sudoku_fiiled
// Return 1 if sudoku is full, 0 otherwise
int check_sudoku_filled(int sudoku[9][9]) {
    int i, j, counter;
    // loop through all cells
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (sudoku[i][j] ==
                0) {  // If an empty cell exists, return not full
                return 0;
            }
        }
    }
    return 1;
}

// Helper function: find_empty_cell
// finds an empty cell
void find_empty_cell(int *i, int *j, int sudoku[9][9]) {
    // loop through all cell
    for (int k = 0; k < 9; k++) {
        for (int l = 0; l < 9; l++) {
            if (sudoku[k][l] ==
                0) {  // if an empty cell exists, dereference the i,j cell
                *i = k;
                *j = l;
                return;
            }
        }
    }
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
    // BEG TODO.
    int i, j;

    if (check_sudoku_filled(sudoku) ==
        1) {  // Base case - check is sudoku is full
        return 1;
    } else {
        find_empty_cell(
            &i, &j, sudoku);  // if some cells are empty, find the empty cell
    }

    for (int num = 1; num <= 9;
         num++) {  // loop through all possible values to input
        if (is_val_valid(num, i, j, sudoku)) {
            sudoku[i][j] =
                num;  // if the value is valid, place val into i,j cell
            if (solve_sudoku(sudoku)) {  // recursion
                return 1;
            }
            sudoku[i][j] = 0;  // couldn't find a possible value
        }
    }

    return 0;  // backtrack
               // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9]) {
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%2d", sudoku[i][j]);
        }
        printf("\n");
    }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
    FILE *reader = fopen(fpath, "r");
    assert(reader != NULL);
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            fscanf(reader, "%d", &sudoku[i][j]);
        }
    }
    fclose(reader);
}