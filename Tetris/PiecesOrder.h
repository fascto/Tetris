#pragma once

#include <memory>
#include <algorithm>
#include <vector>
#include <random>

#include "OPiece.h"
#include "IPiece.h"
#include "TPiece.h"
#include "LPiece.h"
#include "JPiece.h"
#include "SPiece.h"
#include "ZPiece.h"
#include "Piece.h"

// Nombre de las piezas
enum class Tetriminos {
	O_TETRIMINO = 0,
	I_TETRIMINO = 1,
	T_TETRIMINO = 2,
	L_TETRIMINO = 3,
	J_TETRIMINO = 4,
	S_TETRIMINO = 5,
	Z_TETRIMINO = 6,
};

std::unique_ptr<BasePiece> createPiece(Tetriminos type, int x, int y);

std::vector<Tetriminos> bag();