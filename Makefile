all:
	g++ main.cpp structs.cpp functions.cpp smoothMethod.cpp -o test 
clean:
	rm test