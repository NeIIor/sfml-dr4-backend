#include "font.hpp"
#include <SFML/Graphics/Font.hpp>

Font::Font() {
}

Font::~Font() {
}

void Font::LoadFromFile(const std::string& path) {
    loaded_ = font_.loadFromFile(path);
}

void Font::LoadFromBuffer(const void* buffer, size_t size) {
    loaded_ = font_.loadFromMemory(buffer, size);
}

float Font::GetAscent(float fontSize) {
    if (!loaded_) return fontSize * 0.8f;
    
    return fontSize * 0.8f;
}

float Font::GetDescent(float fontSize) {
    if (!loaded_) return -fontSize * 0.2f;
    
    return -fontSize * 0.2f;
}