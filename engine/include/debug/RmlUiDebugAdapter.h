#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace engine::debug
{
struct RmlUiElementInfo
{
    std::uint32_t entityId;
    std::string entityName;
    std::string document;
    std::string elementId;
    bool visible;
    bool active;

    [[nodiscard]] bool hasActiveHiddenIssue() const noexcept
    {
        return active && !visible;
    }
};

class RmlUiDebugAdapter
{
public:
    virtual ~RmlUiDebugAdapter() = default;

    [[nodiscard]] virtual std::vector<RmlUiElementInfo> inspectElements() const = 0;
    virtual bool setElementVisible(std::uint32_t entityId, std::string_view elementId, bool visible) = 0;
};
} // namespace engine::debug
