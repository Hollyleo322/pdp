F_FIl=../data_libs/data_io.c 
S_FIL=../data_module/data_process.c 
T_FIL=../yet_another_decision_module/decision.c 
E_FIL=../data_libs/data_stat.c 
MAIN_FIL=main_executable_module.c 
CFLAGS=-Wall -Wextra -Werror
PATH_STATIC=../data_libs/
STATIC_LIB=data_stat
PATH_DYNAMIC=../data_module/
DYNAMIC_LIB=data_process

all: rebuild clean

rebuild: 
	gcc $(CFLAGS) -o Quest_3 $(F_FIl) $(S_FIL) $(T_FIL) $(E_FIL) $(U_FIL) $(MAIN_FIL) -lm
	mv Quest_3 ../../build 
clean: 
	rm -rf *.o
$(STATIC_LIB): 
	gcc -c $(E_FIL) -o $(PATH_STATIC)data_stat.o
	ar q $(PATH_STATIC)lib$(STATIC_LIB).a $(PATH_STATIC)data_stat.o
	rm -rf $(PATH_STATIC)*.o
build_with_static:
	gcc $(CFLAGS) -o Quest_5 $(F_FIl) $(S_FIL) $(T_FIL) $(U_FIL) $(MAIN_FIL) -L$(PATH_STATIC) -l$(STATIC_LIB) -lm 
	mv Quest_5 ../../build
 data_process.so:
	gcc -fPIC -c $(S_FIL)
	gcc -shared -o libdata_process.so data_process.o
	mv libdata_process.so ../data_module
	rm -rf *.o
build_with_dynamic:
	gcc $(CFLAGS) -o Quest_6 $(F_FIl) $(T_FIL) $(E_FIL) $(U_FIL) $(MAIN_FIL) -L$(PATH_DYNAMIC) -l$(DYNAMIC_LIB) -lm
	mv Quest_6 ../../build



	



