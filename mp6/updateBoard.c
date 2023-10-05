
int getItemBoard(int* board, int rSize, int cSize, int row, int col) {
    if (row >= 0 && col >= 0 && row < rSize && col < cSize)
        return board[row * cSize + col];
    return 0;
}
void boardCopy(int* src, int* dest, int cSize, int rSize) {}
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

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row,
                      int col) {
    if (!(row >= 0 && col >= 0 && row < boardRowSize && col < boardColSize))
        return 0;

    int count = 0;
    for (int r = row - 1; r <= row + 1; r++) {
        for (int c = col - 1; c <= col + 1; c++) {
            if (getItemBoard(board, boardRowSize, boardColSize, r, c) &&
                (row != r || col != c)) {
                count++;
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
    int newBoard[boardSize];
    for (int i = 0; i < boardSize; i++) {
        newBoard[i] = board[i];
    }
    for (int r = 0; r < boardRowSize; r++) {
        for (int c = 0; c < boardColSize; c++) {
            int alive = getItemBoard(board, boardRowSize, boardColSize, r, c);
            int n = countLiveNeighbor(board, boardRowSize, boardColSize, r, c);
            if (alive) {
                if (n < 2 || n > 3) {
                    newBoard[r * boardColSize + c] = 0;
                }
            } else {
                if (n == 3) {
                    newBoard[r * boardColSize + c] = 1;
                }
            }
        }
    }
    for (int i = 0; i < boardSize; i++) {
        board[i] = newBoard[i];
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
    int newBoard[boardSize];
    for (int i = 0; i < boardSize; i++) {
        newBoard[i] = board[i];
    }
    for (int r = 0; r < boardRowSize; r++) {
        for (int c = 0; c < boardColSize; c++) {
            int current = getItemBoard(board, boardRowSize, boardColSize, r, c);
            int n = countLiveNeighbor(board, boardRowSize, boardColSize, r, c);
            if (current) {
                if (n < 2 || n > 3) {
                    newBoard[r * boardColSize + c] = 0;
                }
            } else {
                if (n == 3) {
                    newBoard[r * boardColSize + c] = 1;
                }
            }
        }
    }

    for (int i = 0; i < boardRowSize * boardColSize; i++) {
        if (newBoard[i] != board[i]) return 0;
    }

    return 1;
}
