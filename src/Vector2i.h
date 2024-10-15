//
// Created by Nihar Gagneja on 10/1/24.
//


#ifndef VECTOR2I_H
#define VECTOR2I_H

// similar to Raylib's Vector2 class, but the components are integers
struct Vector2i {
    int x;
    int y;

    bool operator==(const Vector2i & other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2i & other) const {
        return x != other.x || y != other.y;
    }

    // allows ability to "add" the direction to the position for movement
    Vector2i operator+(const Vector2i & other) const {
        return Vector2i {x + other.x, y + other.y};
    }

    // allows ability to see change between 2 positions
    Vector2i operator-(const Vector2i & other) const {
        return Vector2i {x - other.x, y - other.y};
    }

    [[nodiscard]] bool oppositeTo(const Vector2i & other) const {
        return  (this->x == -other.x && this->y ==  other.y) ||
                (this->x ==  other.x && this->y == -other.y);
    }

    std::string toString() const {
        return std::to_string(x) + ", " + std::to_string(y);
    }
};

#endif //VECTOR2I_H