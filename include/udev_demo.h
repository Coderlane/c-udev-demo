

#ifndef UDEV_DEMO_H
#define UDEV_DEMO_H

#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum udev_demo_option {
	UD_OPT_LIST_ALL = 1,
	UD_OPT_LIST_SUBSYSTEM = 2,
	UD_OPT_EXIT = 3 
};

// Public Demo Functions
int init_demo();
int cleanup_demo();
int run_demo();

// Internal functions
enum udev_demo_option get_option();
int list_all();
int list_subsystem();
int list_devs(struct udev_list_entry *devs);
#endif
