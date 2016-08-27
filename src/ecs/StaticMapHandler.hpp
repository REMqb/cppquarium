#pragma once

#include <unordered_map>

#include <iostream>

namespace ecs {

    /**
     * This class handle maps for other when they can't have a static map of instance of themselve because of incomplete type.
     * @param KeyT Type of the map key
     * @param ValueT Type of the value asociated to the key
     * @param FriendT Type of the class in which the map should have been present and that will be friend of this one
     */
    template<typename KeyT, typename ValueT, typename FriendT>
    class StaticMapHandler{
            friend FriendT;
        private:
            static std::unordered_map<KeyT, ValueT> map;

            //static std::unordered_map<KeyT, ValueT>& getMap();

    };

    /*template<typename KeyT, typename ValueT, typename FriendT>
    std::unordered_map<KeyT, ValueT>& StaticMapHandler<KeyT, ValueT, FriendT>::getMap(){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return map;
    };*/

    template<typename KeyT, typename ValueT, typename FriendT>
    std::unordered_map<KeyT, ValueT> StaticMapHandler<KeyT, ValueT, FriendT>::map;
}
