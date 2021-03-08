CXX:= g++
DEBUG:= -g3
LIB_FILES:= xbitLibMain.cpp
LIB_OUT = libxbit.so
LIB_CXX_FLAGS := -Wall -shared -fPIC -std=c++17
TEST_FILES:= testProgram.cpp
TEST_CXX_FLAGS:= -Wall -std=c++17
TEST_OUT:= xbitlibTest.out
TEST_LINK:= -Wl,-rpath=./ -L./ -lxbit

release:
	make clean
	make buildLib
	make buildTest

clean:
	-rm -rf ${LIB_OUT} ${TEST_OUT};
buildLib:
	${CXX} ${LIB_FILES} ${DEBUG} ${LIB_CXX_FLAGS} -o ${LIB_OUT}
buildTest:
	${CXX} ${TEST_FILES} ${DEBUG} ${TEST_CXX_FLAGS} -o ${TEST_OUT} ${TEST_LINK}