#pragma once

namespace ecs {

    template<typename>
    class ComponentManager;

    class ComponentManagerBase {
            template<typename> friend class ComponentManager;
        public:

            virtual ~ComponentManagerBase() = 0;

        private:
            ComponentManagerBase();
    };
}
