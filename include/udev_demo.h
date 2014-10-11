

#ifndef UDEV_DEMO_H
#define UDEV_DEMO_H

#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Public Demo Functions
int init_demo();
int cleanup_demo();
int run_demo(int argc, char **argv);

// Internal functions
enum udev_demo_option get_option();
int list_all();
int list_sysattr(char *sysattr, char *value);
int list_devs(struct udev_list_entry *devs);
#endif
