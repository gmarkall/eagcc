
CC = g++
NEW_PATH = gcc

OBJS = plugin.o

GCCPLUGINS_DIR:= $(shell $(CC) -print-file-name=plugin)
INCLUDE= -I$(GCCPLUGINS_DIR)/include -I$(NEW_PATH)

FLAGS= -fPIC -g

plugin.so: plugin.c 
	$(CC) $(INCLUDE) $(FLAGS) -shared $^ -o $@

test: plugin.so
	$(CC) -fplugin=./plugin.so test.c -fdump-ipa-all -fdump-tree-all

debug: plugin.so
	$(CC) -fplugin=./plugin.so test.c -fdump-ipa-all -fdump-tree-all -wrapper gdb,--args
clean:
	\rm -f plugin.so test *.c.* *~ *.o a.out


