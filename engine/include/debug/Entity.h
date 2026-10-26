#pragma once

#include "debug/Component.h"

#include <concepts>
#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace engine::debug
{
class Entity
{
public:
    Entity(std::string name, std::uint32_t id);

    [[nodiscard]] const std::string& name() const noexcept;
    [[nodiscard]] std::uint32_t id() const noexcept;
    [[nodiscard]] const std::vector<std::unique_ptr<Component>>& components() const noexcept;

    template <typename ComponentType, typename... Args>
        requires std::derived_from<ComponentType, Component>
    ComponentType& addComponent(Args&&... args)
    {
        auto component = std::make_unique<ComponentType>(std::forward<Args>(args)...);
        ComponentType& result = *component;
        components_.push_back(std::move(component));
        return result;
    }

private:
    std::string name_;
    std::uint32_t id_;
    std::vector<std::unique_ptr<Component>> components_;
};
} // namespace engine::debug
