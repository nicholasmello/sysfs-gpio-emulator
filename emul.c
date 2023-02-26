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
#include <linux/module.h> /* Needed by all modules */
#include <linux/init.h>	  /* Needed for the macros */
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/cred.h>

// GPIO Struct
struct GPIO
{
	int active;	   // 0, not active / 1, active
	int value;	   // 0, logic low / 1, logic high
	int direction; // 0, in / 1, out
};

// Global GPIO
int MAX_GPIO_PORTS = 28;
struct GPIO gpio_state[28];

// Global variable for sysfs folder
static struct kobject *gpio_emul;

/**
 * @brief value show callback
 *
 * @param kobj
 * @param attr
 * @param buffer
 * @return ssize_t
 */
static ssize_t value_show(struct kobject *kobj, struct kobj_attribute *attr, char *buffer)
{
	long pinnum = 0;
	kstrtol(attr->attr.name, 10, &pinnum); // there will be an err because gpio0 has characters
	pr_info("Reading from %ld", pinnum);
	return sprintf(buffer, "%d\n", gpio_state[pinnum].value);
}

/**
 * @brief value store callback
 *
 * @param kobj
 * @param attr
 * @param buffer
 * @param count
 * @return ssize_t
 */
static ssize_t value_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buffer, size_t count)
{
	long pinnum = 0;
	long num = 0;
	int err = kstrtol(buffer, 10, &num);
	kstrtol(attr->attr.name, 10, &pinnum); // there will be an err because gpio0 has characters
	if (err)
		return -EINVAL;
	if (num != 0 && num != 1)
		return -EINVAL;
	pr_info("Setting %ld to %ld\n", pinnum, num);
	gpio_state[pinnum].value = num;
	return count;
}

/**
 * @brief direction show callback
 *
 * @param kobj
 * @param attr
 * @param buffer
 * @return ssize_t
 */
static ssize_t direction_show(struct kobject *kobj, struct kobj_attribute *attr, char *buffer)
{
	long pinnum = 0;
	char *dir = "out";
	kstrtol(attr->attr.name, 10, &pinnum); // there will be an err because gpio0 has characters
	pr_info("Reading from %ld", pinnum);
	if (!gpio_state[pinnum].direction) dir = "in";
	return sprintf(buffer, "%s\n", dir);
}



/**
 * @brief direction store callback
 *
 * @param kobj
 * @param attr
 * @param buffer
 * @param count
 * @return ssize_t
 */
static ssize_t direction_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buffer, size_t count)
{
	long pinnum = 0;
	kstrtol(attr->attr.name, 10, &pinnum); // there will be an err because gpio0 has characters
	if (strcmp(buffer, "in") == 0 || strcmp(buffer, "in\n") == 0)
		gpio_state[pinnum].direction = 0;
	else if (strcmp(buffer, "out") == 0 || strcmp(buffer, "out\n") == 0)
		gpio_state[pinnum].direction = 1;
	else
		return -EINVAL;
	return count;
}

// Create attributes
static struct kobject *gpio0;
static struct kobj_attribute gpio0_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio0_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio1;
static struct kobj_attribute gpio1_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio1_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio2;
static struct kobj_attribute gpio2_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio2_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio3;
static struct kobj_attribute gpio3_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio3_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio4;
static struct kobj_attribute gpio4_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio4_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio5;
static struct kobj_attribute gpio5_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio5_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio6;
static struct kobj_attribute gpio6_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio6_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio7;
static struct kobj_attribute gpio7_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio7_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio8;
static struct kobj_attribute gpio8_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio8_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio9;
static struct kobj_attribute gpio9_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio9_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio10;
static struct kobj_attribute gpio10_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio10_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio11;
static struct kobj_attribute gpio11_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio11_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio12;
static struct kobj_attribute gpio12_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio12_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio13;
static struct kobj_attribute gpio13_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio13_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio14;
static struct kobj_attribute gpio14_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio14_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio15;
static struct kobj_attribute gpio15_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio15_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio16;
static struct kobj_attribute gpio16_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio16_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio17;
static struct kobj_attribute gpio17_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio17_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio18;
static struct kobj_attribute gpio18_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio18_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio19;
static struct kobj_attribute gpio19_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio19_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio20;
static struct kobj_attribute gpio20_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio20_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio21;
static struct kobj_attribute gpio21_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio21_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio22;
static struct kobj_attribute gpio22_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio22_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio23;
static struct kobj_attribute gpio23_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio23_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio24;
static struct kobj_attribute gpio24_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio24_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio25;
static struct kobj_attribute gpio25_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio25_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio26;
static struct kobj_attribute gpio26_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio26_direction = __ATTR(direction, 0660, direction_show, direction_store);
static struct kobject *gpio27;
static struct kobj_attribute gpio27_value = __ATTR(value, 0660, value_show, value_store);
static struct kobj_attribute gpio27_direction = __ATTR(direction, 0660, direction_show, direction_store);

