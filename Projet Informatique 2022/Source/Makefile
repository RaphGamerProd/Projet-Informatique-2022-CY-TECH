all: exec

# First we compile all of our C-files
main.o: main.c masterlib.h
	gcc -c main.c -o main.o

misc.o: misc.c masterlib.h
	gcc -c misc.c -o misc.o

grid_generator.o: grid_generator.c masterlib.h
	gcc -c grid_generator.c -o grid_generator.o

pieces_creator.o: pieces_creator.c masterlib.h
	gcc -c pieces_creator.c -o pieces_creator.o


# Create the exec file
exec: main.o misc.o grid_generator.o pieces_creator.o
	gcc main.o misc.o grid_generator.o pieces_creator.o -o exec

# And finally we delete the object files
clean:
	del -f *.o
	rm exec


