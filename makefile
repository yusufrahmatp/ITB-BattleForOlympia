main: main.c mechanics.c player.c unit.c turn_queue.c move_stack.c point.c pcolor.c print_format.c map.c point_queue.c save.c mesinkar.c mesinkata.c
	gcc -o main -Wall -std=c99 main.c mechanics.c player.c unit.c turn_queue.c move_stack.c point.c pcolor.c print_format.c map.c point_queue.c save.c mesinkar.c mesinkata.c -lm

dbase: dbase.c player.c unit.c castle.c tower.c
	gcc -o dbase dbase.c player.c unit.c castle.c tower.c -lm
