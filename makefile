stat: stat.c
	gcc -o stat stat.c

run: stat
	./stat
