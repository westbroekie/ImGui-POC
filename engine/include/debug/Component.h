#pragma once

#include "debug/ComponentInspector.h"

#include <string_view>

namespace engine::debug
{
class Component
{
public:
    virtual ~Component() = default;

    [[nodiscard]] virtual std::string_view typeName() const noexcept = 0;
    virtual void inspect(ComponentInspector& inspector) = 0;
};
} // namespace engine::debug
