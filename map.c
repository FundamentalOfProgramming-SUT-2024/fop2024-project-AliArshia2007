
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int hide;
} Room;
void create_random_rooms(Room rooms[],int num , int y, int x) {
    Room new_room;
    new_room.width = rand() % 6 + 6;
    new_room.height = rand() % 5 + 6;
    new_room.x = x;
    new_room.y = y;
    rooms[num] = new_room;
    rooms->hide=0;
}
int dar_positions[11][3];
int num_dar=0;
void dar(Room room,int t1) {
    int pos;
    switch (t1) {
        case 0:
            pos = rand() % room.width+1;
            dar_positions[num_dar][0] = room.x + pos;
            dar_positions[num_dar][1] = room.y;
            dar_positions[num_dar][2]=0;
            num_dar++;
            break;
        case 1:
            pos = rand() % room.height+1;
            dar_positions[num_dar][0] = room.x + room.width;
            dar_positions[num_dar][1] = room.y + pos;
            dar_positions[num_dar][2]=0;
            num_dar++;
            break;
        case 2:
            pos = rand() % room.width+1;
            dar_positions[num_dar][0] = room.x + pos;
            dar_positions[num_dar][1] = room.y + room.height;
            dar_positions[num_dar][2]=0;
            num_dar++;
            break;
        default:
            pos = rand() % room.height+1;
            dar_positions[num_dar][0] = room.x;
            dar_positions[num_dar][1] = room.y + pos;
            dar_positions[num_dar][2]=0;
            num_dar++;
            break;
    }
}
int soton_position[12][3];
int num_soton=0;
void soton(Room room) {
    int x1,x2, y1,y2;
    x1 = (rand() % room.width)-1;
    y1 = (rand() % room.height)-1;
    if (x1 <= 0)
        x1=1;
    if (y1 <= 0)
        y1=1;
    x1 = room.x + x1; 
    y1 = room.y + y1;
    soton_position[num_soton][0] = x1;
    soton_position[num_soton][1] = y1;
    num_soton++;
    soton_position[num_soton][2]=0;
    x2 = (rand() % room.width)-1;
    y2 = (rand() % room.height)-1;
    if (x2 <= 0)
        x2=1;
    if (y2 <= 0)
        y2=1;
    x2 = room.x + x2; 
    y2 = room.y + y2;
    soton_position[num_soton][0] = x2;
    soton_position[num_soton][1] = y2;
    soton_position[num_soton][2]=0;
    num_soton++;
}
void draw_dar( Room room , int num){
    switch(num){
        case 0:
            dar(room,1);
            break;
        case 1:
            dar(room,3);
            dar(room,1);
            break;
        case 2:
            dar(room,3);
            dar(room,2);
            break;
        case 3:
            dar(room,0);
            dar(room,3);
            break;
        case 4:
            dar(room,1);
            dar(room,3);
            break;
        case 5:
            dar(room,1);
            dar(room,3);
            break;
    }
}
void draw_room(Room room ,int num) {
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
    mvprintw(soton_position[2*num][1],soton_position[2*num][0],"O");
    soton_position[2*num][2]=1;
    refresh();
    mvprintw(soton_position[2*num+1][1],soton_position[2*num+1][0],"O");
    soton_position[2*num+1][2]=1;
    refresh();
    if(num==0){
        mvprintw(dar_positions[num][1],dar_positions[num][0],"+");
        dar_positions[num][2]=1;
        refresh();
    }
    else if(num>0 && num<5){
        mvprintw(dar_positions[2*num-1][1],dar_positions[2*num-1][0],"+");
        mvprintw(dar_positions[2*num][1],dar_positions[2*num][0],"+");
        refresh();
    }
    else{
        mvprintw(dar_positions[2*num-1][1],dar_positions[2*num-1][0],"+");
        mvprintw(dar_positions[2*num][1],dar_positions[2*num][0],">");
        refresh();
    }
    attroff(COLOR_PAIR(4));
}
int path_position[3000][3];
int num_path = 0;
void path(Room room[6]) {
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
int check_move(int x, int y, Room room[6]) {
    for (int i = 0; i <num_dar; i++) {
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
        for (int i = 0; i < num_soton; i++) {
            if (x == soton_position[i][0] && y == soton_position[i][1]) {
                return 0;
            }
        }
        return 1;
        }
    }
    
    return 0;
}

int move_character(Room room[6], int *x, int *y) {
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
        case 'a':
            clear();
            for(int i=0 ; i<6 ; i++){
                draw_room(room[i],i);
            }
            refresh();
            for(int i=0 ; i<num_path ; i++){
                mvprintw(path_position[i][1],path_position[i][0],"#");
                refresh();
            }
            while(1){
                int c = getch();
                if(c=='a'){
                    break;
                }
            }
            clear();
            for (int i=0 ; i< 6; i++)
            {
                if(room[i].hide==1){
                    draw_room(room[i],i);
                }
                refresh();
            }
            for(int i=0 ; i<num_path ; i++){
                if(path_position[i][2]==1){
                    attron(COLOR_PAIR(1));
                    mvprintw(path_position[i][1],path_position[i][0],"#");
                    attroff(COLOR_PAIR(1));
                }
            }
            mvprintw(newy,newx,"I");
            break;
        case 'f':
            int c=getch();
            refresh();
            switch (c){
                case 'j':
                    while(check_move(newx,newy,room)){
                        newy = newy - 1;
                    }
                    newy++;
                    refresh();
                    break;
                case 'k':
                    while(check_move(newx,newy,room)){
                        newy = newy + 1;
                    }
                    newy--;
                    refresh();
                    break;
                case 'h':
                    while(check_move(newx,newy,room)){
                        newx = newx - 1;
                    }
                    newx++;
                    refresh();
                    break;
                case 'l':
                    while(check_move(newx,newy,room)){
                        newx = newx + 1;
                    }
                    newx--;
                    refresh();
                    break;
                case 'y':
                    while(check_move(newx,newy,room)){
                        newx = newx - 1;
                        newy = newy - 1;
                    }
                    newy++;
                    newx++;
                    refresh();
                    break;
                case 'u':
                    while(check_move(newx,newy,room)){
                        newx = newx + 1;
                        newy = newy - 1;
                    }
                    newy++;
                    newx--;
                    refresh();
                    break;
                case 'b':
                    while(check_move(newx,newy,room)){
                        newx = newx - 1;
                        newy = newy + 1;
                    }
                    newy--;
                    newx++;
                    refresh();
                    break;
                case 'n':
                    while(check_move(newx,newy,room)){
                        newx = newx + 1;
                        newy = newy + 1;
                    }
                    newy--;
                    newx--;
                    refresh();
                    break;
            }
            break;
        case 'q':
            return 0;
    }
    if (check_move(newx, newy, room)) {
        for(int i=0 ; i<num_dar ; i++){
            if(dar_positions[i][0]==*x && dar_positions[i][1]==*y){
                draw_room(room[(i+1)/2],(i+1)/2);
                room[(i+1)/2].hide=1;
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
        draw_dar(rooms[i],i);
        soton(rooms[i]);
    }
    draw_room(rooms[0],0);
    rooms[0].hide=1;
    int x = rooms[0].x + 1;
    int y = rooms[0].y + 1;
    path(rooms);
    refresh();
    mvprintw(y, x, "I");
    refresh();
    while (1) {
        if (move_character(rooms, &x, &y) == 0) {
            break;
        }
        refresh();
    }
    refresh();
    getch();
    endwin();
    return 0;
}
