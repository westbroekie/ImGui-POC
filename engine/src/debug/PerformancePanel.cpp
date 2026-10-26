#include "debug/PerformancePanel.h"

#include <imgui.h>

namespace engine::debug
{
void PerformancePanel::render()
{
    // Begin opens the panel; End is required even when its contents are collapsed.
    if (!ImGui::Begin("Performance"))
    {
        ImGui::End();
        return;
    }

    // GetIO exposes frame metrics populated by the active platform/renderer backends.
    const ImGuiIO& io = ImGui::GetIO();
    const float frameTimeMs = io.Framerate > 0.0F ? 1000.0F / io.Framerate : 0.0F;
    // Text uses printf-style format strings; keep format specifiers aligned with the argument types.
    ImGui::Text("Frame time: %.3f ms", frameTimeMs);
    ImGui::Text("FPS: %.1f", io.Framerate);
    // Pair End with Begin to close this panel's ImGui window.
    ImGui::End();
}
} // namespace engine::debug
