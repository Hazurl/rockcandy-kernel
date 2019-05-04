// Page numbers relate to this document:
// https://uclibc.org/docs/elf-64-gen.pdf

#ifndef ELF_H
#define ELF_H

// ELF Types(Page 2)
#if __SIZEOF_LONG__ == 8
typedef unsigned long Elf64_Addr;
typedef unsigned long Elf64_Off;
#else
#error "Unable to define Elf64_Addr"
#endif

#if __SIZEOF_SHORT__ == 2
typedef unsigned short Elf64_Half;
#else
#error "Unable to define Elf64_Half"
#endif

#if __SIZEOF_INT__ == 4
typedef unsigned int Elf64_Word;
typedef signed int Elf64_Sword;
#else
#error "Unable to define Elf64_Word"
#endif

#if __SIZEOF_LONG__ == 8
typedef unsigned long Elf64_Xword;
typedef signed long Elf64_Sxword;
#else
#error "Unable to define Elf64_Xword"
#endif

// File Header(Page 3)
typedef struct {
	unsigned char e_ident[4];
	unsigned char e_class;
	unsigned char e_data;
	unsigned char e_version;
	unsigned char e_osabi;
	unsigned char e_abiversion;
	unsigned char e_pad;
	unsigned char e_unused[5];
	unsigned char e_nident;
	Elf64_Half e_type;
	Elf64_Half e_machine;
	Elf64_Word e_version;
	Elf64_Addr e_entry;
	Elf64_Off e_phoff;
	Elf64_Off e_shoff;
	Elf64_Word e_flags;
	Elf64_Half e_ehsize;
	Elf64_Half e_phentsize;
	Elf64_Half e_phnum;
	Elf64_Half e_shentsize;
	Elf64_Half e_shnum;
	Elf64_Half e_shstrndx;
} Elf64_Ehdr;

// ELF Class(Page 5)
#define ELFCLASS32 1
#define ELFCLASS64 2

// ELF Data(Page 5)
#define ELFDATA2LSB 1 // Little Endian
#define ELFDATA2MSB 2 // Big Endian

// ELF ABI(Page 5)
#define ELFOSABI_LINUX 3 // In case we ever decide to implement a Linux subsystem
#define ELFOSABI_ROCKCANDY 193
#define ELFOSABI_STANDALONE 255

// ELF Type(Page 5)
#define ET_NONE 0
#define ET_REL 1
#define ET_EXEC 2
#define ET_DYN 3
#define ET_CORE 4

// ELF Sections(Page 6)
#define SHN_UNDEF 0
#define SHN_ABS 0xFFF1
#define SHN_COMMON 0xFFSH

// ELF Section Header(Page 6)
typedef struct {
	Elf64_Word sh_name;
	Elf64_Word sh_type;
	Elf64_Xword sh_flags;
	Elf64_Addr sh_addr;
	Elf64_Off sh_offset;
	Elf64_Xword sh_size;
	Elf64_Word sh_link;
	Elf64_Word sh_info;
	Elf64_Xword sh_addralign;
	Elf64_Xword sh_entsize;
} Elf64_Shdr;

// ELF Section Type(Page 7)
#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_HASH 5
#define SHT_DYNAMIC 6
#define SHT_NOTE 7
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHT_SHLIB 10
#define SHT_DYNSYM 11

// ELF Section Flags(Page 8)
#define SHF_WRITE 1 << 0
#define SHF_ALLOC 1 << 1
#define SHF_EXECINSTR 1 << 2

// ELF Symbol(Page 9)
typedef struct {
	Elf64_Word st_name;
	unsigned char st_info;
	unsigned char st_other;
	Elf64_Half st_shndx;
	Elf64_Addr st_value;
	Elf64_Xword st_size;
} Elf64_Sym;

// ELF Bindings(Page 10)
#define STB_LOCAL 0
#define STB_GLOBAL 1
#define STB_WEAK 2

// ELF Types(Page 10)
#define STT_NOTYPE 0
#define STT_OBJECT 1
#define STT_FUNC 2
#define STT_SECTION 3
#define STT_FILE 4

// ELF Relocations(Page 11)
typedef struct {
	Elf64_Addr r_offset;
	Elf64_Xword r_info;
} Elf64_Rel;

typedef struct {
	Elf64_Addr r_offset;
	Elf64_Xword r_info;
	Elf64_Sxword r_addend;
} Elf64_Rela;

// ELF Program Header Table(Page 12)
typedef struct {
  Elf64_Word p_type;
  Elf64_Word p_flags;
  Elf64_Off p_offset;
  Elf64_Addr p_vaddr;
  Elf64_Addr p_paddr;
  Elf64_Xword p_filesz;
  Elf64_Xword p_memsz;
  Elf64_Xword p_align;
} Elf64_Phdr;

// ELF Program Header Type(Page 12)
#define PT_NULL 0
#define PT_LOAD 1
#define PT_DYNAMIC 2
#define PT_INTERP 3
#define PT_NOTE 4
#define PT_SHLIB 5
#define PT_PHDR 6

// ELF Program Header Flags(Page 13)
#define PF_X 1 << 0
#define PF_W 1 << 1
#define PF_R 1 << 2

// ELF Dynamic Table(Page 14)
typedef struct {
  Elf64_Sxword d_tag;
  union {
    Elf64_Xword d_val;
    Elf64_Addr d_ptr;
  } d_un;
} Elf64_Dyn;

// ELF Dynamic Table Entries(Page 15)
#define DT_NULL 0
#define DT_NEEDED 1
#define DT_PLTRELSZ 2
#define DT_PLTGOT 3
#define DT_HASH 4
#define DT_STRTAB 5
#define DT_SYMTAB 6
#define DT_RELA 7
#define DT_RELASZ 8
#define DT_RELAENT 9
#define DT_STRSZ 10
#define DT_SYMENT 11
#define DT_INIT 12
#define DT_FINI 13
#define DT_SONAME 14
#define DT_RPATH 15
#define DT_SYMBOLIC 16
#define DT_REL 17
#define DT_RELSZ 18
#define DT_RELENT 19
#define DT_PLTREL 20
#define DT_DEBUG 21
#define DT_TEXTREL 22
#define DT_JMPREL 23
#define DT_BIND_NOW 24
#define DT_INIT_ARRAY 25
#define DT_FINI_ARRAY 26
#define DT_INIT_ARRAYSZ 27
#define DT_FINI_ARRAYSZ 28

// ELF Hashing Function(Page 17)
usigned long elf64_hash(const unsigned char *name) {
  unsighed long h = 0, g;
  while(*name) {
    h = (h << 4) + *name++;
		if(g = h & (4 << 28)) {
			h ^= g >> 24;
    }
		h &= ~(4 << 28);
  }
	return h;
}

#endif
