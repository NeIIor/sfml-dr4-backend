#include "texture_impl.hpp"
#include "image_impl.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transform.hpp>

void SFMLTexture::SetSize(dr4::Vec2f size) {
    render_texture_.create(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y));
}

dr4::Vec2f SFMLTexture::GetSize() const {
    auto size = render_texture_.getSize();
    return {static_cast<float>(size.x), static_cast<float>(size.y)};
}

float SFMLTexture::GetWidth() const {
    return GetSize().x;
}

float SFMLTexture::GetHeight() const {
    return GetSize().y;
}

void SFMLTexture::Draw(const dr4::Rectangle& rect) {
    sf::RectangleShape shape;
    shape.setSize({rect.rect.size.x, rect.rect.size.y});
    shape.setPosition({rect.rect.pos.x, rect.rect.pos.y});
    shape.setFillColor({rect.fill.r, rect.fill.g, rect.fill.b, rect.fill.a});
    shape.setOutlineColor({rect.borderColor.r, rect.borderColor.g, rect.borderColor.b, rect.borderColor.a});
    shape.setOutlineThickness(rect.borderThickness);
    render_texture_.draw(shape);
}

void SFMLTexture::Draw(const dr4::Text& text) {
    sf::Text sf_text;
    sf_text.setCharacterSize(static_cast<unsigned>(text.fontSize));
    sf_text.setPosition({text.pos.x, text.pos.y});
    sf_text.setFillColor({text.color.r, text.color.g, text.color.b, text.color.a});
    sf_text.setString(text.text);
    render_texture_.draw(sf_text);
}

void SFMLTexture::Draw(const dr4::Image& img, const dr4::Vec2f& pos) {
    const auto& sfml_img = dynamic_cast<const SFMLImage&>(img);
    sf::Transform transform;
    transform.translate({pos.x, pos.y});
    render_texture_.draw(sfml_img.GetVertices(), transform);
}

void SFMLTexture::Draw(const dr4::Texture& texture, const dr4::Vec2f& pos) {
    const auto& sfml_texture = dynamic_cast<const SFMLTexture&>(texture);
    sf::Sprite sprite(sfml_texture.GetRenderTexture().getTexture());
    sprite.setPosition({pos.x, pos.y});
    render_texture_.draw(sprite);
}