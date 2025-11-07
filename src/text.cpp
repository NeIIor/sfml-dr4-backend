#include "text.hpp"

Text::Text() {
}

Text::~Text() {
}

void Text::SetPos(dr4::Vec2f pos) {
    pos_ = pos;
}

void Text::SetText(const std::string& text) {
    text_ = text;
}

void Text::SetColor(const dr4::Color& color) {
    color_ = color;
}

void Text::SetFontSize(float size) {
    font_size_ = size;
}

void Text::SetVAlign(VAlign align) {
    valign_ = align;
}

void Text::SetFont(const dr4::Font* font) {
    font_ = font;
}

float Text::GetWidth() const {
    return text_.length() * font_size_ * 0.6f;
}