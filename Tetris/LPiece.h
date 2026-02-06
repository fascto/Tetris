#pragma once

#include "Piece.h"

class LPiece : public BasePiece {

public:
	LPiece(size_t x, size_t y) {

		this->piece.x = x;
		this->piece.y = y;

		this->piece.form = {
			{1,0,0},
			{1,0,0},
			{1,1,0}
		};
	}

	Piece getPieceData() const override {
		return piece;
	};

};