#include <sys/stat.h>
#include "uart.h"

#ifdef __cplusplus
extern "C" {
#endif

void _exit(int code) {
	while(1);
}

void _kill(int pid, int sig) {

}

int _getpid(void) {
	return 0;
}

extern char _end;
char *used_heap_end = &_end;

void * _sbrk(int incr) {
	char *prev_heap_end = used_heap_end;
	used_heap_end += incr;

	return (void *) prev_heap_end;
}

int _write(int file, char *ptr, int len) {
	int todo;

	for (todo = 0; todo < len; todo++) {
		uart_putc(*ptr++);
	}
	return len;
}

int _read(int file, char *ptr, int len) {
	return 0;
}

int _close(int file) {
	return -1;
}

int _isatty(int file) {
	return 1;
}

int _lseek(int file, int ptr, int dir) {
	return 0;
}

int _fstat(int file, struct stat *st) {
	st->st_mode = S_IFCHR;
	return 0;
}

#ifdef __cplusplus
} /* _CPLUSPLUS */
#endif
