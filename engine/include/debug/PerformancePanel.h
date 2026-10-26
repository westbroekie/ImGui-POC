#pragma once

#include "debug/DebugPanel.h"

namespace engine::debug
{
class PerformancePanel final : public DebugPanel
{
public:
    void render() override;
};
} // namespace engine::debug
