#include "image_impl.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>

void SFMLImage::SetPixel(unsigned x, unsigned y, dr4::Vec2f color) {
    vertices_[y * width_ + x].color = sf::Color(
        static_cast<uint8_t>(color.x * 255),
        static_cast<uint8_t>(color.y * 255),
        0, 255
    );
}

dr4::Color SFMLImage::GetPixel(unsigned x, unsigned y) const {
    const auto& vertex = vertices_[y * width_ + x];
    return {vertex.color.r, vertex.color.g, vertex.color.b, vertex.color.a};
}

void SFMLImage::SetSize(dr4::Vec2f size) {
    width_ = size.x;
    height_ = size.y;
    vertices_.resize(width_ * height_);
}

dr4::Vec2f SFMLImage::GetSize() const {
    return {width_, height_};
}

float SFMLImage::GetWidth() const {
    return width_;
}

float SFMLImage::GetHeight() const {
    return height_;
}