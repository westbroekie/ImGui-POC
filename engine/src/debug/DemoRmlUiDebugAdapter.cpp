#include "debug/DemoRmlUiDebugAdapter.h"

#include "debug/RmlUiElementComponent.h"

namespace engine::debug
{
DemoRmlUiDebugAdapter::DemoRmlUiDebugAdapter(Scene& scene)
    : scene_(scene)
{
}

std::vector<RmlUiElementInfo> DemoRmlUiDebugAdapter::inspectElements() const
{
    std::vector<RmlUiElementInfo> result;
    for (const auto& entity : scene_.entities())
    {
        for (const auto& component : entity->components())
        {
            const auto* element = dynamic_cast<const RmlUiElementComponent*>(component.get());
            if (element == nullptr)
            {
                continue;
            }

            result.push_back({entity->id(),
                              entity->name(),
                              element->document(),
                              element->elementId(),
                              element->visible(),
                              element->active()});
        }
    }
    return result;
}

bool DemoRmlUiDebugAdapter::setElementVisible(std::uint32_t entityId, std::string_view elementId, bool visible)
{
    for (const auto& entity : scene_.entities())
    {
        if (entity->id() != entityId)
        {
            continue;
        }

        for (const auto& component : entity->components())
        {
            auto* element = dynamic_cast<RmlUiElementComponent*>(component.get());
            if (element != nullptr && element->elementId() == elementId)
            {
                element->setVisible(visible);
                return true;
            }
        }
    }
    return false;
}
} // namespace engine::debug
