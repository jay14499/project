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
	{ 0x46a6fb9b, "module_layout" },
	{ 0x4b10fcd5, "device_destroy" },
	{ 0x856722bb, "kthread_stop" },
	{ 0xa970bd05, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x349fd30a, "class_destroy" },
	{ 0x977f511b, "__mutex_init" },
	{ 0xe9ce382, "wake_up_process" },
	{ 0x29b520eb, "kthread_create_on_node" },
	{ 0xca2826eb, "device_create" },
	{ 0x6c13ee30, "__class_create" },
	{ 0x476d1764, "cdev_add" },
	{ 0x12865478, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x409bcb62, "mutex_unlock" },
	{ 0xf9a482f9, "msleep" },
	{ 0x2ab7989d, "mutex_lock" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "2F83E6B7549E4394C514B4C");
