#include "debug/Scene.h"

#include <utility>

namespace engine::debug
{
Entity& Scene::createEntity(std::string name)
{
    entities_.push_back(std::make_unique<Entity>(std::move(name), nextId_++));
    return *entities_.back();
}

const std::vector<std::unique_ptr<Entity>>& Scene::entities() const noexcept
{
    return entities_;
}
} // namespace engine::debug
