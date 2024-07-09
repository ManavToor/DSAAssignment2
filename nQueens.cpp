#include <iostream>
#include <vector>
#include <array>
#include <stack>

/*
 * LOL You guys stole this question from leetcode :)
 */

using namespace std;

// Struct to hold state of board
// Vector of 2-element arrays holding (y, x) components of each queen
struct State {
    vector<array<int, 2>> queens;
};

class Board {
private:
    State queens; // location of queens on board
    int n; // dimension of board (nxn)
    vector<vector<char>> board; // 2D array visualizing board
    // Q - queen
    // . - available space
    // x - unavailable space

    void updateBoard(int row, int col) {
        // Input row and col of queen
        // Updates unavailable spaces
        // Does not check if location of queen is valid

        // horizontal
        for (int i=0; i<n; i++) {
            board[row][i] = 'x';
        }

        // vertical and diagonal
        for (int i=0; i<n; i++) {
            board[i][col] = 'x';

            if (0 <= (col-row + i) && (col-row + i) < n) {
                board[i][col-row + i] = 'x';
            }
            if (0 <= (col+row - i) && (col+row - i) < n) {
                board[i][col+row - i] = 'x';
            }
        }
    }

    bool addQueen(int row, int col) {
        // Adds queen to the board
        // Returns true if valid location
        if (board[row][col] == '.') {
            updateBoard(row, col);
            board[row][col] = 'Q';
            return true;
        }
        return false;
    }

public:
    int num_queens;

    Board(State queenState, int nVal){
        queens = queenState;
        n = nVal;
        num_queens = queens.queens.size();
        board.resize(n, vector<char>(n, '.'));

        // place queens on board
        for (auto & queen : queens.queens) {
            addQueen(queen[0], queen[1]);
        }
    }

    vector<State> openSpaces() {
        // For all valid answers in the n-queens problem, there is a queen on every row
        // Returns all valid States for next row (prevents multiples of same solution when bactracking)
        // ie. if number-of-queens = 0, returns all valid States for 0th row
        //     if number-of-queens = 4, returns all valid States for 4th row
        vector<State> out;
        for (int i=0; i<n; i++) {
            if (board[num_queens][i] == '.') {
                State newState = State{queens.queens};
                newState.queens.push_back({num_queens, i});
                out.push_back(newState);
            }
        }

        return out;
    }

    void printBoard() {
        for (const auto& row : board) {
            for (char cell : row) {
                cout << cell << ' ';
            }
            cout << std::endl;
        }
        cout << endl;
    }
};

int main() {
    // Uses backtracking to solve n-queens problem
    int n = 12;

    // Create stack for holding each State
    stack<State> stack;
    State initialState; // 0 queens
    Board board{initialState, n};

    // Add all possible locations for queen on empty board
    // Will only return valid spaces in first row (since in each valid solution there will be one queen per row) to
    // optimize algorithm by preventing multiples of same solution obtained from different paths
    vector<State> spaces = board.openSpaces();
    for (const auto & space : spaces) {
        stack.push(space);
    }

    // Vector to hold found solutions
    vector<Board> solution;

    while (stack.size() > 0) {
        // Creates new board with State at top of stack
        Board newBoard{stack.top(), n};
        stack.pop();

        if (newBoard.num_queens == n) {
            solution.push_back(newBoard);
        } else {
            // Appends all possible next locations to stack
            for (const auto & space : newBoard.openSpaces()) {
                stack.push(space);
            }
        }

    }

    cout << "Number of solutions: " << solution.size() << endl;

    // Print all found solutions
    for (auto & sol: solution) {
        sol.printBoard();
    }

    return 0;
}
