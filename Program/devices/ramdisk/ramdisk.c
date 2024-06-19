//
// Created by Administrator on 2024/6/16.
//

#include "ramdisk.h"
#include "../../kernel/kernel_device/kernel_device.h"
#include "../console/console.h"
#include "../../kernel/kernel_task/kernel_task.h"

// 注册驱动结构体
REGISTER_DRIVER(ramdisk_driver) {
        .driver_name = "ramdisk",
        .init = NULL,
        .exit = NULL,
        .read = ramdisk_read,
        .write = ramdisk_write,
        .irq = -1, // 没有中断处理
        .irq_interrupt_handler = NULL,
};

// 仅限此处使用，所以要用static，限制作用域在此文件中
static uint8_t *ramdisk = (uint8_t *)0xA0000000; // 定义RAM Disk的存储空间

struct ramdisk_io_request {
    uint32_t address; // 以字节为单位的地址（nor闪存没有扇区的概念，直接以线性地址读写）
    uint32_t size;
    char *buffer;
};

// 擦除块，这是nor闪存特有的操作，nor闪存写之前，必须要擦除该块，然后才能写
int32_t erase_block(uint32_t block_number) {
    if (block_number * BLOCK_SIZE >= RAMDISK_SIZE) {
        return -1; // 超出范围
    }
    memset(ramdisk + block_number * BLOCK_SIZE, 0xFF, BLOCK_SIZE); // 模拟NOR闪存的擦除操作（一次性擦除一个块，就是每一位都用1填充）
    return 0;
}

// 文件系统的擦除要求是4KB，适配
int32_t erase_block_4K(uint32_t addr) {
    if(addr > RAMDISK_SIZE - 0x1000) {
        return -1;
    }
    memset((char *)addr, 0xff, 0x1000);
    return 0;
}

int32_t ramdisk_read(char *args, uint32_t args_size) {
    if(args_size != sizeof(struct ramdisk_io_request)) {
        return -1;
    }
    struct ramdisk_io_request *request = (struct ramdisk_io_request *)args;

    if (request->address + request->size > RAMDISK_SIZE) {
        return -1;
    }
    memcpy(request->buffer, ramdisk + request->address, request->size);
    return request->size;
}

int32_t ramdisk_write(char *args, uint32_t args_size) {
    if(args_size != sizeof(struct ramdisk_io_request)) {
        return -1;
    }
    struct ramdisk_io_request *request = (struct ramdisk_io_request *)args;

    if (request->address + request->size > RAMDISK_SIZE) {
        return -1; // 超出范围
    }

    // 不擦除了，直接写
    memcpy(ramdisk + request->address, request->buffer, request->size);

    return request->size;
}
