#pragma once

#include "debug/DebugPanel.h"
#include "debug/RmlUiDebugAdapter.h"

namespace engine::debug
{
class RmlUiDebugPanel final : public DebugPanel
{
public:
    explicit RmlUiDebugPanel(RmlUiDebugAdapter& adapter);
    void render() override;

private:
    RmlUiDebugAdapter& adapter_;
    bool correctionFailed_{false};
};
} // namespace engine::debug
