

#include <udev_demo.h>

static struct udev *global_udev = NULL;

int init_demo() {
	if(global_udev != NULL) {
		return -1;
	}
	global_udev = udev_new();
	return 0;
}


int cleanup_demo() {
	if(global_udev == NULL) {
		return 0;
	}
	udev_unref(global_udev);
	return 0;
}


int run_demo() {

	return -1;
}
