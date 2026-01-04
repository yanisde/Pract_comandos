#include "Rectangle.h"
#include <cmath>

static const double EPS = 1e-9;

static bool eq(double a, double b) {
    return std::fabs(a - b) < EPS;
}

bool Rectangle::check(Point2D* vertices) {
    if (vertices == nullptr) return false;

    double d01 = Point2D::distance(vertices[0], vertices[1]);
    double d23 = Point2D::distance(vertices[2], vertices[3]);
    double d12 = Point2D::distance(vertices[1], vertices[2]);
    double d30 = Point2D::distance(vertices[3], vertices[0]);

    return eq(d01, d23) && eq(d12, d30);
}

Rectangle::Rectangle() : Shape(), vs(new Point2D[N_VERTICES]) {
    vs[0] = Point2D(-1, 0.5);
    vs[1] = Point2D( 1, 0.5);
    vs[2] = Point2D( 1,-0.5);
    vs[3] = Point2D(-1,-0.5);
}

Rectangle::Rectangle(std::string color, Point2D* vertices) : Shape(color), vs(nullptr) {
    if (!check(vertices))
        throw std::invalid_argument("vertices invalidos");

    vs = new Point2D[N_VERTICES];
    for (int i = 0; i < N_VERTICES; i++)
        vs[i] = vertices[i];
}

Rectangle::Rectangle(const Rectangle& r) : Shape(r.color), vs(new Point2D[N_VERTICES]) {
    for (int i = 0; i < N_VERTICES; i++)
        vs[i] = r.vs[i];
}

Rectangle::~Rectangle() {
    delete[] vs;
}

Point2D Rectangle::get_vertex(int ind) const {
    if (ind < 0 || ind >= N_VERTICES)
        throw std::out_of_range("indice fuera de rango");
    return vs[ind];
}

Point2D Rectangle::operator[](int ind) const {
    return get_vertex(ind);
}

void Rectangle::set_vertices(Point2D* vertices) {
    if (!check(vertices))
        throw std::invalid_argument("vertices invalidos");

    for (int i = 0; i < N_VERTICES; i++)
        vs[i] = vertices[i];
}

Rectangle& Rectangle::operator=(const Rectangle& r) {
    if (this == &r) return *this;

    color = r.color;

    delete[] vs;
    vs = new Point2D[N_VERTICES];
    for (int i = 0; i < N_VERTICES; i++)
        vs[i] = r.vs[i];

    return *this;
}

// Para el rectángulo asumimos lados: v0-v1 y v1-v2
double Rectangle::area() const {
    double a = Point2D::distance(vs[0], vs[1]);
    double b = Point2D::distance(vs[1], vs[2]);
    return a * b;
}

double Rectangle::perimeter() const {
    double a = Point2D::distance(vs[0], vs[1]);
    double b = Point2D::distance(vs[1], vs[2]);
    return 2 * (a + b);
}

void Rectangle::translate(double incX, double incY) {
    for (int i = 0; i < N_VERTICES; i++) {
        vs[i].x += incX;
        vs[i].y += incY;
    }
}

void Rectangle::print() {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream& out, const Rectangle& r) {
    out << "[Rectangle: color = " << r.color << "; vertices = {";
    for (int i = 0; i < Rectangle::N_VERTICES; i++) {
        out << r.vs[i];
        if (i + 1 < Rectangle::N_VERTICES) out << ", ";
    }
    out << "}]";
    return out;
}

