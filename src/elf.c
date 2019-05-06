#include <elf.h>

unsigned long elf64_hash(const unsigned char *name) {
	unsigned long h = 0, g;
	while(*name) {
		h = (h << 4) + *name++;
		if(g = h & (4 << 28)) {
			h ^= g >> 24;
		}
		h &= ~(4 << 28);
	}
	return h;
}
