#!Makefile

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))


SERVER_SOURCES = $(shell find ./server -name "*.c")
SERVER_OBJECTS = $(patsubst %.c, %.o, $(SERVER_SOURCES))

CLIENT_SOURCES = $(shell find ./client -name "*.c")
CLIENT_OBJECTS = $(patsubst %.c, %.o, $(CLIENT_SOURCES))

COMMON_SOURCES = utils.c sockets.c
COMMON_OBJECTS = $(patsubst %.c, %.o, $(COMMON_SOURCES))


CC = gcc 
LD = ld

C_FLAGS = -c -std=gnu99 -Wall -O3 -g -DNDEBUG -pthread

LD_FLAGS = -lpthread -pthread


EXECUTABLES = \
		ser \
		cli \


all: $(EXECUTABLES)

#@表示不显示命令本身，只显示它的结果
# $<: 规则中第一个依赖
# $@: 规则中的目标
# $^: 规则中所有的依赖

.c.o:
	@echo 编译C代码文件 $< ...
	$(CC) $(C_FLAGS) $< -o $@


ser:$(COMMON_OBJECTS) $(SERVER_OBJECTS)
	$(CC) $^ -o $@ $(LD_FLAGS)

cli:$(COMMON_OBJECTS) $(CLIENT_OBJECTS)
	$(CC) $^ -o $@ $(LD_FLAGS)

#ser: $(COMMON_SOURCES) $(SERVER_SOURCES)
#	@echo 链接服务器
#	$(CC) $(C_FLAGS) $^ -o $@ $(LD_FLAGS)

#cli: $(COMMON_SOURCES) $(CLIENT_SOURCES)
#	@echo 链接KEHU
#	$(CC) $(C_FLAGS) $^ -o $@ $(LD_FLAGS)


.PHONY:clean
clean:
	rm -f $(EXECUTABLES) $(C_OBJECTS)
.PHONY:hello
hello:
	@echo 'Hello world!'