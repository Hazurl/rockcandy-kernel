typedef struct {
	void (*clear)();
	unsigned short (*getc)();
	void (*puts)(unsigned short *);
	void (*setattr)(unsigned char attr);
} ROCKCANDY_LIBRARY;

unsigned long _start(ROCKCANDY_LIBRARY* lib) {
    lib->puts(u"Hello from shell.elf :D");
    return 0;
}