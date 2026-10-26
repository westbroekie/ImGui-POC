#pragma once

#include <string_view>

namespace engine::debug
{
class ComponentInspector
{
public:
    virtual ~ComponentInspector() = default;

    virtual void addFloat(std::string_view label, float& value) = 0;
    virtual void addInt(std::string_view label, int& value) = 0;
    virtual void addBool(std::string_view label, bool& value) = 0;
    virtual void addText(std::string_view label, std::string_view value) = 0;
};
} // namespace engine::debug
