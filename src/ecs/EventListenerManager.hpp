#pragma once

#include <unordered_map>
#include <functional>
#include <vector>
#include <iostream>

#include "EventListenerManagerBase.hpp"

namespace ecs {

    template<typename EventT, typename SourceT>
    class EventListenerManager final : public EventListenerManagerBase {
        public:

            void addListener(SourceT* source, std::function<void(EventT&)> listener);
            void dispatchEvent(EventT& event);
            void removeListener();
        private:
            std::unordered_map<SourceT*, std::vector<std::function<void(EventT&)>>> listeners;
    };

    template<typename EventT, typename SourceT>
    void EventListenerManager<EventT, SourceT>::addListener(SourceT* source, std::function<void(EventT&)> listener){
        listeners[source].push_back(listener);
    }

    template<typename EventT, typename SourceT>
    void EventListenerManager<EventT, SourceT>::dispatchEvent(EventT& event){
        for(auto listener : listeners[&event.getSource()]){
            listener(event);
        }
    }
}
