/*
 *  vm.hpp - Virtual memory management
 *
 *  Kheperix (C) 2003-2005 Gwenole Beauchesne
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef VM_H
#define VM_H


#ifdef i386

#ifndef ___X86___
#define ___X86___
#endif

#elif defined __x86_64__

#ifndef ___X86___
#define ___X86___
#endif

#endif

#ifdef ___X86___
#ifdef WORDS_BIGENDIAN
#undef WORDS_BIGENDIAN
#endif
#else
#warning non-x86 computers are currently unsupported in some parts of this
#endif
#ifndef __APPLE__
#warning non-mac computers are currently unsupported in some parts of this
#endif
///
///		Optimized memory accessors
///

/*#if defined(__i386__) || defined(__powerpc__) || defined(__ppc__) || defined(__m68k__) || defined(__x86_64__)*/
#define VM_CAN_ACCESS_UNALIGNED
/*#endif*/

#ifdef WORDS_BIGENDIAN

/*#ifdef VM_CAN_ACCESS_UNALIGNED

#ifndef VM_OPTIMIZED_MEMORY_ACCESS_2
#define VM_OPTIMIZED_MEMORY_ACCESS_2*/
#define vm_do_read_memory_2(a) (uint32)((*((uint16 *)a)))
#define vm_do_write_memory_2(a, v) *(uint16 *)a = (uint16)v
/*static inline uint32 vm_do_read_memory_2(uint16 *a) { return *a; }
static inline void vm_do_write_memory_2(uint16 *a, uint32 v) { *a = v; }
#endif


#ifndef VM_OPTIMIZED_MEMORY_ACCESS_4
#define VM_OPTIMIZED_MEMORY_ACCESS_4*/
#define vm_do_read_memory_4(a) (*((uint32 *)a))
#define vm_do_write_memory_4(a, v) *(uint32 *)a = (uint32)v
/*static inline uint32 vm_do_read_memory_4(uint32 *a) { return *a; }
static inline void vm_do_write_memory_4(uint32 *a, uint32 v) { *a = v; }
#endif

#ifndef VM_OPTIMIZED_MEMORY_ACCESS_8
#define VM_OPTIMIZED_MEMORY_ACCESS_8*/
#define vm_do_read_memory_8 (*((uint64 *)a))
#define vm_do_write_memory_8(a, v) (*((uint64 *)a)) = (uint64)v
/*static inline uint64 vm_do_read_memory_8(uint64 *a) { return *a; }
static inline void vm_do_write_memory_8(uint64 *a, uint64 v) { *a = v; }
#endif

#endif  VM_CAN_ACCESS_UNALIGNED*/

#else

/*#ifdef VM_CAN_ACCESS_UNALIGNED

#ifndef VM_OPTIMIZED_MEMORY_ACCESS_2
#define VM_OPTIMIZED_MEMORY_ACCESS_2
static inline uint32 vm_do_read_memory_2(uint16 *a) { return bswap_16(*a); }
static inline void vm_do_write_memory_2(uint16 *a, uint32 v) { *a = bswap_16(v); }*/

#define vm_do_read_memory_2(a) (uint32)bswap_16(*((uint16 *)a))
#define vm_do_write_memory_2(a, v) *((uint16 *)a) = bswap_16((uint16)v)

/*#endif

#ifndef VM_OPTIMIZED_MEMORY_ACCESS_4
#define VM_OPTIMIZED_MEMORY_ACCESS_4
static inline uint32 vm_do_read_memory_4(uint32 *a) { return bswap_32(*a); }
static inline void vm_do_write_memory_4(uint32 *a, uint32 v) { *a = bswap_32(v); }*/

#define vm_do_read_memory_4(a) bswap_32(*(uint32 *)a)
#define vm_do_write_memory_4(a, v) *(uint32 *)a = bswap_32((uint32)v)

/*#endif

#ifndef VM_OPTIMIZED_MEMORY_ACCESS_8
#define VM_OPTIMIZED_MEMORY_ACCESS_8
static inline uint64 vm_do_read_memory_8(uint64 *a) { return bswap_64(*a); }
static inline void vm_do_write_memory_8(uint64 *a, uint64 v) { *a = bswap_64(v); }*/

