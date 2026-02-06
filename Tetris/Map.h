#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <thread>

#include "ConsoleInput.h"
#include "Piece.h"


using Matrix = std::vector<std::vector<size_t>>;

class Map {

private:

	int rows{};
	int cols{};
	Matrix matrix;

	bool isPieceAt(int i, int j, std::unique_ptr<BasePiece>& activePiece) {

		// offsets
		int row_local = i - activePiece->piece.y;
		int col_local = j - activePiece->piece.x;

		// checkeo si entra verticalmente
		if (!(row_local >= 0 && row_local < activePiece->piece.form.size())) {
			return false;
		}

		// checkeo si entra en el rango horizontal
		if (!(col_local >= 0 && col_local < activePiece->piece.form[row_local].size())) {
			return false;
		}

		if (activePiece->piece.form[row_local][col_local] == 1)
		{
			return true;
		}


		return false;
	}

	bool isBorder(int i, int j) {
		if (j == 0 || j == this->cols-1)
		{
			return true;
		}

		return false;
		
	}

public:

	Map() {}

	Map(size_t rows, size_t cols) : rows(rows), cols(cols) {
		this->matrix = Matrix(rows, std::vector<size_t>(cols, 0));
	}

	Matrix& getMatrix() {
		return this->matrix;
	}

	void renderMap(std::unique_ptr<BasePiece>& activePiece) {
		for (int c = 0; c < this->cols + 2; c++) std::cout << "#";
		std::cout << '\n';

		for (int r = 0; r < this->rows; r++) {
			std::cout << "#";

			for (int c = 0; c < this->cols; c++) {
				if (activePiece != nullptr && isPieceAt(r, c, activePiece)) {
					std::cout << '$';
				}
				else if (this->matrix[r][c] != 0) {
					char chars[] = { ' ', 'O', '*', '+', 'x' };
					std::cout << chars[this->matrix[r][c]];
				}
				else {
					std::cout << (char)250; 
				}
			}

			std::cout << "#" << '\n';
		}

		for (int c = 0; c < this->cols + 2; c++) std::cout << "#";
		std::cout << '\n';
	}

	void writePiece(Piece& solidPiece) {
		for (int r = 0; r < solidPiece.form.size(); r++) {
			for (int c = 0; c < solidPiece.form[r].size(); c++) {
				if (solidPiece.form[r][c] == 1) {

					int mapRow = solidPiece.y + r;
					int mapCol = solidPiece.x + c;

					if (mapRow >= 0 && mapRow < rows && mapCol >= 0 && mapCol < cols) {
						this->matrix[mapRow][mapCol] = 1;
					}
				}
			}
		}
	}

	bool checkLine() {
		std::vector<int> linesToClear;

		for (int i = 0; i < this->rows; i++) {
			bool isFull = true;
			for (int j = 0; j < this->cols; j++) {
				if (this->matrix[i][j] == 0) {
					isFull = false;
					break; 
				}
			}

			if (isFull) {
				linesToClear.push_back(i);
			}
		}

		if (linesToClear.empty()) {
			return false;
		}

		for (int row : linesToClear) {
			clearLine(row);
		}

		return true;
	}
	void clearLine(int row) {
		for (size_t j = 0; j < this->cols; j++) {
			this->matrix[row][j] = 2; 
		}

		ConsoleUtils::clear();
		std::unique_ptr<BasePiece> dummyPiece;
		renderMap(dummyPiece); 
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		ConsoleUtils::clear();

		for (int r = row; r > 0; r--) {
			for (int c = 0; c < this->cols; c++) {
				this->matrix[r][c] = this->matrix[r - 1][c];
			}
		}

		for (int c = 0; c < this->cols; c++) {
			this->matrix[0][c] = 0;
		}
	}

};

