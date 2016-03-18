
CC = g++-4.7.2
NEW_PATH = gcc-4.7.2

OBJS = plugin.o

GCCPLUGINS_DIR:= $(shell $(CC) -print-file-name=plugin)
INCLUDE= -I$(GCCPLUGINS_DIR)/include -I$(NEW_PATH)

FLAGS= -fPIC -O2

plugin.so: plugin.c
	$(CC) $(INCLUDE) $(FLAGS) -shared $^ -o $@

test: plugin.so
	$(CC) -fplugin=./plugin.so test.c -fdump-tree-all

clean:
	\rm -f plugin.so test *.c.* *~ *.o a.out


