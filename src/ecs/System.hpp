#pragma once

#include "SystemBase.hpp"
#include "EntityComponentSystem.hpp"

#include <unordered_map>
#include <memory>
#include <functional>

namespace ecs {

template<typename SystemT>
class System : public SystemBase {
    public:
        System(EntityComponentSystem& ecs);

    protected:

    private:
};

}

