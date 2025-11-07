#pragma once

#include "dr4/math/vec2.hpp"
#include "dr4/math/color.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <memory>

namespace Shapes {

class Circle {
public:
    Circle(float radius = 10.0f);
    void setRadius(float radius);
    void setFillColor(const dr4::Color& color);
    void setOutline(float thickness, const dr4::Color& color);
    void setPosition(const dr4::Vec2f& position);
    void setRotation(float angle);
    void setOrigin(const dr4::Vec2f& origin);
    
    const sf::CircleShape& getShape() const { return shape_; }

private:
    sf::CircleShape shape_;
};

class Rectangle {
public:
    Rectangle(const dr4::Vec2f& size = {20.0f, 20.0f});
    void setSize(const dr4::Vec2f& size);
    void setFillColor(const dr4::Color& color);
    void setOutline(float thickness, const dr4::Color& color);
    void setPosition(const dr4::Vec2f& position);
    void setRotation(float angle);
    void setOrigin(const dr4::Vec2f& origin);
    
    const sf::RectangleShape& getShape() const { return shape_; }

private:
    sf::RectangleShape shape_;
};

class VertexCollection {
public:
    VertexCollection();
    void setType(sf::PrimitiveType type);
    void addVertex(const dr4::Vec2f& position, const dr4::Color& color);
    void clear();
    void resize(size_t count);
    
    const sf::VertexArray& getVertices() const { return vertices_; }
    sf::Vertex& operator[](size_t index);

private:
    sf::VertexArray vertices_;
};

}