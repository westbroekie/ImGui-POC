#include "Engine.h"
#include "debug/Component.h"
#include "debug/DemoRmlUiDebugAdapter.h"
#include "debug/RmlUiElementComponent.h"
#include "debug/Scene.h"

#include <cstdlib>
#include <iostream>
#include <string_view>

namespace
{
class TestComponent final : public engine::debug::Component
{
public:
    [[nodiscard]] std::string_view typeName() const noexcept override
    {
        return "Test";
    }

    void inspect(engine::debug::ComponentInspector&) override {}
};
} // namespace

auto main() -> int
{
    int failures = 0;

    {
        engine::Engine engine;
        engine.init();
        if (!engine.isRunning())
        {
            std::cerr << "FAIL: Engine should be running after init\n";
            failures++;
        }
    }

    {
        engine::debug::Scene scene;
        auto& entity = scene.createEntity("Test entity");
        entity.addComponent<TestComponent>();
        if (entity.id() != 1 || entity.components().size() != 1 || entity.components().front()->typeName() != "Test")
        {
            std::cerr << "FAIL: Scene should create entities with owned components\n";
            failures++;
        }
    }

    {
        engine::debug::Scene scene;
        auto& menu = scene.createEntity("Menu");
        menu.addComponent<engine::debug::RmlUiElementComponent>("menu.rml", "main-menu", false, true);

        engine::debug::DemoRmlUiDebugAdapter adapter(scene);
        const auto elements = adapter.inspectElements();
        if (elements.size() != 1 || !elements.front().hasActiveHiddenIssue())
        {
            std::cerr << "FAIL: Demo adapter should report an active hidden element\n";
            failures++;
        }

        if (!adapter.setElementVisible(menu.id(), "main-menu", true) || !adapter.inspectElements().front().visible ||
            adapter.inspectElements().front().hasActiveHiddenIssue())
        {
            std::cerr << "FAIL: Demo adapter should apply the visible-state correction\n";
            failures++;
        }

        if (adapter.setElementVisible(menu.id(), "missing", true))
        {
            std::cerr << "FAIL: Demo adapter should report when a requested element does not exist\n";
            failures++;
        }
    }

    {
        engine::Engine engine;
        if (engine.isRunning())
        {
            std::cerr << "FAIL: Engine should not be running before init\n";
            failures++;
        }
    }

    {
        engine::Engine engine;
        engine.init();
        engine.shutdown();
        if (engine.isRunning())
        {
            std::cerr << "FAIL: Engine should not be running after shutdown\n";
            failures++;
        }
    }

    if (failures > 0)
    {
        std::cerr << failures << " test(s) failed\n";
        return EXIT_FAILURE;
    }

    std::cout << "All tests passed\n";
    return EXIT_SUCCESS;
}
