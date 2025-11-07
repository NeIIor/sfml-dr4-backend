#pragma once

#include "dr4/texture.hpp"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>

class Texture : public dr4::Texture {
public:
    Texture();
    virtual ~Texture() override;

    void SetSize(dr4::Vec2f size) override;
    dr4::Vec2f GetSize() const override;
    float GetWidth() const override;
    float GetHeight() const override;

    void Clear(dr4::Color color) override;
    void Draw(const dr4::Rectangle& rect) override;
    void Draw(const dr4::Text& text) override;
    void Draw(const dr4::Image& img, const dr4::Vec2f& pos) override;
    void Draw(const dr4::Texture& texture, const dr4::Vec2f& pos) override;

    const sf::RenderTexture& getRenderTexture() const { return render_texture_; }

private:
    void ensureFontLoaded();

    sf::RenderTexture render_texture_;
    std::unique_ptr<sf::Font> default_font_;
    bool font_loaded_ = false;
};