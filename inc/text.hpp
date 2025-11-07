#pragma once

#include "dr4/texture.hpp"
#include <string>

class Text : public dr4::Text {
public:
    Text();
    virtual ~Text() override;

    void SetPos(dr4::Vec2f pos) override;
    void SetText(const std::string& text) override;
    void SetColor(const dr4::Color& color) override;
    void SetFontSize(float size) override;
    void SetVAlign(VAlign align) override;
    void SetFont(const dr4::Font* font) override;

    float GetWidth() const override;

    const dr4::Vec2f& getPos() const { return pos_; }
    const std::string& getText() const { return text_; }
    const dr4::Color& getColor() const { return color_; }
    float getFontSize() const { return font_size_; }
    VAlign getVAlign() const { return valign_; }
    const dr4::Font* getFont() const { return font_; }

private:
    dr4::Vec2f pos_ = {0.0f, 0.0f};
    std::string text_;
    dr4::Color color_ = {255, 255, 255, 255};
    float font_size_ = 16.0f;
    VAlign valign_ = VAlign::TOP;
    const dr4::Font* font_ = nullptr;
};