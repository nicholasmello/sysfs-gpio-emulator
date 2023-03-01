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
	pr_info("GPIO_EMULATOR: Reading from %ld", pinnum);
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
	pr_info("GPIO_EMULATOR: Setting %ld to %ld\n", pinnum, num);
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
	pr_info("GPIO_EMULATOR: Reading from %ld", pinnum);
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

int create_gpio_obj(struct kobject **kobj, const char *kobj_txt, struct kobj_attribute *value, struct kobj_attribute *direction)
{
	*kobj = kobject_create_and_add(kobj_txt, gpio_emul);
	if (!*kobj)
	{
		pr_info("GPIO_EMULATOR: Error creating module");
		return -ENOMEM;
	}
	// Create files
	if (sysfs_create_file(*kobj, &value->attr))
	{
		pr_info("GPIO_EMULATOR: Error creating gpio value file");
		kobject_put(*kobj);
		return -ENOMEM;
	}
	if (sysfs_create_file(*kobj, &direction->attr))
	{
		pr_info("GPIO_EMULATOR: Error creating gpio value file");
		kobject_put(*kobj);
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
	pr_info("GPIO_EMULATOR: Export Number: %ld\n", pinnum);
	if (!gpio_state[pinnum].active) {
		gpio_state[pinnum].active = 1;
		if (pinnum == 0) create_gpio_obj(&gpio0, "gpio0", &gpio0_value, &gpio0_direction);
		else if (pinnum == 1) create_gpio_obj(&gpio1, "gpio1", &gpio1_value, &gpio1_direction);
		else if (pinnum == 2) create_gpio_obj(&gpio2, "gpio2", &gpio2_value, &gpio2_direction);
		else if (pinnum == 3) create_gpio_obj(&gpio3, "gpio3", &gpio3_value, &gpio3_direction);
		else if (pinnum == 4) create_gpio_obj(&gpio4, "gpio4", &gpio4_value, &gpio4_direction);
		else if (pinnum == 5) create_gpio_obj(&gpio5, "gpio5", &gpio5_value, &gpio5_direction);
		else if (pinnum == 6) create_gpio_obj(&gpio6, "gpio6", &gpio6_value, &gpio6_direction);
		else if (pinnum == 7) create_gpio_obj(&gpio7, "gpio7", &gpio7_value, &gpio7_direction);
		else if (pinnum == 8) create_gpio_obj(&gpio8, "gpio8", &gpio8_value, &gpio8_direction);
		else if (pinnum == 9) create_gpio_obj(&gpio9, "gpio9", &gpio9_value, &gpio9_direction);
		else if (pinnum == 10) create_gpio_obj(&gpio10, "gpio10", &gpio10_value, &gpio10_direction);
		else if (pinnum == 11) create_gpio_obj(&gpio11, "gpio11", &gpio11_value, &gpio11_direction);
		else if (pinnum == 12) create_gpio_obj(&gpio12, "gpio12", &gpio12_value, &gpio12_direction);
		else if (pinnum == 13) create_gpio_obj(&gpio13, "gpio13", &gpio13_value, &gpio13_direction);
		else if (pinnum == 14) create_gpio_obj(&gpio14, "gpio14", &gpio14_value, &gpio14_direction);
		else if (pinnum == 15) create_gpio_obj(&gpio15, "gpio15", &gpio15_value, &gpio15_direction);
		else if (pinnum == 16) create_gpio_obj(&gpio16, "gpio16", &gpio16_value, &gpio16_direction);
		else if (pinnum == 17) create_gpio_obj(&gpio17, "gpio17", &gpio17_value, &gpio17_direction);
		else if (pinnum == 18) create_gpio_obj(&gpio18, "gpio18", &gpio18_value, &gpio18_direction);
		else if (pinnum == 19) create_gpio_obj(&gpio19, "gpio19", &gpio19_value, &gpio19_direction);
		else if (pinnum == 20) create_gpio_obj(&gpio20, "gpio20", &gpio20_value, &gpio20_direction);
		else if (pinnum == 21) create_gpio_obj(&gpio21, "gpio21", &gpio21_value, &gpio21_direction);
		else if (pinnum == 22) create_gpio_obj(&gpio22, "gpio22", &gpio22_value, &gpio22_direction);
		else if (pinnum == 23) create_gpio_obj(&gpio23, "gpio23", &gpio23_value, &gpio23_direction);
		else if (pinnum == 24) create_gpio_obj(&gpio24, "gpio24", &gpio24_value, &gpio24_direction);
		else if (pinnum == 25) create_gpio_obj(&gpio25, "gpio25", &gpio25_value, &gpio25_direction);
		else if (pinnum == 26) create_gpio_obj(&gpio26, "gpio26", &gpio26_value, &gpio26_direction);
		else if (pinnum == 27) create_gpio_obj(&gpio27, "gpio27", &gpio27_value, &gpio27_direction);
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

void delete_object(struct kobject *kobj, struct kobj_attribute *value, struct kobj_attribute *direction) {
	if (!kobj) {
		pr_info("GPIO_EMULATOR: null ptr in deletion???? %p", kobj);
		return;
	}
	sysfs_remove_file(kobj, &value->attr);
	sysfs_remove_file(kobj, &direction->attr);
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
	pr_info("GPIO_EMULATOR: UnExport Number: %ld\n", pinnum);
	if (gpio_state[pinnum].active)
	{
		gpio_state[pinnum].active = 0;
		if (pinnum == 0) delete_object(gpio0, &gpio0_value, &gpio0_direction);
		else if (pinnum == 1) delete_object(gpio1, &gpio1_value, &gpio1_direction);
		else if (pinnum == 2) delete_object(gpio2, &gpio2_value, &gpio2_direction);
		else if (pinnum == 3) delete_object(gpio3, &gpio3_value, &gpio3_direction);
		else if (pinnum == 4) delete_object(gpio4, &gpio4_value, &gpio4_direction);
		else if (pinnum == 5) delete_object(gpio5, &gpio5_value, &gpio5_direction);
		else if (pinnum == 6) delete_object(gpio6, &gpio6_value, &gpio6_direction);
		else if (pinnum == 7) delete_object(gpio7, &gpio7_value, &gpio7_direction);
		else if (pinnum == 8) delete_object(gpio8, &gpio8_value, &gpio8_direction);
		else if (pinnum == 9) delete_object(gpio9, &gpio9_value, &gpio9_direction);
		else if (pinnum == 10) delete_object(gpio10, &gpio10_value, &gpio10_direction);
		else if (pinnum == 11) delete_object(gpio11, &gpio11_value, &gpio11_direction);
		else if (pinnum == 12) delete_object(gpio12, &gpio12_value, &gpio12_direction);
		else if (pinnum == 13) delete_object(gpio13, &gpio13_value, &gpio13_direction);
		else if (pinnum == 14) delete_object(gpio14, &gpio14_value, &gpio14_direction);
		else if (pinnum == 15) delete_object(gpio15, &gpio15_value, &gpio15_direction);
		else if (pinnum == 16) delete_object(gpio16, &gpio16_value, &gpio16_direction);
		else if (pinnum == 17) delete_object(gpio17, &gpio17_value, &gpio17_direction);
		else if (pinnum == 18) delete_object(gpio18, &gpio18_value, &gpio18_direction);
		else if (pinnum == 19) delete_object(gpio19, &gpio19_value, &gpio19_direction);
		else if (pinnum == 20) delete_object(gpio20, &gpio20_value, &gpio20_direction);
		else if (pinnum == 21) delete_object(gpio21, &gpio21_value, &gpio21_direction);
		else if (pinnum == 22) delete_object(gpio22, &gpio22_value, &gpio22_direction);
		else if (pinnum == 23) delete_object(gpio23, &gpio23_value, &gpio23_direction);
		else if (pinnum == 24) delete_object(gpio24, &gpio24_value, &gpio24_direction);
		else if (pinnum == 25) delete_object(gpio25, &gpio25_value, &gpio25_direction);
		else if (pinnum == 26) delete_object(gpio26, &gpio26_value, &gpio26_direction);
		else if (pinnum == 27) delete_object(gpio27, &gpio27_value, &gpio27_direction);
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
	pr_info("GPIO_EMULATOR: Loading gpio module...\n");

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
		pr_info("GPIO_EMULATOR: Error creating module");
		return -ENOMEM;
	}
	gpio_emul->ktype->get_ownership = sudo_user_ownership;

	// Create files
	if (sysfs_create_file(gpio_emul, &export.attr))
	{
		pr_info("GPIO_EMULATOR: Error creating export file");
		kobject_put(gpio_emul);
		return -ENOMEM;
	}
	if (sysfs_create_file(gpio_emul, &unexport.attr))
	{
		pr_info("GPIO_EMULATOR: Error creating unexport file");
		kobject_put(gpio_emul);
		return -ENOMEM;
	}

	pr_info("GPIO_EMULATOR: Module loaded!\n");
	return 0;
}

static void __exit module_end(void)
{
	pr_info("GPIO_EMULATOR: Cleaning up gpio emulator\n");
	sysfs_remove_file(gpio_emul, &export.attr);
	sysfs_remove_file(gpio_emul, &unexport.attr);
	kobject_put(gpio_emul);
}

module_init(module_start);
module_exit(module_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nmello");
MODULE_DESCRIPTION("GPIO Emulator for testing without microcontroller");
