SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

FLAGS = -D DEBUG -std=c++11

%.o: %.cpp
	g++ -c -o $@ $< $(FLAGS)

all: $(OBJ)
	g++ $(FLAGS) $(OBJ) -o test

run: all
	./a.out

re: fclean all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f test