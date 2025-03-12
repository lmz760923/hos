# 目录
LIB_DIR = .
LIB_KERNEL = lib_kernel
LIB_USER = lib_user

OBJS = $(LIB_DIR)/kernel.o $(LIB_DIR)/user.o

# 默认目标
all: $(OBJS)

# 目标文件生成规则
$(LIB_DIR)/kernel.o:
	$(MAKE) -C $(LIB_KERNEL) 

$(LIB_DIR)/user.o:
	$(MAKE) -C $(LIB_USER) 

# 清理目标，删除所有 .o 文件
clean:
	rm $(LIB_DIR)/*.o
