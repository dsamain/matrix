SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

FLAGS = -D DEBUG -std=c++11

all: 
	g++ $(FLAGS) $(SRC) 

run: all
	./a.out

re: fclean all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f a.out