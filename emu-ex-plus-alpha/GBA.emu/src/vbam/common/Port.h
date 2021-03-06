#ifndef PORT_H
#define PORT_H

#include "Types.h"
#include <string.h>

#ifdef __ANDROID__
#include <sys/endian.h>
#undef swap16
#undef swap32
#endif

// swaps a 16-bit value
static inline u16 swap16(u16 v)
{
  return (v<<8)|(v>>8);
}

// swaps a 32-bit value
static inline u32 swap32(u32 v)
{
  return (v<<24)|((v<<8)&0xff0000)|((v>>8)&0xff00)|(v>>24);
}

#ifdef WORDS_BIGENDIAN
#if defined(__GNUC__) && defined(__ppc__)

#define READ16LE(base) \
  ({ unsigned short lhbrxResult;       \
     __asm__ ("lhbrx %0, 0, %1" : "=r" (lhbrxResult) : "r" (base) : "memory"); \
      lhbrxResult; })

#define READ32LE(base) \
  ({ unsigned long lwbrxResult; \
     __asm__ ("lwbrx %0, 0, %1" : "=r" (lwbrxResult) : "r" (base) : "memory"); \
      lwbrxResult; })

#define WRITE16LE(base, value) \
  __asm__ ("sthbrx %0, 0, %1" : : "r" (value), "r" (base) : "memory")

#define WRITE32LE(base, value) \
  __asm__ ("stwbrx %0, 0, %1" : : "r" (value), "r" (base) : "memory")

#else
#define READ16LE(x) \
  swap16(*((u16 *)(x)))
#define READ32LE(x) \
  swap32(*((u32 *)(x)))
#define WRITE16LE(x,v) \
  *((u16 *)x) = swap16((v))
#define WRITE32LE(x,v) \
  *((u32 *)x) = swap32((v))
#endif
#else

/*#define READ16LE(x) \
  *((u16 *)x)
#define READ32LE(x) \
  *((u32 *)x)
#define WRITE16LE(x,v) \
  *((u16 *)x) = (v)
#define WRITE32LE(x,v) \
  *((u32 *)x) = (v)*/

static u16 READ16LE(const void *x)
{
	return *((u16 *)x);
	/*u16 tmp;
	memcpy(&tmp, ptr, 2);
	return tmp;*/
}

static u32 READ32LE(const void *x)
{
	return *((u32 *)x);
	/*u32 tmp;
	memcpy(&tmp, ptr, 4);
	return tmp;*/
}

static void WRITE16LE(void *x, u16 v)
{
	*((u16 *)x) = (v);
	//memcpy(x, &v, 2);
}

static void WRITE32LE(void *x, u32 v)
{
	*((u32 *)x) = (v);
	//memcpy(x, &v, 4);
}

#endif

#endif // PORT_H
