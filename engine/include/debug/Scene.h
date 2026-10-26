#pragma once

#include "debug/Entity.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace engine::debug
{
class Scene
{
public:
    Entity& createEntity(std::string name);
    [[nodiscard]] const std::vector<std::unique_ptr<Entity>>& entities() const noexcept;

private:
    std::uint32_t nextId_{1};
    std::vector<std::unique_ptr<Entity>> entities_;
};
} // namespace engine::debug
