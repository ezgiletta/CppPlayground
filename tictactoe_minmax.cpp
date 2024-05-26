#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;
char humanPlayer;
char aiPlayer;

void printBoard(const vector<vector<char>> &board){
     for (const auto& row : board){
        for (const auto& cell : row){
            cout << cell << " ";
        }
        cout << endl;
    }
}

bool areAllElementsSame(const vector<char> &vec){
    char first_char = vec[0];
    if(first_char == '-'){
        return false;
    }
    for(const char &i : vec){
        if(first_char != i){
            return false;
        }
    }
    return true;    
}

pair<bool, char> checkDiagonalsSame(const vector<vector<char>> &board) {
    int size = board.size();
    vector<char> diagonal_vec;
    vector<char> reverse_diagonal_vec;

    for (int i = 0; i < size; i++) {
        diagonal_vec.push_back(board[i][i]);
        reverse_diagonal_vec.push_back(board[i][size - 1 - i]);
    }
    if (areAllElementsSame(diagonal_vec)) {
        return {true, diagonal_vec[0]};
    }
    if (areAllElementsSame(reverse_diagonal_vec)) {
        return {true, reverse_diagonal_vec[0]};
    }

    return {false, '-'};
}

pair<bool, char> checkWinCondition(const vector<vector<char>> &board) {
    for (int i = 0; i < board.size(); i++) {
        vector<char> row = board[i];
        if (areAllElementsSame(row)) {
            return {true, row[0]};
        }

        vector<char> column;
        for (int j = 0; j < board.size(); j++) {
            column.push_back(board[j][i]);
        }
        if (areAllElementsSame(column)) {
            return {true, column[0]};
        }
    }
    auto diagonalCheck = checkDiagonalsSame(board);
    if (diagonalCheck.first) {
        return diagonalCheck;
    }
    return {false, '-'};
}

bool isBoardFull(const vector<vector<char>> &board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == '-') {
                return false;
            }
        }
    }
    return true;
}

int evaluateBoard(const vector<vector<char>>& board) {
    auto winCheck = checkWinCondition(board);
    if (winCheck.first && winCheck.second == aiPlayer) {
        return 10;
    } else if (winCheck.first && winCheck.second == humanPlayer) {
        return -10;
    }
    return 0;
}

int minimax(vector<vector<char>> board, int depth, bool isMaximizing) {

    int score = evaluateBoard(board);

    if (score == 10 || score == -10) { // there is winner
        return score;
    }

    if (isBoardFull(board)) { // tie
        return 0;
    }

    if (isMaximizing) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == '-') {
                    board[i][j] = aiPlayer;
                    best = max(best, minimax(board, depth + 1, !isMaximizing));
                    board[i][j] = '-';
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == '-') {
                    board[i][j] = humanPlayer;
                    best = min(best, minimax(board, depth + 1, !isMaximizing));
                    board[i][j] = '-';
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(vector<vector<char>> &board) { // it is called by algorithm
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == '-') {
                board[i][j] = aiPlayer;
                int moveVal = minimax(board, 0, false);
                board[i][j] = '-'; // remove the child move from the board

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main()
{  
    int rows(3);
    int cols(3); 
    vector<vector<char>> board(rows, vector<char>(cols, '-'));
    bool win(false);
    bool tie(false);

    char playerX('X');
    char playerO('O');

    int row_loc;
    int col_loc;
    char player;
    int wrong_loc_count(0);

    cout << "Select the your player (X/O): ";
    cin >> player;
    
    if (player != 'X' && player != 'O') {
        cout << "Invalid player selection. Choose 'X' or 'O'." << endl;
        return 1;
    } 

    humanPlayer = player; // maximizer
    aiPlayer = (humanPlayer == 'X') ? 'O' : 'X';  //minimizer

    while(!win && !tie){

        if(wrong_loc_count >= 5){
            cout << "Invalid location entered 5 times! Please start the game again!" << endl;
            break;
        }

        if (player == humanPlayer) {
            cout << "Enter the row and column location (" << 0 << "-" << (cols-1) << ") for the move: ";
            cin >> row_loc >> col_loc;

            if (board[row_loc][col_loc] == '-') {
                board[row_loc][col_loc] = player;
            } else {
                cout << "This location is already filled!" << endl;
                wrong_loc_count++;
                continue;
            }    
        } else {
            pair<int, int> bestMove = findBestMove(board);
            row_loc = bestMove.first;
            col_loc = bestMove.second;
            board[row_loc][col_loc] = player;
            cout << "Computer placed '" << player << "' at (" << row_loc << ", " << col_loc << ")." << endl;
 
        }

        win = checkWinCondition(board).first;
        tie = isBoardFull(board) && !win;

        if(win){
            cout << "Player " << player << " win." << endl;
        }
        else if (tie) {
            cout << "The game is a tie!" << endl;
        }
        else{
            player = (player == humanPlayer) ? aiPlayer : humanPlayer;  
        }
       
        printBoard(board);
    }
    return 0;
}