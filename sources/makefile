#后缀为.h的文件都在 ../headers文件夹下寻找
vpath %.h ../headers
#a.out的依赖文件
OBJECTS1 = main.o set_parms.o list.o cal_rho_abscissa_value1.o cal_rho_abscissa_value2.o cal_rho_abscissa_value3.o file.o free_space.o network.o property.o rand.o spread.o
#*.o的依赖文件
OBJECTS2 = config.h 
#cal_rho_abscissa_value.h file.h free_space.h network.h property.h rand.h spread.h
#编译器
CC = g++
#编译器参数
CFLAGs = -O2 -c -Wall -std=c++11

#config.h cal_rho_abscissa_value.h file.h/
#free_space.h network.h property.h rand.h spread.h

a.out : $(OBJECTS1)
		$(CC) -O2 -o a.out $(OBJECTS1)
#-fexceptions -g

main.o : main.cpp $(OBJECTS2)
		$(CC) $(CFLAGs) main.cpp
		
list.o : list.cpp $(OBJECTS2)
		$(CC) $(CFLAGs) list.cpp 

cal_rho_abscissa_value1.o : cal_rho_abscissa_value1.cpp $(OBJECTS2)
		$(CC) $(CFLAGs) cal_rho_abscissa_value1.cpp
		
cal_rho_abscissa_value2.o : cal_rho_abscissa_value2.cpp $(OBJECTS2)
		$(CC) $(CFLAGs) cal_rho_abscissa_value2.cpp

cal_rho_abscissa_value3.o : cal_rho_abscissa_value3.cpp $(OBJECTS2)
		$(CC) $(CFLAGs) cal_rho_abscissa_value3.cpp

file.o : file.cpp $(OBJECTS2)
		$(CC) $(CFLAGs) file.cpp

free_space.o : free_space.cpp $(OBJECTS2)
		$(CC) $(CFLAGs) free_space.cpp

network.o : network.cpp $(OBJECTS2)
		$(CC) $(CFLAGs) network.cpp

property.o : property.cpp $(OBJECTS2)
		$(CC) $(CFLAGs) property.cpp

rand.o : rand.cpp $(OBJECTS2)
		$(CC) $(CFLAGs) rand.cpp

set_parms.o	: set_parms.cpp $(OBJECTS2)
		$(CC) $(CFLAGs) set_parms.cpp

spread.o : spread.cpp $(OBJECTS2)
		$(CC) $(CFLAGs) spread.cpp

.PHONY : clean
clean :
	-rm *.out $(OBJECTS1)