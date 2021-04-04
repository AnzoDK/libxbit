CXX:= g++
DEBUG:= -g3
LIB_FILES:= xbitLibMain.cpp
LIB_OUT = libxbit.so
LIB_CXX_FLAGS := -Wall -shared -fPIC -std=c++17
TEST_FILES:= testProgram.cpp
TEST_CXX_FLAGS:= -Wall -std=c++17
TEST_OUT:= xbitlibTest.out
TEST_LINK:= -Wl,-rpath=./ -L./ -lxbit
OPT_FLAGS:= 
release:
	make clean
	make buildLib
	make buildTest
win:
	make clean
	i686-w64-mingw32-g++ -c -g3 -m32 -Wall -DWIN32 -std=c++17 xbitLibMain.cpp -o ./xbit.o
	i686-w64-mingw32-g++ -c -g3 -m32 -Wall -DWIN32 -std=c++17 testProgram.cpp -o ./test.o
	i686-w64-mingw32-g++ -g3 -m32 -Wall -DWIN32 -std=c++17 test.o xbit.o -static-libstdc++ -static-libgcc -o ./test.exe -static -lpthread
	make clean

clean:
	-rm -rf ${LIB_OUT} ${TEST_OUT};
	-rm -rf *.o
buildLib:
	${CXX} ${LIB_FILES} ${DEBUG} ${OPT_FLAGS} ${LIB_CXX_FLAGS} -o ${LIB_OUT}
buildTest:
	${CXX} ${TEST_FILES} ${DEBUG} ${OPT_FLAGS} ${TEST_CXX_FLAGS} -o ${TEST_OUT} ${TEST_LINK}