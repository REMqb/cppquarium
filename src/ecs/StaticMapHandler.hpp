#include <unordered_map>

#include <iostream>

namespace ecs {
    template<typename KeyT, typename ValueT>
    class StaticMapHandler{
        private:
            static std::unordered_map<KeyT, ValueT> map;

        public:
            static std::unordered_map<KeyT, ValueT>& getMap();

    };

    template<typename KeyT, typename ValueT>
    std::unordered_map<KeyT, ValueT>& StaticMapHandler<KeyT, ValueT>::getMap(){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return map;
    };

    template<typename KeyT, typename ValueT>
    std::unordered_map<KeyT, ValueT> StaticMapHandler<KeyT, ValueT>::map;
}
