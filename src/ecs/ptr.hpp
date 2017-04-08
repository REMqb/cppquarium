#pragma once

namespace ecs {
    /**
     * Alias for raw pointer, never owning the pointed resource.
     */
    template<typename T>
    using ptr = T*;
}
