#pragma once

namespace ecs {


    class EventListenerManagerBase {
            template<typename, typename> friend class EventListenerManager;
        public:

            virtual ~EventListenerManagerBase() = 0;

        private:
            EventListenerManagerBase();
    };
}
