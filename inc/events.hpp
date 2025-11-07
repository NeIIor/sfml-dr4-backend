#pragma once

#include "dr4/event.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>
#include <unordered_map>

namespace Events {

class Manager {
public:
    using Handler = std::function<void(const dr4::Event&)>;
    
    void bind(int event_type, Handler handler);
    void unbind(int event_type);
    void process(const dr4::Event& event);
    
    void handleWindowEvents(sf::RenderWindow& window);

private:
    std::unordered_map<int, Handler> handlers_;
};

class Interactive {
public:
    virtual bool handleEvent(const dr4::Event& event) = 0;
    virtual void update(float delta_time) = 0;
    virtual void draw(sf::RenderTarget& target) const = 0;
    
    virtual ~Interactive() = default;
};

}