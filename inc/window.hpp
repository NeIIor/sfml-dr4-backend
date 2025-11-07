#pragma once

#include "dr4/window.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <memory>
#include <vector>

class Texture;
class Image;
class Font;
class Rectangle;
class Text;

class Window : public dr4::Window {
public:
    Window();
    virtual ~Window() override;

    void SetTitle(const std::string& title) override;
    const std::string& GetTitle() const override;

    dr4::Vec2f GetSize() const override;
    void SetSize(const dr4::Vec2f& size) override;

    void Open() override;
    bool IsOpen() const override;
    void Close() override;

    void Clear(const dr4::Color& color) override;
    void Draw(const dr4::Texture& texture, dr4::Vec2f pos) override;
    void Display() override;

    dr4::Texture* CreateTexture() override;
    dr4::Image* CreateImage() override;
    dr4::Font* CreateFont() override;
    dr4::Rectangle* CreateRectangle() override;
    dr4::Text* CreateText() override;

    std::optional<dr4::Event> PollEvent() override;

private:
    dr4::Event convertEvent(const sf::Event& sf_event);
    dr4::KeyCode convertKey(sf::Keyboard::Key key);
    dr4::KeyMode convertKeyModifiers(const sf::Event& sf_event);
    dr4::MouseButton convertMouse(sf::Mouse::Button button);

    std::string title_;
    dr4::Vec2f size_; 
    sf::RenderWindow sf_window_;
    std::vector<std::unique_ptr<dr4::Texture>> textures_;
    std::vector<std::unique_ptr<dr4::Image>> images_;
    std::vector<std::unique_ptr<dr4::Font>> fonts_;
    std::vector<std::unique_ptr<dr4::Rectangle>> rectangles_;
    std::vector<std::unique_ptr<dr4::Text>> texts_;
};