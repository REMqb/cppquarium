#pragma once

#include <type_traits>
#include <unordered_map>

namespace ecs {
    class SystemBase;
    class Component;
    class Entity;

    namespace detail {
        /**
         * Struct to pass parameters packs around.
         */
        template <typename... Types>
        struct Pack;

        /**
         * Contains template struct, inherit std::true_type if type T1 is contained in passed args (T2 and Args), std::false_type otherwise.
         */
        template <typename T1, typename T2 = void, typename... Args>
        struct Contains :
                public std::conditional<
                    std::is_void<T2>::value, // no types in Args
                    std::false_type,         // => false
                    typename std::conditional<
                        std::is_same<T1, T2>::value,// T1 == T2
                        std::true_type,             // => true
                        Contains<T1, Args...>       // else T2 = Args[0] and test again
                    >::type
                >::type {};

        template <typename SystemT, typename BaseSystemT = typename SystemT::SystemBaseType, typename... ComponentsT>
        struct ComponentsFromSystem :
                public std::conditional<
                    detail::Contains<typename SystemT::ComponentType, ComponentsT...>::value, // if ComponentsT already contains SystemT::ComponentType we don't add it again.
                    ComponentsFromSystem<BaseSystemT, typename SystemT::SystemBaseType, ComponentsT...>,
                    ComponentsFromSystem<BaseSystemT, typename SystemT::SystemBaseType, ComponentsT..., typename SystemT::ComponentType>
                >::type
        {
            using type = typename std::conditional<
                detail::Contains<typename SystemT::ComponentType, ComponentsT...>::value, // if ComponentsT already contains SystemT::ComponentType we don't add it again.
                ComponentsFromSystem<BaseSystemT, typename SystemT::SystemBaseType, ComponentsT...>,
                ComponentsFromSystem<BaseSystemT, typename SystemT::SystemBaseType, ComponentsT..., typename SystemT::ComponentType>
            >::type::type;
        };

        // specialized version to avoid infinite recursion
        template <typename BaseSystemT, typename... ComponentsT>
        struct ComponentsFromSystem<SystemBase, BaseSystemT, ComponentsT...>
        {
            using type = detail::Pack<ComponentsT..., Component>;
        };
    }

template <bool leaf = false, typename ComponentT = void, typename... ComponentBasesT>
class CovariantComponentMap : public CovariantComponentMap<false, ComponentBasesT...>{
    public:

        virtual ~CovariantComponentMap() = 0;
};

template <>
class CovariantComponentMap<false, void> {};

template <typename ComponentT, typename... ComponentBasesT>
class CovariantComponentMap<true, detail::Pack<ComponentT, ComponentBasesT...>> : public CovariantComponentMap<false, ComponentT, ComponentBasesT...> {
    public:
        //CovariantComponentMap();

    private:
        std::unordered_map<std::reference_wrapper<const Entity>, ComponentT> mapImpl;
};

/*template <bool leaf, typename ComponentT, typename... ComponentBasesT>
CovariantComponentMap<leaf, ComponentT, ComponentBasesT...>::CovariantComponentMap(){

}*/

template <bool leaf, typename ComponentT, typename... ComponentBasesT>
CovariantComponentMap<leaf, ComponentT, ComponentBasesT...>::~CovariantComponentMap(){

}



}