/**
 * @brief Read callback for export
 */
static ssize_t export_show(struct kobject *kobj, struct kobj_attribute *attr, char *buffer)
{
	return sprintf(buffer, "Export file not readable\n");
}

int create_gpio_obj(struct kobject *kobj, const char *kobj_txt, struct kobj_attribute *value)
{
	kobj = kobject_create_and_add(kobj_txt, gpio_emul);
	if (!kobj)
	{
		pr_info("Error creating module");
		return -ENOMEM;
	}
	// Create files
	if (sysfs_create_file(kobj, &value->attr))
	{
		pr_info("Error creating gpio value file");
		kobject_put(kobj);
		return -ENOMEM;
	}
	return 0;
}

/**
 * @brief write callback for export
 */
static ssize_t export_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buffer, size_t count)
{
	long pinnum = 0;
	int err = kstrtol(buffer, 10, &pinnum);
	if (err)
		return -EINVAL;
	if (pinnum >= MAX_GPIO_PORTS)
		return -EINVAL;
	pr_info("Export Number: %ld\n", pinnum);
	if (!gpio_state[pinnum].active) {
		gpio_state[pinnum].active = 1;
		if (pinnum == 0) {
			gpio0 = kobject_create_and_add("gpio0", gpio_emul);
			if (!gpio0)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio0, &gpio0_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio0);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio0, &gpio0_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio0);
				return -ENOMEM;
			}
		}
		else if (pinnum == 1) {
			gpio1 = kobject_create_and_add("gpio1", gpio_emul);
			if (!gpio1)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio1, &gpio1_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio1);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio1, &gpio1_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio1);
				return -ENOMEM;
			}
		}
		else if (pinnum == 2) {
			gpio2 = kobject_create_and_add("gpio2", gpio_emul);
			if (!gpio2)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio2, &gpio2_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio2);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio2, &gpio2_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio2);
				return -ENOMEM;
			}
		}
		else if (pinnum == 3) {
			gpio3 = kobject_create_and_add("gpio3", gpio_emul);
			if (!gpio3)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio3, &gpio3_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio3);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio3, &gpio3_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio3);
				return -ENOMEM;
			}
		}
		else if (pinnum == 4) {
			gpio4 = kobject_create_and_add("gpio4", gpio_emul);
			if (!gpio4)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio4, &gpio4_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio4);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio4, &gpio4_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio4);
				return -ENOMEM;
			}
		}
		else if (pinnum == 5) {
			gpio5 = kobject_create_and_add("gpio5", gpio_emul);
			if (!gpio5)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio5, &gpio5_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio5);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio5, &gpio5_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio5);
				return -ENOMEM;
			}
		}
		else if (pinnum == 6) {
			gpio6 = kobject_create_and_add("gpio6", gpio_emul);
			if (!gpio6)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio6, &gpio6_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio6);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio6, &gpio6_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio6);
				return -ENOMEM;
			}
		}
		else if (pinnum == 7) {
			gpio7 = kobject_create_and_add("gpio7", gpio_emul);
			if (!gpio7)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio7, &gpio7_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio7);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio7, &gpio7_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio7);
				return -ENOMEM;
			}
		}
		else if (pinnum == 8) {
			gpio8 = kobject_create_and_add("gpio8", gpio_emul);
			if (!gpio8)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio8, &gpio8_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio8);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio8, &gpio8_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio8);
				return -ENOMEM;
			}
		}
		else if (pinnum == 9) {
			gpio9 = kobject_create_and_add("gpio9", gpio_emul);
			if (!gpio9)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio9, &gpio9_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio9);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio9, &gpio9_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio9);
				return -ENOMEM;
			}
		}
		else if (pinnum == 10) {
			gpio10 = kobject_create_and_add("gpio10", gpio_emul);
			if (!gpio10)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio10, &gpio10_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio10);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio10, &gpio10_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio10);
				return -ENOMEM;
			}
		}
		else if (pinnum == 11) {
			gpio11 = kobject_create_and_add("gpio11", gpio_emul);
			if (!gpio11)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio11, &gpio11_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio11);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio11, &gpio11_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio11);
				return -ENOMEM;
			}
		}
		else if (pinnum == 12) {
			gpio12 = kobject_create_and_add("gpio12", gpio_emul);
			if (!gpio12)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio12, &gpio12_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio12);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio12, &gpio12_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio12);
				return -ENOMEM;
			}
		}
		else if (pinnum == 13) {
			gpio13 = kobject_create_and_add("gpio13", gpio_emul);
			if (!gpio13)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio13, &gpio13_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio13);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio13, &gpio13_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio13);
				return -ENOMEM;
			}
		}
		else if (pinnum == 14) {
			gpio14 = kobject_create_and_add("gpio14", gpio_emul);
			if (!gpio14)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio14, &gpio14_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio14);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio14, &gpio14_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio14);
				return -ENOMEM;
			}
		}
		else if (pinnum == 15) {
			gpio15 = kobject_create_and_add("gpio15", gpio_emul);
			if (!gpio15)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio15, &gpio15_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio15);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio15, &gpio15_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio15);
				return -ENOMEM;
			}
		}
		else if (pinnum == 16) {
			gpio16 = kobject_create_and_add("gpio16", gpio_emul);
			if (!gpio16)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio16, &gpio16_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio16);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio16, &gpio16_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio16);
				return -ENOMEM;
			}
		}
		else if (pinnum == 17) {
			gpio17 = kobject_create_and_add("gpio17", gpio_emul);
			if (!gpio17)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio17, &gpio17_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio17);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio17, &gpio17_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio17);
				return -ENOMEM;
			}
		}
		else if (pinnum == 18) {
			gpio18 = kobject_create_and_add("gpio18", gpio_emul);
			if (!gpio18)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio18, &gpio18_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio18);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio18, &gpio18_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio18);
				return -ENOMEM;
			}
		}
		else if (pinnum == 19) {
			gpio19 = kobject_create_and_add("gpio19", gpio_emul);
			if (!gpio19)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio19, &gpio19_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio19);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio19, &gpio19_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio19);
				return -ENOMEM;
			}
		}
		else if (pinnum == 20) {
			gpio20 = kobject_create_and_add("gpio20", gpio_emul);
			if (!gpio20)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio20, &gpio20_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio20);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio20, &gpio20_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio20);
				return -ENOMEM;
			}
		}
		else if (pinnum == 21) {
			gpio21 = kobject_create_and_add("gpio21", gpio_emul);
			if (!gpio21)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio21, &gpio21_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio21);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio21, &gpio21_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio21);
				return -ENOMEM;
			}
		}
		else if (pinnum == 22) {
			gpio22 = kobject_create_and_add("gpio22", gpio_emul);
			if (!gpio22)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio22, &gpio22_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio22);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio22, &gpio22_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio22);
				return -ENOMEM;
			}
		}
		else if (pinnum == 23) {
			gpio23 = kobject_create_and_add("gpio23", gpio_emul);
			if (!gpio23)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio23, &gpio23_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio23);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio23, &gpio23_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio23);
				return -ENOMEM;
			}
		}
		else if (pinnum == 24) {
			gpio24 = kobject_create_and_add("gpio24", gpio_emul);
			if (!gpio24)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio24, &gpio24_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio24);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio24, &gpio24_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio24);
				return -ENOMEM;
			}
		}
		else if (pinnum == 25) {
			gpio25 = kobject_create_and_add("gpio25", gpio_emul);
			if (!gpio25)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio25, &gpio26_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio25);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio25, &gpio25_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio25);
				return -ENOMEM;
			}
		}
		else if (pinnum == 26) {
			gpio26 = kobject_create_and_add("gpio26", gpio_emul);
			if (!gpio26)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio26, &gpio26_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio26);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio26, &gpio26_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio26);
				return -ENOMEM;
			}
		}
		else if (pinnum == 27) {
			gpio27 = kobject_create_and_add("gpio27", gpio_emul);
			if (!gpio27)
			{
				pr_info("Error creating module");
				return -ENOMEM;
			}
			// Create files
			if (sysfs_create_file(gpio27, &gpio27_value.attr))
			{
				pr_info("Error creating gpio value file");
				kobject_put(gpio27);
				return -ENOMEM;
			}
			if (sysfs_create_file(gpio27, &gpio27_direction.attr))
			{
				pr_info("Error creating gpio direction file");
				kobject_put(gpio27);
				return -ENOMEM;
			}
		}
	}
	return count;
}

