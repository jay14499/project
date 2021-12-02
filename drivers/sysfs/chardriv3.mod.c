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
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x7240ad89, "proc_remove" },
	{ 0xb356c301, "class_destroy" },
	{ 0xbabacef1, "device_destroy" },
	{ 0x78f44845, "cdev_del" },
	{ 0x3aef9ae9, "sysfs_remove_file_ns" },
	{ 0xedf41f4c, "kobject_put" },
	{ 0x648c5b86, "sysfs_create_file_ns" },
	{ 0x26d6900d, "kobject_create_and_add" },
	{ 0x5dc2a243, "kernel_kobj" },
	{ 0xdb59a12d, "proc_create" },
	{ 0x3c9db9ca, "proc_mkdir" },
	{ 0xff9c16ee, "device_create" },
	{ 0x8d62ea07, "__class_create" },
	{ 0x7afe113a, "cdev_add" },
	{ 0xa3036ef8, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x56470118, "__warn_printk" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0x1937241e, "try_module_get" },
	{ 0x3ba859c1, "module_put" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C971CEF35D1826813E4A9F2");
