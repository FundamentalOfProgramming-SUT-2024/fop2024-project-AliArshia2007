
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

typedef struct {
    int x;
    int y;
    int width;
    int height;
} Room;
void create_random_rooms(Room rooms[],int num , int y, int x) {
    Room new_room;
    new_room.width = rand() % 6 + 6;
    new_room.height = rand() % 5 + 6;
    new_room.x = x;
    new_room.y = y;
    rooms[num] = new_room;
}

void dar(Room room, int dar[][2], int index , int t1) {
    int pos;
    switch (t1) {
        case 0:
            pos = rand() % room.width+1;
            mvprintw(room.y, room.x + pos, "+");
            dar[index][0] = room.x + pos;
            dar[index][1] = room.y;
            break;
        case 1:
            pos = rand() % room.height+1;
            mvprintw(room.y + pos, room.x + room.width, "+");
            dar[index][0] = room.x + room.width;
            dar[index][1] = room.y + pos;
            break;
        case 2:
            pos = rand() % room.width+1;
            mvprintw(room.y + room.height, room.x + pos, "+");
            dar[index][0] = room.x + pos;
            dar[index][1] = room.y + room.height;
            break;
        default:
            pos = rand() % room.height+1;
            mvprintw(room.y + pos, room.x, "+");
            dar[index][0] = room.x;
            dar[index][1] = room.y + pos;
            break;
    }
}

void soton(Room room, int soton[][2], int index) {
    int x, y;
    x = (rand() % room.width)-1;
    y = (rand() % room.height)-1;
    if (x <= 0)
        x=1;
    if (y <= 0)
        y=1;
    x = room.x + x; 
    y = room.y + y;
    mvprintw(y, x, "O");
    soton[index][0] = x;
    soton[index][1] = y;
}

void draw(Room room, int soton_positions[][2], int *soton_index, int dar_positions[][2], int *dar_index , int num) {
    attron(COLOR_PAIR(2));
    for (int i = 0; i < room.width; i++) {
        mvprintw(room.y, room.x + i, "_");
        mvprintw(room.y + room.height, room.x + i, "_");
    }
    for (int i = 1; i <= room.height; i++) {
        mvprintw(room.y + i, room.x, "|");
        mvprintw(room.y + i, room.x + room.width, "|");
    }
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
    for (int i = 1; i < room.width; i++) {
        for (int j = 1; j < room.height; j++) {
            mvprintw(room.y + j, room.x + i, ".");
        }
    }
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(4));
    switch(num){
        case 0:
            dar(room, dar_positions, *dar_index,1);
            (*dar_index)++;
            break;
        case 1:
            dar(room, dar_positions, *dar_index,3);
            (*dar_index)++;
            dar(room, dar_positions, *dar_index,1);
            (*dar_index)++;
            break;
        case 2:
            dar(room, dar_positions, *dar_index,3);
            (*dar_index)++;
            dar(room, dar_positions, *dar_index,2);
            (*dar_index)++;
            break;
        case 3:
            dar(room, dar_positions, *dar_index,0);
            (*dar_index)++;
            dar(room, dar_positions, *dar_index,3);
            (*dar_index)++;
            break;
        case 4:
            dar(room, dar_positions, *dar_index,1);
            (*dar_index)++;
            dar(room, dar_positions, *dar_index,3);
            (*dar_index)++;
            break;
        case 5:
            dar(room, dar_positions, *dar_index,1);
            (*dar_index)++;
            dar(room, dar_positions, *dar_index,3);
            (*dar_index)++;
            break;
    }
    soton(room, soton_positions, *soton_index);
    (*soton_index)++;
    mvprintw(dar_positions[10][1],dar_positions[10][0],">");
    attroff(COLOR_PAIR(4));
}
int path_position[3000][3];
int num_path = 0;
void path(Room room[6], int dar_positions[][2]) {
    for (int i = 0; i < 5; i++) {
        int x = dar_positions[2*i][0];
        int y = dar_positions[2*i][1];
        int end_x = dar_positions[2*i+1][0];
        int end_y = dar_positions[2*i+1][1];
        switch (i) {
            case 0:
            case 1:
                x++;
                break;
            case 2:
                y++;
                break;
            case 3:
            case 4:
                x--;
                break;
        }
        path_position[num_path][0] = x;
        path_position[num_path][1] = y;
        num_path++;
        // mvprintw(y, x, "#");
        // refresh();
        if((i)==2){
           while (x != end_x || (y+1) != end_y) {
            int direction = rand() % 4;
            int new_x = x;
            int new_y = y;
            switch (direction) {
                case 0: 
                    if(x>=end_x)
                        new_x = x - 1;
                    break;
                case 1:
                    if(x<=end_x)
                        new_x = x + 1;
                    break;
                case 2:
                    if(y>=end_y)
                        new_y = y - 1;
                    break;
                case 3:
                    if(y<end_y)
                        new_y = y + 1;
                    break;
            }

            int inside_room = 0;
            for (int j = 0; j < 6; j++) {
                if (new_x >= room[j].x && new_x <= (room[j].x + room[j].width) &&
                    new_y >= room[j].y && new_y <= (room[j].y + room[j].height)) {
                    inside_room = 1;
                    break;
                }
            }
            if (!inside_room) {
                x = new_x;
                y = new_y;
                path_position[num_path][0] = x;
                path_position[num_path][1] = y;
                num_path++;
                // mvprintw(y, x, "#");
                // refresh();
            }
        } 
        }
        else if(i==0 || i==1){
            while ((x+1) != end_x || y != end_y) {
            int direction = rand() % 4;
            int new_x = x;
            int new_y = y;
            switch (direction) {
                case 0: 
                    if(x>=end_x)
                        new_x = x - 1;
                    break;
                case 1:
                    if(x<=end_x)
                        new_x = x + 1;
                    break;
                case 2:
                    if(y>=end_y)
                        new_y = y - 1;
                    break;
                case 3:
                    if(y<end_y)
                        new_y = y + 1;
                    break;
            }

            int inside_room = 0;
            for (int j = 0; j < 6; j++) {
                if (new_x >= room[j].x && new_x <= (room[j].x + room[j].width) &&
                    new_y >= room[j].y && new_y <= (room[j].y + room[j].height)) {
                    inside_room = 1;
                    break;
                }
            }
            if (!inside_room) {
                x = new_x;
                y = new_y;
                path_position[num_path][0] = x;
                path_position[num_path][1] = y;
                num_path++;
                // mvprintw(y, x, "#");
                // refresh();
            }
        }
        }
        else{
           while ((x-1) != end_x || y != end_y) {
            int direction = rand() % 4;
            int new_x = x;
            int new_y = y;
            switch (direction) {
                case 0: 
                    if(x>=end_x)
                        new_x = x - 1;
                    break;
                case 1:
                    if(x<=end_x)
                        new_x = x + 1;
                    break;
                case 2:
                    if(y>=end_y)
                        new_y = y - 1;
                    break;
                case 3:
                    if(y<end_y)
                        new_y = y + 1;
                    break;
            }

            int inside_room = 0;
            for (int j = 0; j < 6; j++) {
                if (new_x >= room[j].x && new_x <= (room[j].x + room[j].width) &&
                    new_y >= room[j].y && new_y <= (room[j].y + room[j].height)) {
                    inside_room = 1;
                    break;
                }
            }
            if (!inside_room) {
                x = new_x;
                y = new_y;
                path_position[num_path][0] = x;
                path_position[num_path][1] = y;
                num_path++;
                // mvprintw(y, x, "#");
                // refresh();
            }
        } 
        }
        path_position[num_path][0] = end_x;
        path_position[num_path][1] = end_y;
        num_path++;
    }
    for(int i=0 ; i<num_path ; i++){
        path_position[i][2]=0;   
    }
}

