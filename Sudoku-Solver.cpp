#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

const int N = 9;

// Print Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cout << grid[r][c] << " ";
		}
		cout << "\n";
	}
}

// Check if placing num is valid
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
	for (int x = 0; x < N; x++) {
		if (grid[row][x] == num || grid[x][col] == num) return false;
	}

	int startRow = row - row % 3, startCol = col - col % 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (grid[i + startRow][j + startCol] == num) return false;
		}
	}
	return true;
}

// Find the next empty cell
bool findEmptyCell(const vector<vector<int>>& grid, int& row, int& col) {
	for (row = 0; row < N; row++) {
		for (col = 0; col < N; col++) {
			if (grid[row][col] == 0) return true;
		}
	}
	return false;
}

// Backtracking solver
bool solveSudoku(vector<vector<int>>& grid) {
	int row, col;
	if (!findEmptyCell(grid, row, col)) return true;

	for (int num = 1; num <= 9; num++) {
		if (isSafe(grid, row, col, num)) {
			grid[row][col] = num;
			if (solveSudoku(grid)) return true;
			grid[row][col] = 0;
		}
	}
	return false;
}

// Read grid from user input
vector<vector<int>> readGrid() {
	vector<vector<int>> grid(N, vector<int>(N, 0));
	cout << "Enter Sudoku grid (9 rows, 9 numbers per row, use 0 for empty):\n";
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> grid[r][c];
		}
	}
	return grid;
}

int main() {
	// Sample puzzle (0 means empty cell)
	vector<vector<int>> grid = {
		{ 5, 3, 0, 0, 7, 0, 0, 0, 0 },
		{ 6, 0, 0, 1, 9, 5, 0, 0, 0 },
		{ 0, 9, 8, 0, 0, 0, 0, 6, 0 },

		{ 8, 0, 0, 0, 6, 0, 0, 0, 3 },
		{ 4, 0, 0, 8, 0, 3, 0, 0, 1 },
		{ 7, 0, 0, 0, 2, 0, 0, 0, 6 },

		{ 0, 6, 0, 0, 0, 0, 2, 8, 0 },
		{ 0, 0, 0, 4, 1, 9, 0, 0, 5 },
		{ 0, 0, 0, 0, 8, 0, 0, 7, 9 }
	};

	// Uncomment to read puzzle from user
	// grid = readGrid();

	cout << "Original Puzzle:\n";
	printGrid(grid);

	if (solveSudoku(grid)) {
		cout << "\nSolved Sudoku:\n";
		printGrid(grid);
	}
	else {
		cout << "\nNo solution exists.\n";
	}

	system("pause");
	return 0;
}
