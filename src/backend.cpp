#include "backend.hpp"
#include "window.hpp"

const std::string& Backend::Name() const {
    static const std::string name = "SFMLBackend";
    return name;
}

dr4::Window* Backend::CreateWindow() {
    return new Window();
}

extern "C" dr4::DR4Backend* CreateDR4Backend() {
    return new Backend();
}