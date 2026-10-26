#pragma once

#include "debug/Component.h"

#include <string>
#include <string_view>

namespace engine::debug
{
class RmlUiElementComponent final : public Component
{
public:
    RmlUiElementComponent(std::string document, std::string elementId, bool visible, bool active);

    [[nodiscard]] std::string_view typeName() const noexcept override;
    void inspect(ComponentInspector& inspector) override;

    [[nodiscard]] const std::string& document() const noexcept;
    [[nodiscard]] const std::string& elementId() const noexcept;
    [[nodiscard]] bool visible() const noexcept;
    void setVisible(bool visible) noexcept;
    [[nodiscard]] bool active() const noexcept;

private:
    std::string document_;
    std::string elementId_;
    bool visible_;
    bool active_;
};
} // namespace engine::debug
