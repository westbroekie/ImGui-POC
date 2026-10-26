#pragma once

#include "debug/RmlUiDebugAdapter.h"
#include "debug/Scene.h"

namespace engine::debug
{
class DemoRmlUiDebugAdapter final : public RmlUiDebugAdapter
{
public:
    explicit DemoRmlUiDebugAdapter(Scene& scene);

    [[nodiscard]] std::vector<RmlUiElementInfo> inspectElements() const override;
    bool setElementVisible(std::uint32_t entityId, std::string_view elementId, bool visible) override;

private:
    Scene& scene_;
};
} // namespace engine::debug
