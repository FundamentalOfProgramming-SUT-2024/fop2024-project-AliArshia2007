#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
typedef struct {
    int x;
    int y;
    int width;
    int height;
	int makhfi;
} Room;

int is_overlap(Room r1, Room r2) {
    return !(r1.x + r1.width < (r2.x) || 
             r2.x + r2.width < (r1.x) || 
             r1.y + r1.height < (r2.y) ||
             r2.y + r2.height < (r1.y));
}

void create_random_rooms(Room rooms[], int num_rooms, int max_x, int max_y) {
    for (int i = 0; i < num_rooms; i++) {
        Room new_room;
        int overlap;
        do {
            new_room.width = rand() % 3 + 6;
            new_room.height = rand() % 3 + 6;
            new_room.x = rand() % (max_x - new_room.width + 1);
            new_room.y = rand() % (max_y - new_room.height + 1);
			
            overlap = 0;
            for (int j = 0; j < i; j++) {
                if (is_overlap(new_room, rooms[j])) {
                    overlap = 1;
                    break;
                }
            }
        } while (overlap);

        rooms[i] = new_room;
    }
}
void dar(Room room){
    int t1 = rand() % 4;
	int t2 = rand() % 4;
	if(t1 ==t2){
		t2 = (t1 +1) %4;
	}
    int pos;
    switch (t1) {
        case 0:
            pos = rand() % room.width;
            mvprintw(room.y, room.x + pos, "+");
            break;
        case 1:
            pos = rand() % room.height;
            mvprintw(room.y + pos, room.x + room.width, "+");
            break;
        case 2:
            pos = rand() % room.width;
            mvprintw(room.y + room.height, room.x + pos, "+");
            break;
        default:
            pos = rand() % room.height;
            mvprintw(room.y + pos, room.x, "+");
            break;
    }
	switch (t2) {
        case 0:
            pos = rand() % room.width;
            mvprintw(room.y, room.x + pos, "+");
            break;
        case 1:
            pos = rand() % room.height;
            mvprintw(room.y + pos, room.x + room.width, "+");
            break;
        case 2:
            pos = rand() % room.width;
            mvprintw(room.y + room.height, room.x + pos, "+");
            break;
        default:
            pos = rand() % room.height;
            mvprintw(room.y + pos, room.x, "+");
            break;
    }
}
void soton(Room room){
	int x ,y;
	x=(rand() % room.width);
	y=(rand() % room.height);
	if(x==0)
		x++;
	if(y==0)
		y++;
	x=room.x+x; y=room.y+y;
	mvprintw(y,x,"O");
}
void draw(Room room){
	attron(COLOR_PAIR(2));
    for(int i = 0; i < room.width; i++){
        mvprintw(room.y, room.x + i, "_");
        mvprintw(room.y + room.height, room.x + i, "_");
    }
    for(int i = 1; i <= room.height; i++){
        mvprintw(room.y + i, room.x, "|");
        mvprintw(room.y + i, room.x + room.width, "|");
    }
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(3));
	for(int i = 1; i < room.width; i++){
		for(int j=1 ; j<room.height ; j++){
			mvprintw(room.y+j,room.x+i,".");
		}
	}
	attroff(COLOR_PAIR(3));
	attron(COLOR_PAIR(4));
	dar(room);
	soton(room);
	attroff(COLOR_PAIR(4));
}

int main() {
    srand(time(NULL));
	initscr();
	start_color();
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    init_pair(2,COLOR_RED,COLOR_BLACK);
    init_pair(3,COLOR_YELLOW,COLOR_BLACK);
    init_pair(4,COLOR_BLUE,COLOR_BLACK);
	int t = rand() % 3;
    int num_rooms = 6 +t ;
    int max_x = 80;
    int max_y = 40;
    Room rooms[num_rooms];
    create_random_rooms(rooms, num_rooms, max_x, max_y);
	for(int i=0 ; i<num_rooms ; i++){
		draw(rooms[i]);
		refresh();
	}
	refresh(); 
	getch();
	endwin();
    return 0;
}
