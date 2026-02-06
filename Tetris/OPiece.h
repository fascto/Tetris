#pragma once
#include "Piece.h"

class OPiece : public BasePiece {

public:

	OPiece(size_t x, size_t y) {
		
		this->piece.x = x;
		this->piece.y = y;

		this->piece.form = {
			{1,1},
			{1,1}
		};
	}
	

	Piece getPieceData() const override{
		return piece;
	};

};
