#pragma once

#include "Piece.h"

class JPiece : public BasePiece {

public:
	JPiece(size_t x, size_t y) {

		this->piece.x = x;
		this->piece.y = y;

		this->piece.form = {
			{0,0,1},
			{0,0,1},
			{0,1,1},
		};
	}

	Piece getPieceData() const override {
		return piece;
	};

};