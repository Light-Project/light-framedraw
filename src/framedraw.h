/* SPDX-License-Identifier: GPL-2.0-or-later */
#ifndef _FRAMEDRAW_H_
#define _FRAMEDRAW_H_

#include "macro.h"
#include <stdbool.h>

#define FRAMEDRAW_ROP_COPY  0x00
#define FRAMEDRAW_ROP_XOR   0x01

struct video_image {
    unsigned int width;
    unsigned int height;
    unsigned int xpos;
    unsigned int ypos;
    unsigned char depth;
    uint32_t fgcolor;
    uint32_t bgcolor;
	const void *data;
};

struct framedraw_fillrect {
    unsigned int width;
    unsigned int height;
    unsigned int xpos;
    unsigned int ypos;
    uint32_t color;
    uint32_t rop;
};

struct video_copyarray {
    unsigned int width;
    unsigned int height;
    unsigned int xsrc;
    unsigned int ysrc;
    unsigned int xdest;
    unsigned int ydest;
};

struct framedraw_info {
    unsigned int bpp;
    unsigned int line_size;
    uint32_t *pseudo_palette;
    void *framebuffer;
    bool pseudo_color;
    bool frameswab;
};

#define framedraw_readl(addr) (*(volatile uint32_t *)(addr))
#define framedraw_readq(addr) (*(volatile uint64_t *)(addr))
#define framedraw_writel(addr, value) (*(volatile uint32_t *)(addr) = (value))
#define framedraw_writeq(addr, value) (*(volatile uint64_t *)(addr) = (value))

#define FRAMEDRAW_POS_LEFT(info, bpp) ( \
    (info)->frameswab ?                 \
    (32 - (bpp)) : 0                    \
)

#define FRAMEDRAW_SHIFT_LOW(info, shift, val) (     \
    (info)->frameswab ?                             \
    (val) << (shift) : (val) >> (shift)             \
)

#define FRAMEDRAW_SHIFT_HIGH(info, shift, val) (    \
    (info)->frameswab ?                             \
    (val) >> (shift) : (val) << (shift)             \
)

static inline unsigned long framedraw_cpattern(unsigned int bpp, uint32_t color)
{
    static const unsigned long pattern_table[] = {
        [1  / 2] = (long)0xffffffffffffffffULL,
        [2  / 2] = (long)0x5555555555555555ULL,
        [4  / 2] = (long)0x1111111111111111ULL,
        [8  / 2] = (long)0x0101010101010101ULL,
        [12 / 2] = (long)0x1001001001001001ULL,
        [16 / 2] = (long)0x0001000100010001ULL,
        [24 / 2] = (long)0x0001000001000001ULL,
        [32 / 2] = (long)0x0000000100000001ULL,
    };

    if (bpp / 2 > ARRAY_SIZE(pattern_table))
        return 0;

    return pattern_table[bpp / 2] * color;
}

static inline unsigned long framedraw_comb(unsigned long a, unsigned long b, unsigned long mask)
{
    return ((a ^ b) & mask) ^ b;
}

static inline unsigned long framedraw_rol(unsigned long word, unsigned int shift, unsigned int limit)
{
    return (word << shift) | (word >> (limit - shift));
}

extern void framedraw_imageblit(const struct framedraw_info *info, const struct video_image *image);
extern void framedraw_fillrect(const struct framedraw_info *info, const struct framedraw_fillrect *fillrect);
extern void framedraw_copyarray(const struct framedraw_info *info, const struct video_copyarray *copyarray);

#endif  /* _FRAMEDRAW_H_ */