void print_path(int x , int y){
    for(int i=0 ; i<num_path ; i++){
        if(x+1 == path_position[i][0] && y+1 == path_position[i][1] && path_position[i][2]==0){
            path_position[i][2]=1;
            attron(COLOR_PAIR(2));
            mvprintw(y+1,x+1,"#");
            refresh();
            attroff(COLOR_PAIR(2));
        }
        if(x-1 == path_position[i][0] && y-1 == path_position[i][1] && path_position[i][2]==0){
            path_position[i][2]=1;
            attron(COLOR_PAIR(2));
            mvprintw(y-1,x-1,"#");
            refresh();
            attroff(COLOR_PAIR(2));
        }
        if(x+1 == path_position[i][0] && y-1 == path_position[i][1] && path_position[i][2]==0){
            path_position[i][2]=1;
            attron(COLOR_PAIR(2));
            mvprintw(y-1,x+1,"#");
            refresh();
            attroff(COLOR_PAIR(2));
        }
        if(x-1 == path_position[i][0] && y+1 == path_position[i][1] && path_position[i][2]==0){
            path_position[i][2]=1;
            attron(COLOR_PAIR(2));
            mvprintw(y+1,x-1,"#");
            refresh();
            attroff(COLOR_PAIR(2));
        }
        if(x == path_position[i][0] && y+1 == path_position[i][1] && path_position[i][2]==0){
            path_position[i][2]=1;
            attron(COLOR_PAIR(2));
            mvprintw(y+1,x,"#");
            refresh();
            attroff(COLOR_PAIR(2));
        }
        if(x == path_position[i][0] && y-1 == path_position[i][1] && path_position[i][2]==0){
            path_position[i][2]=1;
            attron(COLOR_PAIR(2));
            mvprintw(y-1,x,"#");
            refresh();
            attroff(COLOR_PAIR(2));
        }
        if(x-1 == path_position[i][0] && y == path_position[i][1] && path_position[i][2]==0){
            path_position[i][2]=1;
            attron(COLOR_PAIR(2));
            mvprintw(y,x-1,"#");
            refresh();
            attroff(COLOR_PAIR(2));
        }
        if(x+1 == path_position[i][0] && y == path_position[i][1] && path_position[i][2]==0){
            path_position[i][2]=1;
            attron(COLOR_PAIR(2));
            mvprintw(y,x+1,"#");
            refresh();
            attroff(COLOR_PAIR(2));
        }
    }
}
int check_move(int x, int y, Room room[6], int soton_positions[][2], int soton_index, int dar_positions[][2], int dar_index , int path_position[][3] , int num_path) {
    for (int i = 0; i <dar_index; i++) {
        if (x == dar_positions[i][0] && y == dar_positions[i][1]) {
            return 1;
        }
    }
    for (int i = 0; i <num_path; i++) {
        if (x == path_position[i][0] && y == path_position[i][1] && path_position[i][2]==1) {
            return 1;
        }
    }
    for(int i=0 ; i<6 ; i++){
        if (x > room[i].x && x < (room[i].x + room[i].width) && y > room[i].y && y < (room[i].y + room[i].height)) {
        for (int i = 0; i < soton_index; i++) {
            if (x == soton_positions[i][0] && y == soton_positions[i][1]) {
                return 0;
            }
        }
        return 1;
        }
    }
    
    return 0;
}

