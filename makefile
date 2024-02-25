SRC:=main.cpp
CFLAGS:=-Wall -Werror -Wextra -Wuninitialized -pedantic-errors -Wconversion
BIN:=output 
STD:=-std=c++17

default:
	g++ $(STD) $(CFLAGS) -o $(BIN) $(SRC)
	g++ $(STD) $(CFLAGS) -o 00-main 00-main.cpp

clean:
	rm -rf $(BIN) 00-main main output *.dSYM
	
