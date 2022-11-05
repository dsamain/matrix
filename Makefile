SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

FLAGS = -D DEBUG

all: $(OBJ)
	g++ $(FLAGS) $^

run: all
	./a.out

re: fclean all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f a.out