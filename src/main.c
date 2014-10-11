
#include <udev_demo.h>


int main(int argc, char **argv) {
	init_demo();
	run_demo(argc, argv);
	cleanup_demo();
	return 0;
}
