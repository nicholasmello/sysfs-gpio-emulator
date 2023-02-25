/**
 * @file gpio.c
 * @author nmello
 * @brief GPIO Emulator for testing without microcontroller
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <linux/module.h>       /* Needed by all modules */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/cred.h>

// Global variable for sysfs folder
static struct kobject *gpio_emul;

/**
 * @brief Read callback for export
 */
static ssize_t export_show(struct kobject *kobj, struct kobj_attribute *attr, char *buffer) {
	return sprintf(buffer, "Export file not readable\n");
}

/**
 * @brief write callback for export
 */
static ssize_t export_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buffer, size_t count) {
	long num = 0;
	int success = kstrtol(buffer, 10, &num);
	if (!success) {
		return success;
	}
	pr_info("Export Number: %ld\n", num);
	return count;
}

// Create export file with callbacks
static struct kobj_attribute export = __ATTR(export, 0220, export_show, export_store);

/**
 * @brief Read callback for export
 */
static ssize_t unexport_show(struct kobject *kobj, struct kobj_attribute *attr, char *buffer) {
	return sprintf(buffer, "UnExport file not readable\n");
}

/**
 * @brief write callback for export
 */
static ssize_t unexport_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buffer, size_t count) {
	pr_info("sysfs_test - you wrote '%s' to /sys/kernel/%s/%s\n", buffer, kobj->name, attr->attr.name);
	return count;
}

// Create export file with callbacks
static struct kobj_attribute unexport = __ATTR(unexport, 0220, unexport_show, unexport_store);

/**
 * @brief Set ownership callback
 */
void sudo_user_ownership(struct kobject *kobj, kuid_t *uid, kgid_t *gid) {
	uid->val = 0;
	gid->val = 27;
}


static int __init module_start(void) {
	pr_info("Loading gpio module...\n");

	// Create folder gpio_emul
	gpio_emul = kobject_create_and_add("gpio_emul", kernel_kobj);
	if (!gpio_emul) {
		pr_info("Error creating module");
		return -ENOMEM;
	}
	gpio_emul->ktype->get_ownership = sudo_user_ownership;

	// Create files
	if (sysfs_create_file(gpio_emul, &export.attr)) {
		pr_info("Error creating export file");
		kobject_put(gpio_emul);
		return -ENOMEM;
	}
	if (sysfs_create_file(gpio_emul, &unexport.attr)) {
		pr_info("Error creating unexport file");
		kobject_put(gpio_emul);
		return -ENOMEM;
	}

	pr_info("Module loaded!\n");
	return 0;
}

static void __exit module_end(void) {
	pr_info("Cleaning up gpio emulator\n");
	sysfs_remove_file(gpio_emul, &export.attr);
	sysfs_remove_file(gpio_emul, &unexport.attr);
	kobject_put(gpio_emul);
}

module_init(module_start);
module_exit(module_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nmello");
MODULE_DESCRIPTION("GPIO Emulator for testing without microcontroller");
