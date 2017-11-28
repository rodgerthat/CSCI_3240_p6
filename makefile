#p6:p6.c ~rbutler/public/courses/cs/p6test.o
p6:p6.c p6test.o 
	#cc -o p6 p6.c ~rbutler/public/courses/cs/p6test.o -lpthread
	cc -o p6 p6.c p6test.o -lpthread -ldl
	#cc -static -o p6 p6.c p6test.o -lpthread -ldl
