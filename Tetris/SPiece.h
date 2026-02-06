#pragma once

#include "Piece.h"

class SPiece : public BasePiece {

public:
	SPiece(size_t x, size_t y) {

		this->piece.x = x;
		this->piece.y = y;

		this->piece.form = {
			{0,1,1},
			{1,1,0},
			{0,0,0}
		};
	}	

	Piece getPieceData() const override {
		return piece;
	};

};