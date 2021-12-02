#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xb3753869, "module_layout" },
	{ 0xbabacef1, "device_destroy" },
	{ 0x8c03d20c, "destroy_workqueue" },
	{ 0x78f44845, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xb356c301, "class_destroy" },
	{ 0x3aef9ae9, "sysfs_remove_file_ns" },
	{ 0xedf41f4c, "kobject_put" },
	{ 0xdf9208c0, "alloc_workqueue" },
	{ 0xc1514a3b, "free_irq" },
	{ 0x2072ee9b, "request_threaded_irq" },
	{ 0x648c5b86, "sysfs_create_file_ns" },
	{ 0x26d6900d, "kobject_create_and_add" },
	{ 0x5dc2a243, "kernel_kobj" },
	{ 0xff9c16ee, "device_create" },
	{ 0x8d62ea07, "__class_create" },
	{ 0x7afe113a, "cdev_add" },
	{ 0xa3036ef8, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xc5b6f236, "queue_work_on" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C2CB1DD86C9AF6C2B9EC1DD");
