#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>


using Form = std::vector<std::vector<size_t>>;

enum class Rotations {
    Left,
    Right,
};

enum class Directions {
    Up,
    Down,
    Left,
    Right,
};

struct Piece {
    size_t x{ 0 }, y{ 0 };
    bool solid = false;
    Form form{};
    Directions current_dir{ Directions::Up };
};

inline std::ostream& operator<<(std::ostream& os, const Piece& p) {
    os << "Pieza en (" << p.x << ", " << p.y << ") - Solid: " << (p.solid ? "YES" : "NO") << "\n";

    for (const auto& row : p.form) {
        for (const auto& cell : row) {
            os << (cell > 0 ? "[#]" : "[ ]");
        }
        os << "\n";
    }
    return os;
}

class BasePiece {
public:

    Piece piece;

    virtual ~BasePiece() = default;

    virtual Piece getPieceData() const = 0;

    void setSolid(bool state) {
        this->piece.solid = state;
    }

    void rotate(Rotations rotation) {
        if (piece.form.empty()) return;

        Form& shape = piece.form;
        size_t rows = shape.size();
        size_t cols = shape[0].size();

        if (rows == 0 || cols == 0) return;

        // Nueva matriz con nueva dimensión
        Form newShape(cols, std::vector<size_t>(rows));

        // transpuesta
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                newShape[j][i] = shape[i][j];
            }
        }

        if (rotation == Rotations::Right) {
            for (auto& row : newShape) {
                std::reverse(row.begin(), row.end());
            }
        }
        else {
            std::reverse(newShape.begin(), newShape.end());
        }

        shape = std::move(newShape);
    }

    void moveDown(Form& map) {
        size_t originalY = this->piece.y;
        this->piece.y += 1;

        if (checkCollision(map)) {
            this->piece.y = originalY;
            this->setSolid(true);
        }
    }

    bool checkCollision(const Form& map) {
        const auto& shape = this->piece.form;
        if (shape.empty() || map.empty() || map[0].empty()) return false;

        size_t rows = shape.size();
        size_t cols = shape[0].size();

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if (shape[i][j] > 0) {
                    size_t nextY = this->piece.y + i;
                    size_t nextX = this->piece.x + j;

                    if (nextY >= map.size() || nextX >= map[0].size()) {
                        return true;
                    }

                    if (map[nextY][nextX] > 0) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void moveSides(Directions dir, const Form& map) {
        size_t originalX = this->piece.x;

        switch (dir) {
        case Directions::Left:
            if (this->piece.x > 0) this->piece.x = this->piece.x - 1;
            if (checkCollision(map)) this->piece.x = originalX;
            break;

        case Directions::Right:
            this->piece.x = this->piece.x + 1;
            if (checkCollision(map)) this->piece.x = originalX;
            break;

        default:
            return;
        }
    }

};