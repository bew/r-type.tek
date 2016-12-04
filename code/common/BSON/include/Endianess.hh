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

#include <limits.h>
#include <stdint.h>

#if CHAR_BIT != 8
#error "unsupported char size"
#endif

enum
{
    O32_LITTLE_ENDIAN = 0x03020100ul,
    O32_BIG_ENDIAN = 0x00010203ul,
    O32_PDP_ENDIAN = 0x01000302ul
};

static const union { unsigned char bytes[4]; uint32_t value; } o32_host_order =
        { { 0, 1, 2, 3 } };

#define O32_HOST_ORDER (o32_host_order.value)

#define CHOOSE_ENDIANESS_32(x) (O32_HOST_ORDER == O32_BIG_ENDIAN ? __builtin_bswap32(x) : x)
#define CHOOSE_ENDIANESS_64(x) (O32_HOST_ORDER == O32_BIG_ENDIAN ? __builtin_bswap64(x) : x)

#endif //ENDIANESS_HH
