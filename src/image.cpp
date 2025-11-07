#include "image.hpp"
#include <SFML/Graphics/Color.hpp>

Image::Image() {
    updateVertices();
}

Image::~Image() {
}

void Image::SetPixel(unsigned x, unsigned y, dr4::Color color) {
    if (x < static_cast<unsigned>(size_.x) && y < static_cast<unsigned>(size_.y)) {
        unsigned index = y * static_cast<unsigned>(size_.x) + x;
        if (index < pixels_.size()) {
            pixels_[index] = color;
            vertices_[index].color = sf::Color(color.r, color.g, color.b, color.a);
        }
    }
}

dr4::Color Image::GetPixel(unsigned x, unsigned y) const {
    if (x < static_cast<unsigned>(size_.x) && y < static_cast<unsigned>(size_.y)) {
        unsigned index = y * static_cast<unsigned>(size_.x) + x;
        if (index < pixels_.size()) {
            return pixels_[index];
        }
    }
    return {0, 0, 0, 0};
}

void Image::SetSize(dr4::Vec2f size) {
    size_ = size;
    pixels_.resize(static_cast<unsigned>(size.x) * static_cast<unsigned>(size.y), 
                   dr4::Color{0, 0, 0, 255});
    updateVertices();
}

dr4::Vec2f Image::GetSize() const {
    return size_;
}

float Image::GetWidth() const {
    return size_.x;
}

float Image::GetHeight() const {
    return size_.y;
}

void Image::updateVertices() {
    vertices_.setPrimitiveType(sf::Points);
    vertices_.resize(static_cast<unsigned>(size_.x * size_.y));
    
    for (unsigned y = 0; y < static_cast<unsigned>(size_.y); ++y) {
        for (unsigned x = 0; x < static_cast<unsigned>(size_.x); ++x) {
            auto& vertex = vertices_[y * static_cast<unsigned>(size_.x) + x];
            vertex.position = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
            
            unsigned index = y * static_cast<unsigned>(size_.x) + x;
            if (index < pixels_.size()) {
                const auto& color = pixels_[index];
                vertex.color = sf::Color(color.r, color.g, color.b, color.a);
            } else {
                vertex.color = sf::Color::White;
            }
        }
    }
}