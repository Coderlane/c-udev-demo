/**
 * @file udev_demo.c
 * @brief A breif demonstration of some libudev features.
 * I'm mostly looking to see what information I can get from it. 
 * @author Travis Lane
 * @version 1.0.0 
 * @date 2014-10-10
 */

#include <udev_demo.h>

static struct udev *global_udev = NULL;

/**
 * @brief Initialize the demonstration.
 *
 * @return A status code.
 */
int init_demo() {
	if(global_udev != NULL) {
		return -1;
	}
	global_udev = udev_new();
	assert(global_udev != NULL);
	return 0;
}

/**
 * @brief Cleanup the demo.
 *
 * @return A status code.
 */
int cleanup_demo() {
	if(global_udev == NULL) {
		return 0;
	}
	udev_unref(global_udev);
	return 0;
}

/**
 * @brief Run the demo on the input.
 * No args = list all.
 * one arg = list based on sysattr.
 * two arg = list based on sysattr and value.
 *
 * @param argc argc from main.
 * @param argv argv from main.
 *
 * @return A status code.
 */
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


/**
 * @brief List all devices and their properites.
 *
 * @return A status code.
 */
int list_all() {
	struct udev_enumerate *enumer = NULL;
	struct udev_list_entry *devs = NULL; 

	// Setup the enumeration.
	enumer = udev_enumerate_new(global_udev);
	udev_enumerate_scan_devices(enumer);
	// Scan and get the list of items.
	devs = udev_enumerate_get_list_entry(enumer);

	list_devs(devs);

	udev_enumerate_unref(enumer);

	return 0;
}

/**
 * @brief List entries filtered by sysattr and value if specified.
 *
 * @param sysattr The sysattr we should search for.
 * @param value The value we should search for, or NULL.
 *
 * @return A status code. 
 */
int list_sysattr(char *sysattr, char *value) {
	struct udev_enumerate *enumer = NULL;
	struct udev_list_entry *devs = NULL; 

	// Set up the enumeration
	enumer = udev_enumerate_new(global_udev);
	// Look for the input values
	udev_enumerate_add_match_sysattr(enumer, sysattr, value);
	// Scan and get the list of items found.
	udev_enumerate_scan_devices(enumer);
	devs = udev_enumerate_get_list_entry(enumer);

	list_devs(devs);

	udev_enumerate_unref(enumer);
	return 0;
}

/**
 * @brief List the devices found.
 * Print the syspath and all properties.
 *
 * @param devs The list of devices found.
 *
 * @return A status code.
 */
int list_devs(struct udev_list_entry *devs) {
	struct udev_list_entry *dev_entry = NULL, 
												 *dev_property = NULL, *dev_properties = NULL;
	struct udev_device *dev = NULL;
	const char *path;
	
	udev_list_entry_foreach(dev_entry, devs) {
		path = udev_list_entry_get_name(dev_entry);
		dev = udev_device_new_from_syspath(global_udev, path);

		// Print the device name.
		printf("SYSPATH:%s\n", path);

		// Get and print the properties
		dev_properties = udev_device_get_properties_list_entry(dev);
		udev_list_entry_foreach(dev_property, dev_properties) {
			printf("%s:%s\n", 
					udev_list_entry_get_name(dev_property),
					udev_list_entry_get_value(dev_property));
		}
		printf("\n");
	}
	return 0;
}
