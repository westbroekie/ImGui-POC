#include "debug/Entity.h"

#include <utility>

namespace engine::debug
{
Entity::Entity(std::string name, std::uint32_t id)
    : name_(std::move(name))
    , id_(id)
{
}

const std::string& Entity::name() const noexcept
{
    return name_;
}

std::uint32_t Entity::id() const noexcept
{
    return id_;
}

const std::vector<std::unique_ptr<Component>>& Entity::components() const noexcept
{
    return components_;
}
} // namespace engine::debug
