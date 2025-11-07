#pragma once

#include "dr4/texture.hpp"

class Rectangle : public dr4::Rectangle {
public:
    Rectangle();
    virtual ~Rectangle() override;

    void SetRect(const dr4::Rect2f& rect) override;
    void SetFill(const dr4::Color& color) override;
    void SetBorderThickness(float thickness) override;
    void SetBorderColor(const dr4::Color& color) override;

    const dr4::Rect2f& getRect() const { return rect_; }
    const dr4::Color& getFill() const { return fill_; }
    float getBorderThickness() const { return border_thickness_; }
    const dr4::Color& getBorderColor() const { return border_color_; }

private:
    dr4::Rect2f rect_;
    dr4::Color fill_;
    float border_thickness_ = 0.0f;
    dr4::Color border_color_;
};