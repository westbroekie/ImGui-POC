#pragma once

namespace engine::debug
{
class DebugPanel
{
public:
    virtual ~DebugPanel() = default;
    virtual void render() = 0;
};
} // namespace engine::debug
