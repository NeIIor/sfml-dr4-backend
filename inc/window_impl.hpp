#pragma once

#include "dr4/window.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class SFMLWindow : public dr4::Window {
public:
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

    std::optional<dr4::Event> PollEvent() override;

private:
    dr4::Event ConvertSFMLEvent(const sf::Event& sf_event);

    std::string title_;
    sf::RenderWindow window_;
};