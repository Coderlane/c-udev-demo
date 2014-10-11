/**
 * @file main.c
 * @brief A breif demonstration of some libudev features.
 * @author Travis Lane
 * @version 1.0.0
 * @date 2014-10-10
 */

#include <udev_demo.h>

int main(int argc, char **argv) {
	init_demo();
	run_demo(argc, argv);
	cleanup_demo();
	return 0;
}
