SRC:=main.cpp
CFLAGS:=-Wall -Werror -Wextra -Wuninitialized -Wconversion -pedantic-errors
BIN:=output 
STD:=-std=c++17

default:
	g++ $(STD) $(CFLAGS) -o $(BIN) $(SRC)
	g++ $(STD) $(CFLAGS) -o 00-main 00-main.cpp
	g++ $(STD) $(CFLAGS) -o 4erros neha3rdFeb_4Error.cpp
	g++ $(STD) $(CFLAGS) -o fix_4erros fix-neha3rdFeb_4Error.cpp
	clang++ $(STD) $(CFLAGS) -o fix_smart smartptr_fix-neha3rdFeb_4Err.cpp

clean:
	rm -rf $(BIN) 00-main main output *.dSYM
	
