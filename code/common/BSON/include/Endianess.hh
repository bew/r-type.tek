/**
 * @file Endianess.hh
 * @brief Useful macro for endianess
 * @author Christopher Paccard
 *
 * Useful macro for endianess
 *
 */

#ifndef ENDIANESS_HH
#define ENDIANESS_HH

#include <climits>

template <typename T>
T swap_endian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}

enum
{
    O32_LITTLE_ENDIAN = 0x03020100ul,
    O32_BIG_ENDIAN = 0x00010203ul,
    O32_PDP_ENDIAN = 0x01000302ul
};

static const union { unsigned char bytes[4]; uint32_t value; } o32_host_order =
        { { 0, 1, 2, 3 } };

#define O32_HOST_ORDER (o32_host_order.value)
#define IS_BIG_ENDIAN (O32_HOST_ORDER == O32_BIG_ENDIAN)

#endif //ENDIANESS_HH
