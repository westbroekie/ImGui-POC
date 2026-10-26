cmake_minimum_required(VERSION 3.25)

add_library(engine STATIC
    src/core/Engine.cpp
    src/debug/Entity.cpp
    src/debug/Scene.cpp
    src/debug/DebugUISystem.cpp
    src/debug/EntityInspectorPanel.cpp
    src/debug/ImGuiComponentInspector.cpp
    src/debug/PerformancePanel.cpp
    src/debug/DemoRmlUiDebugAdapter.cpp
    src/debug/RmlUiElementComponent.cpp
    src/debug/RmlUiDebugPanel.cpp
)

target_include_directories(engine PUBLIC
    include
)

find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(engine
    PRIVATE
        imgui::imgui
        glfw
        OpenGL::GL
    PUBLIC
        project_sanitizers
        project_warnings
)

target_compile_features(engine PUBLIC cxx_std_20)
