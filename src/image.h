

#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <sys/types.h>

#include "device.h"

enum image_type {
	IMAGE_UNKNOWN = 0,
	IMAGE_XLOADER,
	IMAGE_2ND,
	IMAGE_SECONDARY,
	IMAGE_KERNEL,
	IMAGE_INITFS,
	IMAGE_ROOTFS,
	IMAGE_OMAP_NAND,
	IMAGE_MMC,
	IMAGE_CMT_2ND,
	IMAGE_CMT_ALGO,
	IMAGE_CMT_MCUSW,
};

struct image {
	enum image_type type;
	enum device device;
	char * hwrevs;
	char * version;
	char * layout;
	uint16_t hash;
	uint32_t size;

	int fd;
	int is_shared_fd;
	uint32_t align;
	off_t offset;
	off_t cur;
	off_t acur;
};

struct image_list {
	struct image * image;
	struct image_list * prev;
	struct image_list * next;
};

struct image * image_alloc_from_file(const char * file, const char * type, const char * device, const char * hwrevs, const char * version, const char * layout);
struct image * image_alloc_from_shared_fd(int fd, size_t size, size_t offset, uint16_t hash, const char * type, const char * device, const char * hwrevs, const char * version, const char * layout);
void image_free(struct image * image);
void image_seek(struct image * image, off_t whence);
size_t image_read(struct image * image, void * buf, size_t count);
void image_list_add(struct image_list ** list, struct image * image);
void image_list_del(struct image_list * list);

uint16_t image_hash_from_data(struct image * image);
enum image_type image_type_from_data(struct image * image);
char * image_name_alloc_from_values(struct image * image);
enum image_type image_type_from_string(const char * type);
const char * image_type_to_string(enum image_type type);

#endif