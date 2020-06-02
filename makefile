matrix: main.c board.c utils.c ship.c shots.c
	gcc -std=c99 -D_POSIX_C_SOURCE=199309L -DMATRIX -o battleShip main.c board.c utils.c ship.c shots.c

qt: main.c utils.c quadtree.c ship.c shots.c
	gcc -std=c99 -D_POSIX_C_SOURCE=199309L -DQT -o battleShip main.c quadtree.c utils.c ship.c shots.c

clean: 
	rm -f battleShip