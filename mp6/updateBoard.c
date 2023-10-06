/*
 * partners: crjung2,hyunwoo6,awinick2
 * This code is separated into 4 sections of getItemBoard, countLiveNeighbor, updateBoard, and aliveStable
 * getItemBoard checks the element (alive 1 or dead 0) in the 1D array with rows and columns as inputs through the row* column size + column
 * getItemBoard is also used to make sure when checking edge elements, it will be set to 0 when outside the array
 * countLiveNeighbor initializes counter to 0 then loops through 8 surrounding cells of the imputted element
 * it will increment the counter everytime it detects 1 (alive) around
 * update board creates a temporary board to adjust the board elements
 * with if statements, check if the cell right now is alive and should be dead now since it doesn't have 2 or 3 people living around
 * or if it is dead, it should be alive through reproduction since there is exactly 3 people living around
 * then the board is updated after looping though every cell
 * alive stable repeats everything in updateBoard but when the newboard is updated, it will be compared to the original board
 * if no change was detected (every element is the same as before) it will be determined to be stable
 */


/* 
 * getItemBoard
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * rSize: the number of rows on the game board.
 * cSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return if the given cell is alive or not. It returns 0 for locations out of bounds.
 */
 
int getItemBoard(int* board, int rSize, int cSize, int row, int col) {
    if (row >= 0 && col >= 0 && row < rSize && col < cSize) //Check if in bounds
        return board[row * cSize + col]; //Return the current state of the selected element (o or 1)
    return 0; //If input is out of bounds
}

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col) {
    if (!(row >= 0 && col >= 0 && row < boardRowSize && col < boardColSize))
        return 0; //If input is out of bounds
    int count = 0;
    for (int r = row - 1; r <= row + 1; r++) {
        for (int c = col - 1; c <= col + 1; c++) { //Checking all adjacent
            if (getItemBoard(board, boardRowSize, boardColSize, r, c) && !(row == r && col == c)) {
                count++; //If the element is alive and is adjacent (not yourself), increment
            }
        }
    }
    return count;
}

/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */

void updateBoard(int* board, int boardRowSize, int boardColSize) {
    int boardSize = boardRowSize * boardColSize;
    int newBoard[boardSize]; //Create 1D array of board
    for (int i = 0; i < boardSize; i++) {
        newBoard[i] = board[i]; //Create a copy of board
    }
    for (int r = 0; r < boardRowSize; r++) {
        for (int c = 0; c < boardColSize; c++) {
            int alive = getItemBoard(board, boardRowSize, boardColSize, r, c); //Check if person is alive
            int n = countLiveNeighbor(board, boardRowSize, boardColSize, r, c); //Num alive ppl around
            if (alive) {
                if (n < 2 || n > 3) {
                    newBoard[r * boardColSize + c] = 0; //If alive, turn dead if not 2 or 3 ppl living
                }
            } else {
                if (n == 3) {
                    newBoard[r * boardColSize + c] = 1; //If dead, turn alive if 3 ppl living
                }
            } //Else don't update
        }
    }
    for (int i = 0; i < boardSize; i++) {
        board[i] = newBoard[i]; //Update to new board
    }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 

int aliveStable(int* board, int boardRowSize, int boardColSize) {
    int boardSize = boardColSize * boardRowSize;
    int newBoard[boardSize]; //Create 1D array of board
    for (int i = 0; i < boardSize; i++) {
        newBoard[i] = board[i]; //Create a copy of board
    }
    for (int r = 0; r < boardRowSize; r++) {
        for (int c = 0; c < boardColSize; c++) {
            int current = getItemBoard(board, boardRowSize, boardColSize, r, c); //Check if person is alive
            int n = countLiveNeighbor(board, boardRowSize, boardColSize, r, c); //Num alive ppl around
            if (current) {
                if (n < 2 || n > 3) {
                    newBoard[r * boardColSize + c] = 0;  //If alive, turn dead if not 2 or 3 ppl living
                }
            } else {
                if (n == 3) {
                    newBoard[r * boardColSize + c] = 1; //If dead, turn alive if 3 ppl living
                }
            }
        }
    }

    for (int i = 0; i < boardRowSize * boardColSize; i++) {
        if (newBoard[i] != board[i]) return 0; //Board was updated
    }

    return 1; //Board was the same, thus stable
}