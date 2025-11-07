#include "shapes.hpp"

namespace Shapes {

Circle::Circle(float radius) : shape_(radius) {
    shape_.setFillColor(sf::Color::White);
}

void Circle::setRadius(float radius) {
    shape_.setRadius(radius);
}

void Circle::setFillColor(const dr4::Color& color) {
    shape_.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
}

void Circle::setOutline(float thickness, const dr4::Color& color) {
    shape_.setOutlineThickness(thickness);
    shape_.setOutlineColor(sf::Color(color.r, color.g, color.b, color.a));
}

void Circle::setPosition(const dr4::Vec2f& position) {
    shape_.setPosition(position.x, position.y);
}

void Circle::setRotation(float angle) {
    shape_.setRotation(angle);
}

void Circle::setOrigin(const dr4::Vec2f& origin) {
    shape_.setOrigin(origin.x, origin.y);
}

Rectangle::Rectangle(const dr4::Vec2f& size) {
    shape_.setSize(sf::Vector2f(size.x, size.y));
    shape_.setFillColor(sf::Color::White);
}

void Rectangle::setSize(const dr4::Vec2f& size) {
    shape_.setSize(sf::Vector2f(size.x, size.y));
}

void Rectangle::setFillColor(const dr4::Color& color) {
    shape_.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
}

void Rectangle::setOutline(float thickness, const dr4::Color& color) {
    shape_.setOutlineThickness(thickness);
    shape_.setOutlineColor(sf::Color(color.r, color.g, color.b, color.a));
}

void Rectangle::setPosition(const dr4::Vec2f& position) {
    shape_.setPosition(position.x, position.y);
}

void Rectangle::setRotation(float angle) {
    shape_.setRotation(angle);
}

void Rectangle::setOrigin(const dr4::Vec2f& origin) {
    shape_.setOrigin(origin.x, origin.y);
}

VertexCollection::VertexCollection() {
    vertices_.setPrimitiveType(sf::Points);
}

void VertexCollection::setType(sf::PrimitiveType type) {
    vertices_.setPrimitiveType(type);
}

void VertexCollection::addVertex(const dr4::Vec2f& position, const dr4::Color& color) {
    vertices_.append(sf::Vertex(
        sf::Vector2f(position.x, position.y),
        sf::Color(color.r, color.g, color.b, color.a)
    ));
}

void VertexCollection::clear() {
    vertices_.clear();
}

void VertexCollection::resize(size_t count) {
    vertices_.resize(count);
}

sf::Vertex& VertexCollection::operator[](size_t index) {
    return vertices_[index];
}

}