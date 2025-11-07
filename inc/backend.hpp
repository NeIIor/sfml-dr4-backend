#pragma once

#include "misc/dr4_ifc.hpp"

class Backend : public dr4::DR4Backend {
public:
    const std::string& Name() const override;
    dr4::Window* CreateWindow() override;
};

extern "C" dr4::DR4Backend* CreateDR4Backend();