#pragma once

#include "dr4/texture.hpp"
#include <SFML/Graphics/VertexArray.hpp>

class SFMLImage : public dr4::Image {
public:
    SFMLImage(unsigned width, unsigned height) : dr4::Image(width, height) {
        SetSize({static_cast<float>(width), static_cast<float>(height)});
    }

    void SetPixel(unsigned x, unsigned y, dr4::Vec2f color) override;
    dr4::Color GetPixel(unsigned x, unsigned y) const override;

    void SetSize(dr4::Vec2f size) override;
    dr4::Vec2f GetSize() const override;
    float GetWidth() const override;
    float GetHeight() const override;

    const sf::VertexArray& GetVertices() const { return vertices_; }

private:
    sf::VertexArray vertices_;
    float width_ = 0;
    float height_ = 0;
};