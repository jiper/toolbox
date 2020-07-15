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