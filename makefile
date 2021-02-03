#test:test.c test1.c test2.c
		#gcc test.c test1.c test2.c -o test

#test:test.c test1.c test2.c
#		gcc $^ -o $@


#src = $(wildcard ./*.c)   #获取当前目录下所有以.c结尾的文件的文件名称
#test:$(src)
#		gcc $^ -o $@



#make只会执行makefile中的第一个目标文件，然后就会退出
#所以下面代码只会执行test.o
#test.o:test.c
#		gcc -c $^ -o $@
#test1.o:test1.c
#		gcc -c $^ -o $@
#test2.o:test2.c
#		gcc -c $^ -o $@
		
#src = $(wildcard ./*.o)
#test:$src
#		gcc $^ -o $@



#先找对应的依赖文件，在生成目标文件
#test:test.o test1.o test2.o
#		gcc $^ -o $@

#test.o:test.c
#		gcc -c $^ -o $@
#test1.o:test1.c
#		gcc -c $^ -o $@
#test2.o:test2.c
#		gcc -c $^ -o $@



#src = $(wildcard ./*.c)
#obj = $(patsubst %.c,%.o,$(src))   #将src变量的内容中的.c替换为.o,然后存放到obj变量中  obj中：test.o   test1.o    test2.o
#test:$(obj)
#test:test.o test1.o test2.o
#		gcc $^ -o $@

#%是通配符,相当于匹配   
#test.o:test.c
#test1.o:test1.c
#test2.o:test2.c
#%.o:%.c
#		gcc -c $< -o $@



src = $(wildcard ./*.c)
obj = $(patsubst %.c,%.o,$(src))
test:$(obj)
#test:test.o test1.o test2.o
		gcc $^ -o $@

%.o:%.c
		gcc -c $< -o $@


#伪对象：声明一个对象与外部文件无关，每次都要重新生成（不会因为当前文件是最新的而导致不需要重新生成）
.PHONY:clean
clean:
		rm -r test $(obj)
