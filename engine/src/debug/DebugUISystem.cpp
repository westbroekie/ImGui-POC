#include "debug/DebugUISystem.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdexcept>
#include <utility>

namespace engine::debug
{
DebugUISystem::~DebugUISystem()
{
    // The facade owns the GUI lifecycle and performs cleanup when the host forgets explicit shutdown.
    shutdown();
}

void DebugUISystem::addPanel(std::unique_ptr<DebugPanel> panel)
{
    // Reject null panels at registration so frame rendering never silently skips an invalid entry.
    if (!panel)
    {
        throw std::invalid_argument("DebugUISystem cannot register a null panel.");
    }
    panels_.push_back(std::move(panel));
}

void DebugUISystem::init()
{
    // Prevent creating a second context/window over resources already owned by this facade.
    if (window_ != nullptr)
    {
        throw std::logic_error("DebugUISystem is already initialized.");
    }

    // glfwInit initializes GLFW's process-level window/input services and must precede window creation.
    if (glfwInit() != GLFW_TRUE)
    {
        throw std::runtime_error("GLFW initialization failed.");
    }
    glfwInitialized_ = true;

    // Window hints request a portable OpenGL 3.2 core context before GLFW creates the window.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined(__APPLE__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    // glfwCreateWindow returns null on failure; terminate GLFW before reporting that failure.
    window_ = glfwCreateWindow(1280, 720, "Game Engine - Dear ImGui PoC", nullptr, nullptr);
    if (window_ == nullptr)
    {
        shutdown();
        throw std::runtime_error("GLFW could not create an OpenGL window.");
    }

    // OpenGL calls must target this window's current context; swap interval enables vsync.
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);

    // The version check catches mismatched Dear ImGui headers/library before creating a context.
    IMGUI_CHECKVERSION();
    // CreateContext establishes the current ImGui context required by every subsequent ImGui API call.
    ImGui::CreateContext();
    imguiContextCreated_ = true;
    // StyleColorsDark selects the stock dark theme; applications may replace it after initialization.
    ImGui::StyleColorsDark();

    // Install GLFW input/window callbacks; true chains previously installed callbacks where supported.
    if (!ImGui_ImplGlfw_InitForOpenGL(window_, true))
    {
        shutdown();
        throw std::runtime_error("Dear ImGui GLFW backend initialization failed.");
    }
    glfwBackendInitialized_ = true;

    // OpenGL3 backend uploads ImGui draw lists; the GLSL version must match the requested context.
    if (!ImGui_ImplOpenGL3_Init("#version 150"))
    {
        shutdown();
        throw std::runtime_error("Dear ImGui OpenGL3 backend initialization failed.");
    }
    openglBackendInitialized_ = true;
}

void DebugUISystem::renderFrame()
{
    // Require a valid initialized context instead of silently dropping a frame.
    if (window_ == nullptr)
    {
        throw std::logic_error("DebugUISystem must be initialized before rendering.");
    }

    // GLFW event polling updates input/window state before the ImGui backends sample it.
    glfwPollEvents();
    // Start each backend frame before ImGui::NewFrame; the order is required by the backend contract.
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Panels contribute widgets to the active frame; they must not call ImGui::Render themselves.
    for (const auto& panel : panels_)
    {
        panel->render();
    }

    // Render finalizes ImGui's draw lists; do not call it more than once for a frame.
    ImGui::Render();

    int displayWidth = 0;
    int displayHeight = 0;
    // Use framebuffer pixels (not logical window coordinates) for high-DPI OpenGL viewports.
    glfwGetFramebufferSize(window_, &displayWidth, &displayHeight);
    // Clear and render into the current framebuffer before swapping it onto the display.
    glViewport(0, 0, displayWidth, displayHeight);
    glClearColor(0.08F, 0.09F, 0.12F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);
    // Submit Dear ImGui's generated draw data through the initialized OpenGL3 backend.
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // Present the completed back buffer and make it the visible window contents.
    glfwSwapBuffers(window_);
}

bool DebugUISystem::shouldClose() const noexcept
{
    // A missing window is treated as closed so the host loop cannot spin after failed setup.
    // glfwWindowShouldClose reads the close flag set by the operating system or application.
    return window_ == nullptr || glfwWindowShouldClose(window_) == GLFW_TRUE;
}

void DebugUISystem::shutdown() noexcept
{
    // Tear down in reverse initialization order while the OpenGL context is still alive.
    if (openglBackendInitialized_)
    {
        // Stop renderer backend work before its OpenGL context/window are destroyed.
        ImGui_ImplOpenGL3_Shutdown();
        openglBackendInitialized_ = false;
    }
    if (glfwBackendInitialized_)
    {
        // Remove ImGui's GLFW callbacks before terminating the GLFW window system.
        ImGui_ImplGlfw_Shutdown();
        glfwBackendInitialized_ = false;
    }
    if (imguiContextCreated_)
    {
        // DestroyContext releases ImGui-owned state after both backends have stopped using it.
        ImGui::DestroyContext();
        imguiContextCreated_ = false;
    }
    if (window_ != nullptr)
    {
        // Destroy the window while GLFW is still initialized and its context is available.
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
    if (glfwInitialized_)
    {
        // glfwTerminate releases process-level resources; call only after destroying the window.
        glfwTerminate();
        glfwInitialized_ = false;
    }
}
} // namespace engine::debug
