#include "debug/EntityInspectorPanel.h"

#include "ImGuiComponentInspector.h"

#include <imgui.h>
#include <string>

namespace engine::debug
{
EntityInspectorPanel::EntityInspectorPanel(Scene& scene)
    : scene_(scene)
{
}

void EntityInspectorPanel::render()
{
    // Begin opens the inspector; always call End even when Begin reports a collapsed window.
    if (!ImGui::Begin("Entity Inspector"))
    {
        ImGui::End();
        return;
    }

    ImGuiComponentInspector inspector;
    for (const auto& entity : scene_.entities())
    {
        const std::string entityLabel = entity->name() + "###entity-" + std::to_string(entity->id());
        if (ImGui::TreeNode(entityLabel.c_str()))
        {
            int componentIndex = 0;
            for (const auto& component : entity->components())
            {
                // PushID distinguishes components with identical type names on the same entity.
                ImGui::PushID(componentIndex++);
                const std::string componentLabel{component->typeName()};
                // TreeNode creates a collapsible component section; inspect only while it is open.
                if (ImGui::TreeNode(componentLabel.c_str()))
                {
                    component->inspect(inspector);
                    // TreePop balances each successful TreeNode call and restores the parent tree level.
                    ImGui::TreePop();
                }
                // PopID balances PushID regardless of whether the component tree is open.
                ImGui::PopID();
            }
            // Balance the entity TreeNode before moving to the next entity.
            ImGui::TreePop();
        }
    }

    // End must be called once for every Begin, including the collapsed-window early return above.
    ImGui::End();
}
} // namespace engine::debug
