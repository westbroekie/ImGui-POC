#pragma once

#include "debug/DebugPanel.h"

#include <memory>
#include <vector>

struct GLFWwindow;

namespace engine::debug
{
// Facade around GLFW, the Dear ImGui context/backends, and the OpenGL render pass.
// The game loop talks to this class instead of managing individual library lifecycles.
class DebugUISystem
{
public:
    DebugUISystem() = default;
    ~DebugUISystem();

    DebugUISystem(const DebugUISystem&) = delete;
    auto operator=(const DebugUISystem&) -> DebugUISystem& = delete;
    DebugUISystem(DebugUISystem&&) = delete;
    auto operator=(DebugUISystem&&) -> DebugUISystem& = delete;

    // Takes ownership of a panel; register panels before init and keep their referenced data alive.
    void addPanel(std::unique_ptr<DebugPanel> panel);
    // Creates the GLFW window, ImGui context, and both rendering/input backends.
    void init();
    // Polls input, starts an ImGui frame, renders all panels, and presents the frame.
    void renderFrame();
    // Allows the host game loop to close when the GLFW window receives a close request.
    [[nodiscard]] bool shouldClose() const noexcept;
    // Releases initialized backends and window resources; safe to call during partial initialization.
    void shutdown() noexcept;

private:
    GLFWwindow* window_{nullptr};
    bool glfwInitialized_{false};
    bool imguiContextCreated_{false};
    bool glfwBackendInitialized_{false};
    bool openglBackendInitialized_{false};
    std::vector<std::unique_ptr<DebugPanel>> panels_;
};
} // namespace engine::debug
