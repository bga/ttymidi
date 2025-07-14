//# from #include <sys/ioctl.h>
int ioctl(int, int, ...);

//# bit hack...
#include "/usr/include/asm-generic/termbits.h"
#include "/usr/include/asm-generic/ioctls.h"

// #include <termios.h>    /* POSIX terminal control definitions */


int TTY_setCustomBaudRate(int serialFd, int baudrate) {
	struct termios2 tio;

	ioctl(serialFd, TCGETS2, &tio);
	
	tio.c_cflag &= ~CBAUD;
	tio.c_cflag |= BOTHER;
	tio.c_ispeed = baudrate;
	tio.c_ospeed = baudrate;

	int ret = ioctl(serialFd, TCSETS2, &tio);

	return ret;
}
