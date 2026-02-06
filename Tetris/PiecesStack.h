#pragma once

#include <stack>

#include "PiecesOrder.h"

class PiecesStack {

private:
	std::stack<Tetriminos> internalStack;
	
	void populateStack() {

		std::vector<Tetriminos> bagPieces = bag();

		for (auto& piece : bagPieces) {
			internalStack.push(piece);
		}
	}

public:
	
	std::unique_ptr<BasePiece> getNextPiece(size_t x, size_t y) {
		if (internalStack.empty()) populateStack();

		Tetriminos piece = internalStack.top();
		internalStack.pop();

		return createPiece(piece, x, y);
	}


};