#define vm_do_read_memory_8(a) bswap_64(*(uint64 *)a)
#define vm_do_write_memory_8(a, v) *(uint64 *)a = bswap_64((uint64)v)

/*#endif

#endif  VM_CAN_ACCESS_UNALIGNED*/

#endif  /* WORDS_BIGENDIAN */

///
///		Generic core memory accessors
///

#define vm_do_read_memory_1(a) (uint32)*(uint8 *)a
#define vm_do_write_memory_1(a, v) *(uint8 *)a = (uint8)v

/*static inline uint32 vm_do_read_memory_1(uint8 *a)
{
	return *a;
}
static inline void vm_do_write_memory_1(uint8 *a, uint32 v)
{
	*a = v;
}*/

/*#ifndef VM_OPTIMIZED_MEMORY_ACCESS_2
static inline uint32 vm_do_read_memory_2(uint16 *a)
{
	uint8 * b = (uint8 *)a;
	return (b[0] << 8) | b[1];
}
static inline void vm_do_write_memory_2(uint16 *a, uint32 v)
{
	uint8 * b = (uint8 *)a;
	b[0] = v >> 8;
	b[1] = v;
}
#endif

#ifndef VM_OPTIMIZED_MEMORY_ACCESS_4
static inline uint32 vm_do_read_memory_4(uint32 *a)
{
	uint8 * b = (uint8 *)a;
	return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3];
}
static inline void vm_do_write_memory_4(uint32 *a, uint32 v)
{
	uint8 * b = (uint8 *)a;
	b[0] = v >> 24;
	b[1] = v >> 16;
	b[2] = v >> 8;
	b[3] = v;
}
#endif

#ifndef VM_OPTIMIZED_MEMORY_ACCESS_8
static inline uint64 vm_do_read_memory_8(uint64 *a)
{
	uint8 * b = (uint8 *)a;
	return
		((uint64)b[0] << 56) |
		((uint64)b[1] << 48) |
		((uint64)b[2] << 40) |
		((uint64)b[3] << 32) |
		((uint64)b[4] << 24) |
		((uint64)b[5] << 16) |
		((uint64)b[6] << 8) |
		((uint64)b[7]);
}

static inline void vm_do_write_memory_8(uint64 *a, uint64 v)
{
	uint8 * b = (uint8 *)a;
	b[0] = v >> 56;
	b[1] = v >> 48;
	b[2] = v >> 40;
	b[3] = v >> 32;
	b[4] = v >> 24;
	b[5] = v >> 16;
	b[6] = v >> 8;
	b[7] = v;
}
#endif*/

#ifdef WORDS_BIGENDIAN
/*#ifndef VM_OPTIMIZED_MEMORY_ACCESS_2_REVERSED*/
static inline uint32 vm_do_read_memory_2_reversed(uint16 *a)
{
	return bswap_16(*a);
}
static inline void vm_do_write_memory_2_reversed(uint16 *a, uint32 v)
{
	*a = bswap_16((uint16)v);
}
/*#endif

#ifndef VM_OPTIMIZED_MEMORY_ACCESS_4_REVERSED*/
static inline uint32 vm_do_read_memory_4_reversed(uint32 *a)
{
	return bswap_32(*a);
}
static inline void vm_do_write_memory_4_reversed(uint32 *a, uint32 v)
{
	*a = bswap_32(v);
}
/*#endif*/
static inline uint64 vm_do_read_memory_8_reversed(uint64 * a)
{
	return bswap_64(*a);
}
static inline void vm_do_write_memory_8_reversed(uint64 * a, uint64 v)
{
	*a = bswap_64(v);
}
#else

#define vm_do_read_memory_2_reversed(a) (uint32)*(uint16 *)a
#define vm_do_write_memory_2_reversed(a, v) *(uint16 *)a = (uint16)v
#define vm_do_read_memory_4_reversed(a) *(uint32 *)a
#define vm_do_write_memory_4_reversed(a, v) *(uint32 *)a = (uint32)v
#define vm_do_read_memory_8_reversed(a) *(uint64 *)a
#define vm_do_write_memory_8_reversed(a, v) *(uint64 *)a = (uint64)v

