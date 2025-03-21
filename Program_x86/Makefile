# 主Makefile，用于整合各模块操作

# 汇编器和编译器、链接器等各种工具
# 编译工具链更换
GCC=gcc -m32
AS=as --32
LD = ld
MAKE = make

# 因为这个操作系统本质上是个宏内核，所有的组件都要打包在一个kernel.bin里面
# 这样烧写起来也方便，所以要在主Makefile这里统一链接

# 所有组件目录
BOOT_DIR = boot
KERNEL_DIR = kernel
LIB_DIR = lib
DEVICE_DIR = devices
USER_DIR = user
FS_DIR = fs

# 输出文件
KERNEL_BIN = $(KERNEL_DIR)/kernel.bin

# 链接脚本位置
KERNEL_LINKER_SCRIPT = $(KERNEL_DIR)/kernel_linker.ld

# 链接标志
LDFLAGS = -T $(KERNEL_LINKER_SCRIPT) -m elf_i386 --oformat binary

.PHONY: all

# 编译各组件，要把工具参数传输过去，然后主Makefile汇总链接生成 kernel.bin
all: compile link

# 编译各组件
compile:
	$(MAKE) -C $(BOOT_DIR) 
	$(MAKE) -C $(LIB_DIR) 
	$(MAKE) -C $(KERNEL_DIR) 
	$(MAKE) -C $(DEVICE_DIR) 
	$(MAKE) -C $(USER_DIR) 
	$(MAKE) -C $(FS_DIR) 

# 链接生成 kernel.bin
link:
	$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(wildcard $(KERNEL_DIR)/*.o) \
										$(wildcard $(LIB_DIR)/*.o) \
										$(wildcard $(DEVICE_DIR)/*.o) \
										$(wildcard $(USER_DIR)/*.o) \
										$(wildcard $(FS_DIR)/*.o)


clean:
	$(MAKE) -C $(BOOT_DIR) clean
	$(MAKE) -C $(KERNEL_DIR) clean
	$(MAKE) -C $(LIB_DIR) clean
	$(MAKE) -C $(DEVICE_DIR) clean
	$(MAKE) -C $(USER_DIR) clean
	$(MAKE) -C $(FS_DIR) clean
