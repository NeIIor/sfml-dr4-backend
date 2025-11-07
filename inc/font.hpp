#pragma once

#include "dr4/texture.hpp"
#include <SFML/Graphics/Font.hpp>
#include <string>

class Font : public dr4::Font {
public:
    Font();
    virtual ~Font() override;

    void LoadFromFile(const std::string& path) override;
    void LoadFromBuffer(const void* buffer, size_t size) override;

    float GetAscent(float fontSize) override;
    float GetDescent(float fontSize) override;

    const sf::Font& getSFMLFont() const { return font_; }

private:
    sf::Font font_;
    bool loaded_ = false;
};