/*static inline uint32 vm_do_read_memory_2_reversed(uint16 * a)
{
	return *a;
}
static inline void vm_do_write_memory_2_reversed(uint16 * a, uint32 v)
{
	*a = (uint16)v;
}
static inline uint32 vm_do_read_memory_4_reversed(uint32 * a)
{
	return *a;
}
static inline void vm_do_write_memory_4_reversed(uint32 * a, uint32 v)
{
	*a = v;
}
static inline uint64 vm_do_read_memory_8_reversed(uint64 * a)
{
	return *a;
}
static inline void vm_do_write_memory_8_reversed(uint64 * a, uint64 v)
{
	*a = v;
}*/

#endif
///
///		Actual memory accessors visible to CPU through virtual addresses
///

typedef uintptr vm_addr_t;

/*#if REAL_ADDRESSING
const uintptr VMBaseDiff = 8192;
#elif DIRECT_ADDRESSING
#ifdef NATMEM_OFFSET
const uintptr VMBaseDiff = NATMEM_OFFSET;
#endif
// Wrap address to 32-bit if we are not using 33-bit addressing space
#if defined(SHEEPSHAVER) && SIZEOF_VOID_P == 8
#define vm_wrap_address(ADDR) (uintptr)(uint32)(ADDR)
#endif
#else
const uintptr VMBaseDiff = 0x100000000;
#endif*/
extern uintptr VMBaseDiff;
extern uint32 address_size;
extern uint8 * sheep_mem;
void vm_ini(uint8 * mem);
void setSize(uint32 size);
void init_sheep_mem(uint8 * mem);
#ifndef vm_wrap_address
#define vm_wrap_address(ADDR) (ADDR)
#endif
#define sheep_base 0x60000000
#define page_size 4096
#define NULL_PAGE 0x59000000
#define NULL_PAGE_SIZE 0x3000
#define KERNEL_DATA_BASE  0x68ffe000	// Address of Kernel Data
#define KERNEL_DATA2_BASE  0x5fffe000	// Alternate address of Kernel Data
#define KERNEL_AREA_SIZE  0x2000		// Size of Kernel Data area
#define KERNEL_DATA(a) ((a & 0xFFFFE000) == KERNEL_DATA_BASE)
#define KERNEL_DATA2(a) ((a & 0xFFFFE000) == KERNEL_DATA2_BASE)
#define KERNEL(a) (KERNEL_DATA(a) || KERNEL_DATA2(a))
#define in_sheep_mem(addr) ((addr >= sheep_base) && (addr <= (sheep_base + page_size)))
#define in_sheep_mem_host(a) ((a >= sheep_mem) && (a <= (sheep_mem + page_size)))
#define HIMEM(a) ((in_sheep_mem(a))||(KERNEL(a)))
#define too_big(addr) ((addr >= address_size)&&(!(HIMEM(addr))))
#define ZERO too_big
/*too_big(addr) is so we don't crash on too big addresses*/
#define NO_WRITE ZERO
/*#if REAL_ADDRESSING || DIRECT_ADDRESSING*/
extern uint8 /*gZeroPage[0x3000],*/ gKernelData[0x2000];
static inline uint8 * vm_get_host_address(vm_addr_t addr)
{
/*#ifdef __APPLE__
#ifdef __x86_64__*/

	/*if (a < 0x3000) return &gZeroPage[a];
	else*/ if (KERNEL(addr)) {
		return (uint8 *)vm_wrap_address((gKernelData + (addr & 0x1fff)));
	}
	else if (in_sheep_mem(addr)) {
		return (uint8 *)vm_wrap_address((sheep_mem + (addr - sheep_base)));
	}
	/*else if (too_big((uint32)addr)) {
		printf("address too big: 0x%08x\n", addr);
	}*/
/*#elif defined i386
#endif*/
	/*else*/
	return (uint8 *)vm_wrap_address(VMBaseDiff + addr);

}
static inline vm_addr_t vm_get_guest_address(uint8 *addr)
{
	if ((addr >= gKernelData) && (addr <= gKernelData + 0x2000)) {
		return KERNEL_DATA_BASE + addr - gKernelData;
	}
	else if (in_sheep_mem_host(addr)) {
		return ((sheep_base + (addr - sheep_mem)));
	}
	/*else*/
		return vm_wrap_address((uintptr)addr - VMBaseDiff);
}
/*#define vm_do_get_virtual_address(addr) ((vm_addr_t)addr)*/

