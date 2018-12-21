power: power.o test-power.o
	gcc -ggdb3 -o power power.o test-power.o

power.o:power.c
	gcc -ggdb3 -c -Wall -Werror -pedantic -std=gnu99 power.c
test-power.o: test-power.c
	gcc -ggdb3 -c -Wall -Werror -pedantic -std=gnu99 test-power.c
