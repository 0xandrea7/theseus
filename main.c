#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WALL '#'

struct Game{
	char table[25][25];
	int Sx;
	int Sy;
};

typedef struct{
	int x;
	int y;
} Point;

struct Stack{
	Point path[1000];
	int top;
};

void print_table(struct Game *g){
	printf("\n");
	for (int y = 0; y < 25; y++){
		for (int x = 0; x < 25; x++){
			printf("%c",g->table[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}

void init_table(struct Game *g, char *filename){
	FILE *fpnt = fopen(filename, "r");
	if (fpnt == NULL){
		printf("Could not find or open file %s\n", filename);
		return ;
	}
	char buff[50];
	int y = 0;
	while (fgets(buff, sizeof(buff), fpnt) != NULL && 
			y < 25){
		for (int i = 0; i < 25; i++){
			if (buff[i] == 'S') {
				g->Sx = i;
				g->Sy = y;
			}
			g->table[y][i] = buff[i];
		}
		y++;
	}
	fclose(fpnt);
}

int is_empty(struct Stack *s){
	if (s->top == 999) return 1;
	if (s->top == -1) return -1;
	return 0;
}

int push(struct Stack *s, int x, int y){
	if (is_empty(s) != 1){
		s->top++;
		s->path[s->top].x = x;
		s->path[s->top].y = y;
		return 0;
	}
	return -1;
}

int pop(struct Stack *s){
	if (is_empty(s) != -1){
		s->top--;
		return 0;
	}
	return -1;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		printf("Usage: %s <file>\n", argv[0]);
		return -1;
	}

	struct Game g;
	struct Stack s;
	s.top = -1;

	init_table(&g, argv[1]);
	print_table(&g);

	int x = g.Sx;
	int y = g.Sy;

	push(&s, x, y);

	while (s.top != -1){
		x = s.path[s.top].x;
		y = s.path[s.top].y;

		if (g.table[y][x] == 'E') break;
		if ((x+1 <= 24) && 
				(g.table[y][x+1] == ' ' || 
				 g.table[y][x+1] == 'E')){
			if (push(&s, x+1, y) == 0){
				if (g.table[y][x+1] != 'E') g.table[y][x+1] = '.';
			}
		}
		else if ((y+1 <= 24) && 
				(g.table[y+1][x] == ' ' || 
				 g.table[y+1][x] == 'E')){
			if (push(&s, x, y+1) == 0){
				if (g.table[y+1][x] != 'E') g.table[y+1][x] = '.';
			}
		}
		else if ((y-1 >= 0) && 
				(g.table[y-1][x] == ' ' || 
				 g.table[y-1][x] == 'E')){
			if (push(&s, x, y-1) == 0){
				if (g.table[y-1][x] != 'E') g.table[y-1][x] = '.';
			}
		}
		else if ((x-1 >= 0) && 
				(g.table[y][x-1] == ' ' || 
				 g.table[y][x-1] == 'E')){
			if (push(&s, x-1, y) == 0){
				if (g.table[y][x-1] != 'E') g.table[y][x-1] = '.';
			}
		}
		else { 
			pop(&s);
			if (g.table[y][x] != 'S') {
				g.table[y][x] = 'x';
			}
		}
		printf("\e[1;1H\e[2J");
		usleep(50000);
		print_table(&g);
	}

	return 0;
}
