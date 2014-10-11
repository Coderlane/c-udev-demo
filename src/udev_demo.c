

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


int run_demo() {
	enum udev_demo_option opt;

	while((opt = get_option()) != UD_OPT_EXIT) {
		switch(opt) {
			case UD_OPT_LIST_ALL:
				list_all();
				break;
			case UD_OPT_LIST_SUBSYSTEM:
				list_subsystem();
				break;
			default:
				printf("Invalid Option!\n");
				break;
		}
	}
	return -1;
}

enum udev_demo_option get_option() {
	int input = -1;
	while(input == -1) {
		printf("1: List All\n");
		printf("2: List Subsystem\n");
		printf("3: Exit Demo\n");
		printf("Choice: ");
		scanf("%d", &input);
		if(input < UD_OPT_LIST_ALL || input > UD_OPT_EXIT) {
			input = -1;
		}	
	}
	return input;
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

int list_subsystem() {

	return -1;
}


int list_devs(struct udev_list_entry *devs) {
	struct udev_list_entry *dev_entry = NULL;
	struct udev_device *dev = NULL;

	udev_list_entry_foreach(dev_entry, devs) {
		const char *path;
		path = udev_list_entry_get_name(dev_entry);
		dev = udev_device_new_from_syspath(global_udev, path);

		printf("dev name: %s\n", path);
		printf("dev path: %s\n", udev_device_get_devnode(dev));
	}
	return 0;
}
