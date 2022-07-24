/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2022 Sanpe <sanpeqf@gmail.com>
 */

#ifndef _MACRO_H_
#define _MACRO_H_

#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <endian.h>

#if BYTE_ORDER == LITTLE_ENDIAN
#define le32_to_cpu(val) (val)
#define le64_to_cpu(val) (val)
#define cpu_to_le32(val) (val)
#define cpu_to_le64(val) (val)
#endif
#if BYTE_ORDER == BIG_ENDIAN
#define le32_to_cpu(val) __bswap_32(val)
#define le64_to_cpu(val) __bswap_64(val)
#define cpu_to_le32(val) __bswap_32(val)
#define cpu_to_le64(val) __bswap_64(val)
#endif


#define BITS_PER_BYTE           8
#define BITS_PER_TYPE(type)     (sizeof(type) * BITS_PER_BYTE)
#define BITS_WORD(bit)          ((bit) / BITS_PER_LONG)

#define BYTES_PER_U32           sizeof(uint32_t)
#define BYTES_PER_LONG          sizeof(long)
#define BITS_PER_U8             BITS_PER_TYPE(uint8_t)
#define BITS_PER_U32            BITS_PER_TYPE(uint32_t)
#define BITS_TO_U8(nr)          DIV_ROUND_UP(nr, BITS_PER_U8)

#define _cpu_to_le_type(type)   cpu_to_le##type
#define cpu_to_le_type(type)    _cpu_to_le_type(type)
#define cpu_to_le_long(val)     cpu_to_le_type(BITS_PER_LONG)(val)

#define _le_type_to_cpu(type)   le##type##_to_cpu
#define le_type_to_cpu(type)    _le_type_to_cpu(type)
#define le_long_to_cpu(val)     le_type_to_cpu(BITS_PER_LONG)(val)

#define ARRAY_SIZE(arr) ( \
    sizeof(arr) / sizeof((arr)[0]) \
)

#define DIV_ROUND_UP(n, d) ( \
    ((n) + (d) - 1) / (d) \
)

#define BIT(nr) ( \
    (1UL) << ((nr) % BITS_PER_LONG) \
)

#define BIT_LOW_MASK(nbits) ( \
    ULONG_MAX >> \
    (-(nbits) & (BITS_PER_LONG - 1)) \
)

#define align_low(size, align) ({ \
    (size) & ~((align) - 1); \
})

#define align_ptr_low(ptr, align) ({ \
    (typeof(ptr))align_low((size_t)(ptr), align); \
})

#endif  /* _MACRO_H_ */
