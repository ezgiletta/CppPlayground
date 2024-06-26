# Tic Tac Toe with Minimax and Alpha-Beta Pruning in C++

This repository contains three implementations of the Tic Tac Toe game in C++:
1. `tictactoe`
2. `tictactoe_minimax`
3. `tictactoe_alpha_beta_pruning`

## Table of Contents
- [Tic Tac Toe](#tic-tac-toe)
- [Tic Tac Toe with Minimax](#tic-tac-toe-with-minimax)
- [Tic Tac Toe with Minimax and Alpha-Beta Pruning](#tic-tac-toe-with-minimax-and-alpha-beta-pruning)
- [Big O Complexity](#big-o-complexity)

## Tic Tac Toe
This is a basic implementation of the Tic Tac Toe game where two players (user vs. computer or user vs. user) can play against each other.

### Logic
- The game is played on a 3x3 grid.
- Players take turns to place their symbol (X or O) on an empty cell.
- The first player to get three of their symbols in a row (vertically, horizontally, or diagonally) wins the game.
- If all cells are filled and no player has three in a row, the game is a tie.

## Tic Tac Toe with Minimax
This implementation includes an AI player using the Minimax algorithm.

### Logic
- The Minimax algorithm is a recursive method used to choose the optimal move for the AI player.
- It simulates all possible moves, then backtracks to choose the move that maximizes the AI's chances of winning while minimizing the opponent's chances.
- The algorithm evaluates the game tree up to the terminal states (win, tie).

## Tic Tac Toe with Minimax and Alpha-Beta Pruning
This implementation enhances the Minimax algorithm with Alpha-Beta Pruning.

### Logic
- Alpha-Beta Pruning improves the efficiency of the Minimax algorithm by eliminating branches in the game tree that do not need to be explored.
- It keeps track of two values, alpha and beta, which represent the minimum score that the maximizing player is assured of and the maximum score that the minimizing player is assured of, respectively.
- Branches of the tree that cannot affect the final decision are pruned away, reducing the number of nodes evaluated.

## Big O Complexity

### Tic Tac Toe
- **Time Complexity:** `O(1)` for each move.
- **Space Complexity:** `O(1)`

### Minimax Algorithm for Tic Tac Toe
- **Time Complexity:** `O(b^d)`
  - `b`: branching factor (maximum 9)
  - `d`: depth of the game tree (maximum 9)
- **Space Complexity:** `O(bd)`

### Alpha-Beta Pruning for Tic Tac Toe
- **Time Complexity:**
  - **Best Case:** `O(b^{d/2})`
  - **Worst Case:** `O(b^d)`
- **Space Complexity:** `O(bd)`

