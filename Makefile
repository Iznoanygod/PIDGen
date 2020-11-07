all:
	gcc -mavx -mavx2 PIDGen_Util.c -c -o PIDGen_Util.o
	gcc -mavx -mavx2 PIDGen.c -c -o PIDGen.o
	gcc -mavx -mavx2 PIDGen_pthread.c -c -o PIDGen_pthread.o
	gcc -o PIDGen PIDGen.o PIDGen_Util.o PIDGen_pthread.o -lpthread
clean:
	rm PIDGen_pthread.o PIDGen PIDGen.o PIDGen_Util.o
