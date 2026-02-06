#include "PiecesOrder.h"

std::unique_ptr<BasePiece> createPiece(Tetriminos type, int x, int y) {
	switch (type) {
	case Tetriminos::O_TETRIMINO:
		return std::make_unique<OPiece>(x, y);
	case Tetriminos::I_TETRIMINO:
		return std::make_unique<IPiece>(x, y);
	case Tetriminos::T_TETRIMINO:
		return std::make_unique<TPiece>(x, y);
	case Tetriminos::L_TETRIMINO:
		return std::make_unique<LPiece>(x, y);
	case Tetriminos::J_TETRIMINO:
		return std::make_unique<JPiece>(x, y);
	case Tetriminos::S_TETRIMINO:
		return std::make_unique<SPiece>(x, y);
	case Tetriminos::Z_TETRIMINO:
		return std::make_unique<ZPiece>(x, y);
	default:
		return nullptr;
	}
}

// 7Bag randomizer
std::vector<Tetriminos> bag() {

	// Optimizacion: El static hace que las variables estas 
	// se inicialicen una sola vez nomas
	static std::random_device rd;
	static std::mt19937 g(rd());

	std::vector<Tetriminos> pieces = {
			Tetriminos::O_TETRIMINO,
			Tetriminos::I_TETRIMINO,
			Tetriminos::T_TETRIMINO,
			Tetriminos::L_TETRIMINO,
			Tetriminos::J_TETRIMINO,
			Tetriminos::S_TETRIMINO,
			Tetriminos::Z_TETRIMINO
	};

	std::shuffle(pieces.begin(), pieces.end(), g);

	return pieces;
}