#define vm_get_physical_address
#define vm_get_virtual_address

static inline uint32 vm_read_physical_memory_1(vm_addr_t addr)
{
	if (ZERO(addr)) {
		return 0;
	}
	return vm_do_read_memory_1(vm_get_host_address(addr));
}
static inline uint32 vm_read_physical_memory_2(vm_addr_t addr)
{
	if (ZERO(addr)) {
		return 0;
	}
	return vm_do_read_memory_2((uint16 *)vm_get_host_address(addr));
}
static inline uint32 vm_read_physical_memory_4(vm_addr_t addr)
{
	if (ZERO(addr)) {
		return 0;
	}
	return vm_do_read_memory_4((uint32 *)vm_get_host_address(addr));
}
static inline uint64 vm_read_physical_memory_8(vm_addr_t addr)
{
	if (ZERO(addr)) {
		return 0;
	}
	return vm_do_read_memory_8((uint64 *)vm_get_host_address(addr));
}
#define vm_read_physical_memory_1_reversed vm_read_physical_memory_1
static inline uint32 vm_read_physical_memory_2_reversed(vm_addr_t addr)
{
	if (ZERO(addr)) {
		return 0;
	}
	return vm_do_read_memory_2_reversed((uint16 *)vm_get_host_address(addr));
}
static inline uint32 vm_read_physical_memory_4_reversed(vm_addr_t addr)
{
	if (ZERO(addr)) {
		return 0;
	}
	return vm_do_read_memory_4_reversed((uint32 *)vm_get_host_address(addr));
}
static inline uint64 vm_read_physical_memory_8_reversed(vm_addr_t addr)
{
	if (ZERO(addr)) {
		return 0;
	}
	return vm_do_read_memory_8_reversed((uint64 *)vm_get_host_address(addr));
}

#define vm_read_virtual_memory_1(a) vm_read_physical_memory_1(vm_get_physical_address(a))
#define vm_read_virtual_memory_2(a) vm_read_physical_memory_2(vm_get_physical_address(a))
#define vm_read_virtual_memory_4(a) vm_read_physical_memory_4(vm_get_physical_address(a))
#define vm_read_virtual_memory_8(a) vm_read_physical_memory_8(vm_get_physical_address(a))

#define vm_read_virtual_memory_1_reversed(a) vm_read_physical_memory_1_reversed(vm_get_physical_address(a))
#define vm_read_virtual_memory_2_reversed(a) vm_read_physical_memory_2_reversed(vm_get_physical_address(a))
#define vm_read_virtual_memory_4_reversed(a) vm_read_physical_memory_4_reversed(vm_get_physical_address(a))
#define vm_read_virtual_memory_8_reversed(a) vm_read_physical_memory_8_reversed(vm_get_physical_address(a))

#define vm_read_memory_1 vm_read_virtual_memory_1
#define vm_read_memory_2 vm_read_virtual_memory_2
#define vm_read_memory_4 vm_read_virtual_memory_4
#define vm_read_memory_8 vm_read_virtual_memory_8

#define vm_read_memory_1_reversed vm_read_virtual_memory_1_reversed
#define vm_read_memory_2_reversed vm_read_virtual_memory_2_reversed
#define vm_read_memory_4_reversed vm_read_virtual_memory_4_reversed
#define vm_read_memory_8_reversed vm_read_virtual_memory_8_reversed

