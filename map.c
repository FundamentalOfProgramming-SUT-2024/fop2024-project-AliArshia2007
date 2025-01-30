
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
int fl,color=3,dif=3;
typedef struct {
    int x;
    int y;
    int width;
    int height;
    int hide;
} Room;
void create_random_rooms(Room rooms[],int num , int y, int x) {
    Room new_room;
    new_room.width = rand() % 3+ 6;
    new_room.height = rand() % 3 + 6;
    new_room.x = x;
    new_room.y = y;
    new_room.hide=0;
    rooms[num] = new_room;
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
    x1 = (rand() % (room.width-2));
    y1 = (rand() % (room.height-2));
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
int tale_position[6][4];
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
int food_position[24][3];
int num_food=0;
int nf=0;
void food(Room room){
    int x1,y1;
        x1 = (rand() % (room.width-2));
        y1 = (rand() % (room.height-2));
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
        for(int i=0 ; i<num_tale ; i++){
            if(tale_position[i][0]==x1 && tale_position[i][1]==y1){
                x1 ++ ;
            }
        }
        food_position[num_food][0] = x1;
        food_position[num_food][1] = y1;
        food_position[num_food][2]=0;
        num_food++;
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
    attron(COLOR_PAIR(6));
    mvprintw(gold_position[2*num][1],gold_position[2*num][0],"\u0454");
    mvprintw(gold_position[2*num+1][1],gold_position[2*num+1][0],"\u0454");
    soton_position[2*num][2]=0;
    soton_position[2*num+1][2]=0;
    refresh();
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(7));
    mvprintw(food_position[num][1],food_position[num][0],"\u03C6");
    refresh();
    attroff(COLOR_PAIR(7));
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
            int x=(room.x+room.width-2) , y=(room.y+room.height-1);
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
            attron(COLOR_PAIR(4));
            mvprintw(password[0][1],password[0][0],"&");
            attroff(COLOR_PAIR(4));
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
            mvprintw(gold_position[i][1],gold_position[i][0],"\u0454");
            attroff(COLOR_PAIR(2));
        }
    }
    for(int i=0 ; i<num_food ; i++){
        if(food_position[i][2]==1){
            attron(COLOR_PAIR(2));
            mvprintw(food_position[i][1],food_position[i][0],"\u03C6");
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
    mvprintw(35,10,"gold: %d",g);
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(1));
    mvprintw(35,25,"score: %d",(g*3));
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    attron(COLOR_PAIR(7));
    mvprintw(35,40,"food: %d",nf);
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(2));
    mvprintw(35,55,"weapon:");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(6));
    mvprintw(35,70,"talisman:");
    attroff(COLOR_PAIR(6));
    move(2,0);
    clrtoeol();
    attron(COLOR_PAIR(3));
    mvprintw(2,1,"healty:");
    attroff(COLOR_PAIR(3));
    for(int i=0 ; i<(health) ; i+=2){
        attron(COLOR_PAIR(2));
        mvprintw(2,10+i,"\u2665");
        attroff(COLOR_PAIR(2));
    }
    refresh();
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
            mvprintw(10,80,"password is %d.",ramz);
            attroff(COLOR_PAIR(2));
            refresh();
            sleep(10);
            move(10,59);
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
                mvprintw(10,80,"write password: ");
                int mistake=0;
                attroff(COLOR_PAIR(2));
                if(num_key==1){
                    attron(COLOR_PAIR(1));
                    mvprintw(11,80,"press 1 to use master key.");
                    attroff(COLOR_PAIR(1));
                }
                while(1){
                    move(12,79);
                    clrtoeol();
                    move(10,95);
                    clrtoeol();
                    int d; 
                    scanw("%d",&d);
                    mvprintw(10,95,"%d",d);
                    if(num_key==1){
                        if(d==1){
                            attron(COLOR_PAIR(1));
                            move(10,79);
                            clrtoeol();
                            move(11,79);
                            clrtoeol();
                            mvprintw(10,80,"You use the master key.");
                            dar_positions[i][2]=4;
                            refresh();
                            attroff(COLOR_PAIR(1));
                            sleep(2);
                            move(10,79);
                            clrtoeol();
                            refresh();
                            num_key--;  
                            return 1;
                        }
                    }
                    if(d==ramz){
                        move(10,79);
                        clrtoeol();
                        move(11,79);
                        clrtoeol();
                        attron(COLOR_PAIR(1));
                        mvprintw(10,80,"password is correct.");
                        dar_positions[i][2]=4;
                        refresh();
                        attroff(COLOR_PAIR(1));
                        sleep(2);
                        refresh();
                        move(10,79);
                        clrtoeol();
                        return 1;
                    }
                    else{
                        if(mistake==0){
                            attron(COLOR_PAIR(6));
                            mvprintw(12,80,"password is not corect.");
                            attroff(COLOR_PAIR(6));
                            refresh();
                            sleep(2);
                            mistake++;
                        }
                        else if(mistake==1){
                            attron(COLOR_PAIR(2));
                            mvprintw(12,80,"password is not corect.");
                            attroff(COLOR_PAIR(6));
                            refresh();
                            sleep(2);
                            mistake++;
                        }
                        else if(mistake==2){
                            attron(COLOR_PAIR(3));
                            mvprintw(12,80,"IF write wrong answer,password is change!");
                            attroff(COLOR_PAIR(3));
                            refresh();
                            sleep(2);
                            mistake++;
                        }
                        else{
                            attron(COLOR_PAIR(3));
                            mvprintw(12,80,"password is change!");
                            attroff(COLOR_PAIR(3));
                            refresh();
                            sleep(2);
                            move(12,79); clrtoeol();
                            move(10,79); clrtoeol();
                            move(11,79); clrtoeol();
                            refresh();
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
    for (int i = 0; i <num_food; i++) {
        if (x == food_position[i][0] && y == food_position[i][1] && nf<5) {
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
int numroom=0;
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
        case 's':
            clear();
            for(int i=0 ; i<=(numroom+1) ; i++){
                draw_room(room[i],i);
                refresh();
            }
            draw_page();
            refresh();
            for(int i=0 ; i<=(numroom+1) ; i++){
                if(tale_position[i][2]==0){
                    attron(COLOR_PAIR(2));
                    mvprintw(tale_position[i][1],tale_position[i][0],"^");
                    refresh();
                    attroff(COLOR_PAIR(2));
                }
            }
            for(int i=0 ; i<=(numroom+1) ; i++){
                if(dar_positions[i][2]==2){
                    attron(COLOR_PAIR(4));
                    mvprintw(dar_positions[i][1],dar_positions[i][0],"?");
                    refresh();
                    attroff(COLOR_PAIR(4));
                }
                if(dar_positions[i][2]==5){
                    attron(COLOR_PAIR(1));
                    mvprintw(dar_positions[i][1],dar_positions[i][0],"?");
                    refresh();
                    attroff(COLOR_PAIR(1));
                }
            }
            while(1){
                int c = getch();
                if(c=='s'){
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
        case 'e':
            while(TRUE){
                move(10,79);clrtoeol();
                if(nf==0){
                    attron(COLOR_PAIR(2));
                    mvprintw(10,80,"you don't have any food.");
                    refresh();
                    attroff(COLOR_PAIR(2));
                }
                attron(COLOR_PAIR(7));
                for(int i=0 ; i<nf ; i++){
                    mvprintw(29-i,80,"food %d",nf-i);
                    refresh();
                }
                mvprintw(30,80,"press 10 to return the game.");
                mvprintw(31,80,"enter your choise:");
                refresh();
                move(31,99);
                clrtoeol();
                int d;
                move(31,100);
                scanw("%d",&d);
                mvprintw(31,100,"%d",d);
                if(d==10)
                    break;
                refresh();
                srand(time(0));
                int h=rand()%4;
                if(h>0){
                    health += 2;
                    if(health>20)
                        health=20;
                    mvprintw(10,80,"your food is healthy.");
                    draw_page();
                    refresh();
                    sleep(2);
                    nf--;
                }
                else{
                    health -= 1;
                    mvprintw(10,80,"your food is unhealthy.");
                    draw_page();
                    refresh();
                    sleep(2);
                    nf--;
                    if(health<0)
                        health=0;
                    if(health==0){
                        attron(COLOR_PAIR(2));
                        mvprintw(20,80,"You are Lost.");
                        refresh();
                        attroff(COLOR_PAIR(2));
                        getchar();
                        endwin();
                        return 0;
                    }
                }
                move(15,139);
                clrtoeol();
                for(int i=0 ; i<=6 ; i++){
                    move(25+i,79);
                    clrtoeol();
                }
            }
            for(int i=0 ; i<=6 ; i++){
                move(25+i,79);
                clrtoeol();
            }
            attroff(COLOR_PAIR(7));
            move(10,79);
            clrtoeol();
            move(30,79);
            clrtoeol();
            move(31,79);
            clrtoeol();
            return 1;
        case 'q':
            clear();
            attron(COLOR_PAIR(7));
            mvprintw(10,20,"Please type your game name:");
            refresh();
            move(10,50);
            char name[20];
            scanw("%s",name);
            mvprintw(10,50,"%s",name);
            refresh();
            attroff(COLOR_PAIR(7));
            FILE *file = fopen(name,"w");
            for(int i=0 ; i<6 ; i++){
                fprintf(file,"%d %d %d %d %d\n",room[i].x,room[i].y,room[i].width,room[i].height,room[i].hide);
            }
            for(int i=0 ; i<num_dar ; i++){
                fprintf(file,"%d %d %d\n",dar_positions[i][0],dar_positions[i][1],dar_positions[i][2]);
            }
            for(int i=0 ; i<num_soton ; i++){
                fprintf(file,"%d %d %d\n",soton_position[i][0],soton_position[i][1],soton_position[i][2]);
            }
            for(int i=0 ; i<num_gold ; i++){
                fprintf(file,"%d %d %d %d\n",gold_position[i][0],gold_position[i][1],gold_position[i][2],gold_position[i][3]);
            }
            for(int i=0 ; i<num_tale ; i++){
                fprintf(file,"%d %d %d %d\n",tale_position[i][0],tale_position[i][1],tale_position[i][2],tale_position[i][3]);
            }
            for(int i=0 ; i<num_food ; i++){
                fprintf(file,"%d %d %d\n",food_position[i][0],food_position[i][1],food_position[i][2]);
            }
            for(int i=0 ; i<num_path ; i++){
                fprintf(file,"%d %d %d %d\n",path_position[i][0],path_position[i][1],path_position[i][2],path_position[i][3]);
            }
            fprintf(file,"%d %d %d %d %d %d\n",fl,g,nf,health,*x,*y);
            fclose(file);
            getchar();
            return 0;
    }
    if (check_move(newx, newy, room)) {
        if(password[0][0]==*x && password[0][1]==*y){
            attron(COLOR_PAIR(4));
            mvprintw(*y, *x, "&");
            attroff(COLOR_PAIR(4));
            *x = newx;
            *y = newy;
        }
        if(key[0]==*x && key[1]==*y){
            attron(COLOR_PAIR(1));
            mvprintw(*y, *x, "\u0394");
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(6));
            mvprintw(10,80,"You get the master key.");
            key[3]=1;
            attroff(COLOR_PAIR(6));
            refresh();
            sleep(1);
            move(10,79);
            clrtoeol();
            refresh();
            *x = newx;
            *y = newy;
            num_key++;
        }
        for(int i=0 ; i<num_dar ; i++){
            if(dar_positions[i][0]==*x && dar_positions[i][1]==*y){
                if(i%2==1 && numroom<4){
                    numroom ++;
                }
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
            }
        }for(int i=0 ; i<num_food ; i++){
            if(food_position[i][0]==*x && food_position[i][1]==*y){
                if(nf==5){
                    attron(COLOR_PAIR(2));
                    mvprintw(10,80,"You have enough food.");
                    attron(COLOR_PAIR(2));
                    refresh();
                    sleep(1);
                    move(10,79);
                    clrtoeol();
                    refresh();
                    attron(COLOR_PAIR(7));
                    mvprintw(*y, *x, "\u03C6");
                    attroff(COLOR_PAIR(7));
                    *x = newx;
                    *y = newy;
                }
                if(food_position[i][2]==1){
                    attron(COLOR_PAIR(6));
                    mvprintw(10,80,"You take it befor.");
                    attroff(COLOR_PAIR(6));
                    refresh();
                    sleep(1);
                    move(10,79);
                    clrtoeol();
                    refresh();
                }
                else{
                    attron(COLOR_PAIR(6));
                    if(food_position[i][2]==0){
                        mvprintw(10,80,"You get food.");
                        food_position[i][2]=1;
                        nf ++;
                    }
                    attroff(COLOR_PAIR(6));
                    refresh();
                    sleep(1);
                    move(10,79);
                    clrtoeol();
                    refresh();
                }
                attron(COLOR_PAIR(2));
                mvprintw(*y, *x, "\u03C6");
                attroff(COLOR_PAIR(2));
                *x = newx;
                *y = newy;
            }
        }
        for(int i=0 ; i<num_gold ; i++){
            if(gold_position[i][0]==*x && gold_position[i][1]==*y){
                if(gold_position[i][2]==1){
                    attron(COLOR_PAIR(6));
                    mvprintw(10,80,"You take it befor.");
                    attron(COLOR_PAIR(6));
                    refresh();
                    sleep(1);
                    move(10,79);
                    clrtoeol();
                    refresh();
                }
                else{
                    attron(COLOR_PAIR(6));
                    mvprintw(10,80,"You get %d gold.",gold_position[i][3]);
                    gold_position[i][2]=1;
                    attron(COLOR_PAIR(6));
                    refresh();
                    sleep(1);
                    move(10,79);
                    clrtoeol();
                    refresh();
                }
                attron(COLOR_PAIR(2));
                mvprintw(*y, *x, "\u0454");
                attroff(COLOR_PAIR(2));
                *x = newx;
                *y = newy;
                g += gold_position[i][3];
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
            }
        }
        for(int i=0 ; i<num_path ; i++){
            if(path_position[i][0]==*x && path_position[i][1]==*y && path_position[i][2]==1){
                attron(COLOR_PAIR(1));
                mvprintw(*y, *x, "#");
                attroff(COLOR_PAIR(1));
                *x = newx;
                *y = newy;
            }
        }
        attron(COLOR_PAIR(3));
        mvprintw(*y, *x, ".");
        attroff(COLOR_PAIR(3));
        *x = newx;
        *y = newy;
    }
    switch (color)
            {
            case 1:
                attron(COLOR_PAIR(2));
                mvprintw(*y, *x, "\u2735");
                refresh();
                attroff(COLOR_PAIR(2));
                break;
            case 2:
                attron(COLOR_PAIR(1));
                mvprintw(*y, *x, "\u2735");
                refresh();
                attroff(COLOR_PAIR(1));
                break;
            case 3:
                attron(COLOR_PAIR(7));
                mvprintw(*y, *x, "\u2735");
                refresh();
                attroff(COLOR_PAIR(7));
                break;
            case 4:
                attron(COLOR_PAIR(6));
                mvprintw(*y, *x, "\u2735");
                refresh();
                attroff(COLOR_PAIR(6));
                break;
            }
            draw_page();
            refresh();
            return 1;
}
int main() {
    setlocale(LC_ALL, "");
    initscr();
    srand(time(NULL));
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7,COLOR_CYAN,COLOR_BLACK);
    for(int i=0 ; i<4 ; i++){
        fl=i;
        clear();
        srand(time(0));
        int num_rooms = 6 ;
        Room rooms[num_rooms];
        int x1 = rand()%5;
        int y1 = rand()%5;
        create_random_rooms(rooms,0,5+y1,10+x1);
        x1 = rand()%5;
        y1 = rand()%5;
        create_random_rooms(rooms,1,5+y1,35+x1);
        x1 = rand()%5;
        y1 = rand()%5;
        create_random_rooms(rooms,2,5+y1,60+x1);
        x1 = rand()%5;
        y1 = rand()%5;
        create_random_rooms(rooms,3,20+y1,60+x1);
        x1 = rand()%5;
        y1 = rand()%5;
        create_random_rooms(rooms,4,20+y1,35+x1);
        x1 = rand()%5;
        y1 = rand()%5;
        create_random_rooms(rooms,5,20+y1,10+x1);
        for(int j=0 ; j<6 ; j++){
            draw_dar(rooms[j],j);
            soton(rooms[j]);
            gold(rooms[j]);
            tale(rooms[j]);
            food(rooms[j]);
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
        mvprintw(y, x, "\u2735");
        refresh();
        time(&startTime);
        while (health > 0) {
            time(&currentTime);
            if(dif==1){
                if (difftime(currentTime, startTime) >= 15) {
                    healthy();
                    time(&startTime);
                }
            }
            if(dif==2){
                if (difftime(currentTime, startTime) >= 10) {
                    healthy();
                    time(&startTime);
                }
            }
            if(dif==3){
                if (difftime(currentTime, startTime) >= 7) {
                    healthy();
                    time(&startTime);
                }
            }
            if (move_character(rooms, &x, &y) == 0) {
                clear();
                mvprintw(20,20,"I hope enjoy the game.");
                refresh();
                getchar();
                endwin();
                return 0;
            }
            refresh();
            if(x==dar_positions[10][0]&& y==dar_positions[10][1]){
                break;
            }
        }
        if(health==0){
            attron(COLOR_PAIR(2));
            mvprintw(20,140,"You are Lost.");
            refresh();
            attroff(COLOR_PAIR(2));
            getchar();
            endwin();
            return 0;
        }
        for(int j=0 ; j<num_dar ; j++){
            dar_positions[j][0]=dar_positions[j][1]=dar_positions[j][2]=0;
        }
        for(int j=0 ; j<num_path ; j++){
            path_position[j][0]=path_position[j][1]=path_position[j][2]=0;
        }
        for(int j=0 ; j<num_soton ; j++){
            soton_position[j][0]=soton_position[j][1]=soton_position[j][2]=0;
        }
        for(int j=0 ; j<num_gold ; j++){
            gold_position[j][0]=gold_position[j][1]=gold_position[j][2]=gold_position[j][3]=0;
        }
        for(int j=0 ; j<num_tale ; j++){
            tale_position[j][0]=tale_position[j][1]=tale_position[j][2]=tale_position[j][3]=0;
        }
        for(int j=0 ; j<num_food ; j++){
            food_position[j][0]=food_position[j][1]=food_position[j][2]=0;
        }
        key[0]=key[1]=key[2]=key[3]=0;
        num_dar=num_path=num_key=num_rooms=num_tale=num_soton=num_gold=num_food=numroom=0;
        sleep(2);
        }
        attron(COLOR_PAIR(6));
        mvprintw(10,50,"You won.");
        mvprintw(11,40,"Gold: %d score: %d",g,g*3);
        refresh();
        attroff(COLOR_PAIR(6));
        getchar();
        endwin();
        return 0;
}
