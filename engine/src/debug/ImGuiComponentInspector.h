#pragma once

#include "debug/ComponentInspector.h"

namespace engine::debug
{
class ImGuiComponentInspector final : public ComponentInspector
{
public:
    void addFloat(std::string_view label, float& value) override;
    void addInt(std::string_view label, int& value) override;
    void addBool(std::string_view label, bool& value) override;
    void addText(std::string_view label, std::string_view value) override;
};
} // namespace engine::debug
