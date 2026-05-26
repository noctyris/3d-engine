BUILDDIR := build
INCDIR := inc

CC = gcc
CFLAGS = `pkg-config --cflags sdl3` -ggdb3 -O0 --std=c99 -Wall -I$(INCDIR)
LIBS = `pkg-config --libs sdl3` -lm

HDRS := $(wildcard inc/*.h)
SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=$(BUILDDIR)/%.o)
EXEC := launch

all: $(EXEC)

$(BUILDDIR):
	mkdir -p $@

$(BUILDDIR)/%.o: %.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

$(EXEC): $(OBJS) | 
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LIBS)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -rf $(BUILDDIR) $(EXEC)

.PHONY: all clean run
