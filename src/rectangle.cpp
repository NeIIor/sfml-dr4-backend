#include "rectangle.hpp"

Rectangle::Rectangle() 
    : rect_({0, 0}, {100, 100}), 
      fill_({255, 255, 255, 255}),
      border_color_({0, 0, 0, 255}) {
}

Rectangle::~Rectangle() {
}

void Rectangle::SetRect(const dr4::Rect2f& rect) {
    rect_ = rect;
}

void Rectangle::SetFill(const dr4::Color& color) {
    fill_ = color;
}

void Rectangle::SetBorderThickness(float thickness) {
    border_thickness_ = thickness;
}

void Rectangle::SetBorderColor(const dr4::Color& color) {
    border_color_ = color;
}