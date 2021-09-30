list: list.c list.h driver.c
	gcc -O0 -w -std=c99 -g -fsanitize=address  -lrt -lm $^ -o driver

clean:
	rm -f driver