// Create export file with callbacks
static struct kobj_attribute export = __ATTR(export, 0220, export_show, export_store);

/**
 * @brief Read callback for export
 */
static ssize_t unexport_show(struct kobject *kobj, struct kobj_attribute *attr, char *buffer)
{
	return sprintf(buffer, "UnExport file not readable\n");
}

void delete_object(struct kobject *kobj, struct kobj_attribute *value) {
	if (!kobj) {
		pr_info("null ptr in deletion????");
		return;
	}
	sysfs_remove_file(kobj, &value->attr);
	kobject_del(kobj);
}

/**
 * @brief write callback for export
 */
static ssize_t unexport_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buffer, size_t count)
{
	long pinnum = 0;
	int err = kstrtol(buffer, 10, &pinnum);
	if (err)
		return -EINVAL;
	if (pinnum >= MAX_GPIO_PORTS)
		return -EINVAL;
	pr_info("UnExport Number: %ld\n", pinnum);
	if (gpio_state[pinnum].active)
	{
		gpio_state[pinnum].active = 0;
		if (pinnum == 0) {
			if (!gpio0) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio0, &gpio0_value.attr);
				sysfs_remove_file(gpio0, &gpio0_direction.attr);
				kobject_del(gpio0);
			}
		}
		else if (pinnum == 1) {
			if (!gpio1) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio1, &gpio1_value.attr);
				sysfs_remove_file(gpio1, &gpio1_direction.attr);
				kobject_del(gpio1);
			}
		}
		else if (pinnum == 2) {
			if (!gpio2) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio2, &gpio2_value.attr);
				sysfs_remove_file(gpio2, &gpio2_direction.attr);
				kobject_del(gpio2);
			}
		}
		else if (pinnum == 3) {
			if (!gpio3) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio3, &gpio3_value.attr);
				sysfs_remove_file(gpio3, &gpio3_direction.attr);
				kobject_del(gpio3);
			}
		}
		else if (pinnum == 4) {
			if (!gpio4) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio4, &gpio4_value.attr);
				sysfs_remove_file(gpio4, &gpio4_direction.attr);
				kobject_del(gpio4);
			}
		}
		else if (pinnum == 5) {
			if (!gpio5) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio5, &gpio5_value.attr);
				sysfs_remove_file(gpio5, &gpio5_direction.attr);
				kobject_del(gpio5);
			}
		}
		else if (pinnum == 6) {
			if (!gpio6) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio6, &gpio6_value.attr);
				sysfs_remove_file(gpio6, &gpio6_direction.attr);
				kobject_del(gpio6);
			}
		}
		else if (pinnum == 7) {
			if (!gpio7) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio7, &gpio7_value.attr);
				sysfs_remove_file(gpio7, &gpio7_direction.attr);
				kobject_del(gpio7);
			}
		}
		else if (pinnum == 8) {
			if (!gpio8) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio8, &gpio8_value.attr);
				sysfs_remove_file(gpio8, &gpio8_direction.attr);
				kobject_del(gpio8);
			}
		}
		else if (pinnum == 9) {
			if (!gpio9) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio9, &gpio9_value.attr);
				sysfs_remove_file(gpio9, &gpio9_direction.attr);
				kobject_del(gpio9);
			}
		}
		else if (pinnum == 10) {
			if (!gpio10) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio10, &gpio10_value.attr);
				sysfs_remove_file(gpio10, &gpio10_direction.attr);
				kobject_del(gpio10);
			}
		}
		else if (pinnum == 11) {
			if (!gpio11) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio11, &gpio11_value.attr);
				sysfs_remove_file(gpio11, &gpio11_direction.attr);
				kobject_del(gpio11);
			}
		}
		else if (pinnum == 12) {
			if (!gpio12) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio12, &gpio12_value.attr);
				sysfs_remove_file(gpio12, &gpio12_direction.attr);
				kobject_del(gpio12);
			}
		}
		else if (pinnum == 13) {
			if (!gpio13) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio13, &gpio13_value.attr);
				sysfs_remove_file(gpio13, &gpio13_direction.attr);
				kobject_del(gpio13);
			}
		}
		else if (pinnum == 14) {
			if (!gpio14) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio14, &gpio14_value.attr);
				sysfs_remove_file(gpio14, &gpio14_direction.attr);
				kobject_del(gpio14);
			}
		}
		else if (pinnum == 15) {
			if (!gpio15) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio15, &gpio15_value.attr);
				sysfs_remove_file(gpio15, &gpio15_direction.attr);
				kobject_del(gpio15);
			}
		}
		else if (pinnum == 16) {
			if (!gpio16) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio16, &gpio16_value.attr);
				sysfs_remove_file(gpio16, &gpio16_direction.attr);
				kobject_del(gpio16);
			}
		}
		else if (pinnum == 17) {
			if (!gpio17) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio17, &gpio17_value.attr);
				sysfs_remove_file(gpio17, &gpio17_direction.attr);
				kobject_del(gpio17);
			}
		}
		else if (pinnum == 18) {
			if (!gpio18) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio18, &gpio18_value.attr);
				sysfs_remove_file(gpio18, &gpio18_direction.attr);
				kobject_del(gpio18);
			}
		}
		else if (pinnum == 19) {
			if (!gpio19) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio19, &gpio19_value.attr);
				sysfs_remove_file(gpio19, &gpio19_direction.attr);
				kobject_del(gpio19);
			}
		}
		else if (pinnum == 20) {
			if (!gpio20) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio20, &gpio20_value.attr);
				sysfs_remove_file(gpio20, &gpio20_direction.attr);
				kobject_del(gpio20);
			}
		}
		else if (pinnum == 21) {
			if (!gpio21) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio21, &gpio21_value.attr);
				sysfs_remove_file(gpio21, &gpio21_direction.attr);
				kobject_del(gpio21);
			}
		}
		else if (pinnum == 22) {
			if (!gpio22) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio22, &gpio22_value.attr);
				sysfs_remove_file(gpio22, &gpio22_direction.attr);
				kobject_del(gpio22);
			}
		}
		else if (pinnum == 23) {
			if (!gpio23) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio23, &gpio23_value.attr);
				sysfs_remove_file(gpio23, &gpio23_direction.attr);
				kobject_del(gpio23);
			}
		}
		else if (pinnum == 24) {
			if (!gpio24) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio24, &gpio24_value.attr);
				sysfs_remove_file(gpio24, &gpio24_direction.attr);
				kobject_del(gpio24);
			}
		}
		else if (pinnum == 25) {
			if (!gpio25) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio25, &gpio25_value.attr);
				sysfs_remove_file(gpio25, &gpio25_direction.attr);
				kobject_del(gpio25);
			}
		}
		else if (pinnum == 26) {
			if (!gpio26) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio26, &gpio26_value.attr);
				sysfs_remove_file(gpio26, &gpio26_direction.attr);
				kobject_del(gpio26);
			}
		}
		else if (pinnum == 27) {
			if (!gpio27) {
				pr_info("null ptr in deletion????");
			} else {
				sysfs_remove_file(gpio27, &gpio27_value.attr);
				sysfs_remove_file(gpio27, &gpio27_direction.attr);
				kobject_del(gpio27);
			}
		}
	}
	return count;
}

