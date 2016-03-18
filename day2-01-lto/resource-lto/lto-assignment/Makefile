CC=g++-4.7.2-lto

FLAGS= -fPIC -O2
FLAGS1= -fdump-ipa-all -O3

GCCPLUGINS_DIR:= $(shell $(CC) -print-file-name=plugin)
INCLUDE= -I$(GCCPLUGINS_DIR)/include

plugin.so: plugin.c
	$(CC) $(INCLUDE) $(FLAGS) -shared $^ -o $@

test: plugin.so test1.c test2.c
	$(CC) -fplugin=./plugin.so -c test1.c $(FLAGS1)
	$(CC) -fplugin=./plugin.so -c test2.c $(FLAGS1)
	$(CC) -fplugin=./plugin.so -o merged test1.o test2.o $(FLAGS1)

test-default: plugin.so test1.c test2.c
	$(CC) -fplugin=./plugin.so -c test1.c -flto $(FLAGS1)
	$(CC) -fplugin=./plugin.so -c test2.c -flto $(FLAGS1)
	$(CC) -fplugin=./plugin.so -o merged test1.o test2.o -flto $(FLAGS1)

test-none: plugin.so test1.c test2.c
	$(CC) -fplugin=./plugin.so -c test1.c -flto $(FLAGS1)
	$(CC) -fplugin=./plugin.so -c test2.c -flto $(FLAGS1)
	$(CC) -fplugin=./plugin.so -o merged test1.o test2.o -flto -flto-partition=none $(FLAGS1)

test-1to1: plugin.so test1.c test2.c
	$(CC) -fplugin=./plugin.so -c test1.c -flto $(FLAGS1)
	$(CC) -fplugin=./plugin.so -c test2.c -flto $(FLAGS1)
	$(CC) -fplugin=./plugin.so -o merged test1.o test2.o -flto -flto-partition=1to1 $(FLAGS1)

test-balanced: plugin.so test1.c test2.c
	$(CC) -fplugin=./plugin.so -c test1.c -flto $(FLAGS1) 
	$(CC) -fplugin=./plugin.so -c test2.c -flto $(FLAGS1) 
	$(CC) -fplugin=./plugin.so -o merged test1.o test2.o -flto -flto-partition=balanced $(FLAGS1)

test-balanced1: plugin.so test1.c test2.c
	$(CC) -fplugin=./plugin.so -c test1.c -flto $(FLAGS1) 
	$(CC) -fplugin=./plugin.so -c test2.c -flto $(FLAGS1) 
	$(CC) -fplugin=./plugin.so -o merged test1.o test2.o -flto -flto-partition=balanced $(FLAGS1) --param lto-partitions=3 --param lto-min-partition=5

test-balanced2: plugin.so test1.c test2.c
	$(CC) -fplugin=./plugin.so -c -flto test1.c $(FLAGS1) 
	$(CC) -fplugin=./plugin.so -c -flto test2.c $(FLAGS1) 
	$(CC) -fplugin=./plugin.so -o merged test1.o test2.o -flto -flto-partition=balanced $(FLAGS1) --param lto-partitions=3 --param lto-min-partition=300

clean:
	\rm -f *.so test *.c.* *~ *.o a.out test1.c.* test2.c.* merged* 

