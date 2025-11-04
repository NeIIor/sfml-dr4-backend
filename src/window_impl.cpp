#include "window_impl.hpp"
#include "texture_impl.hpp"
#include "image_impl.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

void SFMLWindow::SetTitle(const std::string& title) {
    title_ = title;
    window_.setTitle(title_);
}

const std::string& SFMLWindow::GetTitle() const {
    return title_;
}

dr4::Vec2f SFMLWindow::GetSize() const {
    auto size = window_.getSize();
    return {static_cast<float>(size.x), static_cast<float>(size.y)};
}

void SFMLWindow::SetSize(const dr4::Vec2f& size) {
    window_.setSize(sf::Vector2u(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y)));
}

void SFMLWindow::Open() {
    window_.create(sf::VideoMode(800, 600), title_);
}

bool SFMLWindow::IsOpen() const {
    return window_.isOpen();
}

void SFMLWindow::Close() {
    window_.close();
}

void SFMLWindow::Clear(const dr4::Color& color) {
    window_.clear(sf::Color(color.r, color.g, color.b, color.a));
}

void SFMLWindow::Draw(const dr4::Texture& texture, dr4::Vec2f pos) {
    const auto& sfml_texture = dynamic_cast<const SFMLTexture&>(texture);
    sf::Sprite sprite(sfml_texture.GetRenderTexture().getTexture());
    sprite.setPosition({pos.x, pos.y});
    window_.draw(sprite);
}

void SFMLWindow::Display() {
    window_.display();
}

dr4::Texture* SFMLWindow::CreateTexture() {
    return new SFMLTexture();
}

dr4::Image* SFMLWindow::CreateImage() {
    return new SFMLImage(100, 100);
}

std::optional<dr4::Event> SFMLWindow::PollEvent() {
    sf::Event sf_event;
    if (window_.pollEvent(sf_event)) {
        return ConvertSFMLEvent(sf_event);
    }
    return std::nullopt;
}

dr4::Event SFMLWindow::ConvertSFMLEvent(const sf::Event& sf_event) {
    dr4::Event event;
    
    switch (sf_event.type) {
        case sf::Event::Closed:
            event.type = dr4::Event::Type::QUIT;
            break;
        case sf::Event::KeyPressed:
            event.type = dr4::Event::Type::KEY_DOWN;
            break;
        case sf::Event::KeyReleased:
            event.type = dr4::Event::Type::KEY_UP;
            break;
        case sf::Event::MouseButtonPressed:
            event.type = dr4::Event::Type::MOUSE_DOWN;
            break;
        case sf::Event::MouseButtonReleased:
            event.type = dr4::Event::Type::MOUSE_UP;
            break;
        case sf::Event::MouseMoved:
            event.type = dr4::Event::Type::MOUSE_MOVE;
            break;
        default:
            event.type = dr4::Event::Type::UNKNOWN;
            break;
    }
    
    return event;
}