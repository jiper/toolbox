## 工程架构

* app：存放入口函数
* data：存放输入输出数据文件
* obj：存放.o文件
* src：存放源文件，每一个功能模块在此文件夹中建立子文件夹。增加功能模块后，只需要在makefile文件中的INCDIRS和SRCDIRS中增加目录即可，其余保持不变
* 可执行文件放在根目录下

## makefile

```makefile
CC := g++
CFLAGS :=-Wall -std=c++11 -pthread -lpthread -g 
TARGET := ntrip_client

INCDIRS := src/debug \
			src/innerPrecisionCal \
			src/ntripClient \
			src/uart
SRCDIRS := src/debug \
			src/innerPrecisionCal \
			src/ntripClient \
			src/uart \
			app

INCLUDE := $(foreach dir, $(INCDIRS), $(patsubst %, -I %,$(INCDIRS)))
CCFILES := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cc))

CCFILESNDIR := $(notdir $(CCFILES))

OBJSNDIR = $(patsubst %.cc, %.o, $(CCFILESNDIR))
OBJS = $(patsubst %, obj/%, $(OBJSNDIR))

VPATH := $(SRCDIRS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(INCLUDE) $(CFLAGS)

$(OBJS): obj/%.o: %.cc
	$(CC) -c -o $@ $< $(INCLUDE) $(CFLAGS)

.PHONU:clean print
clean:
	rm -rf obj/*.o $(TARGET)
print:
	@echo "include = $(INCLUDE)\n"
	@echo "c file = $(CCFILES)\n"
	@echo  "c file without dir = $(CCFILESNDIR)\n"
	@echo  "obj = $(OBJS)\n"
```

