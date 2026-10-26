#include "Engine.h"
#include "debug/DebugUISystem.h"
#include "debug/DemoRmlUiDebugAdapter.h"
#include "debug/EntityInspectorPanel.h"
#include "debug/PerformancePanel.h"
#include "debug/RmlUiDebugPanel.h"
#include "debug/RmlUiElementComponent.h"
#include "debug/Scene.h"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string_view>

namespace
{
class TransformComponent final : public engine::debug::Component
{
public:
    [[nodiscard]] std::string_view typeName() const noexcept override
    {
        return "Transform";
    }

    void inspect(engine::debug::ComponentInspector& inspector) override
    {
        inspector.addFloat("Position X", positionX_);
        inspector.addFloat("Position Y", positionY_);
        inspector.addFloat("Rotation", rotation_);
    }

private:
    float positionX_{0.0F};
    float positionY_{0.0F};
    float rotation_{0.0F};
};
} // namespace

auto main() -> int
{
    try
    {
        engine::Engine gameEngine;
        gameEngine.init();

        engine::debug::Scene scene;
        auto& player = scene.createEntity("Player");
        player.addComponent<TransformComponent>();

        auto& menu = scene.createEntity("Menu");
        menu.addComponent<TransformComponent>();
        menu.addComponent<engine::debug::RmlUiElementComponent>("menu.rml", "main-menu", false, true);

        engine::debug::DemoRmlUiDebugAdapter rmlUiAdapter(scene);
        engine::debug::DebugUISystem debugUI;
        debugUI.addPanel(std::make_unique<engine::debug::EntityInspectorPanel>(scene));
        debugUI.addPanel(std::make_unique<engine::debug::PerformancePanel>());
        debugUI.addPanel(std::make_unique<engine::debug::RmlUiDebugPanel>(rmlUiAdapter));
        debugUI.init();

        while (gameEngine.isRunning() && !debugUI.shouldClose())
        {
            debugUI.renderFrame();
        }

        debugUI.shutdown();
        gameEngine.shutdown();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Game startup/runtime error: " << exception.what() << '\n';
        return EXIT_FAILURE;
    }
}