int move_character(Room room[6], int *x, int *y, int soton_positions[][2], int soton_index, int dar_positions[][2], int dar_index, int path_position[][3] , int num_path) {
    int newx = *x;
    int newy = *y;
    print_path(newx,newy);
    int ch = getch();
    refresh();
    switch (ch) {
        case 'j':
            newy = *y - 1;
            break;
        case 'k':
            newy = *y + 1;
            break;
        case 'h':
            newx = *x - 1;
            break;
        case 'l':
            newx = *x + 1;
            break;
        case 'y':
            newx = *x - 1;
            newy = *y - 1;
            break;
        case 'u':
            newx = *x + 1;
            newy = *y - 1;
            break;
        case 'b':
            newx = *x - 1;
            newy = *y + 1;
            break;
        case 'n':
            newx = *x + 1;
            newy = *y + 1;
            break;
        case 'q':
            return 0;
    }
    if (check_move(newx, newy, room, soton_positions, soton_index, dar_positions, dar_index,path_position,num_path)) {
        for(int i=0 ; i<dar_index ; i++){
            if(dar_positions[i][0]==*x && dar_positions[i][1]==*y){
                attron(COLOR_PAIR(1));
                mvprintw(*y, *x, "+");
                attroff(COLOR_PAIR(1));
                *x = newx;
                *y = newy;
                mvprintw(*y, *x, "I");
                refresh();
                return 1;

            }
        }
        for(int i=0 ; i<num_path ; i++){
            if(path_position[i][0]==*x && path_position[i][1]==*y && path_position[i][2]==1){
                attron(COLOR_PAIR(1));
                mvprintw(*y, *x, "#");
                attroff(COLOR_PAIR(1));
                *x = newx;
                *y = newy;
                mvprintw(*y, *x, "I");
                refresh();
                return 1;

            }
        }
        attron(COLOR_PAIR(3));
        mvprintw(*y, *x, ".");
        attroff(COLOR_PAIR(3));
        *x = newx;
        *y = newy;
        mvprintw(*y, *x, "I");
        refresh();
    }
    return 1;
}

int main() {
    srand(time(NULL));
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    int num_rooms = 6 ;
    int soton_positions[num_rooms * 2][2]; 
    int dar_positions[num_rooms * 2][2]; 
    int soton_index = 0;
    int dar_index = 0;
    Room rooms[num_rooms];
    int x1 = rand()%5;
    int y1 = rand()%5;
    create_random_rooms(rooms,0,5+y1,10+x1);
    x1 = rand()%5;
    y1 = rand()%5;
    create_random_rooms(rooms,1,5+y1,60+x1);
    x1 = rand()%5;
    y1 = rand()%5;
    create_random_rooms(rooms,2,5+y1,110+x1);
    x1 = rand()%5;
    y1 = rand()%5;
    create_random_rooms(rooms,3,25+y1,110+x1);
    x1 = rand()%5;
    y1 = rand()%5;
    create_random_rooms(rooms,4,25+y1,60);
    x1 = rand()%5;
    y1 = rand()%5;
    create_random_rooms(rooms,5,25+y1,10+x1);
    for(int i=0 ; i<6 ; i++){
        draw(rooms[i], soton_positions, &soton_index, dar_positions, &dar_index , i);
        refresh();
    }
    int x = rooms[0].x + 1;
    int y = rooms[0].y + 1;
    path(rooms,dar_positions);
    refresh();
    mvprintw(y, x, "I");
    refresh();

    while (1) {
        if (move_character(rooms, &x, &y, soton_positions, soton_index, dar_positions, dar_index,path_position,num_path) == 0) {
            break;
        }
        refresh();
    }
    refresh();
    getch();
    endwin();
    return 0;
}
