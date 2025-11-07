#include "texture.hpp"
#include "image.hpp"
#include "font.hpp"
#include "rectangle.hpp"
#include "text.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

Texture::Texture() {
    render_texture_.create(1, 1);
    sf::View view(sf::FloatRect(0, 1, 1, -1)); 
    render_texture_.setView(view);
}

Texture::~Texture() {
}

void Texture::SetSize(dr4::Vec2f size) {
    render_texture_.create(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y));
    sf::View view(sf::FloatRect(0, size.y, size.x, -size.y)); 
    render_texture_.setView(view);    
}

dr4::Vec2f Texture::GetSize() const {
    auto size = render_texture_.getSize();
    return {static_cast<float>(size.x), static_cast<float>(size.y)};
}

float Texture::GetWidth() const {
    return GetSize().x;
}

float Texture::GetHeight() const {
    return GetSize().y;
}

void Texture::Clear(dr4::Color color) {
    render_texture_.clear(sf::Color(color.r, color.g, color.b, color.a));
}

void Texture::Draw(const dr4::Rectangle& rect) {
    const auto& concrete_rect = dynamic_cast<const Rectangle&>(rect);
    
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(concrete_rect.getRect().size.x, concrete_rect.getRect().size.y));
    
    float invertedY = GetHeight() - concrete_rect.getRect().pos.y - concrete_rect.getRect().size.y;
    shape.setPosition(concrete_rect.getRect().pos.x, invertedY);
    
    shape.setFillColor(sf::Color(
        concrete_rect.getFill().r, 
        concrete_rect.getFill().g, 
        concrete_rect.getFill().b, 
        concrete_rect.getFill().a
    ));
    
    if (concrete_rect.getBorderThickness() > 0) {
        shape.setOutlineThickness(concrete_rect.getBorderThickness());
        shape.setOutlineColor(sf::Color(
            concrete_rect.getBorderColor().r,
            concrete_rect.getBorderColor().g,
            concrete_rect.getBorderColor().b,
            concrete_rect.getBorderColor().a
        ));
    }
    
    render_texture_.draw(shape);
}

void Texture::Draw(const dr4::Text& text) {
    const auto& concrete_text = dynamic_cast<const Text&>(text);
    
    ensureFontLoaded();
    
    sf::Text sf_text;
    if (default_font_) {
        sf_text.setFont(*default_font_);
    }
    sf_text.setCharacterSize(static_cast<unsigned>(concrete_text.getFontSize()));
    
    float invertedY = GetHeight() - concrete_text.getPos().y - concrete_text.getFontSize();
    
    sf_text.setPosition(concrete_text.getPos().x, invertedY);
    sf_text.setFillColor(sf::Color(
        concrete_text.getColor().r,
        concrete_text.getColor().g, 
        concrete_text.getColor().b,
        concrete_text.getColor().a
    ));
    sf_text.setString(concrete_text.getText());
    
    render_texture_.draw(sf_text);
}

void Texture::Draw(const dr4::Image& img, const dr4::Vec2f& pos) {
    const auto& concrete_img = dynamic_cast<const Image&>(img);
    sf::RenderStates states;
    float invertedY = GetHeight() - pos.y - concrete_img.GetSize().y;
    states.transform.translate(pos.x, invertedY);
    render_texture_.draw(concrete_img.getVertices(), states);
}

void Texture::Draw(const dr4::Texture& texture, const dr4::Vec2f& pos) {
    const auto& concrete_texture = dynamic_cast<const Texture&>(texture);
    sf::Sprite sprite(concrete_texture.render_texture_.getTexture());
    float invertedY = GetHeight() - pos.y - concrete_texture.GetHeight();
    sprite.setPosition(pos.x, invertedY);
    render_texture_.draw(sprite);
}

void Texture::ensureFontLoaded() {
    if (font_loaded_) return;
    
    default_font_ = std::make_unique<sf::Font>();
    std::vector<std::string> font_paths = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "C:/Windows/Fonts/arial.ttf",
        "/Library/Fonts/Arial.ttf"
    };
    
    for (const auto& path : font_paths) {
        if (default_font_->loadFromFile(path)) {
            font_loaded_ = true;
            return;
        }
    }
    
    font_loaded_ = false;
}