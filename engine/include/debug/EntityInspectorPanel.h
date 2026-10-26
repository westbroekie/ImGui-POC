#pragma once

#include "debug/DebugPanel.h"
#include "debug/Scene.h"

namespace engine::debug
{
class EntityInspectorPanel final : public DebugPanel
{
public:
    explicit EntityInspectorPanel(Scene& scene);
    void render() override;

private:
    Scene& scene_;
};
} // namespace engine::debug
