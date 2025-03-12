
# 所有设备目录
DEVICE_DIR = .
PIT8253_DIR = pit8253
CONSOLE_DIR = console
KEYBOARD_DIR = keyboard
RAMDISK_DIR = ramdisk
RTC_CMOS_DIR = rtc_cmos

# 标签标记所有的任务（输出什么文件），方便修改
DEVICE_OBJS = pit8253.o console.o keyboard.o ramdisk.o rtc_cmos.o

.PHONY: all

all: $(DEVICE_OBJS)

# 执行各子模块编译
pit8253.o:
	$(MAKE) -C $(PIT8253_DIR) 

console.o:
	$(MAKE) -C $(CONSOLE_DIR) 

keyboard.o:
	$(MAKE) -C $(KEYBOARD_DIR) 

ramdisk.o:
	$(MAKE) -C $(RAMDISK_DIR) 

rtc_cmos.o:
	$(MAKE) -C $(RTC_CMOS_DIR) 

# 清理规则
clean:
	rm $(DEVICE_DIR)/*.o 
	rm $(DEVICE_DIR)/*.bin
