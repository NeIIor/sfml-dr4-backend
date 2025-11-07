#include "events.hpp"
#include <SFML/Window/Event.hpp>

namespace Events {

void Manager::bind(int event_type, Handler handler) {
    handlers_[event_type] = handler;
}

void Manager::unbind(int event_type) {
    handlers_.erase(event_type);
}

void Manager::process(const dr4::Event& event) {
    auto it = handlers_.find(static_cast<int>(event.type));
    if (it != handlers_.end()) {
        it->second(event);
    }
}

void Manager::handleWindowEvents(sf::RenderWindow& window) {
    sf::Event sf_event;
    while (window.pollEvent(sf_event)) {
        dr4::Event event;
        
        switch (sf_event.type) {
            case sf::Event::Closed:
                event.type = dr4::Event::Type::QUIT;
                break;
            case sf::Event::KeyPressed:
                event.type = dr4::Event::Type::KEY_DOWN;
                break;
            case sf::Event::KeyReleased:
                event.type = dr4::Event::Type::KEY_UP;
                break;
            case sf::Event::MouseButtonPressed:
                event.type = dr4::Event::Type::MOUSE_DOWN;
                break;
            case sf::Event::MouseButtonReleased:
                event.type = dr4::Event::Type::MOUSE_UP;
                break;
            case sf::Event::MouseMoved:
                event.type = dr4::Event::Type::MOUSE_MOVE;
                break;
            default:
                continue;
        }
        
        process(event);
    }
}

}