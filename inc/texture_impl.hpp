#pragma once

#include "dr4/texture.hpp"
#include <SFML/Graphics/RenderTexture.hpp>

class SFMLTexture : public dr4::Texture {
public:
    void SetSize(dr4::Vec2f size) override;
    dr4::Vec2f GetSize() const override;
    float GetWidth() const override;
    float GetHeight() const override;

    void Draw(const dr4::Rectangle& rect) override;
    void Draw(const dr4::Text& text) override;
    void Draw(const dr4::Image& img, const dr4::Vec2f& pos) override;
    void Draw(const dr4::Texture& texture, const dr4::Vec2f& pos) override;

    const sf::RenderTexture& GetRenderTexture() const { return render_texture_; }

private:
    sf::RenderTexture render_texture_;
};