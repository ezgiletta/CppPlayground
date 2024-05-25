#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

bool checkDiagonalsSame(const vector<vector<char>> &board){

    int size = board.size();
    vector<char> diagonal_vec;
    vector<char> reverse_diagonal_vec;

    for (int i = 0; i < size; i++){
        diagonal_vec.push_back(board[i][i]); 
        reverse_diagonal_vec.push_back(board[i][size - 1 - i]);    
    }
    if(areAllElementsSame(diagonal_vec) || areAllElementsSame(reverse_diagonal_vec)){return true;}

    return false;
}

bool checkWinCondition(const vector<vector<char>> &board){

    for(int i = 0; i < board.size(); i ++){
        
        vector<char> row = board[i];
        
        if(areAllElementsSame(row)){
        return true;
        }

        vector<char> column;
        for(int j = 0; j < board[i].size(); j++){
            column.push_back(board[j][i]);
        }

        if(areAllElementsSame(column)){
        return true;
        }
    }    
    if(checkDiagonalsSame(board)){
        return true;
    }
    return false;
}

int main()
{  
    int rows(3);
    int cols(3); 
    vector<vector<char>> board(rows, vector<char>(cols, '-'));
    bool win(false);

    char playerX('X');
    char playerO('O');

    int row_loc;
    int col_loc;
    char player;
    int wrong_loc_count(0);

    cout << "Select the starter player (X/O): ";
    cin >> player;
    
    if (player != 'X' && player != 'O') {
        cout << "Invalid player selection. Choose 'X' or 'O'." << endl;
        return 1;
    }
    
    while(!win){

        if(wrong_loc_count >= 5){
            cout << "Invalid location entered 5 times! Please start the game again!" << endl;
            break;
        }

        cout << "Enter the row and column location (" << 0 << "-" << (cols-1) << ") for the move: ";
        cin >> row_loc >> col_loc;

        if(board[row_loc][col_loc] == '-'){
            board[row_loc][col_loc] = player;
        }
        else{
            cout << "This location is already filled!" << endl;
            wrong_loc_count++;
        }
        
        win = checkWinCondition(board);

        if(win){
            cout << "Player " << player << " win. Congratulations!" << endl;
        }
        else{
            player = (player == playerX) ? playerO : playerX;  
        }
       
        printBoard(board);
    }
    return 0;
}