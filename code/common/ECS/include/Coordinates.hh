
/**
 * @file Coordinates.hh
 * @author Alexis.
 * @brief Type for coordinates.
 *
 */

#pragma once

/**
 * Namespace of ECS.
 */
namespace ECS {

    /**
     * Type for coordinates. Can be int or float.
     */
    template<typename T>
    struct coordinates
    {
        /**
         * Constructor.
         */
        coordinates(T x, T y)
            : _x(x), _y(y)
            {}
        /**
         * Destructor.
         */
        ~coordinates() {}

        /**
         * x coordinate.
         */
        T     _x;
        /**
         * y coordinate.
         */
        T     _y;
    };
}
