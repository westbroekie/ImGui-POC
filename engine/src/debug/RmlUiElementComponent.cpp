#include "debug/RmlUiElementComponent.h"

#include <utility>

namespace engine::debug
{
RmlUiElementComponent::RmlUiElementComponent(std::string document, std::string elementId, bool visible, bool active)
    : document_(std::move(document))
    , elementId_(std::move(elementId))
    , visible_(visible)
    , active_(active)
{
}

std::string_view RmlUiElementComponent::typeName() const noexcept
{
    return "RmlUiElement (demo state)";
}

void RmlUiElementComponent::inspect(ComponentInspector& inspector)
{
    inspector.addText("Document", document_);
    inspector.addText("Element", elementId_);
    inspector.addBool("Visible", visible_);
    inspector.addBool("Active", active_);
}

const std::string& RmlUiElementComponent::document() const noexcept
{
    return document_;
}

const std::string& RmlUiElementComponent::elementId() const noexcept
{
    return elementId_;
}

bool RmlUiElementComponent::visible() const noexcept
{
    return visible_;
}

void RmlUiElementComponent::setVisible(bool visible) noexcept
{
    visible_ = visible;
}

bool RmlUiElementComponent::active() const noexcept
{
    return active_;
}
} // namespace engine::debug
