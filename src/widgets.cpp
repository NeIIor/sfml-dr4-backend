#include "widgets.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>

namespace Widgets {

Button::Button(const dr4::Vec2f& position, const dr4::Vec2f& size, const std::string& label) {
    background_.setSize(sf::Vector2f(size.x, size.y));
    background_.setPosition(position.x, position.y);
    background_.setFillColor(sf::Color(normal_color_.r, normal_color_.g, normal_color_.b, normal_color_.a));
    
    label_.setString(label);
    label_.setCharacterSize(16);
    label_.setFillColor(sf::Color::White);
    
    setPosition(position);
}

void Button::setPosition(const dr4::Vec2f& position) {
    background_.setPosition(position.x, position.y);
    centerText();
}

void Button::setSize(const dr4::Vec2f& size) {
    background_.setSize(sf::Vector2f(size.x, size.y));
    centerText();
}

void Button::setLabel(const std::string& label) {
    label_.setString(label);
    centerText();
}

void Button::setColors(const dr4::Color& normal, const dr4::Color& hover, const dr4::Color& press) {
    normal_color_ = normal;
    hover_color_ = hover;
    press_color_ = press;
    updateAppearance();
}

void Button::setFont(const sf::Font& font, unsigned size) {
    label_.setFont(font);
    label_.setCharacterSize(size);
    centerText();
}

bool Button::contains(const dr4::Vec2f& point) const {
    auto pos = background_.getPosition();
    auto size = background_.getSize();
    return point.x >= pos.x && point.x <= pos.x + size.x &&
           point.y >= pos.y && point.y <= pos.y + size.y;
}

void Button::onMouseEnter() {
    hovered_ = true;
    updateAppearance();
}

void Button::onMouseLeave() {
    hovered_ = false;
    updateAppearance();
}

void Button::onMousePress() {
    pressed_ = true;
    updateAppearance();
}

void Button::onMouseRelease() {
    if (pressed_ && hovered_) {
        clicked_ = true;
    }
    pressed_ = false;
    updateAppearance();
}

bool Button::wasClicked() const {
    return clicked_;
}

void Button::draw(sf::RenderTarget& target) const {
    target.draw(background_);
    target.draw(label_);
}

void Button::updateAppearance() {
    if (pressed_) {
        background_.setFillColor(sf::Color(press_color_.r, press_color_.g, press_color_.b, press_color_.a));
    } else if (hovered_) {
        background_.setFillColor(sf::Color(hover_color_.r, hover_color_.g, hover_color_.b, hover_color_.a));
    } else {
        background_.setFillColor(sf::Color(normal_color_.r, normal_color_.g, normal_color_.b, normal_color_.a));
    }
}

void Button::centerText() {
    auto bounds = label_.getLocalBounds();
    auto button_pos = background_.getPosition();
    auto button_size = background_.getSize();
    
    label_.setPosition(
        button_pos.x + (button_size.x - bounds.width) / 2 - bounds.left,
        button_pos.y + (button_size.y - bounds.height) / 2 - bounds.top
    );
}

TextField::TextField(const dr4::Vec2f& position, const dr4::Vec2f& size) {
    background_.setSize(sf::Vector2f(size.x, size.y));
    background_.setPosition(position.x, position.y);
    background_.setFillColor(sf::Color(background_color_.r, background_color_.g, background_color_.b, background_color_.a));
    background_.setOutlineThickness(2);
    background_.setOutlineColor(sf::Color(border_color_.r, border_color_.g, border_color_.b, border_color_.a));
    
    cursor_.setSize(sf::Vector2f(2, size.y * 0.8f));
    cursor_.setFillColor(sf::Color::White);
    
    setPosition(position);
}

void TextField::setPosition(const dr4::Vec2f& position) {
    background_.setPosition(position.x, position.y);
    updateTextDisplay();
    updateCursor();
}

void TextField::setSize(const dr4::Vec2f& size) {
    background_.setSize(sf::Vector2f(size.x, size.y));
    cursor_.setSize(sf::Vector2f(2, size.y * 0.8f));
    updateTextDisplay();
    updateCursor();
}

void TextField::setText(const std::string& text) {
    text_ = text;
    updateTextDisplay();
    updateCursor();
}

void TextField::setFont(const sf::Font& font, unsigned size) {
    display_text_.setFont(font);
    display_text_.setCharacterSize(size);
    display_text_.setFillColor(sf::Color(text_color_.r, text_color_.g, text_color_.b, text_color_.a));
    updateTextDisplay();
    updateCursor();
}

void TextField::setColors(const dr4::Color& background, const dr4::Color& text, const dr4::Color& border) {
    background_color_ = background;
    text_color_ = text;
    border_color_ = border;
    
    background_.setFillColor(sf::Color(background_color_.r, background_color_.g, background_color_.b, background_color_.a));
    background_.setOutlineColor(sf::Color(border_color_.r, border_color_.g, border_color_.b, border_color_.a));
    display_text_.setFillColor(sf::Color(text_color_.r, text_color_.g, text_color_.b, text_color_.a));
}

bool TextField::contains(const dr4::Vec2f& point) const {
    auto pos = background_.getPosition();
    auto size = background_.getSize();
    return point.x >= pos.x && point.x <= pos.x + size.x &&
           point.y >= pos.y && point.y <= pos.y + size.y;
}

void TextField::setFocus(bool focused) {
    focused_ = focused;
    cursor_visible_ = focused;
    cursor_timer_ = 0.0f;
    
    if (focused) {
        background_.setOutlineColor(sf::Color(200, 200, 255, 255));
    } else {
        background_.setOutlineColor(sf::Color(border_color_.r, border_color_.g, border_color_.b, border_color_.a));
    }
}

void TextField::addCharacter(char c) {
    if (c >= 32 && c <= 126) {
        text_ += c;
        updateTextDisplay();
        updateCursor();
    }
}

void TextField::backspace() {
    if (!text_.empty()) {
        text_.pop_back();
        updateTextDisplay();
        updateCursor();
    }
}

void TextField::draw(sf::RenderTarget& target) const {
    target.draw(background_);
    target.draw(display_text_);
    
    if (focused_ && cursor_visible_) {
        target.draw(cursor_);
    }
}

void TextField::updateCursor() {
    auto text_bounds = display_text_.getLocalBounds();
    auto field_pos = background_.getPosition();
    auto field_size = background_.getSize();
    
    float text_width = display_text_.findCharacterPos(text_.size()).x - display_text_.getPosition().x;
    cursor_.setPosition(
        field_pos.x + 5 + text_width,
        field_pos.y + (field_size.y - cursor_.getSize().y) / 2
    );
}

void TextField::updateTextDisplay() {
    display_text_.setString(text_);
    
    auto field_pos = background_.getPosition();
    display_text_.setPosition(field_pos.x + 5, field_pos.y + 5);
}

ScrollBar::ScrollBar(const dr4::Vec2f& position, const dr4::Vec2f& size, bool vertical) 
    : vertical_(vertical) {
    track_.setSize(sf::Vector2f(size.x, size.y));
    track_.setPosition(position.x, position.y);
    track_.setFillColor(sf::Color(100, 100, 100, 255));
    
    float thumb_size = vertical ? size.x : size.y;
    sf::Vector2f thumb_dim = vertical ? 
        sf::Vector2f(size.x, thumb_size) : 
        sf::Vector2f(thumb_size, size.y);
        
    thumb_.setSize(thumb_dim);
    thumb_.setFillColor(sf::Color(150, 150, 150, 255));
    
    setPosition(position);
}

void ScrollBar::setPosition(const dr4::Vec2f& position) {
    track_.setPosition(position.x, position.y);
    updateThumbPosition();
}

void ScrollBar::setSize(const dr4::Vec2f& size) {
    track_.setSize(sf::Vector2f(size.x, size.y));
    updateThumbPosition();
}

void ScrollBar::setScrollRange(float min, float max) {
    min_scroll_ = min;
    max_scroll_ = max;
    updateThumbPosition();
}

void ScrollBar::setScrollPosition(float position) {
    scroll_position_ = std::clamp(position, min_scroll_, max_scroll_);
    updateThumbPosition();
}

void ScrollBar::setColors(const dr4::Color& track, const dr4::Color& thumb) {
    track_.setFillColor(sf::Color(track.r, track.g, track.b, track.a));
    thumb_.setFillColor(sf::Color(thumb.r, thumb.g, thumb.b, thumb.a));
}

bool ScrollBar::contains(const dr4::Vec2f& point) const {
    auto pos = track_.getPosition();
    auto size = track_.getSize();
    return point.x >= pos.x && point.x <= pos.x + size.x &&
           point.y >= pos.y && point.y <= pos.y + size.y;
}

void ScrollBar::onMouseDrag(const dr4::Vec2f& position) {
    if (!dragging_) return;
    
    auto track_pos = track_.getPosition();
    auto track_size = track_.getSize();
    auto thumb_size = thumb_.getSize();
    
    if (vertical_) {
        float track_height = track_size.y - thumb_size.y;
        float relative_y = position.y - track_pos.y - thumb_drag_offset_;
        float percentage = std::clamp(relative_y / track_height, 0.0f, 1.0f);
        scroll_position_ = min_scroll_ + percentage * (max_scroll_ - min_scroll_);
    } else {
        float track_width = track_size.x - thumb_size.x;
        float relative_x = position.x - track_pos.x - thumb_drag_offset_;
        float percentage = std::clamp(relative_x / track_width, 0.0f, 1.0f);
        scroll_position_ = min_scroll_ + percentage * (max_scroll_ - min_scroll_);
    }
    
    updateThumbPosition();
}

float ScrollBar::getScrollPercentage() const {
    if (max_scroll_ == min_scroll_) return 0.0f;
    return (scroll_position_ - min_scroll_) / (max_scroll_ - min_scroll_);
}

void ScrollBar::draw(sf::RenderTarget& target) const {
    target.draw(track_);
    target.draw(thumb_);
}

void ScrollBar::updateThumbPosition() {
    auto track_pos = track_.getPosition();
    auto track_size = track_.getSize();
    auto thumb_size = thumb_.getSize();
    
    float percentage = getScrollPercentage();
    
    if (vertical_) {
        float available_height = track_size.y - thumb_size.y;
        thumb_.setPosition(
            track_pos.x,
            track_pos.y + percentage * available_height
        );
    } else {
        float available_width = track_size.x - thumb_size.x;
        thumb_.setPosition(
            track_pos.x + percentage * available_width,
            track_pos.y
        );
    }
}

}