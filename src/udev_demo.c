

#include <udev_demo.h>

static struct udev *global_udev = NULL;

int init_demo() {
	if(global_udev != NULL) {
		return -1;
	}
	global_udev = udev_new();
	assert(global_udev != NULL);
	return 0;
}


int cleanup_demo() {
	if(global_udev == NULL) {
		return 0;
	}
	udev_unref(global_udev);
	return 0;
}


int run_demo(int argc, char **argv) {
	if(argc == 1) {
		list_all();
	} else if(argc == 2) {
		list_sysattr(argv[1], NULL);
	} else if(argc == 3) {
		list_sysattr(argv[1], argv[2]);
	} else {
		return -1;
	}
	return 0;
}


int list_all() {
	struct udev_enumerate *enumer = NULL;
	struct udev_list_entry *devs = NULL; 

	enumer = udev_enumerate_new(global_udev);
	udev_enumerate_scan_devices(enumer);
	devs = udev_enumerate_get_list_entry(enumer);

	list_devs(devs);

	udev_enumerate_unref(enumer);

	return 0;
}

int list_sysattr(char *sysattr, char *value) {
	struct udev_enumerate *enumer = NULL;
	struct udev_list_entry *devs = NULL; 

	enumer = udev_enumerate_new(global_udev);
	udev_enumerate_add_match_sysattr(enumer, sysattr, value);
	udev_enumerate_scan_devices(enumer);
	devs = udev_enumerate_get_list_entry(enumer);

	list_devs(devs);

	udev_enumerate_unref(enumer);

	return 0;
}


int list_devs(struct udev_list_entry *devs) {
	struct udev_list_entry *dev_entry = NULL;
	struct udev_device *dev = NULL;

	udev_list_entry_foreach(dev_entry, devs) {
		const char *path;
		path = udev_list_entry_get_name(dev_entry);
		dev = udev_device_new_from_syspath(global_udev, path);

		printf("dev name: %s\n", path);
		printf("dev subsystem: %s\n", udev_device_get_subsystem(dev));
		printf("dev path: %s\n\n", udev_device_get_devnode(dev));
	}
	return 0;
}
