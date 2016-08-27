#pragma once

namespace ecs {

    template<typename, typename>
    class EventListenerManager;

    class EntityComponentSystem;

    class EventListenerManagerBase {
            template<typename, typename> friend class EventListenerManager;
        public:

            virtual ~EventListenerManagerBase() = 0;

        private:
            EventListenerManagerBase(EntityComponentSystem& ecs);
    };
}
