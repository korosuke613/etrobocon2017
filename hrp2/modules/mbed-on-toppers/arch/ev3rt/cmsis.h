// NOTE: REV and REV16 is only support in ARMv6 and above

//static inline
//uint16_t __REV16(uint16_t x) { return x >> 8 | x << 8; }

#define __REV16(x) __builtin_bswap16(x)
#define __REV(x)   __builtin_bswap32(x)
//static inline
//uint32_t __REV(uint32_t x) { return ((x << 24) & 0xFF000000) | ((x << 8) & 0x00FF0000) | ((x >> 8) & 0x0000FF00) | ((x >> 24) & 0x000000FF); }