static inline void vm_write_physical_memory_1(vm_addr_t addr, uint32 value)
{
	if (NO_WRITE(addr)) {
		return;/*just ignore invalid writes*/
	}
	vm_do_write_memory_1(vm_get_host_address(addr), value);
}
static inline void vm_write_physical_memory_2(vm_addr_t addr, uint32 value)
{
	if (NO_WRITE(addr)) {
		return;/*just ignore invalid writes*/
	}
	vm_do_write_memory_2((uint16 *)vm_get_host_address(addr), value);
}
static inline void vm_write_physical_memory_4(vm_addr_t addr, uint32 value)
{
	if (NO_WRITE(addr)) {
		return;/*just ignore invalid writes*/
	}
	vm_do_write_memory_4((uint32 *)vm_get_host_address(addr), value);
}
static inline void vm_write_physical_memory_8(vm_addr_t addr, uint64 value)
{
	if (NO_WRITE(addr)) {
		return;/*just ignore invalid writes*/
	}
	vm_do_write_memory_8((uint64 *)vm_get_host_address(addr), value);
}
#define vm_write_physical_memory_1_reversed vm_write_physical_memory_1
static inline void vm_write_physical_memory_2_reversed(vm_addr_t addr, uint32 value)
{
	if (NO_WRITE(addr)) {
		return;/*just ignore invalid writes*/
	}
	vm_do_write_memory_2_reversed((uint16 *)vm_get_host_address(addr), value);
}
static inline void vm_write_physical_memory_4_reversed(vm_addr_t addr, uint32 value)
{
	if (NO_WRITE(addr)) {
		return;/*just ignore invalid writes*/
	}
	vm_do_write_memory_4_reversed((uint32 *)vm_get_host_address(addr), value);
}
static inline void vm_write_physical_memory_8_reversed(vm_addr_t addr, uint64 value)
{
	if (NO_WRITE(addr)) {
		return;/*just ignore invalid writes*/
	}
	vm_do_write_memory_8_reversed((uint64 *)vm_get_host_address(addr), value);
}

#define vm_write_virtual_memory_1(a, v) vm_write_physical_memory_1(vm_get_physical_address(a), v)
#define vm_write_virtual_memory_2(a, v) vm_write_physical_memory_2(vm_get_physical_address(a), v)
#define vm_write_virtual_memory_4(a, v) vm_write_physical_memory_4(vm_get_physical_address(a), v)
#define vm_write_virtual_memory_8(a, v) vm_write_physical_memory_8(vm_get_physical_address(a), v)

#define vm_write_virtual_memory_1_reversed(a, v) vm_write_physical_memory_1_reversed(vm_get_physical_address(a), v)
#define vm_write_virtual_memory_2_reversed(a, v) vm_write_physical_memory_2_reversed(vm_get_physical_address(a), v)
#define vm_write_virtual_memory_4_reversed(a, v) vm_write_physical_memory_4_reversed(vm_get_physical_address(a), v)
#define vm_write_virtual_memory_8_reversed(a, v) vm_write_physical_memory_8_reversed(vm_get_physical_address(a), v)

#define vm_write_memory_1 vm_write_virtual_memory_1
#define vm_write_memory_2 vm_write_virtual_memory_2
#define vm_write_memory_4 vm_write_virtual_memory_4
#define vm_write_memory_8 vm_write_virtual_memory_8

#define vm_write_memory_1_reversed vm_write_virtual_memory_1_reversed
#define vm_write_memory_2_reversed vm_write_virtual_memory_2_reversed
#define vm_write_memory_4_reversed vm_write_virtual_memory_4_reversed
#define vm_write_memory_8_reversed vm_write_virtual_memory_8_reversed

static inline void *vm_memset(vm_addr_t addr, int c, size_t n)
{
	if (NO_WRITE(addr)) {
		return NULL;/*just ignore invalid writes*/
	}
	return memset((uint8 *)vm_get_host_address(addr), c, n);
}
#ifdef __cplusplus
static inline void *vm_memcpy(void *dest, vm_addr_t src, size_t n)
{
	if (ZERO(src)) {
		return memset(dest, 0, n);
	}
	else {
		return memcpy(dest, vm_get_host_address(src), n);
	}
}
static inline void *vm_memcpy(vm_addr_t dest, const void *src, size_t n)
{
	if (NO_WRITE(dest)) {
		return NULL;
	}
	/*else*/
		return memcpy(vm_get_host_address(dest), src, n);
}
#endif
static inline void *vm_memcpy(vm_addr_t dest, vm_addr_t src, size_t n)
{
	if (NO_WRITE(dest)) {
		return NULL;
	}
	else if (ZERO(src)) {
		return memset(vm_get_host_address(dest), 0, n);
	}
	/*else*/
		return memcpy(vm_get_host_address(dest), vm_get_host_address(src), n);
}
/*#endif*/

#endif /* VM_H */

