#include "../inc/backend_impl.hpp"
#include "../inc/window_impl.hpp"

const std::string& SFMLBackend::Name() const {
    static const std::string name = "SFMLBackend";
    return name;
}

dr4::Window* SFMLBackend::CreateWindow() {
    return new SFMLWindow();
}

extern "C" dr4::DR4Backend* CreateDR4Backend() {
    return new SFMLBackend();
}