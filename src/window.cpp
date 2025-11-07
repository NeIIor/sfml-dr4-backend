#include "window.hpp"
#include "texture.hpp"
#include "image.hpp"
#include "font.hpp"
#include "rectangle.hpp"
#include "text.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

Window::Window() : title_("SFML Window") {
}

Window::~Window() {
    if (sf_window_.isOpen()) {
        sf_window_.close();
    }
}

void Window::SetTitle(const std::string& title) {
    title_ = title;
    if (sf_window_.isOpen()) {
        sf_window_.setTitle(title_);
    }
}

const std::string& Window::GetTitle() const {
    return title_;
}

dr4::Vec2f Window::GetSize() const {
    auto size = sf_window_.getSize();
    return {static_cast<float>(size.x), static_cast<float>(size.y)};
}

void Window::SetSize(const dr4::Vec2f& size) {
    if (sf_window_.isOpen()) {
        sf_window_.setSize(sf::Vector2u(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y)));
    }
}

void Window::Open() {
    if (!sf_window_.isOpen()) {
        sf_window_.create(sf::VideoMode(1600, 1000), title_);
        sf_window_.setFramerateLimit(60);
    }
}

bool Window::IsOpen() const {
    return sf_window_.isOpen();
}

void Window::Close() {
    if (sf_window_.isOpen()) {
        sf_window_.close();
    }
}

void Window::Clear(const dr4::Color& color) {
    sf_window_.clear(sf::Color(color.r, color.g, color.b, color.a));
}

void Window::Draw(const dr4::Texture& texture, dr4::Vec2f pos) {
    const auto& concrete_texture = dynamic_cast<const Texture&>(texture);
    sf::Sprite sprite(concrete_texture.getRenderTexture().getTexture());
    
    auto window_size = sf_window_.getSize();
    auto texture_size = concrete_texture.getRenderTexture().getTexture().getSize();
    
    sprite.setPosition(pos.x, window_size.y - pos.y - texture_size.y);
    
    sf_window_.draw(sprite);
}

void Window::Display() {
    sf_window_.display();
}

dr4::Texture* Window::CreateTexture() {
    textures_.push_back(std::make_unique<Texture>());
    return textures_.back().get();
}

dr4::Image* Window::CreateImage() {
    images_.push_back(std::make_unique<Image>());
    return images_.back().get();
}

dr4::Font* Window::CreateFont() {
    fonts_.push_back(std::make_unique<Font>());
    return fonts_.back().get();
}

dr4::Rectangle* Window::CreateRectangle() {
    rectangles_.push_back(std::make_unique<Rectangle>());
    return rectangles_.back().get();
}

dr4::Text* Window::CreateText() {
    texts_.push_back(std::make_unique<Text>());
    return texts_.back().get();
}

std::optional<dr4::Event> Window::PollEvent() {
    sf::Event sf_event;
    if (sf_window_.pollEvent(sf_event)) {
        return convertEvent(sf_event);
    }
    return std::nullopt;
}

dr4::Event Window::convertEvent(const sf::Event& sf_event) {
    dr4::Event event;
    
    switch (sf_event.type) {
        case sf::Event::Closed:
            event.type = dr4::Event::Type::QUIT;
            break;
            
        case sf::Event::KeyPressed: {
            event.type = dr4::Event::Type::KEY_DOWN;
            event.key.sym = convertKey(sf_event.key.code);
            event.key.mod = convertKeyModifiers(sf_event);
            break;
        }
            
        case sf::Event::KeyReleased: {
            event.type = dr4::Event::Type::KEY_UP;
            event.key.sym = convertKey(sf_event.key.code);
            event.key.mod = convertKeyModifiers(sf_event);
            break;
        }
            
        case sf::Event::MouseButtonPressed: {
            event.type = dr4::Event::Type::MOUSE_DOWN;
            event.mouseButton.button = convertMouse(sf_event.mouseButton.button);
            event.mouseButton.pos = {
                static_cast<float>(sf_event.mouseButton.x), 
                static_cast<float>(sf_event.mouseButton.y)
            };
            break;
        }
            
        case sf::Event::MouseButtonReleased: {
            event.type = dr4::Event::Type::MOUSE_UP;
            event.mouseButton.button = convertMouse(sf_event.mouseButton.button);
            event.mouseButton.pos = {
                static_cast<float>(sf_event.mouseButton.x), 
                static_cast<float>(sf_event.mouseButton.y)
            };
            break;
        }
            
        case sf::Event::MouseMoved: {
            event.type = dr4::Event::Type::MOUSE_MOVE;
            event.mouseMove.pos = {
                static_cast<float>(sf_event.mouseMove.x), 
                static_cast<float>(sf_event.mouseMove.y)
            };
            event.mouseMove.rel = {0.0f, 0.0f};
            break;
        }
            
        case sf::Event::MouseWheelScrolled: {
            event.type = dr4::Event::Type::MOUSE_WHEEL;
            event.mouseWheel.delta = static_cast<int>(sf_event.mouseWheelScroll.delta);
            event.mouseWheel.pos = {
                static_cast<float>(sf_event.mouseWheelScroll.x), 
                static_cast<float>(sf_event.mouseWheelScroll.y)
            };
            break;
        }
            
        case sf::Event::TextEntered: {
            event.type = dr4::Event::Type::TEXT_EVENT;
            event.text.unicode = sf_event.text.unicode;
            break;
        }
            
        default:
            event.type = dr4::Event::Type::UNKNOWN;
            break;
    }
    
    return event;
}

