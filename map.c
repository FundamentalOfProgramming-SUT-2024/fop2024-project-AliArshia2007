
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>
int password[1][2];
int key[4];
int num_key=0;
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
    x1 = (rand() % (room.width-1));
    y1 = (rand() % (room.height-1));
    if(x1==0)
        x1++;
    if(y1==0)
        y1++;
    x1 = room.x + x1 + 1; 
    y1 = room.y + y1 + 1 ;
    soton_position[num_soton][0] = x1;
    soton_position[num_soton][1] = y1;
    num_soton++;
    soton_position[num_soton][2]=0;
    x2 = (rand() % (room.width-1));
    y2 = (rand() % (room.height-1));
    if(x2==0)
        x2++;
    if(y2==0)
        y2++;
    x2 = room.x + x2+1; 
    y2 = room.y + y2+1;
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
int gold_position[12][4];
int num_gold=0;
int g=0;
void gold(Room room){
        int x1,y1,x2,y2,price1,price2;
        x1 = (rand() % (room.width-1));
        y1 = (rand() % (room.height-1));
        price1=(rand()%5)+1;
        if(x1==0)
            x2++;
        if(y1==0)
            y2++;
        x1 = room.x + x1 +1; 
        y1 = room.y + y1 +1;
        for(int i=0 ; i<num_soton ; i++){
            if(soton_position[i][0]==x1 && soton_position[i][1]==y1){
                x1 ++ ;
            }
        }
        gold_position[num_gold][0] = x1;
        gold_position[num_gold][1] = y1;
        gold_position[num_gold][2]=0;
        gold_position[num_gold][3]=price1;
        num_gold++;
        x2 = (rand() % (room.width-1));
        y2 = (rand() % (room.height-1));
        price2=(rand()%5)+1;
        if(x2==0)
            x2++;
        if(y2==0)
            y2++;
        x2 = room.x + x2 +1 ; 
        y2 = room.y + y2 +1;
        for(int i=0 ; i<num_soton ; i++){
            if(soton_position[i][0]==x2 && soton_position[i][1]==y2){
                x2 ++ ;
            }
        }
        gold_position[num_gold][0] = x2;
        gold_position[num_gold][1] = y2;
        gold_position[num_gold][2]=0;
        gold_position[num_gold][3]=price2;
        num_gold++;
}
int tale_position[6][3];
int num_tale=0;
void tale(Room room){
    int x1,y1;
        x1 = (rand() % (room.width-1));
        y1 = (rand() % (room.height-1));
        if (x1 <= 0)
            x1=1;
        if (y1 <= 0)
            y1=1;
        x1 = room.x + x1+1; 
        y1 = room.y + y1+1;
        for(int i=0 ; i<num_soton ; i++){
            if(soton_position[i][0]==x1 && soton_position[i][1]==y1){
                x1 ++ ;
            }
        }
        for(int i=0 ; i<num_gold ; i++){
            if(gold_position[i][0]==x1 && gold_position[i][1]==y1){
                x1 ++ ;
            }
        }
        tale_position[num_tale][0] = x1;
        tale_position[num_tale][1] = y1;
        tale_position[num_tale][2]=0;
        num_tale++;
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
    attron(COLOR_PAIR(5));
    mvprintw(gold_position[2*num][1],gold_position[2*num][0],"G");
    mvprintw(gold_position[2*num+1][1],gold_position[2*num+1][0],"G");
    soton_position[2*num][2]=0;
    soton_position[2*num+1][2]=0;
    refresh();
    attroff(COLOR_PAIR(5));
    if(num==0){
        if(dar_positions[num][2]==2){
            attron(COLOR_PAIR(2));
            mvprintw(dar_positions[num][1],dar_positions[num][0],"|");
            attroff(COLOR_PAIR(2));
            refresh();
        }
        else if(dar_positions[num][2]==5){
            attron(COLOR_PAIR(1));
            mvprintw(dar_positions[num][1],dar_positions[num][0],"?");
            attroff(COLOR_PAIR(1));
        }
        else{
            attron(COLOR_PAIR(4));
            mvprintw(dar_positions[num][1],dar_positions[num][0],"+");
            attroff(COLOR_PAIR(4));
            dar_positions[num][2]=1;
            refresh();
        }
    }
    else if(num>0 && num<5){
        mvprintw(dar_positions[2*num-1][1],dar_positions[2*num-1][0],"+");
        if(dar_positions[2*num][2]==2){
            attron(COLOR_PAIR(2));
            mvprintw(dar_positions[2*num][1],dar_positions[2*num][0],"|");
            attroff(COLOR_PAIR(2));
            refresh();
        }
        else if(dar_positions[2*num][2]==3){
            attron(COLOR_PAIR(2));
            mvprintw(dar_positions[2*num][1],dar_positions[2*num][0],"@");
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(4));
            int x=(room.x+room.width-1) , y=(room.y+room.height-1);
            password[0][0]=x;
            password[0][1]=y;
            mvprintw(y,x,"&");
            attroff(COLOR_PAIR(4));
            refresh();
        }
        else if(dar_positions[2*num][2]==4){
            attron(COLOR_PAIR(1));
            mvprintw(dar_positions[2*num][1],dar_positions[2*num][0],"@");
            attroff(COLOR_PAIR(1));
        }
        else if(dar_positions[2*num][2]==5){
            attron(COLOR_PAIR(1));
            mvprintw(dar_positions[2*num][1],dar_positions[2*num][0],"?");
            attroff(COLOR_PAIR(1));
        }
        else{
            attron(COLOR_PAIR(4));
            mvprintw(dar_positions[2*num][1],dar_positions[2*num][0],"+");
            attroff(COLOR_PAIR(4));
            refresh();
        }
        
    }
    else{
        attron(COLOR_PAIR(4));
        mvprintw(dar_positions[2*num-1][1],dar_positions[2*num-1][0],"+");
        mvprintw(dar_positions[2*num][1],dar_positions[2*num][0],">");
        refresh();
        attroff(COLOR_PAIR(4));
    }
    for(int i=0 ; i<num_gold ; i++){
        if(gold_position[i][2]==1){
            attron(COLOR_PAIR(2));
            mvprintw(gold_position[i][1],gold_position[i][0],"G");
            attroff(COLOR_PAIR(2));
        }
    }
    for(int i=0 ; i<num_dar ; i++){
        if(dar_positions[i][2]==1){
            attron(COLOR_PAIR(1));
            mvprintw(dar_positions[i][1],dar_positions[i][0],"+");
            attroff(COLOR_PAIR(1));
        }
        else if(dar_positions[i][2]==4){
            attron(COLOR_PAIR(1));
            mvprintw(dar_positions[i][1],dar_positions[i][0],"@");
            attroff(COLOR_PAIR(1));
        }
        else if(dar_positions[i][2]==5){
            attron(COLOR_PAIR(1));
            mvprintw(dar_positions[i][1],dar_positions[i][0],"?");
            attroff(COLOR_PAIR(1));
        }
    }
    for(int i=0 ; i<num_tale ; i++){
        if(tale_position[i][2]==1){
            attron(COLOR_PAIR(2));
            mvprintw(tale_position[i][1],tale_position[i][0],"^");
            attroff(COLOR_PAIR(2));
        }
    }
    if(key[2]==num){
        if(key[3]==0){
            attron(COLOR_PAIR(6));
            move(key[1], key[0]);
            printw("\u0394");
            attroff(COLOR_PAIR(6));
            refresh();
        }
        else{
            attron(COLOR_PAIR(1));
            move(key[1], key[0]);
            printw("\u0394");
            attroff(COLOR_PAIR(1));
            refresh(); 
        }
        
    }
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
int health=20;
time_t startTime, currentTime;
void healthy(){
    if(health==0){
        return;
    }
    --health;
}
void draw_page(){
    attron(COLOR_PAIR(6));
    mvprintw(45,20,"gold: %d",g);
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(1));
    mvprintw(45,50,"score: %d",(g*8+15));
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    if(health>=10)
        mvprintw(45,80,"health: %d",health);
    else
       mvprintw(45,80,"health: 0%d",health); 
    attron(COLOR_PAIR(2));
}
int ramz;
int check_move(int x, int y, Room room[6]) {
    for (int i = 0; i <num_gold; i++) {
        if (x == gold_position[i][0] && y == gold_position[i][1]) {
            return 1;
        }
    }
    if(x==password[0][0] && y==password[0][1]){
        srand(time(0));
            ramz= rand()%9000 +1000;
            attron(COLOR_PAIR(2));
            mvprintw(15,140,"password is %d.",ramz);
            attroff(COLOR_PAIR(2));
            refresh();
            sleep(10);
            move(15,139);
            clrtoeol();
    }
    if(key[0]==x && key[1]==y){
        return 1;
    }
    for (int i = 0; i <num_dar; i++) {
        if (x == dar_positions[i][0] && y == dar_positions[i][1]) {
            srand(time(0));
            if(dar_positions[i][2]==3){
                attron(COLOR_PAIR(2));
                mvprintw(15,140,"write password: ");
                int mistake=0;
                attroff(COLOR_PAIR(2));
                if(num_key==1){
                    attron(COLOR_PAIR(1));
                    mvprintw(16,140,"press 1 to use master key.");
                    attroff(COLOR_PAIR(1));
                }
                while(1){
                    move(17,139);
                    clrtoeol();
                    move(15,155);
                    clrtoeol();
                    int d; 
                    scanw("%d",&d);
                    mvprintw(15,155,"%d",d);
                    if(num_key==1){
                        if(d==1){
                            attron(COLOR_PAIR(1));
                            move(15,139);
                            clrtoeol();
                            move(16,139);
                            clrtoeol();
                            mvprintw(15,140,"You use the master key.");
                            dar_positions[i][2]=4;
                            refresh();
                            attroff(COLOR_PAIR(1));
                            sleep(2);
                            move(15,139);
                            clrtoeol();
                            refresh();
                            num_key--;  
                            return 1;
                        }
                    }
                    if(d==ramz){
                        move(15,139);
                        clrtoeol();
                        move(16,139);
                        clrtoeol();
                        attron(COLOR_PAIR(1));
                        mvprintw(15,140,"password is correct.");
                        dar_positions[i][2]=4;
                        refresh();
                        attroff(COLOR_PAIR(1));
                        sleep(2);
                        refresh();
                        move(15,139);
                        clrtoeol();
                        return 1;
                    }
                    else{
                        if(mistake==0){
                            attron(COLOR_PAIR(6));
                            mvprintw(17,140,"password is not corect.");
                            attroff(COLOR_PAIR(6));
                            refresh();
                            sleep(2);
                            mistake++;
                        }
                        else if(mistake==1){
                            attron(COLOR_PAIR(2));
                            mvprintw(17,140,"password is not corect.");
                            attroff(COLOR_PAIR(6));
                            refresh();
                            sleep(2);
                            mistake++;
                        }
                        else if(mistake==2){
                            attron(COLOR_PAIR(3));
                            mvprintw(17,140,"IF write wrong answer , password is change!");
                            attroff(COLOR_PAIR(3));
                            refresh();
                            sleep(2);
                            mistake++;
                        }
                        else{
                            attron(COLOR_PAIR(3));
                            mvprintw(17,140,"password is change!");
                            attroff(COLOR_PAIR(3));
                            refresh();
                            sleep(2);
                            move(17,139); clrtoeol();
                            ramz=0;
                            return 0;
                        }
                    }
                }
            }
        }
        if(x == dar_positions[i][0] && y == dar_positions[i][1]){
            if(dar_positions[i][2]==0){
                dar_positions[i][2]=1;
                return 1;
            }
            if(dar_positions[i][2]==4){
                return 1;
            }
            if(dar_positions[i][2]==5){
                return 1;
            }
            if(dar_positions[i][2]==1){
                return 1;
            }
        }
        if(x+1 == dar_positions[i][0] && y == dar_positions[i][1] && dar_positions[i][2]==2){
            attron(COLOR_PAIR(4));
            mvprintw(dar_positions[i][1],dar_positions[i][0],"?");
            dar_positions[i][2]=5;
            attroff(COLOR_PAIR(4));
        }
        if(x+1 == dar_positions[i][0] && y+1 == dar_positions[i][1] && dar_positions[i][2]==2){
            attron(COLOR_PAIR(4));
            mvprintw(dar_positions[i][1],dar_positions[i][0],"?");
            dar_positions[i][2]=5;
            attroff(COLOR_PAIR(4));
        }
        if(x+1 == dar_positions[i][0] && y-1 == dar_positions[i][1] && dar_positions[i][2]==2){
            attron(COLOR_PAIR(4));
            mvprintw(dar_positions[i][1],dar_positions[i][0],"?");
            dar_positions[i][2]=5;
            attroff(COLOR_PAIR(4));
        }
    }
    for (int i = 0; i <num_path; i++) {
        if (x == path_position[i][0] && y == path_position[i][1] && path_position[i][2]==1) {
            path_position[i][2]=1;
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
            draw_page();
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
        if(password[0][0]==*x && password[0][1]==*y){
            attron(COLOR_PAIR(4));
            mvprintw(*y, *x, "&");
            attroff(COLOR_PAIR(4));
            *x = newx;
            *y = newy;
            mvprintw(*y, *x, "I");
            draw_page();
            refresh();
            return 1;
        }
        if(key[0]==*x && key[1]==*y){
            attron(COLOR_PAIR(1));
            mvprintw(*y, *x, "\u0394");
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(6));
            mvprintw(10,140,"You get the master key.");
            key[3]=1;
            attroff(COLOR_PAIR(6));
            refresh();
            sleep(1);
            move(10,139);
            clrtoeol();
            refresh();
            *x = newx;
            *y = newy;
            num_key++;
            mvprintw(*y, *x, "I");
            draw_page();
            refresh();
            return 1;
        }
        for(int i=0 ; i<num_dar ; i++){
            if(dar_positions[i][0]==*x && dar_positions[i][1]==*y){
                if(dar_positions[i][2]==4){
                    attron(COLOR_PAIR(1));
                    mvprintw(*y, *x, "@");
                    refresh();
                    attroff(COLOR_PAIR(1)); 
                }
                if(dar_positions[i][2]==5){
                    attron(COLOR_PAIR(1));
                    mvprintw(*y, *x, "?");
                    refresh();
                    attroff(COLOR_PAIR(1)); 
                }
                else{
                    attron(COLOR_PAIR(1));
                    mvprintw(*y, *x, "+");
                    refresh();
                    attroff(COLOR_PAIR(1)); 
                }
                draw_room(room[(i+1)/2],(i+1)/2);
                room[(i+1)/2].hide=1;
                *x = newx;
                *y = newy;
                mvprintw(*y, *x, "I");
                draw_page();
                refresh();
                return 1;

            }
        }
        for(int i=0 ; i<num_gold ; i++){
            if(gold_position[i][0]==*x && gold_position[i][1]==*y){
                if(gold_position[i][2]==1){
                    attron(COLOR_PAIR(6));
                    mvprintw(10,140,"You take it befor.");
                    attron(COLOR_PAIR(6));
                    refresh();
                    sleep(1);
                    move(10,139);
                    clrtoeol();
                    refresh();
                }
                else{
                    attron(COLOR_PAIR(6));
                    mvprintw(10,140,"You get %d gold.",gold_position[i][3]);
                    gold_position[i][2]=1;
                    attron(COLOR_PAIR(6));
                    refresh();
                    sleep(1);
                    move(10,139);
                    clrtoeol();
                    refresh();
                }
                attron(COLOR_PAIR(2));
                mvprintw(*y, *x, "G");
                attroff(COLOR_PAIR(2));
                *x = newx;
                *y = newy;
                mvprintw(*y, *x, "I");
                g += gold_position[i][3];
                draw_page();
                refresh();
                return 1;
            }
        }
        for(int i=0 ; i<num_tale ; i++){
            if(tale_position[i][0]==*x && tale_position[i][1]==*y){
                if(tale_position[i][2]==0)
                    health -= 2;
                    tale_position[i][2]=1;
                attron(COLOR_PAIR(2));
                mvprintw(*y, *x, "^");
                attroff(COLOR_PAIR(2));
                *x = newx;
                *y = newy;
                mvprintw(*y, *x, "I");
                draw_page();
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
                draw_page();
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
        draw_page();
        refresh();
    }
    return 1;
}
int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
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
        gold(rooms[i]);
        tale(rooms[i]);
    }
    int q=rand()%3;
    key[0]=rooms[q].x+rand()%(rooms[q].width-2)+1;
    key[1]=rooms[q].y+rand()%(rooms[q].height-2)+1;
    key[2]=q; key[3]=0;
    int t=2*(rand()%2);
    dar_positions[t][2]=2;
    dar_positions[t+6][2]=3;
    draw_room(rooms[0],0);
    rooms[0].hide=1;
    draw_page();
    int x = rooms[0].x + 1;
    int y = rooms[0].y + 1;
    path(rooms);
    refresh();
    mvprintw(y, x, "I");
    refresh();
    time(&startTime);
    while (health > 0) {
        time(&currentTime);
        if (difftime(currentTime, startTime) >= 8) {
            healthy();
            time(&startTime);
        }
        if (move_character(rooms, &x, &y) == 0) {
            break;
        }
        refresh();
    }
    if(health==0){
        attron(COLOR_PAIR(2));
        mvprintw(20,140,"You are Lost.");
        refresh();
        sleep(5);
        attroff(COLOR_PAIR(2));
    }
    else{
        mvprintw(20,140,"I hope enjoy the game.");
        refresh();
        sleep(5);  
    }
    endwin();
    return 0;
}
