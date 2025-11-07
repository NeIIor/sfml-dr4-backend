#pragma once

#include "dr4/texture.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

class Image : public dr4::Image {
public:
    Image();
    virtual ~Image() override;

    void SetPixel(unsigned x, unsigned y, dr4::Color color) override;
    dr4::Color GetPixel(unsigned x, unsigned y) const override;

    void SetSize(dr4::Vec2f size) override;
    dr4::Vec2f GetSize() const override;
    float GetWidth() const override;
    float GetHeight() const override;

    const sf::VertexArray& getVertices() const { return vertices_; }

private:
    void updateVertices();

    sf::VertexArray vertices_;
    std::vector<dr4::Color> pixels_;
    dr4::Vec2f size_ = {100.0f, 100.0f};
};