SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=client
CC:=gcc
CFLAGS:=-g
$(ELF):$(OBJS)
	gcc $^ -o $@ -lpthread
.PHONY:clean
clean:
	rm -rf $(ELF) $(OBJS)
