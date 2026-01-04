#include "Square.h"
#include <cmath>

static const double EPS = 1e-9;

static bool eq(double a, double b) {
    return std::fabs(a - b) < EPS;
}

bool Square::check(Point2D* vertices) {
    if (vertices == nullptr) return false;

    double d01 = Point2D::distance(vertices[0], vertices[1]);
    double d12 = Point2D::distance(vertices[1], vertices[2]);
    double d23 = Point2D::distance(vertices[2], vertices[3]);
    double d30 = Point2D::distance(vertices[3], vertices[0]);

    return eq(d01, d12) && eq(d12, d23) && eq(d23, d30);
}

Square::Square() : Rectangle() {
    Point2D v[N_VERTICES] = {
        Point2D(-1,  1),
        Point2D( 1,  1),
        Point2D( 1, -1),
        Point2D(-1, -1)
    };
    set_vertices(v);
}

Square::Square(std::string color, Point2D* vertices) : Rectangle(color, vertices) {
    if (!check(vertices))
        throw std::invalid_argument("vertices invalidos");
    // Rectangle(color, vertices) ya copió; pero garantizamos condición de cuadrado
}

void Square::set_vertices(Point2D* vertices) {
    if (!check(vertices))
        throw std::invalid_argument("vertices invalidos");
    // vs es protected en Rectangle
    for (int i = 0; i < N_VERTICES; i++)
        vs[i] = vertices[i];
}

void Square::print() {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream& out, const Square& s) {
    out << "[Square: color = " << s.color << "; vertices = {";
    for (int i = 0; i < Rectangle::N_VERTICES; i++) {
        out << s.vs[i];
        if (i + 1 < Rectangle::N_VERTICES) out << ", ";
    }
    out << "}]";
    return out;
}