dr4::KeyMode Window::convertKeyModifiers(const sf::Event& sf_event) {
    dr4::KeyMode mod = dr4::KEYMOD_NONE;
    if (sf_event.key.shift) mod = static_cast<dr4::KeyMode>(mod | dr4::KEYMOD_SHIFT);
    if (sf_event.key.control) mod = static_cast<dr4::KeyMode>(mod | dr4::KEYMOD_CTRL);
    if (sf_event.key.alt) mod = static_cast<dr4::KeyMode>(mod | dr4::KEYMOD_ALT);
    return mod;
}

dr4::KeyCode Window::convertKey(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::A: return dr4::KEYCODE_A;
        case sf::Keyboard::B: return dr4::KEYCODE_B;
        case sf::Keyboard::C: return dr4::KEYCODE_C;
        case sf::Keyboard::D: return dr4::KEYCODE_D;
        case sf::Keyboard::E: return dr4::KEYCODE_E;
        case sf::Keyboard::F: return dr4::KEYCODE_F;
        case sf::Keyboard::G: return dr4::KEYCODE_G;
        case sf::Keyboard::H: return dr4::KEYCODE_H;
        case sf::Keyboard::I: return dr4::KEYCODE_I;
        case sf::Keyboard::J: return dr4::KEYCODE_J;
        case sf::Keyboard::K: return dr4::KEYCODE_K;
        case sf::Keyboard::L: return dr4::KEYCODE_L;
        case sf::Keyboard::M: return dr4::KEYCODE_M;
        case sf::Keyboard::N: return dr4::KEYCODE_N;
        case sf::Keyboard::O: return dr4::KEYCODE_O;
        case sf::Keyboard::P: return dr4::KEYCODE_P;
        case sf::Keyboard::Q: return dr4::KEYCODE_Q;
        case sf::Keyboard::R: return dr4::KEYCODE_R;
        case sf::Keyboard::S: return dr4::KEYCODE_S;
        case sf::Keyboard::T: return dr4::KEYCODE_T;
        case sf::Keyboard::U: return dr4::KEYCODE_U;
        case sf::Keyboard::V: return dr4::KEYCODE_V;
        case sf::Keyboard::W: return dr4::KEYCODE_W;
        case sf::Keyboard::X: return dr4::KEYCODE_X;
        case sf::Keyboard::Y: return dr4::KEYCODE_Y;
        case sf::Keyboard::Z: return dr4::KEYCODE_Z;
        case sf::Keyboard::Num0: return dr4::KEYCODE_NUM0;
        case sf::Keyboard::Num1: return dr4::KEYCODE_NUM1;
        case sf::Keyboard::Num2: return dr4::KEYCODE_NUM2;
        case sf::Keyboard::Num3: return dr4::KEYCODE_NUM3;
        case sf::Keyboard::Num4: return dr4::KEYCODE_NUM4;
        case sf::Keyboard::Num5: return dr4::KEYCODE_NUM5;
        case sf::Keyboard::Num6: return dr4::KEYCODE_NUM6;
        case sf::Keyboard::Num7: return dr4::KEYCODE_NUM7;
        case sf::Keyboard::Num8: return dr4::KEYCODE_NUM8;
        case sf::Keyboard::Num9: return dr4::KEYCODE_NUM9;
        case sf::Keyboard::Escape: return dr4::KEYCODE_ESCAPE;
        case sf::Keyboard::Space: return dr4::KEYCODE_SPACE;
        case sf::Keyboard::Enter: return dr4::KEYCODE_ENTER;
        case sf::Keyboard::Backspace: return dr4::KEYCODE_BACKSPACE;
        case sf::Keyboard::Tab: return dr4::KEYCODE_TAB;
        case sf::Keyboard::Left: return dr4::KEYCODE_LEFT;
        case sf::Keyboard::Right: return dr4::KEYCODE_RIGHT;
        case sf::Keyboard::Up: return dr4::KEYCODE_UP;
        case sf::Keyboard::Down: return dr4::KEYCODE_DOWN;
        default: return dr4::KEYCODE_UNKNOWN;
    }
}

dr4::MouseButton Window::convertMouse(sf::Mouse::Button button) {
    switch (button) {
        case sf::Mouse::Left: return dr4::MouseButton::LEFT;
        case sf::Mouse::Right: return dr4::MouseButton::RIGHT;
        case sf::Mouse::Middle: return dr4::MouseButton::MIDDLE;
        default: return dr4::MouseButton::UNKNOWN;
    }
}