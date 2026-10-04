#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbd03ed67, "page_offset_base" },
	{ 0xbd03ed67, "vmemmap_base" },
	{ 0xe8213e80, "_printk" },
	{ 0x7fe4a857, "fs_bio_set" },
	{ 0x6afaff0d, "bio_alloc_bioset" },
	{ 0x2ea058af, "bio_add_page" },
	{ 0x9661019d, "submit_bio_wait" },
	{ 0xa7d57700, "bio_put" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xbd03ed67, "phys_base" },
	{ 0x43a349ca, "strlen" },
	{ 0x092a35a2, "_copy_to_user" },
	{ 0xbd03ed67, "random_kmalloc_seed" },
	{ 0x9f568b3d, "kmalloc_caches" },
	{ 0xea8ca849, "__kmalloc_cache_noprof" },
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0xd2554727, "cdev_init" },
	{ 0xdb375fb3, "cdev_add" },
	{ 0x326b4c7f, "class_create" },
	{ 0x160b81b4, "device_create" },
	{ 0x7bfbb55c, "bdev_file_open_by_path" },
	{ 0xef7b3af1, "file_bdev" },
	{ 0x2e921116, "cdev_del" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0x07a5cde6, "class_destroy" },
	{ 0xcb8b6ec6, "kfree" },
	{ 0xd17123e4, "device_destroy" },
	{ 0xd272d446, "__fentry__" },
	{ 0x5cb46e6d, "validate_usercopy_range" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0xd954c786, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xbd03ed67,
	0xbd03ed67,
	0xe8213e80,
	0x7fe4a857,
	0x6afaff0d,
	0x2ea058af,
	0x9661019d,
	0xa7d57700,
	0xd272d446,
	0xbd03ed67,
	0x43a349ca,
	0x092a35a2,
	0xbd03ed67,
	0x9f568b3d,
	0xea8ca849,
	0x9f222e1e,
	0xd2554727,
	0xdb375fb3,
	0x326b4c7f,
	0x160b81b4,
	0x7bfbb55c,
	0xef7b3af1,
	0x2e921116,
	0x0bc5fb0d,
	0x07a5cde6,
	0xcb8b6ec6,
	0xd17123e4,
	0xd272d446,
	0x5cb46e6d,
	0xa61fd7aa,
	0x092a35a2,
	0xd954c786,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"page_offset_base\0"
	"vmemmap_base\0"
	"_printk\0"
	"fs_bio_set\0"
	"bio_alloc_bioset\0"
	"bio_add_page\0"
	"submit_bio_wait\0"
	"bio_put\0"
	"__x86_return_thunk\0"
	"phys_base\0"
	"strlen\0"
	"_copy_to_user\0"
	"random_kmalloc_seed\0"
	"kmalloc_caches\0"
	"__kmalloc_cache_noprof\0"
	"alloc_chrdev_region\0"
	"cdev_init\0"
	"cdev_add\0"
	"class_create\0"
	"device_create\0"
	"bdev_file_open_by_path\0"
	"file_bdev\0"
	"cdev_del\0"
	"unregister_chrdev_region\0"
	"class_destroy\0"
	"kfree\0"
	"device_destroy\0"
	"__fentry__\0"
	"validate_usercopy_range\0"
	"__check_object_size\0"
	"_copy_from_user\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "93CC7DA098337A88A287046");
