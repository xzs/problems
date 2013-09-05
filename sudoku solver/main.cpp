#include <iostream>
using namespace std;

// This is the sudoku board. 0 indicates an empty cell.
int board[9][9]={0,9,3,1,0,5,6,4,0,
				 7,0,0,0,0,0,0,0,5,
				 5,0,1,2,0,9,3,0,7,
				 2,0,0,0,0,0,0,0,3,
				 0,3,6,9,0,7,5,2,0,
	             9,0,0,0,0,0,0,0,1,
	             3,0,2,4,0,8,1,0,9,
				 6,0,0,0,0,0,0,0,4,
				 0,4,7,3,0,2,8,5,0};

int row, col;

void print() {
	for (int i=0;i<9;i++) {
			for (int j=0;j<9;j++) {
				cout << board[i][j] << " ";
			}
		cout << endl;
	}
}

// Checks if the number n meets the criteria for the 3 by 3 square
// corresponding to the cell at i,j.
bool checkSquare(int n, int i, int j) {
	int row = i/3;
	int col = j/3;
	
	for (int a = row*3; a < row*3+3; a++) {
		for (int b = col*3; b < col*3+3; b++) {
			if (board[a][b]==n) {
				return false;
			}
		}
	}
	return true;	
}

// Checks if the number n meets the criteria for row i.
bool checkRow(int n, int i) {
	for (int a=0; a<9; a++) {
		if (board[i][a]==n) {
			return false;
		}
	}
	return true;
}

// Checks if the number n meets the criteria for column j.
bool checkColumn(int n, int j) {

	for (int a=0; a<9; a++) {
		if (board[a][j]==n) {
			return false;
		}
	}
	return true;
}

// Checks if the board has any empty spaces left. If there is an empty
// cell, it will set the global row and col value.
bool findEmpty() {
	for (int i=0;i<9;i++) {
		for (int j=0;j<9;j++) {
			if (board[i][j] == 0) {
				row = i;
				col = j;
				return true;
			}
		}
	}
	return false;
}

// Checks if number n can be placed in cell i,j.
bool valid(int n, int i, int j) {
	if (checkRow(n,i)&&checkColumn(n,j)&&checkSquare(n,i,j)) {
		return true;
	} else
		return false;
}

// Recursive backtracking algorithm to solve sudoku board.
bool solveSudoku() {
	if (!findEmpty()) {
		return true;
	}

	int i = row;
	int j = col;

	for (int n=1; n<=9;n++) {
		if (valid(n,i,j)) {
			board[i][j]=n;
			if (solveSudoku()) {
				return true;
			}
			board[i][j] = 0;
		}
	}	
	return false; 
}

int main() {
	cout << "This is your sudoku board" << endl;
	print();
	cout << endl;
	if (solveSudoku()) {
		cout << "Solved it!" << endl;
		print();
	} else {
		cout << "Can't solve this one.";
	}
}
