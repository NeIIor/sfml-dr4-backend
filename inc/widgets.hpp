#pragma once

#include "dr4/math/vec2.hpp"
#include "dr4/math/color.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include <vector>
#include <functional>
#include <string>

namespace Widgets {

class Button {
public:
    Button(const dr4::Vec2f& position, const dr4::Vec2f& size, const std::string& label);
    
    void setPosition(const dr4::Vec2f& position);
    void setSize(const dr4::Vec2f& size);
    void setLabel(const std::string& label);
    void setColors(const dr4::Color& normal, const dr4::Color& hover, const dr4::Color& press);
    void setFont(const sf::Font& font, unsigned size);
    
    bool contains(const dr4::Vec2f& point) const;
    void onMouseEnter();
    void onMouseLeave();
    void onMousePress();
    void onMouseRelease();
    
    bool isPressed() const { return pressed_; }
    bool wasClicked() const;
    
    void draw(sf::RenderTarget& target) const;

private:
    void updateAppearance();
    void centerText();

    sf::RectangleShape background_;
    sf::Text label_;
    dr4::Color normal_color_ = {100, 100, 100, 255};
    dr4::Color hover_color_ = {150, 150, 150, 255};
    dr4::Color press_color_ = {50, 50, 50, 255};
    bool hovered_ = false;
    bool pressed_ = false;
    bool clicked_ = false;
};

class TextField {
public:
    TextField(const dr4::Vec2f& position, const dr4::Vec2f& size);
    
    void setPosition(const dr4::Vec2f& position);
    void setSize(const dr4::Vec2f& size);
    void setText(const std::string& text);
    void setFont(const sf::Font& font, unsigned size);
    void setColors(const dr4::Color& background, const dr4::Color& text, const dr4::Color& border);
    
    bool contains(const dr4::Vec2f& point) const;
    void setFocus(bool focused);
    void addCharacter(char c);
    void backspace();
    
    const std::string& getText() const { return text_; }
    void draw(sf::RenderTarget& target) const;

private:
    void updateCursor();
    void updateTextDisplay();

    sf::RectangleShape background_;
    sf::Text display_text_;
    sf::RectangleShape cursor_;
    std::string text_;
    dr4::Color background_color_ = {50, 50, 50, 255};
    dr4::Color text_color_ = {255, 255, 255, 255};
    dr4::Color border_color_ = {100, 100, 100, 255};
    bool focused_ = false;
    bool cursor_visible_ = true;
    float cursor_timer_ = 0.0f;
};

class ScrollBar {
public:
    ScrollBar(const dr4::Vec2f& position, const dr4::Vec2f& size, bool vertical = true);
    
    void setPosition(const dr4::Vec2f& position);
    void setSize(const dr4::Vec2f& size);
    void setScrollRange(float min, float max);
    void setScrollPosition(float position);
    void setColors(const dr4::Color& track, const dr4::Color& thumb);
    
    bool contains(const dr4::Vec2f& point) const;
    void onMouseDrag(const dr4::Vec2f& position);
    
    float getScrollPosition() const { return scroll_position_; }
    float getScrollPercentage() const;
    void draw(sf::RenderTarget& target) const;

private:
    void updateThumbPosition();

    sf::RectangleShape track_;
    sf::RectangleShape thumb_;
    bool vertical_;
    float min_scroll_ = 0.0f;
    float max_scroll_ = 100.0f;
    float scroll_position_ = 0.0f;
    float thumb_drag_offset_ = 0.0f;
    bool dragging_ = false;
};

}