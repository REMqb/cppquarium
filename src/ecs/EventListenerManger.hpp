#pragma once

#include <unordered_map>
#include <functional>
#include <vector>

template<typename EventT, typename SourceT>
class EventListenerManager final {
    public:

        void addListener(SourceT* source, std::function<void(EventT&)> listener);
        void removeListener();
    private:
        std::unordered_map<SourceT*, std::vector<std::function<void(EventT&)>>> listeners;
};