// Create export file with callbacks
static struct kobj_attribute unexport = __ATTR(unexport, 0220, unexport_show, unexport_store);

/**
 * @brief Set ownership callback
 */
void sudo_user_ownership(struct kobject *kobj, kuid_t *uid, kgid_t *gid)
{
	uid->val = 0;
	gid->val = 27;
}

static int __init module_start(void)
{
	int i = 0;
	pr_info("Loading gpio module...\n");

	while (i < MAX_GPIO_PORTS)
	{
		gpio_state[i].active = 0;
		gpio_state[i].value = 0;
		gpio_state[i].direction = 0;
		i = i + 1;
	}

	// Create folder gpio_emul
	gpio_emul = kobject_create_and_add("gpio_emul", kernel_kobj);
	if (!gpio_emul)
	{
		pr_info("Error creating module");
		return -ENOMEM;
	}
	gpio_emul->ktype->get_ownership = sudo_user_ownership;

	// Create files
	if (sysfs_create_file(gpio_emul, &export.attr))
	{
		pr_info("Error creating export file");
		kobject_put(gpio_emul);
		return -ENOMEM;
	}
	if (sysfs_create_file(gpio_emul, &unexport.attr))
	{
		pr_info("Error creating unexport file");
		kobject_put(gpio_emul);
		return -ENOMEM;
	}

	pr_info("Module loaded!\n");
	return 0;
}

static void __exit module_end(void)
{
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
