# Object files
OBJ = main.o event.o manager.o resource.o system.o

# Target to build the executable
all: main event manager resource system
	gcc -o Project2 $(OBJ) -pthread

# Separate targets
main: main.c defs.h
	gcc -g -Wall -Wextra -Werror -pthread -c main.c 

event: event.c defs.h
	gcc -g -Wall -Wextra -Werror -pthread -c event.c 

manager: manager.c defs.h
	gcc -g -Wall -Wextra -Werror -pthread -c manager.c 

resource: resource.c defs.h
	gcc -g -Wall -Wextra -Werror -pthread -c resource.c 

system: system.c defs.h
	gcc -g -Wall -Wextra -Werror -pthread -c system.c 


# Clean target
clean:
	rm -f $(OBJ) Project2
