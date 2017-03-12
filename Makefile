all:
	g++ main.cpp structs.cpp functions.cpp smoothMethod.cpp smoothMethod2.cpp -o test 
clean:
	rm test