#test:test.c test1.c test2.c test.h
#	gcc test.c test1.c test2.c test.h -o test
	

#test:test.o test1.o test2.o
#	gcc $^ -o $@

#test.o:test.c
#	gcc -c $^ -o $@
#test1.o:test1.c
#	gcc -c $^ -o $@
#test2.o:test2.c
#	gcc -c $^ -o $@



#src = $(wildcard ./*.c) #获取当前目录下所有以.c结尾文件的文件名称 src:test.c test1.c test2.c
#obj = $(patsubst %.c,%.o,$(src)) #将src变量中的文件名称全部替换为以.o结尾的文件名称，并存放到obj变量中 obj:test.o test1.o test2.o

#test:$(obj)
#	gcc $^ -o $@

test:test.o test1.o test2.o
	gcc $^ -o $@

%.o:%.c
	gcc -c $^ -o $@ 

.PHONY:clean
clean:
	rm -r test $(obj) 
