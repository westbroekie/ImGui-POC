#include "ImGuiComponentInspector.h"

#include <imgui.h>
#include <string>

namespace engine::debug
{
void ImGuiComponentInspector::addFloat(std::string_view label, float& value)
{
    const std::string labelText{label};
    // DragFloat edits the referenced component value directly; its return value indicates a change.
    ImGui::DragFloat(labelText.c_str(), &value, 0.1F);
}

void ImGuiComponentInspector::addInt(std::string_view label, int& value)
{
    const std::string labelText{label};
    // DragInt provides an immediate-mode integer editor bound to the component's owned value.
    ImGui::DragInt(labelText.c_str(), &value);
}

void ImGuiComponentInspector::addBool(std::string_view label, bool& value)
{
    const std::string labelText{label};
    // Checkbox toggles the referenced boolean in place, allowing the inspector to edit ECS data.
    ImGui::Checkbox(labelText.c_str(), &value);
}

void ImGuiComponentInspector::addText(std::string_view label, std::string_view value)
{
    const std::string labelText{label};
    const std::string valueText{value};
    // Text formats the labels as data, not as a format string, avoiding accidental format interpretation.
    ImGui::Text("%s: %s", labelText.c_str(), valueText.c_str());
}
} // namespace engine::debug
