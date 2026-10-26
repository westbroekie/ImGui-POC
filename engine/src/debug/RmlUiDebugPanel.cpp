#include "debug/RmlUiDebugPanel.h"

#include <imgui.h>

namespace engine::debug
{
RmlUiDebugPanel::RmlUiDebugPanel(RmlUiDebugAdapter& adapter)
    : adapter_(adapter)
{
}

void RmlUiDebugPanel::render()
{
    // Begin starts this panel; pair it with End even when the user collapses the window.
    if (!ImGui::Begin("RmlUi Debug (demo state)"))
    {
        ImGui::End();
        return;
    }

    // TextWrapped keeps the current integration boundary visible to demo viewers.
    ImGui::TextWrapped("Demo adapter only: no live RmlUi context is connected yet.");
    ImGui::Separator();

    if (correctionFailed_)
    {
        // TextColored makes stale targets or failed writes visible instead of implying success.
        ImGui::TextColored(ImVec4(1.0F, 0.35F, 0.25F, 1.0F), "Correction failed: element is no longer available.");
    }

    // The adapter owns lookup and mutation, keeping ImGui independent of RmlUi and ECS implementation details.
    const auto elements = adapter_.inspectElements();
    if (elements.empty())
    {
        ImGui::TextUnformatted("No UI elements were returned by the debug adapter.");
    }

    for (const auto& element : elements)
    {
        // PushID scopes repeated labels by entity and element so controls keep stable unique ImGui IDs.
        ImGui::PushID(static_cast<int>(element.entityId));
        ImGui::PushID(element.elementId.c_str());

        // Text reports identifiers that can be used to locate the element in the source UI document.
        ImGui::Text("%s / %s / %s", element.entityName.c_str(), element.document.c_str(), element.elementId.c_str());
        ImGui::Text("Visible: %s | Active: %s", element.visible ? "yes" : "no", element.active ? "yes" : "no");

        if (element.hasActiveHiddenIssue())
        {
            // TextColored signals the detected state mismatch; it is not a complete RmlUi validator.
            ImGui::TextColored(ImVec4(1.0F, 0.35F, 0.25F, 1.0F), "Issue: element is active but hidden.");
            // Button requests a suggested correction through the adapter; its implementation decides how to mutate.
            if (ImGui::Button("Apply correction: show element"))
            {
                correctionFailed_ = !adapter_.setElementVisible(element.entityId, element.elementId, true);
            }
        }

        ImGui::Separator();
        // PopID restores the prior ID scope after this element's controls have been emitted.
        ImGui::PopID();
        ImGui::PopID();
    }

    // End closes the window begun above, including when the panel is collapsed.
    ImGui::End();
}
} // namespace engine::debug
