#pragma once

#include <unordered_map>
#include <functional>
#include <vector>
#include <iostream>

#include "EventListenerManagerBase.hpp"

#include "../StaticMapHandler.hpp"

namespace ecs {

    class EntityComponentSystem;

    template<typename EventT, typename SourceT>
    class EventListenerManager final : public EventListenerManagerBase {
        public:

            void addListener(SourceT* source, std::function<void(EventT&)> listener);
            void dispatchEvent(EventT& event);
            void removeListener();

            /////// STATICS ///////

            static EventListenerManager<EventT, SourceT>& getEventListenerManagerFor(EntityComponentSystem& ecs);
            static void removeEventListenerManagerFor(EntityComponentSystem& ecs);
        private:

            EventListenerManager(EntityComponentSystem& ecs);

            std::unordered_map<SourceT*, std::vector<std::function<void(EventT&)>>> listeners;

            /////// STATICS ///////

            static std::unordered_map<std::reference_wrapper<EntityComponentSystem>, EventListenerManager<EventT, SourceT>>& eventListenerManagers;
    };

    template<typename EventT, typename SourceT>
    EventListenerManager<EventT, SourceT>::EventListenerManager(EntityComponentSystem& ecs) : EventListenerManagerBase(ecs) {
    }

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

    /////// STATICS ///////

    template<typename EventT, typename SourceT>
    EventListenerManager<EventT, SourceT>& EventListenerManager<EventT, SourceT>::getEventListenerManagerFor(EntityComponentSystem& ecs){
        auto result = eventListenerManagers.find(ecs);

        if(result == eventListenerManagers.end()){
            return eventListenerManagers.emplace(ecs, EventListenerManager<EventT, SourceT>{ecs}).first->second;
        }else{
            return result->second;
        }
    }

    template<typename EventT, typename SourceT>
    std::unordered_map<std::reference_wrapper<EntityComponentSystem>, EventListenerManager<EventT, SourceT>>& EventListenerManager<EventT, SourceT>::eventListenerManagers = StaticMapHandler<std::reference_wrapper<EntityComponentSystem>, EventListenerManager<EventT, SourceT>, EventListenerManager<EventT, SourceT>>::map;
}
