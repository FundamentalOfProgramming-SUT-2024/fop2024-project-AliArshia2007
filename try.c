#include <ncurses.h>
#include<stdio.h>
#include<string.h>
#include <time.h>
#include<stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>
int check_pas();
int check_email();
void save_user();
int check_login();
int check_name();
void safhe();
void find_pas();
void login();
void new_user();
int entery();
void table(); 
void sort();
void new_game();
void load_game();
void set_difficulty();
void set_hero_color();
void play_music();
void choose_music();
int password[1][2];
int lost_weapon[50][4], num_lost = 0;
int key[4];
int num_key=0;
int fl,color=3,dif=1,num_game=0,dif2,numroom=0;
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
int weapon_position[5][5],num_weapon=0,wea=0;
int current_weapon[2];
void weapon(Room room , int num){
    int x1,y1;
    x1 = room.x + 1; 
    y1 = room.y + room.height- 1 ;
    weapon_position[num_weapon][0] = x1;
    weapon_position[num_weapon][1] = y1;
    weapon_position[num_weapon][2]=0;
    switch (fl)
    {
    case 0:
        weapon_position[num_weapon][3]=12;
        weapon_position[num_weapon][4]=0;
        break;
    case 1:
        weapon_position[num_weapon][3]=15;
        weapon_position[num_weapon][4]=0;
        break; 
    case 2:
        weapon_position[num_weapon][3]=5;
        weapon_position[num_weapon][4]=0;
        break; 
    case 3:
        weapon_position[num_weapon][3]=10;
        weapon_position[num_weapon][4]=0;
        break;
    }
    num_weapon++;
}
int soton_position[12][3];
int num_soton=0;
void soton(Room room) {
    int x1,x2, y1,y2;
    x1 = (rand() % (room.width-3));
    y1 = (rand() % (room.height-3));
    if(x1==0)
        x1++;
    if(y1==0)
        y1++;
    x1 = room.x + x1+1; 
    y1 = room.y + y1+1;
    if((x1==(room.x+1)|| (x1)==room.x+2) && y1==(room.y+room.height-1)){
        x1 += 2;
    }
    soton_position[num_soton][0] = x1;
    soton_position[num_soton][1] = y1;
    num_soton++;
    soton_position[num_soton][2]=0;
    x2 = (rand() % (room.width-3));
    y2 = (rand() % (room.height-3));
    if(x2==0)
        x2++;
    if(y2==0)
        y2++;
    x2 = room.x + x2+1; 
    y2 = room.y + y2+1;
    if((x2==(room.x+1)|| (x2)==room.x+2) && y2==(room.y+room.height-1)){
        x2 += 2;
    }
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
        x1 = (rand() % (room.width-2));
        y1 = (rand() % (room.height-2));
        price1=(rand()%5)+1;
        if(x1==0)
            x1++;
        if(y1==0)
            y1++;
        x1 = room.x + x1 +1; 
        y1 = room.y + y1 +1;
        if((x1==(room.x+1)|| (x1)==room.x+2) && y1==(room.y+room.height-1)){
            x1 += 2;
        }
        for(int i=0 ; i<num_soton ; i++){
            if(soton_position[i][0]==x1 && soton_position[i][1]==y1){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }
        gold_position[num_gold][0] = x1;
        gold_position[num_gold][1] = y1;
        gold_position[num_gold][2]=0;
        gold_position[num_gold][3]=price1;
        num_gold++;
        x2 = (rand() % (room.width-2));
        y2 = (rand() % (room.height-2));
        price2=(rand()%5)+1;
        if(x2==0)
            x2++;
        if(y2==0)
            y2++;
        x2 = room.x + x2 +1; 
        y2 = room.y + y2 +1;
        if((x2==(room.x+1)|| (x2)==room.x+2) && y2==(room.y+room.height-1)){
            x2 += 2;
        }
        for(int i=0 ; i<num_soton ; i++){
            if(soton_position[i][0]==x2 && soton_position[i][1]==y2){
                if(x2 < (room.x+room.width-2)){
                    x2 ++;
                }
                else{
                    x2--;
                }
            }
        }
        gold_position[num_gold][0] = x2;
        gold_position[num_gold][1] = y2;
        gold_position[num_gold][2]=0;
        gold_position[num_gold][3]=price2;
        num_gold++;
}
int tale_position[6][3];
int num_tale=0,speed_tel=0,health_tel=0,strangh_tel=0;
void tale(Room room){
        int x1,y1;
        x1 = (rand() % (room.width-3));
        y1 = (rand() % (room.height-3));
        if (x1 <= 0)
            x1=1;
        if (y1 <= 0)
            y1=1;
        x1 = room.x + x1+1; 
        y1 = room.y + y1+1;
        if((x1==(room.x+1)|| (x1)==room.x+2) && y1==(room.y+room.height-1)){
            x1 += 2;
        }
        for(int i=0 ; i<num_soton ; i++){
            if(soton_position[i][0]==x1 && soton_position[i][1]==y1){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }
        for(int i=0 ; i<num_gold ; i++){
            if(gold_position[i][0]==x1 && gold_position[i][1]==y1){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
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
        if((x1==(room.x+1)|| (x1)==room.x+2) && y1==(room.y+room.height-1)){
            x1 += 2;
        }
        for(int i=0 ; i<num_soton ; i++){
            if(soton_position[i][0]==x1 && soton_position[i][1]==y1){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }  
        for(int i=0 ; i<num_gold ; i++){
            if(gold_position[i][0]==x1 && gold_position[i][1]==y1){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }
        for(int i=0 ; i<num_tale ; i++){
            if(tale_position[i][0]==x1 && tale_position[i][1]==y1){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }
        food_position[num_food][0] = x1;
        food_position[num_food][1] = y1;
        food_position[num_food][2]=0;
        num_food++;
}
int telesm_position[3][4],num_tel=0,tel=0;
void telesm(Room room , int num){
    int x1,y1;
        x1 = (rand() % (room.width-2));
        y1 = (rand() % (room.height-2));
        if(x1<=0)
            x1=1;
        if(y1<=0)
            y1=1;
        x1 = room.x + x1 +1; 
        y1 = room.y + y1 +1;
        if((x1==(room.x+1)|| (x1)==room.x+2) && y1==(room.y+room.height-1)){
            x1 += 2;
        }
        for(int i=0 ; i<num_soton ; i++){
            if(soton_position[i][0]==x1 && soton_position[i][1]==y1){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }
        for(int i=0 ; i<num_gold ; i++){
            if(gold_position[i][0]==x1 && gold_position[i][1]==y1){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }
        for(int i=0 ; i<num_tale ; i++){
            if(tale_position[i][0]==x1 && tale_position[i][1]==y1){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }
        for(int i=0 ; i<num_food ; i++){
            if(food_position[i][0]==x1 && food_position[i][1]==y1){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }
        telesm_position[num_tel][0] = x1;
        telesm_position[num_tel][1] = y1;
        telesm_position[num_tel][2]=num;
        telesm_position[num_tel][3]=0;
        num_tel++;
}
int enemy_position[5][5],num_enemy=0;
void enemy(Room room , int num){
    int x1 , y1;
    x1 = (rand() % (room.width-2));
    y1 = (rand() % (room.height-2));
    if (x1 <= 0)
        x1=1;
    if (y1 <= 0)
        y1=1;
    x1 = room.x + x1+1; 
    y1 = room.y + y1+1;
    if((x1==(room.x+1)|| (x1)==room.x+2) && y1==(room.y+room.height-1)){
            x1 += 2;
        }
        for(int i=0 ; i<num_soton ; i++){
            if(soton_position[i][0]==x1 && soton_position[i][1]==y1){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }  
        for(int i=0 ; i<num_gold ; i++){
            if(gold_position[i][0]==x1 && gold_position[i][1]==y1){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }
        for(int i=0 ; i<num_tale ; i++){
            if(tale_position[i][0]==x1 && tale_position[i][1]==y1){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }
        for(int i=0 ; i<num_food ; i++){
            if(food_position[i][0]==x1 && food_position[i][1]==y1){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }
        enemy_position[num_enemy][0] = x1;
        enemy_position[num_enemy][1] = y1;
        enemy_position[num_enemy][2]=0;
        switch (num)
        {
        case 1:
            enemy_position[num_enemy][3]=5;
            enemy_position[num_enemy][4]=0;
            break;
        case 2:
            enemy_position[num_enemy][3]=10;
            enemy_position[num_enemy][4]=1;
            break;
        case 3:
            enemy_position[num_enemy][3]=15;
            enemy_position[num_enemy][4]=2;
            break;
        case 4:
            enemy_position[num_enemy][3]=20;
            enemy_position[num_enemy][4]=3;
            break;    
        case 5:
            enemy_position[num_enemy][3]=30;
            enemy_position[num_enemy][4]=4;
            break;
        }
        num_enemy++;
}
int tal[5][3],num_tal;
int gol[8][4],num_gol;
void gold_gold(Room room){
    for(int i=0 ; i<8 ; i++){
        int x1,y1,price1;
        x1 = (rand() % (room.width));
        y1 = (rand() % (room.height));
        price1=(rand()%5)+1;
        if(x1==0)
            x1++;
        if(y1==0)
            y1++;
        x1 = room.x + x1; 
        y1 = room.y + y1;
        for(int i=0 ; i<num_gol ; i++){
            if(x1==gol[i][0] && y1==gol[i][1]){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }
        gol[num_gol][0] = x1;
        gol[num_gol][1] = y1;
        gol[num_gol][2]=0;
        gol[num_gol][3]=price1;
        num_gol++;
    }
}
void tal_gold(Room room){
    for(int i=0 ; i<5 ; i++){
        int x1,y1;
        x1 = (rand() % (room.width));
        y1 = (rand() % (room.height));
        if (x1 <= 0)
            x1=1;
        if (y1 <= 0)
            y1=1;
        x1 = room.x + x1; 
        y1 = room.y + y1;
        for(int i=0 ; i<num_gol ; i++){
            if(x1==gol[i][0] && y1==gol[i][1]){
                if(x1 < (room.x+room.width-2)){
                    x1 ++;
                }
                else{
                    x1--;
                }
            }
        }
        tal[num_tal][0] = x1;
        tal[num_tal][1] = y1;
        tal[num_tal][2]=0;
        num_tal++;
    }
}
void draw_room(Room room ,int num) {
    if(fl==3 && num==5){
        attron(COLOR_PAIR(6));
        for (int i = 0; i < room.width; i++) {
            mvprintw(room.y, room.x + i, "_");
            mvprintw(room.y + room.height, room.x + i, "_");
        }
        for (int i = 1; i <= room.height; i++) {
            mvprintw(room.y + i, room.x, "|");
            mvprintw(room.y + i, room.x + room.width, "|");
        }
        attroff(COLOR_PAIR(6));
        attron(COLOR_PAIR(3));
        for (int i = 1; i < room.width; i++) {
            for (int j = 1; j < room.height; j++) {
                mvprintw(room.y + j, room.x + i, ".");
            }
        }
        if(dar_positions[9][2]==0){
            attron(COLOR_PAIR(4));
            mvprintw(dar_positions[2*num-1][1],dar_positions[2*num-1][0],"+");
            mvprintw(dar_positions[2*num][1],dar_positions[2*num][0],">");
            attroff(COLOR_PAIR(4));
            refresh();
        }
        else{
           attron(COLOR_PAIR(1));
            mvprintw(dar_positions[2*num-1][1],dar_positions[2*num-1][0],"+");
            mvprintw(dar_positions[2*num][1],dar_positions[2*num][0],">");
            attroff(COLOR_PAIR(1));
            refresh(); 
        }
        for(int i=0 ; i<num_gol ; i++){
            if(gol[i][2]==0){
                attron(COLOR_PAIR(6));
                mvprintw(gol[i][1],gol[i][0],"\u0454");
                refresh();
                attroff(COLOR_PAIR(6));
            }
            if(gol[i][2]==1){
                attron(COLOR_PAIR(2));
                mvprintw(gol[i][1],gol[i][0],"\u0454");
                refresh();
                attroff(COLOR_PAIR(2));
            }
        }
        for(int i=0 ; i<num_tal ; i++){
            if(tal[i][2]==1){
                attron(COLOR_PAIR(2));
                mvprintw(tal[i][1],tal[i][0],"^");
                refresh();
                attroff(COLOR_PAIR(2));
            }
        }
    }
    else{
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
                if(num ==0 && i==2 && j==(room.height-1) && num==0){
                    mvprintw(room.y + j, room.x + i, " ");
                }
                else{
                    mvprintw(room.y + j, room.x + i, ".");
                }
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
        for(int i=0 ; i<num_lost ; i++){
            attron(COLOR_PAIR(3));
            if(lost_weapon[i][2]==1){
                mvprintw(lost_weapon[i][1],lost_weapon[i][0],".");
                refresh();
            }
            else{
                switch (lost_weapon[i][3])
                {
                case 0:
                    mvprintw(lost_weapon[i][1],lost_weapon[i][0],"\U0001F5E1");
                    break;
                case 1:
                    mvprintw(lost_weapon[i][1],lost_weapon[i][0],"\u16E3");
                    break;
                case 2:
                    mvprintw(lost_weapon[i][1],lost_weapon[i][0],"\u27B3");
                    break;
                }
            }
            attroff(COLOR_PAIR(3));
        }
        if(num>0){
            switch (num)
            {
            case 1:
                if(enemy_position[num-1][2]==2){
                   attron(COLOR_PAIR(2));
                    mvprintw(enemy_position[num-1][1],enemy_position[num-1][0],".");
                    attroff(COLOR_PAIR(2)); 
                    break;
                }
                attron(COLOR_PAIR(2));
                mvprintw(enemy_position[num-1][1],enemy_position[num-1][0],"D");
                attroff(COLOR_PAIR(2));
                break;
            case 2:
                if(enemy_position[num-1][2]==2){
                   attron(COLOR_PAIR(2));
                    mvprintw(enemy_position[num-1][1],enemy_position[num-1][0],".");
                    attroff(COLOR_PAIR(2)); 
                    break;
                }
                attron(COLOR_PAIR(2));
                mvprintw(enemy_position[num-1][1],enemy_position[num-1][0],"F");
                attroff(COLOR_PAIR(2));
                break;
            case 3:
                if(enemy_position[num-1][2]==2){
                   attron(COLOR_PAIR(2));
                    mvprintw(enemy_position[num-1][1],enemy_position[num-1][0],".");
                    attroff(COLOR_PAIR(2)); 
                    break;
                }
                attron(COLOR_PAIR(2));
                mvprintw(enemy_position[num-1][1],enemy_position[num-1][0],"G");
                attroff(COLOR_PAIR(2));
                break;
            case 4:
                if(enemy_position[num-1][2]==2){
                   attron(COLOR_PAIR(2));
                    mvprintw(enemy_position[num-1][1],enemy_position[num-1][0],".");
                    attroff(COLOR_PAIR(2)); 
                    break;
                }
                attron(COLOR_PAIR(2));
                mvprintw(enemy_position[num-1][1],enemy_position[num-1][0],"S");
                attroff(COLOR_PAIR(2));
                break;
            case 5:
                if(enemy_position[num-1][2]==2){
                   attron(COLOR_PAIR(2));
                    mvprintw(enemy_position[num-1][1],enemy_position[num-1][0],".");
                    attroff(COLOR_PAIR(2)); 
                    break;
                }
                attron(COLOR_PAIR(2));
                mvprintw(enemy_position[num-1][1],enemy_position[num-1][0],"U");
                attroff(COLOR_PAIR(2));
                break;
        }
        }
        switch (fl)
        {
        case 1:
            if(weapon_position[1][2]==0)
                mvprintw(weapon_position[1][1],weapon_position[1][0],"\u16E3");
            else{
                attron(COLOR_PAIR(3));
                mvprintw(weapon_position[1][1],weapon_position[1][0],".");
                mvprintw(weapon_position[1][1],weapon_position[1][0]+1,".");
                attroff(COLOR_PAIR(3));
            }
            refresh();
            break;
        
        case 2:
            if(weapon_position[2][2]==0)
                mvprintw(weapon_position[2][1],weapon_position[2][0],"\u27B3");
            else{
                attron(COLOR_PAIR(3));
                mvprintw(weapon_position[2][1],weapon_position[2][0],".");
                mvprintw(weapon_position[2][1],weapon_position[2][0]+1,".");
                attroff(COLOR_PAIR(3));
            }
            refresh();
            break;
        case 3:
            if(weapon_position[3][2]==0)
                mvprintw(weapon_position[3][1],weapon_position[3][0],"\u2694");
            else{
                attron(COLOR_PAIR(3));
                mvprintw(weapon_position[3][1],weapon_position[3][0],".");
                mvprintw(weapon_position[3][1],weapon_position[3][0]+1,".");
                attroff(COLOR_PAIR(3));
            }
            refresh();
            break;
        case 0:
            if(weapon_position[0][2]==0)
                mvprintw(weapon_position[0][1],weapon_position[0][0],"\U0001F5E1");
            else{
                attron(COLOR_PAIR(3));
                mvprintw(weapon_position[0][1],weapon_position[0][0],".");
                mvprintw(weapon_position[0][1],weapon_position[0][0]+1,".");
                attroff(COLOR_PAIR(3));
            }
            refresh();
            break;
        }
            switch (num)
            {
            case 0:
                attron(COLOR_PAIR(1));
                mvprintw(telesm_position[num][1],telesm_position[num][0],"\u22D2");
                attroff(COLOR_PAIR(1));
                break;
            case 2:
                attron(COLOR_PAIR(4));
                mvprintw(telesm_position[num/2][1],telesm_position[num/2][0],"\u0E19");
                attroff(COLOR_PAIR(4));
                break;
            case 4:
                mvprintw(telesm_position[num/2][1],telesm_position[num/2][0],"\u03BB");
                break;
            }
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
        for(int i=0 ; i<num_tel ; i++){
            if(telesm_position[i][3]==1){
                switch (i)
                {
                case 0:
                    attron(COLOR_PAIR(2));
                    mvprintw(telesm_position[i][1],telesm_position[i][0],"\u22D2");
                    attroff(COLOR_PAIR(2));
                    break;
                case 1:
                    attron(COLOR_PAIR(2));
                    mvprintw(telesm_position[i][1],telesm_position[i][0],"\u0E19");
                    attroff(COLOR_PAIR(2));
                    break;
                case 2:
                    attron(COLOR_PAIR(2));
                    mvprintw(telesm_position[i][1],telesm_position[i][0],"\u03BB");
                    attroff(COLOR_PAIR(2));
                    break;
                }
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
    move(35,9); clrtoeol();
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
    switch (current_weapon[0])
    {
    case 4:
        mvprintw(35,55,"weapon: Mace %d",current_weapon[1]);
        break;
    case 5:
        mvprintw(35,55,"weapon: Arrow %d",current_weapon[1]);
        break;    
    case 12:
        mvprintw(35,55,"weapon: Dagger %d",current_weapon[1]);
        break;
    case 15:
        mvprintw(35,55,"weapon: Majic Wand %d",current_weapon[1]);
        break;
    case 10:
        mvprintw(35,55,"weapon: Sword %d",current_weapon[1]);
        break;
    }
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(6));
    mvprintw(35,78,"talisman %d:" , tel);
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
            move(10,79);
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
                            ramz=0;
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
                        ramz=0;
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
    for (int i = 0; i <num_tel; i++) {
        if (x == telesm_position[i][0] && y == telesm_position[i][1]) {
            return 1;
        }
    }
    for (int i = 0; i <num_gol; i++) {
        if (x == gol[i][0] && y == gol[i][1]) {
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
int check(int x , int y, Room room[6]){
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
void check_enemy(int x , int y){
    for(int i=0 ; i<num_enemy ; i++){
            if(enemy_position[i][2]!=2){
                if((x+1)==enemy_position[i][0] && y==enemy_position[i][1]){
                    enemy_position[i][3] = enemy_position[i][3] -current_weapon[0];
                    if(enemy_position[i][3]<0)
                        enemy_position[i][3]=0;
                    switch (enemy_position[i][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d",enemy_position[i][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster,health: %d",enemy_position[i][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant,health: %d",enemy_position[i][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake,health: %d",enemy_position[i][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undeed health: %d",enemy_position[i][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79);clrtoeol();
                }
                else if((x+1)==enemy_position[i][0] && (y+1)==enemy_position[i][1]){
                    enemy_position[i][3] = enemy_position[i][3] - current_weapon[0];
                    if(enemy_position[i][3]<0)
                        enemy_position[i][3]=0;
                    switch (enemy_position[i][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d",enemy_position[i][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster,health: %d",enemy_position[i][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant,health: %d",enemy_position[i][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake,health: %d",enemy_position[i][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undeed health: %d",enemy_position[i][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79);clrtoeol();
                }
                else if((x+1)==enemy_position[i][0] && (y-1)==enemy_position[i][1]){
                    enemy_position[i][3] = enemy_position[i][3] -current_weapon[0];
                    if(enemy_position[i][3]<0)
                        enemy_position[i][3]=0;
                    switch (enemy_position[i][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d",enemy_position[i][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster,health: %d",enemy_position[i][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant,health: %d",enemy_position[i][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake,health: %d",enemy_position[i][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undeed health: %d",enemy_position[i][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79);clrtoeol();
                }
                else if((x)==enemy_position[i][0] && (y+1)==enemy_position[i][1]){
                    enemy_position[i][3] = enemy_position[i][3] -current_weapon[0];
                    if(enemy_position[i][3]<0)
                        enemy_position[i][3]=0;
                    switch (enemy_position[i][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d",enemy_position[i][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster,health: %d",enemy_position[i][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant,health: %d",enemy_position[i][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake,health: %d",enemy_position[i][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undeed health: %d",enemy_position[i][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79);clrtoeol();
                }
                else if((x)==enemy_position[i][0] && (y-1)==enemy_position[i][1]){
                    enemy_position[i][3] = enemy_position[i][3] -current_weapon[0];
                    if(enemy_position[i][3]<0)
                        enemy_position[i][3]=0;
                    switch (enemy_position[i][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d",enemy_position[i][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster,health: %d",enemy_position[i][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant,health: %d",enemy_position[i][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake,health: %d",enemy_position[i][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undeed health: %d",enemy_position[i][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79);clrtoeol();
                }
                else if((x-1)==enemy_position[i][0] && (y+1)==enemy_position[i][1]){
                    enemy_position[i][3] = enemy_position[i][3] -current_weapon[0];
                    if(enemy_position[i][3]<0)
                        enemy_position[i][3]=0;
                    switch (enemy_position[i][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d",enemy_position[i][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster,health: %d",enemy_position[i][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant,health: %d",enemy_position[i][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake,health: %d",enemy_position[i][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undeed health: %d",enemy_position[i][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79);clrtoeol();
                }
                else if((x-1)==enemy_position[i][0] && (y-1)==enemy_position[i][1]){
                    enemy_position[i][3] = enemy_position[i][3] -current_weapon[0];
                    if(enemy_position[i][3]<0)
                        enemy_position[i][3]=0;
                    switch (enemy_position[i][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d",enemy_position[i][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster,health: %d",enemy_position[i][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant,health: %d",enemy_position[i][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake,health: %d",enemy_position[i][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undeed health: %d",enemy_position[i][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79);clrtoeol();
                }
                else if((x-1)==enemy_position[i][0] && (y)==enemy_position[i][1]){
                    enemy_position[i][3] = enemy_position[i][3] -current_weapon[0];
                    if(enemy_position[i][3]<0)
                        enemy_position[i][3]=0;
                    switch (enemy_position[i][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d",enemy_position[i][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster,health: %d",enemy_position[i][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant,health: %d",enemy_position[i][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake,health: %d",enemy_position[i][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undeed health: %d",enemy_position[i][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79);clrtoeol();
                }
                if(enemy_position[i][3]<1){
                    enemy_position[i][2]=2;
                    attron(COLOR_PAIR(3));
                    mvprintw(enemy_position[i][1],enemy_position[i][0],".");
                    attroff(COLOR_PAIR(3));
                    switch (enemy_position[i][4])
                    {
                    case 0:
                        mvprintw(10,80,"You kill deamon.");
                        break;
                    case 1:
                        mvprintw(10,80,"You kill Fire breathing Monster.");
                        break;
                    case 2:
                        mvprintw(10,80,"You kill one Giant.");
                        break;
                    case 3:
                        mvprintw(10,80,"You kill Snake.");
                        break;
                    case 4:
                        mvprintw(10,80,"You kill Undeed.");
                        break;
                    }
                    refresh();
                    sleep(1);
                    move(10,79); clrtoeol();
                    health +=5;
                    if(health>20){
                        health=20;
                    }
                }
            }
    }
}
void check_enemy2(int x , int y , int distance ,Room room[6]){
    int t = 0 ,ch;
    int c = getch();
    refresh();
    switch (c)
    {
    case 'l':
        for(int i=1; i<=distance; i++){
            if(check(x+i , y , room)==0){
                distance=i-1;
                break;
            }
            for(int j=0; j<num_enemy; j++){
                if((x+i) == enemy_position[j][0] && (y) == enemy_position[j][1] && enemy_position[j][2] != 2){
                    t++;
                    enemy_position[j][3] -= current_weapon[0];
                    if(enemy_position[j][3] < 0)
                        enemy_position[j][3] = 0;
                    switch (enemy_position[j][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d", enemy_position[j][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster, health: %d", enemy_position[j][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant, health: %d", enemy_position[j][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake, health: %d", enemy_position[j][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undead, health: %d", enemy_position[j][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79); clrtoeol();
                    if(enemy_position[j][3] < 1){
                        enemy_position[j][2] = 2;
                        attron(COLOR_PAIR(3));
                        mvprintw(enemy_position[j][1], enemy_position[j][0], ".");
                        attroff(COLOR_PAIR(3));
                        switch (enemy_position[j][4])
                        {
                        case 0:
                            mvprintw(10,80,"You kill deamon.");
                            break;
                        case 1:
                            mvprintw(10,80,"You kill Fire breathing Monster.");
                            break;
                        case 2:
                            mvprintw(10,80,"You kill one Giant.");
                            break;
                        case 3:
                            mvprintw(10,80,"You kill Snake.");
                            break;
                        case 4:
                            mvprintw(10,80,"You kill Undead.");
                            break;
                        }
                        refresh();
                        sleep(1);
                        move(10,79); clrtoeol();
                        health += 5;
                        if(health > 20){
                            health = 20;
                        }
                    }
                    current_weapon[1]--;
                    switch (current_weapon[0])
                    {
                    case 12:
                        weapon_position[0][4]--;
                        break;
                    case 15:
                        weapon_position[1][4]--;
                        break;
                    case 5:
                        weapon_position[2][4]--;
                        break;
                    }
                    break;
                }
                if(t>0)
                    break;
            }
            if(t>0)
                break;
        }
        if(t > 0){
                t = 0;
                break;
            }
            else {
                mvprintw(10,80,"you miss.");
                refresh();
                sleep(1.5);
                move(10,79); clrtoeol();
                lost_weapon[num_lost][0] = (x + distance);
                lost_weapon[num_lost][1] = (y);
                attron(COLOR_PAIR(3));
                switch (current_weapon[0])
                {
                case 12:
                    lost_weapon[num_lost][3] = 0;
                    current_weapon[1]--;
                    weapon_position[0][4]--;
                     mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\U0001F5E1");
                    break;
                case 15:
                    lost_weapon[num_lost][3] = 1;
                    current_weapon[1]--;
                    weapon_position[1][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u16E3");
                    break;
                case 5:
                    lost_weapon[num_lost][3] = 2;
                    current_weapon[1]--;
                    weapon_position[2][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u27B3");
                    break;
                }
                attroff(COLOR_PAIR(3));
                refresh();
                num_lost++;
            }
        break;
    case 'k':
        for(int i=1; i<=distance; i++){
            if(check(x , y+i , room)==0){
                distance=i-1;
                break;
            }
            for(int j=0; j<num_enemy; j++){
                if((x) == enemy_position[j][0] && (y+i) == enemy_position[j][1] && enemy_position[j][2] != 2){
                    t++;
                    enemy_position[j][3] -= current_weapon[0];
                    if(enemy_position[j][3] < 0)
                        enemy_position[j][3] = 0;
                    switch (enemy_position[j][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d", enemy_position[j][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster, health: %d", enemy_position[j][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant, health: %d", enemy_position[j][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake, health: %d", enemy_position[j][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undead, health: %d", enemy_position[j][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79); clrtoeol();
                    if(enemy_position[j][3] < 1){
                        enemy_position[j][2] = 2;
                        attron(COLOR_PAIR(3));
                        mvprintw(enemy_position[j][1], enemy_position[j][0], ".");
                        attroff(COLOR_PAIR(3));
                        switch (enemy_position[j][4])
                        {
                        case 0:
                            mvprintw(10,80,"You kill deamon.");
                            break;
                        case 1:
                            mvprintw(10,80,"You kill Fire breathing Monster.");
                            break;
                        case 2:
                            mvprintw(10,80,"You kill one Giant.");
                            break;
                        case 3:
                            mvprintw(10,80,"You kill Snake.");
                            break;
                        case 4:
                            mvprintw(10,80,"You kill Undead.");
                            break;
                        }
                        refresh();
                        sleep(1);
                        move(10,79); clrtoeol();
                        health += 5;
                        if(health > 20){
                            health = 20;
                        }
                    }
                    current_weapon[1]--;
                    switch (current_weapon[0])
                    {
                    case 12:
                        weapon_position[0][4]--;
                        break;
                    case 15:
                        weapon_position[1][4]--;
                        break;
                    case 5:
                        weapon_position[2][4]--;
                        break;
                    }
                    break;
                }
                if(t>0)
                    break;
            }
            if(t>0)
                break;
        }
        if(t > 0){
                t = 0;
                break;
            }
            else {
                mvprintw(10,80,"you miss.");
                refresh();
                sleep(1.5);
                move(10,79); clrtoeol();
                lost_weapon[num_lost][0] = (x);
                lost_weapon[num_lost][1] = (y + distance);
                attron(COLOR_PAIR(3));
                switch (current_weapon[0])
                {
                case 12:
                    lost_weapon[num_lost][3] = 0;
                    current_weapon[1]--;
                    weapon_position[0][4]--;
                     mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\U0001F5E1");
                    break;
                case 15:
                    lost_weapon[num_lost][3] = 1;
                    current_weapon[1]--;
                    weapon_position[1][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u16E3");
                    break;
                case 5:
                    lost_weapon[num_lost][3] = 2;
                    current_weapon[1]--;
                    weapon_position[2][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u27B3");
                    break;
                }
                attroff(COLOR_PAIR(3));
                refresh();
                num_lost++;
            }
        break;
        case 'j':
        for(int i=1; i<=distance; i++){
            if(check(x , y-i , room)==0){
                distance=i-1;
                break;
            }
            for(int j=0; j<num_enemy; j++){
                if((x) == enemy_position[j][0] && (y-i) == enemy_position[j][1] && enemy_position[j][2] != 2){
                    t++;
                    enemy_position[j][3] -= current_weapon[0];
                    if(enemy_position[j][3] < 0)
                        enemy_position[j][3] = 0;
                    switch (enemy_position[j][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d", enemy_position[j][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster, health: %d", enemy_position[j][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant, health: %d", enemy_position[j][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake, health: %d", enemy_position[j][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undead, health: %d", enemy_position[j][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79); clrtoeol();
                    if(enemy_position[j][3] < 1){
                        enemy_position[j][2] = 2;
                        attron(COLOR_PAIR(3));
                        mvprintw(enemy_position[j][1], enemy_position[j][0], ".");
                        attroff(COLOR_PAIR(3));
                        switch (enemy_position[j][4])
                        {
                        case 0:
                            mvprintw(10,80,"You kill deamon.");
                            break;
                        case 1:
                            mvprintw(10,80,"You kill Fire breathing Monster.");
                            break;
                        case 2:
                            mvprintw(10,80,"You kill one Giant.");
                            break;
                        case 3:
                            mvprintw(10,80,"You kill Snake.");
                            break;
                        case 4:
                            mvprintw(10,80,"You kill Undead.");
                            break;
                        }
                        refresh();
                        sleep(1);
                        move(10,79); clrtoeol();
                        health += 5;
                        if(health > 20){
                            health = 20;
                        }
                    }
                    current_weapon[1]--;
                    switch (current_weapon[0])
                    {
                    case 12:
                        weapon_position[0][4]--;
                        break;
                    case 15:
                        weapon_position[1][4]--;
                        break;
                    case 5:
                        weapon_position[2][4]--;
                        break;
                    }
                    break;
                }
                if(t>0)
                    break;
            }
            if(t>0)
                break;
        }
        if(t > 0){
                t = 0;
                break;
            }
            else {
                mvprintw(10,80,"you miss.");
                refresh();
                sleep(1.5);
                move(10,79); clrtoeol();
                lost_weapon[num_lost][0] = (x);
                lost_weapon[num_lost][1] = (y -distance);
                attron(COLOR_PAIR(3));
                switch (current_weapon[0])
                {
                case 12:
                    lost_weapon[num_lost][3] = 0;
                    current_weapon[1]--;
                    weapon_position[0][4]--;
                     mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\U0001F5E1");
                    break;
                case 15:
                    lost_weapon[num_lost][3] = 1;
                    current_weapon[1]--;
                    weapon_position[1][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u16E3");
                    break;
                case 5:
                    lost_weapon[num_lost][3] = 2;
                    current_weapon[1]--;
                    weapon_position[2][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u27B3");
                    break;
                }
                attroff(COLOR_PAIR(3));
                refresh();
                num_lost++;
            }
        break;
    case 'h':
        for(int i=1; i<=distance; i++){
            if(check(x-i , y , room)==0){
                distance=i-1;
                break;
            }
            for(int j=0; j<num_enemy; j++){
                if((x-i) == enemy_position[j][0] && (y) == enemy_position[j][1] && enemy_position[j][2] != 2){
                    t++;
                    enemy_position[j][3] -= current_weapon[0];
                    if(enemy_position[j][3] < 0)
                        enemy_position[j][3] = 0;
                    switch (enemy_position[j][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d", enemy_position[j][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster, health: %d", enemy_position[j][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant, health: %d", enemy_position[j][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake, health: %d", enemy_position[j][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undead, health: %d", enemy_position[j][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79); clrtoeol();
                    if(enemy_position[j][3] < 1){
                        enemy_position[j][2] = 2;
                        attron(COLOR_PAIR(3));
                        mvprintw(enemy_position[j][1], enemy_position[j][0], ".");
                        attroff(COLOR_PAIR(3));
                        switch (enemy_position[j][4])
                        {
                        case 0:
                            mvprintw(10,80,"You kill deamon.");
                            break;
                        case 1:
                            mvprintw(10,80,"You kill Fire breathing Monster.");
                            break;
                        case 2:
                            mvprintw(10,80,"You kill one Giant.");
                            break;
                        case 3:
                            mvprintw(10,80,"You kill Snake.");
                            break;
                        case 4:
                            mvprintw(10,80,"You kill Undead.");
                            break;
                        }
                        refresh();
                        sleep(1);
                        move(10,79); clrtoeol();
                        health += 5;
                        if(health > 20){
                            health = 20;
                        }
                    }
                    current_weapon[1]--;
                    switch (current_weapon[0])
                    {
                    case 12:
                        weapon_position[0][4]--;
                        break;
                    case 15:
                        weapon_position[1][4]--;
                        break;
                    case 5:
                        weapon_position[2][4]--;
                        break;
                    }
                    break;
                }
                if(t>0)
                    break;
            }
            if(t>0)
                break;
        }
        if(t > 0){
                t = 0;
                break;
            }
            else {
                mvprintw(10,80,"you miss.");
                refresh();
                sleep(1.5);
                move(10,79); clrtoeol();
                lost_weapon[num_lost][0] = (x - distance);
                lost_weapon[num_lost][1] = (y);
                attron(COLOR_PAIR(3));
                switch (current_weapon[0])
                {
                case 12:
                    lost_weapon[num_lost][3] = 0;
                    current_weapon[1]--;
                    weapon_position[0][4]--;
                     mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\U0001F5E1");
                    break;
                case 15:
                    lost_weapon[num_lost][3] = 1;
                    current_weapon[1]--;
                    weapon_position[1][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u16E3");
                    break;
                case 5:
                    lost_weapon[num_lost][3] = 2;
                    current_weapon[1]--;
                    weapon_position[2][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u27B3");
                    break;
                }
                attroff(COLOR_PAIR(3));
                refresh();
                num_lost++;
            }
        break;
    case 'y':
        for(int i=1; i<=distance; i++){
            if(check(x-i , y-i , room)==0){
                distance=i-1;
                break;
            }
            for(int j=0; j<num_enemy; j++){
                if((x-i) == enemy_position[j][0] && (y-i) == enemy_position[j][1] && enemy_position[j][2] != 2){
                    t++;
                    enemy_position[j][3] -= current_weapon[0];
                    if(enemy_position[j][3] < 0)
                        enemy_position[j][3] = 0;
                    switch (enemy_position[j][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d", enemy_position[j][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster, health: %d", enemy_position[j][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant, health: %d", enemy_position[j][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake, health: %d", enemy_position[j][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undead, health: %d", enemy_position[j][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79); clrtoeol();
                    if(enemy_position[j][3] < 1){
                        enemy_position[j][2] = 2;
                        attron(COLOR_PAIR(3));
                        mvprintw(enemy_position[j][1], enemy_position[j][0], ".");
                        attroff(COLOR_PAIR(3));
                        switch (enemy_position[j][4])
                        {
                        case 0:
                            mvprintw(10,80,"You kill deamon.");
                            break;
                        case 1:
                            mvprintw(10,80,"You kill Fire breathing Monster.");
                            break;
                        case 2:
                            mvprintw(10,80,"You kill one Giant.");
                            break;
                        case 3:
                            mvprintw(10,80,"You kill Snake.");
                            break;
                        case 4:
                            mvprintw(10,80,"You kill Undead.");
                            break;
                        }
                        refresh();
                        sleep(1);
                        move(10,79); clrtoeol();
                        health += 5;
                        if(health > 20){
                            health = 20;
                        }
                    }
                    current_weapon[1]--;
                    switch (current_weapon[0])
                    {
                    case 12:
                        weapon_position[0][4]--;
                        break;
                    case 15:
                        weapon_position[1][4]--;
                        break;
                    case 5:
                        weapon_position[2][4]--;
                        break;
                    }
                    break;
                }
                if(t>0)
                    break;
            }
            if(t>0)
                break;
        }
        if(t > 0){
                t = 0;
                break;
            }
            else {
                mvprintw(10,80,"you miss.");
                refresh();
                sleep(1.5);
                move(10,79); clrtoeol();
                lost_weapon[num_lost][0] = (x - distance);
                lost_weapon[num_lost][1] = (y - distance);
                attron(COLOR_PAIR(3));
                switch (current_weapon[0])
                {
                case 12:
                    lost_weapon[num_lost][3] = 0;
                     mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\U0001F5E1");
                    break;
                case 15:
                    lost_weapon[num_lost][3] = 1;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u16E3");
                    break;
                case 5:
                    lost_weapon[num_lost][3] = 2;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u27B3");
                    break;
                }
                attroff(COLOR_PAIR(3));
                refresh();
                num_lost++;
            }
        break;
    case 'u':
        for(int i=1; i<=distance; i++){
            if(check(x+i , y-i , room)==0){
                distance=i-1;
                break;
            }
            for(int j=0; j<num_enemy; j++){
                if((x+i) == enemy_position[j][0] && (y-i) == enemy_position[j][1] && enemy_position[j][2] != 2){
                    t++;
                    enemy_position[j][3] -= current_weapon[0];
                    if(enemy_position[j][3] < 0)
                        enemy_position[j][3] = 0;
                    switch (current_weapon[0])
                {
                case 12:
                    lost_weapon[num_lost][3] = 0;
                    current_weapon[1]--;
                    weapon_position[0][4]--;
                     mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\U0001F5E1");
                    break;
                case 15:
                    lost_weapon[num_lost][3] = 1;
                    current_weapon[1]--;
                    weapon_position[1][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u16E3");
                    break;
                case 5:
                    lost_weapon[num_lost][3] = 2;
                    current_weapon[1]--;
                    weapon_position[2][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u27B3");
                    break;
                }
                    refresh();
                    sleep(1.5);
                    move(10,79); clrtoeol();
                    if(enemy_position[j][3] < 1){
                        enemy_position[j][2] = 2;
                        attron(COLOR_PAIR(3));
                        mvprintw(enemy_position[j][1], enemy_position[j][0], ".");
                        attroff(COLOR_PAIR(3));
                        switch (enemy_position[j][4])
                        {
                        case 0:
                            mvprintw(10,80,"You kill deamon.");
                            break;
                        case 1:
                            mvprintw(10,80,"You kill Fire breathing Monster.");
                            break;
                        case 2:
                            mvprintw(10,80,"You kill one Giant.");
                            break;
                        case 3:
                            mvprintw(10,80,"You kill Snake.");
                            break;
                        case 4:
                            mvprintw(10,80,"You kill Undead.");
                            break;
                        }
                        refresh();
                        sleep(1);
                        move(10,79); clrtoeol();
                        health += 5;
                        if(health > 20){
                            health = 20;
                        }
                    }
                    current_weapon[1]--;
                    switch (current_weapon[0])
                    {
                    case 12:
                        weapon_position[0][4]--;
                        break;
                    case 15:
                        weapon_position[1][4]--;
                        break;
                    case 5:
                        weapon_position[2][4]--;
                        break;
                    }
                    break;
                }
                if(t>0)
                    break;
            }
            if(t>0)
                break;
        }
        if(t > 0){
                t = 0;
                break;
            }
            else {
                mvprintw(10,80,"you miss.");
                refresh();
                sleep(1.5);
                move(10,79); clrtoeol();
                lost_weapon[num_lost][0] = (x + distance);
                lost_weapon[num_lost][1] = (y - distance);
                attron(COLOR_PAIR(3));
                switch (current_weapon[0])
                {
                case 12:
                    lost_weapon[num_lost][3] = 0;
                    current_weapon[1]--;
                    weapon_position[0][4]--;
                     mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\U0001F5E1");
                    break;
                case 15:
                    lost_weapon[num_lost][3] = 1;
                    current_weapon[1]--;
                    weapon_position[1][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u16E3");
                    break;
                case 5:
                    lost_weapon[num_lost][3] = 2;
                    current_weapon[1]--;
                    weapon_position[2][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u27B3");
                    break;
                }
                attroff(COLOR_PAIR(3));
                refresh();
                num_lost++;
            }
        break;
    case 'b':
        for(int i=1; i<=distance; i++){
            if(check(x-i , y+i , room)==0){
                distance=i-1;
                break;
            }
            for(int j=0; j<num_enemy; j++){
                if((x-i) == enemy_position[j][0] && (y+i) == enemy_position[j][1] && enemy_position[j][2] != 2){
                    t++;
                    enemy_position[j][3] -= current_weapon[0];
                    if(enemy_position[j][3] < 0)
                        enemy_position[j][3] = 0;
                    switch (enemy_position[j][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d", enemy_position[j][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster, health: %d", enemy_position[j][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant, health: %d", enemy_position[j][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake, health: %d", enemy_position[j][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undead, health: %d", enemy_position[j][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79); clrtoeol();
                    if(enemy_position[j][3] < 1){
                        enemy_position[j][2] = 2;
                        attron(COLOR_PAIR(3));
                        mvprintw(enemy_position[j][1], enemy_position[j][0], ".");
                        attroff(COLOR_PAIR(3));
                        switch (enemy_position[j][4])
                        {
                        case 0:
                            mvprintw(10,80,"You kill deamon.");
                            break;
                        case 1:
                            mvprintw(10,80,"You kill Fire breathing Monster.");
                            break;
                        case 2:
                            mvprintw(10,80,"You kill one Giant.");
                            break;
                        case 3:
                            mvprintw(10,80,"You kill Snake.");
                            break;
                        case 4:
                            mvprintw(10,80,"You kill Undead.");
                            break;
                        }
                        refresh();
                        sleep(1);
                        move(10,79); clrtoeol();
                        health += 5;
                        if(health > 20){
                            health = 20;
                        }
                    }
                    current_weapon[1]--;
                    switch (current_weapon[0])
                    {
                    case 12:
                        weapon_position[0][4]--;
                        break;
                    case 15:
                        weapon_position[1][4]--;
                        break;
                    case 5:
                        weapon_position[2][4]--;
                        break;
                    }
                    break;
                }
                if(t>0)
                    break;
            }
            if(t>0)
                break;
        }
        if(t > 0){
                t = 0;
                break;
            }
            else {
                mvprintw(10,80,"you miss.");
                refresh();
                sleep(1.5);
                move(10,79); clrtoeol();
                lost_weapon[num_lost][0] = (x - distance);
                lost_weapon[num_lost][1] = (y + distance);
                attron(COLOR_PAIR(3));
                switch (current_weapon[0])
                {
                case 12:
                    lost_weapon[num_lost][3] = 0;
                    current_weapon[1]--;
                    weapon_position[0][4]--;
                     mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\U0001F5E1");
                    break;
                case 15:
                    lost_weapon[num_lost][3] = 1;
                    current_weapon[1]--;
                    weapon_position[1][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u16E3");
                    break;
                case 5:
                    lost_weapon[num_lost][3] = 2;
                    current_weapon[1]--;
                    weapon_position[2][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u27B3");
                    break;
                }
                attroff(COLOR_PAIR(3));
                refresh();
                num_lost++;
            }
        break;
    case 'n':
        for(int i=1; i<=distance; i++){
            if(check(x+i , y+i , room)==0){
                distance=i-1;
                break;
            }
            for(int j=0; j<num_enemy; j++){
                if((x+i) == enemy_position[j][0] && (y+i) == enemy_position[j][1] && enemy_position[j][2] != 2){
                    t++;
                    enemy_position[j][3] -= current_weapon[0];
                    if(enemy_position[j][3] < 0)
                        enemy_position[j][3] = 0;
                    switch (enemy_position[j][4])
                    {
                    case 0:
                        mvprintw(10,80,"You beat deamon, health: %d", enemy_position[j][3]);
                        break;
                    case 1:
                        mvprintw(10,80,"You beat Fire breathing Monster, health: %d", enemy_position[j][3]);
                        break;
                    case 2:
                        mvprintw(10,80,"You beat one Giant, health: %d", enemy_position[j][3]);
                        break;
                    case 3:
                        mvprintw(10,80,"You beat Snake, health: %d", enemy_position[j][3]);
                        break;
                    case 4:
                        mvprintw(10,80,"You beat Undead, health: %d", enemy_position[j][3]);
                        break;
                    }
                    refresh();
                    sleep(1.5);
                    move(10,79); clrtoeol();
                    if(enemy_position[j][3] < 1){
                        enemy_position[j][2] = 2;
                        attron(COLOR_PAIR(3));
                        mvprintw(enemy_position[j][1], enemy_position[j][0], ".");
                        attroff(COLOR_PAIR(3));
                        switch (enemy_position[j][4])
                        {
                        case 0:
                            mvprintw(10,80,"You kill deamon.");
                            break;
                        case 1:
                            mvprintw(10,80,"You kill Fire breathing Monster.");
                            break;
                        case 2:
                            mvprintw(10,80,"You kill one Giant.");
                            break;
                        case 3:
                            mvprintw(10,80,"You kill Snake.");
                            break;
                        case 4:
                            mvprintw(10,80,"You kill Undead.");
                            break;
                        }
                        refresh();
                        sleep(1);
                        move(10,79); clrtoeol();
                        health += 5;
                        if(health > 20){
                            health = 20;
                        }
                    }
                    current_weapon[1]--;
                    switch (current_weapon[0])
                    {
                    case 12:
                        weapon_position[0][4]--;
                        break;
                    case 15:
                        weapon_position[1][4]--;
                        break;
                    case 5:
                        weapon_position[2][4]--;
                        break;
                    }
                    break;
                }
                if(t>0)
                    break;
            }
            if(t>0)
                break;
        }
        if(t > 0){
                t = 0;
                break;
            }
            else {
                mvprintw(10,80,"you miss.");
                refresh();
                sleep(1.5);
                move(10,79); clrtoeol();
                lost_weapon[num_lost][0] = (x + distance);
                lost_weapon[num_lost][1] = (y + distance);
                attron(COLOR_PAIR(3));
                switch (current_weapon[0])
                {
                case 12:
                    lost_weapon[num_lost][3] = 0;
                    current_weapon[1]--;
                    weapon_position[0][4]--;
                     mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\U0001F5E1");
                    break;
                case 15:
                    lost_weapon[num_lost][3] = 1;
                    current_weapon[1]--;
                    weapon_position[1][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u16E3");
                    break;
                case 5:
                    lost_weapon[num_lost][3] = 2;
                    current_weapon[1]--;
                    weapon_position[2][4]--;
                    mvprintw(lost_weapon[num_lost][1],lost_weapon[num_lost][0],"\u27B3");
                    break;
                }
                attroff(COLOR_PAIR(3));
                refresh();
                num_lost++;
            }
        break;
    }
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
            mvprintw(newy,newx,"\u03BB");
            break;
        case 's':
            clear();
            for(int i=0 ; i<=(numroom+1) ; i++){
                if(i==6){
                    break;
                }
                draw_room(room[i],i);
                refresh();
            }
            draw_page();
            refresh();
            for(int i=0 ; i<=(numroom+1) ; i++){
                if(i==6){
                    break;
                }
                if(tale_position[i][2]==0){
                    attron(COLOR_PAIR(2));
                    mvprintw(tale_position[i][1],tale_position[i][0],"^");
                    refresh();
                    attroff(COLOR_PAIR(2));
                }
            }
            if(numroom==5){
                for(int i=0 ; i<num_tal ; i++){
                    if(tal[i][2]==0){
                    attron(COLOR_PAIR(2));
                    mvprintw(tal[i][1],tal[i][0],"^");
                    refresh();
                    attroff(COLOR_PAIR(2));
                }
                }
            }
            for(int i=0 ; i<(numroom+1) ; i++){
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
            mvprintw(newy,newx,"\u03BB");
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
                mvprintw(31,80,"    enter your choise:");
                refresh();
                move(31,103);
                clrtoeol();
                int d;
                while (1)
                {
                    move(31,105);
                    scanw("%d",&d);
                    mvprintw(31,105,"%d",d);
                    if((d>0 && d<=nf) || d==10){
                        break;
                    }
                    else{
                        move(10,79);clrtoeol();
                        move(31,103);clrtoeol();
                        mvprintw(10,80,"Choose correct food!");
                        refresh();
                    }
                }
                move(10,79);
                clrtoeol();
                if(d==10){
                    break;
                }
                else if(nf==0){
                    mvprintw(10,80,"You don't have food.");
                    sleep(1);
                    move(10,70);
                    clrtoeol();
                    break;
                }
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
                move(10,79);
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
        case 'r':
            int d;
            while(1){
                for(int i=27 ; i<32 ; i++){
                    move(i,79);
                    clrtoeol();
                }
                attron(COLOR_PAIR(7));
                mvprintw(27,80,"1. %d of health Talisman.",health_tel);
                mvprintw(28,80,"2. %d of speed Talisman.",speed_tel);
                mvprintw(29,80,"3. %d of strength Talisman.",strangh_tel);
                mvprintw(30,80,"   choose your talisman:");
                mvprintw(31,80," press 10 to return the game.");
                refresh();
                attroff(COLOR_PAIR(7));
                move(30,105);
                echo();
                scanw("%d",&d);
                noecho();
                if(d==10){
                    for(int i=27 ; i<32 ; i++){
                        move(i,79);
                        clrtoeol();
                    }
                    break;
                }
                if(d==1){
                    if(health_tel>0){
                        attron(COLOR_PAIR(1));
                        mvprintw(10,80,"You use health Talisman.");
                        attroff(COLOR_PAIR(1));
                        health_tel --;
                        refresh();
                        tel --;
                        health=20;
                    }
                    else{
                        attron(COLOR_PAIR(2));
                        mvprintw(10,80,"You don't have health Talisman.");
                        attroff(COLOR_PAIR(2));
                    }
                }
                if(d==2){
                    if(speed_tel>0){
                        attron(COLOR_PAIR(1));
                        mvprintw(10,80,"You use speed Talisman.");
                        attroff(COLOR_PAIR(1));
                        speed_tel --;
                        refresh();
                        tel --;
                    }
                    else{
                        attron(COLOR_PAIR(2));
                        mvprintw(10,80,"You don't have speed Talisman.");
                        attroff(COLOR_PAIR(2));
                    }
                }
                if(d==3){
                    if(strangh_tel>0){
                        attron(COLOR_PAIR(1));
                        mvprintw(10,80,"You use strength Talisman.");
                        attroff(COLOR_PAIR(1));
                        strangh_tel --;
                        refresh();
                        tel --;
                        current_weapon[1]=current_weapon[1]*2;
                        switch (current_weapon[0])
                        {
                        case 12:
                            weapon_position[0][4] *=2;
                            break;
                        
                        case 15:
                            weapon_position[1][4] *=2;
                            break;
                        case 5:
                            weapon_position[2][4] *=2;
                            break;
                        }
                    }
                    else{
                        attron(COLOR_PAIR(2));
                        mvprintw(10,80,"You don't have strength Talisman.");
                        attroff(COLOR_PAIR(2));
                    }
                }
                if(d>3){
                    attron(COLOR_PAIR(2));
                    mvprintw(10,80,"Choose correct!.");
                    attroff(COLOR_PAIR(2));
                }
                refresh();
                draw_page();
                sleep(1);
                move(10,79);
                clrtoeol();
            }
            move(10,79);
            clrtoeol();
            for(int i=27 ; i<32 ; i++){
                move(i,79);
                clrtoeol();
            }
            refresh();
            break;
        case 'i':
            clear();
            mvprintw(5,5,"1.Mace  : power=4   short_rang     number: 1");
            mvprintw(7,5,"2.Sword : power=10  short_rang     number: %d",weapon_position[3][4]);
            mvprintw(5,60,"3.Dagger     : power=12  long_rang(5)   number: %d",weapon_position[0][4]);
            mvprintw(7,60,"4.Magic Wand : power=15  long_rang(10)   number: %d",weapon_position[1][4]);
            mvprintw(9,60,"5.Arrow      : power=5   long_rang(5)   number: %d",weapon_position[2][4]);
            mvprintw(15,30,"press 10 to back the game.");
            mvprintw(16,30,"     Your choose:");
            refresh();
            int ch;
            while(1){
                move(13,29);
                clrtoeol();
                echo();
                move(16,50);
                clrtoeol();
                scanw("%d",&ch);
                noecho();
                if(ch==10){
                    break;
                }
                switch (ch)
                {
                case 1:
                    current_weapon[0]=4;
                    current_weapon[1]=1;
                    attron(COLOR_PAIR(1));
                    mvprintw(2,30,"your current weapon change to Mace.");
                    attroff(COLOR_PAIR(1));
                    break;
                case 2:
                    if(weapon_position[3][4]!=0){
                        current_weapon[0]=10;
                        current_weapon[1]=1;
                        attron(COLOR_PAIR(1));
                        mvprintw(2,30,"your current weapon change to Sword.");
                        attroff(COLOR_PAIR(1));
                    }
                    else{
                        attron(COLOR_PAIR(2));
                        mvprintw(13,30,"You don't have this weapon.");
                        attroff(COLOR_PAIR(2));
                        refresh();
                    }
                    break;
                case 3:
                    if(weapon_position[0][4]!=0){
                        current_weapon[0]=12;
                        current_weapon[1]=weapon_position[0][4];
                        attron(COLOR_PAIR(1));
                        mvprintw(2,30,"your current weapon change to Dagger.");
                        attroff(COLOR_PAIR(1));
                    }
                    else{
                        attron(COLOR_PAIR(2));
                        mvprintw(13,30,"You don't have this weapon.");
                        attroff(COLOR_PAIR(2));
                        refresh();
                    }
                    break;
                case 4:
                    if(weapon_position[1][4]!=0){
                        current_weapon[0]=15;
                        current_weapon[1]=weapon_position[1][4];
                        attron(COLOR_PAIR(1));
                        mvprintw(2,30,"your current weapon change to Majic Wand.");
                        attroff(COLOR_PAIR(1));
                    }
                    else{
                        attron(COLOR_PAIR(2));
                        mvprintw(13,30,"You don't have this weapon.");
                        refresh();
                        attroff(COLOR_PAIR(2));
                    }
                    break;
                case 5:
                    if(weapon_position[2][4]!=0){
                        current_weapon[0]=5;
                        current_weapon[1]=weapon_position[2][4];
                        attron(COLOR_PAIR(1));
                        mvprintw(2,30,"your current weapon change to Arrow.");
                        attroff(COLOR_PAIR(1));
                    }
                    else{
                        attron(COLOR_PAIR(2));
                        mvprintw(13,30,"You don't have this weapon.");
                        attroff(COLOR_PAIR(2));
                        refresh();
                    }
                    break;
                default:
                    move(13,29);
                    clrtoeol();
                    mvprintw(13,30,"Invalid choise.");
                    break;
                }
                sleep(1);
            }
            clear();
            for(int i=0 ; i<6 ; i++){
                if(room[i].hide==1){
                    draw_room(room[i],i);
                }
            }
            for(int i=0 ; i<num_path ; i++){
                if(path_position[i][2]==1){
                    attron(COLOR_PAIR(1));
                    mvprintw(path_position[i][1],path_position[i][0],"#");
                    attroff(COLOR_PAIR(1));
                }
                refresh();
            }
            break;
        case ' ':
            switch (current_weapon[0])
            {
            case 4:
                check_enemy(*x , *y);
                break;
            case 10:
                check_enemy(*x , *y);
                break;
            case 12:
                if(current_weapon[1]==0){
                    mvprintw(10,80,"You don't have enough weapon!");
                    break;
                }
                check_enemy2(*x , *y , 5 , room);
            break;
            case 15:
                if(current_weapon[1]==0){
                    mvprintw(10,80,"You don't have enough weapon!");
                    break;
                }
                check_enemy2(*x , *y , 10 , room);
            break;
            case 5:
                if(current_weapon[1]==0){
                    mvprintw(10,80,"You don't have enough weapon!");
                    break;
                }
                check_enemy2(*x , *y , 5 , room);
            break;
            }
            break;
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
            fprintf(file,"%d\n",fl);
            for(int i=0 ; i<6 ; i++){
                fprintf(file,"%d %d %d %d %d\n",room[i].x,room[i].y,room[i].width,room[i].height,room[i].hide);
            }
            fprintf(file,"%d\n",num_dar);
            for(int i=0 ; i<num_dar ; i++){
                fprintf(file,"%d %d %d\n",dar_positions[i][0],dar_positions[i][1],dar_positions[i][2]);
            }
            fprintf(file,"%d\n",num_soton);
            for(int i=0 ; i<num_soton ; i++){
                fprintf(file,"%d %d %d\n",soton_position[i][0],soton_position[i][1],soton_position[i][2]);
            }
            fprintf(file,"%d\n",num_gold);
            for(int i=0 ; i<num_gold ; i++){
                fprintf(file,"%d %d %d %d\n",gold_position[i][0],gold_position[i][1],gold_position[i][2],gold_position[i][3]);
            }
            fprintf(file,"%d\n",num_gol);
            for(int i=0 ; i<num_gol ; i++){
                fprintf(file,"%d %d %d %d\n",gol[i][0],gol[i][1],gol[i][2],gol[i][3]);
            }
            fprintf(file,"%d\n",num_tale);
            for(int i=0 ; i<num_tale ; i++){
                fprintf(file,"%d %d %d\n",tale_position[i][0],tale_position[i][1],tale_position[i][2]);
            }
            fprintf(file,"%d\n",num_tal);
            for(int i=0 ; i<num_tal ; i++){
                fprintf(file,"%d %d %d\n",tal[i][0],tal[i][1],tal[i][2]);
            }
            fprintf(file,"%d\n",num_food);
            for(int i=0 ; i<num_food ; i++){
                fprintf(file,"%d %d %d\n",food_position[i][0],food_position[i][1],food_position[i][2]);
            }
            fprintf(file,"%d\n",num_path);
            for(int i=0 ; i<num_path ; i++){
                fprintf(file,"%d %d %d\n",path_position[i][0],path_position[i][1],path_position[i][2]);
            }
            fprintf(file,"%d\n",num_tel);
            for(int i=0 ; i<num_tel ; i++){
                fprintf(file,"%d %d %d %d\n",telesm_position[i][0],telesm_position[i][1],telesm_position[i][2],telesm_position[i][3]);
            }
            fprintf(file,"%d\n",num_enemy);
            for(int i=0 ; i<num_enemy ; i++){
                fprintf(file,"%d %d %d %d\n",enemy_position[i][0],enemy_position[i][1],enemy_position[i][2],enemy_position[i][3]);
            }
            fprintf(file,"%d\n",num_weapon);
            for(int i=0 ; i<num_weapon ; i++){
                fprintf(file,"%d %d %d %d %d\n",weapon_position[i][0],weapon_position[i][1],weapon_position[i][2],weapon_position[i][3],weapon_position[i][4]);
            }
            fprintf(file,"%d\n",num_lost);
            for(int i=0 ; i<num_lost ; i++){
                fprintf(file,"%d %d %d %d\n",lost_weapon[i][0],lost_weapon[i][1],lost_weapon[i][2],lost_weapon[i][3]);
            }
            fprintf(file,"%d %d %d %d\n",key[0],key[1],key[2],key[3]);
            fprintf(file,"%d %d %d %d %d %d %d %d %d\n",num_key ,g,nf,health,tel,wea,*x,*y,numroom);
            fprintf(file,"%d %d %d\n",health_tel,speed_tel,strangh_tel);
            fprintf(file,"%d %d\n",current_weapon[0],current_weapon[1]);
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
                if(i%2==1 && numroom<=4){
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
        }
        for(int i=0 ; i<num_lost ; i++){
            if(lost_weapon[i][0]==*x && lost_weapon[i][1]==*y && lost_weapon[i][2]!=1){
                lost_weapon[i][2]=1;
                switch (lost_weapon[i][3])
                {
                case 0:
                    mvprintw(10,80,"You pick up one Dagger.");
                    refresh();
                    sleep(1);
                    move(10,79);clrtoeol();
                    weapon_position[0][4]++;
                    break;
                case 1:
                    mvprintw(10,80,"You pick up one Majic Wand.");
                    refresh();
                    sleep(1);
                    move(10,79);clrtoeol();
                    weapon_position[1][4]++;
                    break;
                case 2:
                    mvprintw(10,80,"You pick up one Arrow.");
                    refresh();
                    sleep(1);
                    move(10,79);clrtoeol();
                    weapon_position[2][4]++;
                    break;
                }
                if(lost_weapon[i][3]==0 && current_weapon[0]==12){
                    current_weapon[1]++;
                }
                else if(lost_weapon[i][3]==1 && current_weapon[0]==15){
                    current_weapon[1]++;
                }
                else if(lost_weapon[i][3]==2 && current_weapon[0]==5){
                    current_weapon[1]++;
                }
                attron(COLOR_PAIR(3));
                mvprintw(*y,*x,".");
                attroff(COLOR_PAIR(3));
                newx= *x;
                newy= *y;
            }
        }
        for(int i=0 ; i<num_food ; i++){
            if(food_position[i][0]==*x && food_position[i][1]==*y){
                if(nf>=5){
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
                else if(food_position[i][2]==1){
                    attron(COLOR_PAIR(6));
                    mvprintw(10,80,"You take it befor.");
                    attroff(COLOR_PAIR(6));
                    refresh();
                    sleep(1);
                    move(10,79);
                    clrtoeol();
                    refresh();
                    attron(COLOR_PAIR(2));
                    mvprintw(*y, *x, "\u03C6");
                    attroff(COLOR_PAIR(2));
                    *x = newx;
                    *y = newy;
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
                    attron(COLOR_PAIR(2));
                    mvprintw(*y, *x, "\u03C6");
                    attroff(COLOR_PAIR(2));
                    *x = newx;
                    *y = newy;
                }
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
                    attron(COLOR_PAIR(2));
                    mvprintw(*y, *x, "\u0454");
                    attroff(COLOR_PAIR(2));
                    *x = newx;
                    *y = newy;
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
                    attron(COLOR_PAIR(2));
                    mvprintw(*y, *x, "\u0454");
                    attroff(COLOR_PAIR(2));
                    *x = newx;
                    *y = newy;
                    g += gold_position[i][3];
                }
            }
        }
        for(int i=0 ; i<num_gol ; i++){
            if(gol[i][0]==*x && gol[i][1]==*y){
                if(gol[i][2]==1){
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
                    mvprintw(10,80,"You get %d gold.",gol[i][3]);
                    gol[i][2]=1;
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
                g += gol[i][3];
            }
        }
        for(int i=0 ; i<num_tel ; i++){
            if(telesm_position[i][0]==*x && telesm_position[i][1]==*y){
                if(telesm_position[i][3]==1){
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
                    switch (telesm_position[i][2])
                    {
                    case 0:
                        attron(COLOR_PAIR(6));
                        mvprintw(10,80,"You take the health Talisman.");
                        health_tel ++;
                        attroff(COLOR_PAIR(6));
                        refresh();
                        break;
                    case 4:
                        attron(COLOR_PAIR(6));
                        mvprintw(10,80,"You take the strength Talisman.");
                        strangh_tel++;
                        attroff(COLOR_PAIR(6));
                        refresh();
                        break;
                    default:
                        attron(COLOR_PAIR(6));
                        mvprintw(10,80,"You take the speed Talisman.");
                        speed_tel++;
                        attroff(COLOR_PAIR(6));
                        refresh();
                        break;
                    }
                    telesm_position[i][3]=1;
                    refresh();
                    sleep(1);
                    move(10,79);
                    clrtoeol();
                    refresh();
                    tel ++;
                }
                switch (i)
                    {
                    case 0:
                        attron(COLOR_PAIR(2));
                        mvprintw(*y, *x, "\u22D2");
                        refresh();
                        attroff(COLOR_PAIR(2));
                        break;
                    case 1:
                        attron(COLOR_PAIR(2));
                        mvprintw(*y, *x, "\u0E19");
                        refresh();
                        attroff(COLOR_PAIR(2));
                        break;
                    case 2:
                        attron(COLOR_PAIR(2));
                        mvprintw(*y, *x, "\u03BB");
                        refresh();
                        attroff(COLOR_PAIR(2));
                        break;
                    }
                *x = newx;
                *y = newy;
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
        for(int i=0 ; i<num_tal ; i++){
            if(tal[i][0]==*x && tal[i][1]==*y){
                if(tal[i][2]==0)
                    health -= 2;
                    tal[i][2]=1;
                attron(COLOR_PAIR(2));
                mvprintw(*y, *x, "^");
                attroff(COLOR_PAIR(2));
                *x = newx;
                *y = newy;
            }
        }
        for(int i=0 ; i<num_weapon ; i++){
            if(weapon_position[i][0]==*x && weapon_position[i][1]==*y){
                if(weapon_position[i][2]==0){
                    weapon_position[i][2]=1;
                    wea++;
                    switch (weapon_position[i][3])
                    {
                    case 12:
                        attron(COLOR_PAIR(7));
                        mvprintw(10, 80, "You pick up Dagger.");
                        refresh();
                        attroff(COLOR_PAIR(7));
                        sleep(2);
                        move(10,79);
                        clrtoeol();
                        weapon_position[i][4]=10;
                        break;
                    case 15:
                        attron(COLOR_PAIR(7));
                        mvprintw(10, 80, "You pick up Majic Wand.");
                        refresh();
                        attroff(COLOR_PAIR(7));
                        sleep(2);
                        move(10,79);
                        clrtoeol();
                        weapon_position[i][4]=8;
                        break;    
                    case 5:
                        attron(COLOR_PAIR(7));
                        mvprintw(10, 80, "You pick up Normal Arrow.");
                        refresh();
                        attroff(COLOR_PAIR(7));
                        sleep(2);
                        move(10,79);
                        clrtoeol();
                        weapon_position[i][4]=20;
                        break;    
                    case 10:
                        attron(COLOR_PAIR(7));
                        mvprintw(10, 80, "You pick up Sword.");
                        refresh();
                        attroff(COLOR_PAIR(7));
                        sleep(2);
                        move(10,79);
                        clrtoeol();
                        weapon_position[i][4]=1;
                        break;    
                    }
                }
                attron(COLOR_PAIR(3));
                mvprintw(*y, *x, ".");
                attroff(COLOR_PAIR(3));
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
typedef struct {
    char name[50];
    char password[50];
    char email[50];
    int score;
    int gold;
    int number_of_games;
    time_t first_Game_Time;
} User;
typedef struct{
    char password[50];
    char name[50];
}Game;
int check_pas(char password[]){
    if(strlen(password)>7){
        int up=0,low=0,adad=0;
        for(int i=0 ; i<strlen(password) ; i++){
            if(password[i]>='a' && password[i]<='z'){
                low++;
            }
            else if(password[i]>='A' && password[i]<='Z'){
                up++;
            }
            else if(password[i]>='0' && password[i]<='9'){
                adad++;
            }
        }
        if(low>0 && up>0 && adad>0){
            return 1;
        }
        else{
            return 0;
        }
    }
    return 0;
}
int check_email(char email[]) {
    int at_position = -1;
    int dot_position = -1;
    int length = strlen(email);
    for (int i = 0; i < length; i++) {
        if (email[i] == '@') {
            at_position = i;
        } else if (email[i] == '.') {
            dot_position = i;
        }
    }
    if (at_position == -1 || dot_position == -1) {
        return 0;
    }
    if (at_position > dot_position) {
        return 0;
    }
    if (at_position == 0 || at_position == length - 1 || dot_position == 0 || dot_position == length - 1) {
        return 0;
    }
    return 1;
}
void save_user(const char *filename, User *user) {
    FILE *file = fopen(filename, "a");
    fprintf(file, "%s %s %s %d %d %d %ld\n", user->name, user->password, user->email,user->score,user->gold,user->number_of_games,user->first_Game_Time);
    fclose(file);
}
int check_login(const char *filename , const char* name , const char* password){
    FILE *file =fopen(filename,"r");
    User user;
    while(fscanf(file,"%s %s %s %d %d %d %ld", user.name, user.password, user.email,&user.score,&user.gold,&user.number_of_games,&user.first_Game_Time) != EOF){
        if(strcmp(user.name , name)==0 && strcmp(user.password , password)==0 ){
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
int check_name(const char* filename , const char * name){
    FILE *file=fopen(filename,"r");
    User user;
    while (fscanf(file , "%s %s %s" , user.name , user.password , user.email)!= EOF )
    {
        if(strcmp(user.name , name)==0){
            return 0;
        }
    }
    return 1;
}
void safhe(){
    move(5,20);
    for(int i=0 ; i<20 ; i++){
        printw("*");
        move(5+i,20);
    }
    move(5,20);
    for(int i=0 ; i<50 ; i++){
        printw("*");
        move(5,20+i);
    }
    for(int i=0 ; i<20 ; i++){
        printw("*");
        move(5+i,70);
    }
    move(24,20);
    for(int i=0 ; i<=51 ; i++){
        printw("*");
        move(24,20+i);
    }
}
void find_pas(const char* filename){
    attron(COLOR_PAIR(6));
    move(18,20);
    clrtoeol();
    mvprintw(16,22,"Email address:");
    char email[50];
    move(20,21);
    clrtoeol();
    move(19,21);
    clrtoeol();
    scanw("%s",email);
    FILE *file=fopen(filename,"r");
    User users[100];
    int count=0,check=0;
    while (fscanf(file, "%s %s %s %d %d %d %ld", users[count].name, users[count].password, 
                users[count].email, &users[count].score ,&users[count].gold,&users[count].number_of_games,&users[count].first_Game_Time) != EOF)
    {
        if(strcmp(users[count].email , email)==0){
            move(19,20);
            clrtoeol();
            mvprintw(19,22,"Your password is: %s",users[count].password);
            fclose(file);
            check++;
            break;
        }
        count++;
    }
    attroff(COLOR_PAIR(6));
    if(check==0){
        attron(COLOR_PAIR(2));
        mvprintw(20,22,"Your email-address can't be found.");
        attroff(COLOR_PAIR(2));
    }
}
void sort(User users[] , int count){
    User temp;
    for(int i=0 ; i< count -1; i++){
        for(int j=i+1 ; j<count ; j++){
            if(users[j].score > users[i].score){
               temp= users[i];
               users[i]=users[j];
               users[j]=temp;
            }
        }
    }
}
void table(const char* filename,const char*name){
    clear();
    FILE *file=fopen(filename,"r");
    User users[1000];
    int count =0;
    while (fscanf(file, "%s %s %s %d %d %d %ld", users[count].name, users[count].password, 
                users[count].email, &users[count].score ,&users[count].gold,&users[count].number_of_games,&users[count].first_Game_Time) != EOF)
    {
        count++;
    }
    fclose(file);
    sort(users, count);
    attron(COLOR_PAIR(2));
    mvprintw(3, 20, "Rank     username"); mvprintw(3,40,"score     gold     number_of_games      first_Game_Time");
    for(int i=0; i<75 ; i++){
        mvprintw(4,20+i,"-");
    }
    attroff(COLOR_PAIR(2));
    for(int i=0 ; i<count ; i++){
        time_t currentTime = time(NULL);
        double experience = difftime(currentTime, users[i].first_Game_Time) / (60 * 60);
        if(i==0){
            mvprintw(i+5,15,"\U0001F947");
            attron(COLOR_PAIR(6) | A_BOLD);
            mvprintw(i+5,20,"Goat      %s",users[i].name);
            mvprintw(i+5,41,"%d",users[i].score);
            mvprintw(i+5,50,"%d",users[i].gold);
            mvprintw(i+5,66,"%d",users[i].number_of_games);
            mvprintw(i+5,83,"%.2f hour",experience);
            attroff(COLOR_PAIR(6) | A_BOLD);
        }
        else if(i==1){
            mvprintw(i+5,15,"\U0001F948");
            attron(COLOR_PAIR(6) | A_BOLD);
            mvprintw(i+5,20,"Legend    %s",users[i].name);
            mvprintw(i+5,41,"%d",users[i].score);
            mvprintw(i+5,50,"%d",users[i].gold);
            mvprintw(i+5,66,"%d",users[i].number_of_games);
            mvprintw(i+5,83,"%.2f hour",experience);
            attroff(COLOR_PAIR(6) | A_BOLD);
        }
        else if(i==2){
            mvprintw(i+5,15,"\U0001F949");
            attron(COLOR_PAIR(6) | A_BOLD);
            mvprintw(i+5,20,"Silver    %s",users[i].name);
            mvprintw(i+5,41,"%d",users[i].score);
            mvprintw(i+5,50,"%d",users[i].gold);
            mvprintw(i+5,66,"%d",users[i].number_of_games);
            mvprintw(i+5,83,"%.2f hour",experience);
            attroff(COLOR_PAIR(6) | A_BOLD);
        }
        else{
            mvprintw(i+5,20," %d        %s",i+1,users[i].name);
            mvprintw(i+5,41,"%d",users[i].score);
            mvprintw(i+5,50,"%d",users[i].gold);
            mvprintw(i+5,66,"%d",users[i].number_of_games);
            mvprintw(i+5,83,"%.2f hour",experience);
        }
        if(strcmp(users[i].name,name)==0){
            mvprintw(i+5,5,"---->");
        }
        
    }
    attroff(COLOR_PAIR(2));
    refresh();
    getchar();
    clear();
    menu(name);
    refresh();
}
void update(const char*filename ,const char *name){
    FILE *file = fopen(filename, "r+");
    User users[100];
    int count = 0;
    while (fscanf(file, "%s %s %s %d %d %d %ld", users[count].name, users[count].password, 
                users[count].email, &users[count].score ,&users[count].gold,&users[count].number_of_games,&users[count].first_Game_Time) != EOF)
    {
        count++;
    }
    for(int i=0 ; i<count ; i++){
        if(strcmp(users[i].name , name)==0){
            users[i].gold=users[i].gold+g;
            users[i].score=users[i].score+(3*g);
            users[i].number_of_games=users[i].number_of_games+num_game;
            break;
        }
    }
    rewind(file);
    for(int i=0 ; i<count ; i++){
        fprintf(file, "%s %s %s %d %d %d %ld\n", users[i].name, users[i].password, 
                users[i].email, users[i].score ,users[i].gold,users[i].number_of_games,users[i].first_Game_Time);
    }
    fclose(file);
}
void new_game(const char*filename ,const char *name){
    int qu=0;
    fl=0;
    health=20;
    for(int i=0 ; i<4 ; i++){
        keypad(stdscr, TRUE);
        noecho();
        if(qu!=0){
            break;
        }
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
            if(fl==3 && j==5){
                draw_dar(rooms[j],j);
                gold_gold(rooms[j]);
                tal_gold(rooms[j]);
            }
            else{
                if(j==0){
                weapon(rooms[j],j);
                }
                draw_dar(rooms[j],j);
                soton(rooms[j]);
                gold(rooms[j]);
                tale(rooms[j]);
                food(rooms[j]);
                if(j%2 ==0){
                    telesm(rooms[j],j);
                }
            }
        }
        for(int j=1 ; j<6 ; j++){
            enemy(rooms[j] , j);
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
        if(fl==0){
            current_weapon[0]=4;
            current_weapon[1]=1;
        }
        mvprintw(y, x, "\u2735");
        refresh();
        time(&startTime);
        while (health > 0) {
            time(&currentTime);
            if(dif==1){
                if (difftime(currentTime, startTime) >= 50) {
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
                qu++;
                break;
            }
            refresh();
            if(x==dar_positions[10][0]&& y==dar_positions[10][1]){
                fl++;
                break;
            }
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
        for(int j=0 ; j<num_gol ; j++){
            gol[j][0]=gol[j][1]=gol[j][2]=gol[j][3]=0;
        }
        for(int j=0 ; j<num_gold ; j++){
            gold_position[j][0]=gold_position[j][1]=gold_position[j][2]=gold_position[j][3]=0;
        }
        for(int j=0 ; j<num_tale ; j++){
            tale_position[j][0]=tale_position[j][1]=tale_position[j][2]=tale_position[j][3]=0;
        }
        for(int j=0 ; j<num_tal ; j++){
            tal[j][0]=tal[j][1]=tal[j][2]=tal[j][3]=0;
        }
        for(int j=0 ; j<num_tel ; j++){
            telesm_position[j][0]=telesm_position[j][1]=telesm_position[j][2]=telesm_position[j][3]=0;
        }
        for(int j=0 ; j<num_food ; j++){
            food_position[j][0]=food_position[j][1]=food_position[j][2]=0;
        }
        for(int j=0 ; j<num_enemy ; j++){
            enemy_position[j][0]=enemy_position[j][1]=enemy_position[j][2]=enemy_position[j][3]=0;
        }
        for(int j=0 ; j<num_lost ; j++){
            lost_weapon[j][0]=lost_weapon[j][1]=lost_weapon[j][2]=lost_weapon[j][3]=0;
        }
        key[0]=key[1]=key[2]=key[3]=0;
        num_dar=num_path=num_key=num_rooms=num_tale=num_soton=num_gold=num_food=numroom=num_tel=num_enemy=num_gol=num_tal=num_lost=0;
        if(health==0){
            attron(COLOR_PAIR(2));
            mvprintw(20,140,"You are Lost.");
            refresh();
            attroff(COLOR_PAIR(2));
            getchar();
            break;
        }
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
        for(int j=0 ; j<num_gol ; j++){
            gol[j][0]=gol[j][1]=gol[j][2]=gol[j][3]=0;
        }
        for(int j=0 ; j<num_gold ; j++){
            gold_position[j][0]=gold_position[j][1]=gold_position[j][2]=gold_position[j][3]=0;
        }
        for(int j=0 ; j<num_tale ; j++){
            tale_position[j][0]=tale_position[j][1]=tale_position[j][2]=tale_position[j][3]=0;
        }
        for(int j=0 ; j<num_tal ; j++){
            tal[j][0]=tal[j][1]=tal[j][2]=tal[j][3]=0;
        }
        for(int j=0 ; j<num_tel ; j++){
            telesm_position[j][0]=telesm_position[j][1]=telesm_position[j][2]=telesm_position[j][3]=0;
        }
        for(int j=0 ; j<num_food ; j++){
            food_position[j][0]=food_position[j][1]=food_position[j][2]=0;
        }
        for(int j=0 ; j<num_enemy ; j++){
            enemy_position[j][0]=enemy_position[j][1]=enemy_position[j][2]=enemy_position[j][3]=0;
        }
        for(int i=0 ; i++ ; i<num_weapon){
            weapon_position[i][0]=weapon_position[i][1]=weapon_position[i][2]=weapon_position[i][3]=weapon_position[i][4]=0;
        }
        for(int j=0 ; j<num_lost ; j++){
            lost_weapon[j][0]=lost_weapon[j][1]=lost_weapon[j][2]=lost_weapon[j][3]=0;
        }
        key[0]=key[1]=key[2]=key[3]=0;
        num_dar=num_path=num_key=num_tale=num_soton=num_gold=num_food=numroom=num_tel=num_enemy=num_weapon=num_gol=num_tal=num_lost=0;
        current_weapon[0]=4;
        current_weapon[1]=1;
        attron(COLOR_PAIR(6));
        clear();
        if(qu==0){
            mvprintw(10,50,"You won.");
            mvprintw(11,45,"Gold: %d score: %d",g,g*3);
            num_game=1;
        }
        qu=0;
        refresh();
        attroff(COLOR_PAIR(6));
        getchar();
        update(filename,name);
        g=0;
        num_game=0;
    clear();
    menu(name);
}
void load_game(const char*filename , const char*game_name , const char* name){
    keypad(stdscr, TRUE);
    noecho();
    clear();
    int x;
    int y;
    int qu=0;
    FILE *file=fopen(game_name,"r");
    Room rooms[6];
    fscanf(file,"%d",&fl);
    for(int i=0 ; i<6 ; i++){
        fscanf(file,"%d %d %d %d %d",&rooms[i].x,&rooms[i].y,&rooms[i].width,&rooms[i].height,&rooms[i].hide);
    }
    fscanf(file,"%d",&num_dar);
    for(int i=0 ; i<num_dar ; i++){
        fscanf(file,"%d %d %d",&dar_positions[i][0],&dar_positions[i][1],&dar_positions[i][2]);
    }
    fscanf(file,"%d",&num_soton);
    for(int i=0 ; i<num_soton ; i++){
        fscanf(file,"%d %d %d",&soton_position[i][0],&soton_position[i][1],&soton_position[i][2]);
    }
    fscanf(file,"%d",&num_gold);
    for(int i=0 ; i<num_gold; i++){
        fscanf(file,"%d %d %d %d",&gold_position[i][0],&gold_position[i][1],&gold_position[i][2],&gold_position[i][3]);
    }
    fscanf(file,"%d",&num_gol);
    for(int i=0 ; i<num_gol; i++){
        fscanf(file,"%d %d %d %d",&gol[i][0],&gol[i][1],&gol[i][2],&gol[i][3]);
    }
    fscanf(file,"%d",&num_tale);
    for(int i=0 ; i<num_tale ; i++){
        fscanf(file,"%d %d %d",&tale_position[i][0],&tale_position[i][1],&tale_position[i][2]);
    }
    fscanf(file,"%d",&num_tal);
    for(int i=0 ; i<num_tal ; i++){
        fscanf(file,"%d %d %d",&tal[i][0],&tal[i][1],&tal[i][2]);
    }
    fscanf(file,"%d",&num_food);
    for(int i=0 ; i<num_food ; i++){
        fscanf(file,"%d %d %d",&food_position[i][0],&food_position[i][1],&food_position[i][2]);
    }
    fscanf(file,"%d",&num_path);
    for(int i=0 ; i<num_path; i++){
        fscanf(file,"%d %d %d",&path_position[i][0],&path_position[i][1],&path_position[i][2]);
    }
    fscanf(file,"%d",&num_tel);
    for(int i=0 ; i<num_tel ; i++){
        fscanf(file,"%d %d %d %d",&telesm_position[i][0],&telesm_position[i][1],&telesm_position[i][2],&telesm_position[i][3]);
    }
    fscanf(file,"%d",&num_enemy);
    for(int i=0 ; i<num_enemy ; i++){
        fscanf(file,"%d %d %d %d",&enemy_position[i][0],&enemy_position[i][1],&enemy_position[i][2],&enemy_position[i][3]);
    }
    fscanf(file,"%d",&num_weapon);
    for(int i=0 ; i<num_weapon ; i++){
        fscanf(file,"%d %d %d %d %d",&weapon_position[i][0],&weapon_position[i][1],&weapon_position[i][2],&weapon_position[i][3],&weapon_position[i][4]);
    }
    fscanf(file,"%d",&num_lost);
    for(int i=0 ; i<num_lost ; i++){
        fscanf(file,"%d %d %d %d %d",&lost_weapon[i][0],&lost_weapon[i][1],&lost_weapon[i][2],&lost_weapon[i][3],&lost_weapon[i][4]);
    }
    fscanf(file,"%d %d %d %d",&key[0],&key[1],&key[2],&key[3]);
    fscanf(file," %d %d %d %d %d %d %d %d %d",&num_key ,&g,&nf,&health,&tel,&wea,&x,&y,&numroom);
    fscanf(file,"%d %d %d",&health_tel,&speed_tel,&strangh_tel);
    fscanf(file,"%d %d",&current_weapon[0],&current_weapon[1]);
    fclose(file);
    rooms[0].hide=1;
    for(int i=0 ; i<6 ; i++){
        if(rooms[i].hide ==1)
            draw_room(rooms[i],i);
        refresh();
    }
    for(int i=0 ; i<num_path ; i++){
        if(path_position[i][2]==1){
            attron(COLOR_PAIR(1));
            mvprintw(path_position[i][1],path_position[i][0],"#");
            attroff(COLOR_PAIR(1));
            refresh();
        }
    }
    draw_page();
    refresh();
    mvprintw(y,x,"\u2735");
    refresh();
    time(&startTime);
    while (health > 0) {
        time(&currentTime);
        if(dif==1){
            if (difftime(currentTime, startTime) >= 50) {
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
            qu++;
            break;
        }
        refresh();
        if(x==dar_positions[10][0]&& y==dar_positions[10][1]){
            fl++;
            break;
        }
    }
    if(qu!=0){
        for(int i=0 ; i<num_weapon ; i++){
            weapon_position[i][0]=weapon_position[i][1]=weapon_position[i][2]=weapon_position[i][3]=weapon_position[i][4]=0;
        }
        num_weapon=0;
        current_weapon[0]=4;
        current_weapon[1]=1;
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
    for(int j=0 ; j<num_gol ; j++){
        gol[j][0]=gol[j][1]=gol[j][2]=gol[j][3]=0;
    }
    for(int j=0 ; j<num_tale ; j++){
        tale_position[j][0]=tale_position[j][1]=tale_position[j][2]=tale_position[j][3]=0;
    }
    for(int j=0 ; j<num_tal ; j++){
        tal[j][0]=tal[j][1]=tal[j][2]=tal[j][3]=0;
    }
    for(int j=0 ; j<num_tel ; j++){
        telesm_position[j][0]=telesm_position[j][1]=telesm_position[j][2]=telesm_position[j][3]=0;
    }
    for(int j=0 ; j<num_food ; j++){
        food_position[j][0]=food_position[j][1]=food_position[j][2]=0;
    }
    for(int j=0 ; j<num_enemy ; j++){
        enemy_position[j][0]=enemy_position[j][1]=enemy_position[j][2]=enemy_position[j][3]=0;
    }
    for(int i=0 ; i<num_lost ; i++){
        lost_weapon[i][0]=lost_weapon[i][1]=lost_weapon[i][2]=lost_weapon[i][3]=0;
    }
    key[0]=key[1]=key[2]=key[3]=0;
    num_dar=num_path=num_key=num_tale=num_soton=num_gold=num_food=numroom=num_tel=num_enemy=num_tal=num_gol=num_lost=0;
    if(qu==0){
        for(fl ; fl<4 ; fl++){
            if(qu!=0){
                break;
            }
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
                if(fl==3 && j==5){
                    draw_dar(rooms[j],j);
                    gold_gold(rooms[j]);
                    tal_gold(rooms[j]);
                }
                else{
                    if(j==0){
                    weapon(rooms[j],j);
                    }
                    draw_dar(rooms[j],j);
                    soton(rooms[j]);
                    gold(rooms[j]);
                    tale(rooms[j]);
                    food(rooms[j]);
                    if(j%2 ==0){
                        telesm(rooms[j],j);
                    }
                }
            }
            for(int j=1 ; j<6 ; j++){
                enemy(rooms[j] , j);
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
                    if (difftime(currentTime, startTime) >= 50) {
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
                    qu++;
                    break;
                }
                refresh();
                if(x==dar_positions[10][0]&& y==dar_positions[10][1]){
                    break;
                }
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
            for(int j=0 ; j<num_gol ; j++){
                gol[j][0]=gol[j][1]=gol[j][2]=gol[j][3]=0;
            }
            for(int j=0 ; j<num_tale ; j++){
                tale_position[j][0]=tale_position[j][1]=tale_position[j][2]=tale_position[j][3]=0;
            }
            for(int j=0 ; j<num_tal ; j++){
                tal[j][0]=tal[j][1]=tal[j][2]=tal[j][3]=0;
            }
            for(int j=0 ; j<num_tel ; j++){
                telesm_position[j][0]=telesm_position[j][1]=telesm_position[j][2]=telesm_position[j][3]=0;
            }
            for(int j=0 ; j<num_food ; j++){
                food_position[j][0]=food_position[j][1]=food_position[j][2]=0;
            }
            for(int j=0 ; j<num_enemy ; j++){
                enemy_position[j][0]=enemy_position[j][1]=enemy_position[j][2]=enemy_position[j][3]=0;
            }
            for(int i=0 ; i<num_lost ; i++){
                lost_weapon[i][0]=lost_weapon[i][1]=lost_weapon[i][2]=lost_weapon[i][3]=0;
            }
            key[0]=key[1]=key[2]=key[3]=0;
            num_dar=num_path=num_key=num_rooms=num_tale=num_soton=num_gold=num_food=numroom=num_tel=num_enemy=num_tal=num_gol=num_lost=0;
            if(health==0){
                attron(COLOR_PAIR(2));
                mvprintw(20,140,"You are Lost.");
                refresh();
                attroff(COLOR_PAIR(2));
                getchar();
                break;
            }
            sleep(2);
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
            for(int j=0 ; j<num_gol ; j++){
                gol[j][0]=gol[j][1]=gol[j][2]=gol[j][3]=0;
            }
            for(int j=0 ; j<num_tale ; j++){
                tale_position[j][0]=tale_position[j][1]=tale_position[j][2]=tale_position[j][3]=0;
            }
            for(int j=0 ; j<num_tal ; j++){
                tal[j][0]=tal[j][1]=tal[j][2]=tal[j][3]=0;
            }
            for(int j=0 ; j<num_tel ; j++){
                telesm_position[j][0]=telesm_position[j][1]=telesm_position[j][2]=telesm_position[j][3]=0;
            }
            for(int j=0 ; j<num_food ; j++){
                food_position[j][0]=food_position[j][1]=food_position[j][2]=0;
            }
            for(int j=0 ; j<num_enemy ; j++){
                enemy_position[j][0]=enemy_position[j][1]=enemy_position[j][2]=enemy_position[j][3]=0;
            }
            for(int i=0 ; i<num_weapon ; i++){
                weapon_position[i][0]=weapon_position[i][1]=weapon_position[i][2]=weapon_position[i][3]=weapon_position[i][4]=0;
            }
            for(int i=0 ; i<num_lost ; i++){
                lost_weapon[i][0]=lost_weapon[i][1]=lost_weapon[i][2]=lost_weapon[i][3]=0;
            }
            key[0]=key[1]=key[2]=key[3]=0;
            num_dar=num_path=num_key=num_tale=num_soton=num_gold=num_food=numroom=num_tel=num_enemy=num_weapon=num_tal=num_gol=num_lost=0;
            current_weapon[0]=4;
            current_weapon[1]=1;
            attron(COLOR_PAIR(6));
            clear();
            if(qu==0){
                mvprintw(10,50,"You won.");
                mvprintw(11,45,"Gold: %d score: %d",g,g*3);
                num_game=1;
            }
            qu=0;
            refresh();
            attroff(COLOR_PAIR(6));
            getchar();
            update(filename,name);
            g=0;
            num_game=0;
        clear();
        menu(name);
    }
    clear();
    menu(name);
}
void settings_menu(const char* name){
    int choice;
    initscr();
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(5, 10, "1. Set Difficulty");
    mvprintw(7, 10, "2. Set Hero Color");
    mvprintw(9,10,"3. Set Background Music");
    mvprintw(11, 10, "4. Exit");
    attroff(COLOR_PAIR(1));
    refresh();
    mvprintw(13, 10, "Enter your choice: ");
    while (TRUE) {
        move(13,30);
        clrtoeol();
        move(13,30);
        scanw("%d", &choice);
        switch (choice) {
            case 1:
                set_difficulty(name);
                break;
            case 2:
                set_hero_color(name);
                break;
            case 3:
                choose_music(name);
                break;
            case 4:
                menu(name);
                return;
            default:
                attron(COLOR_PAIR(2));
                mvprintw(15, 10, "Invalid choice! Please try again.");
                attroff(COLOR_PAIR(2));
                refresh();
                break;
        }
        if(choice>0 && choice<4){
            break;
        }
    }
}
void play_music(const char *file) {
    if (fork() == 0) {
        char command[256];
        snprintf(command, sizeof(command), "ffplay -nodisp -autoexit -loop 0 %s > /dev/null 2>&1", file);
        execl("/bin/sh", "sh", "-c", command, (char *) 0);
        exit(0);
    }
}

void stop_music() {
    system("pkill ffplay");
}
void choose_music( const char* name) {
    int music_choice;
    initscr();
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(5, 10, "Choose Background Music");
    mvprintw(7, 10, "1. Music 1");
    mvprintw(9, 10, "2. Music 2");
    mvprintw(11, 10, "3. Music 3");
    mvprintw(13, 10, "4. Music 4");
    mvprintw(15, 10, "5. Music 5");
    mvprintw(17, 10, "6. Music 6");
    mvprintw(19, 10, "7. Music 7");
    mvprintw(21, 10, "8. stop music");
    mvprintw(23, 10, "9. exit");
    attroff(COLOR_PAIR(1));
    refresh();
    mvprintw(25, 10, "Enter your choice: ");
    scanw("%d", &music_choice);
    switch (music_choice)
    {
    case 1:
        stop_music();
        play_music("music1.mp3");
        break;
    
    case 2:
        stop_music();
        play_music("music2.mp3");

        break;
    case 3:
        stop_music();
        play_music("music3.mp3");
        break;
    case 4:
        stop_music();
        play_music("music4.mp3");
        break;
    case 5:
        stop_music();
        play_music("music5.mp3");
        break;
    case 6:
        stop_music();
        play_music("music6.mp3");
        break;
    case 7:
        stop_music();
        play_music("music7.mp3");
        break;
    case 8:
        stop_music();
        break;
    case 9:
        break;
    }
    refresh();
    getch();
    settings_menu(name);
}
void set_difficulty(const char* name) {
    int difficulty;
    clear();
    mvprintw(5, 10, "Choose Difficulty Level:");
    attron(COLOR_PAIR(1));
    mvprintw(7, 10, "1. Easy");
    mvprintw(8, 10, "2. Medium");
    mvprintw(9, 10, "3. Hard");
    attron(COLOR_PAIR(1));
    refresh();
    mvprintw(11, 10, "Enter your choice: ");
    scanw("%d", &difficulty);
    switch (difficulty)
    {
    case 1:
        mvprintw(13, 10, "Difficulty set to Easy.");
        break;
    
    case 2:
        mvprintw(13, 10, "Difficulty set to Medium.");
        break;
    case 3:
        mvprintw(13, 10, "Difficulty set to Hard.");
        break;
    }
    dif=difficulty;
    refresh();
    getch();
    settings_menu(name);
}

void set_hero_color(const char* name) {
    int c;
    clear();
    mvprintw(5, 10, "Choose Hero Color:");
    attron(COLOR_PAIR(2));
    mvprintw(7, 10, "1. Red");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(1));
    mvprintw(8, 10, "2. Green");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(7));
    mvprintw(9, 10, "3. Blue");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(6));
    mvprintw(10, 10, "4. Yellow");
    attroff(COLOR_PAIR(6));
    refresh();
    mvprintw(13, 10, "Enter your choice: ");
    scanw("%d", &c);
    switch (c)
    {
    case 1:
        attron(COLOR_PAIR(2));
        mvprintw(15, 10, "Hero color set to Red.");
        attroff(COLOR_PAIR(2));
        break;
    case 2:
        attron(COLOR_PAIR(1));
        mvprintw(15, 10, "Hero color set to Green.");
        attroff(COLOR_PAIR(1));
        break;
    case 3:
        attron(COLOR_PAIR(7));
        mvprintw(15, 10, "Hero color set to Blue.");
        attroff(COLOR_PAIR(7));
        break;
    case 4:
        attron(COLOR_PAIR(6));
        mvprintw(15, 10, "Hero color set to Yellow.");
        attroff(COLOR_PAIR(6));
        break;
    }
    color=c;
    refresh();
    getch();
    settings_menu(name);
}
int menu(const char*name){
    echo();
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(3,5,"Welcome %s",name);
    attroff(COLOR_PAIR(1));
    refresh();
    int choice;
    initscr();
    start_color();
    attron(COLOR_PAIR(6));
    mvprintw(5, 10, "1- New Game");
    mvprintw(7, 10, "2- Load Game");
    mvprintw(9, 10, "3- Table");
    mvprintw(11,10, "4- Settings_menu");
    mvprintw(13, 10, "5- Exit");
    attroff(COLOR_PAIR(6));
    mvprintw(15, 10, "Enter your choice: ");
    refresh();
    while (TRUE) {
        move(15,30);
        clrtoeol();
        move(15,30);
        scanw("%d", &choice);
        printw("%d",choice);
        refresh();
        switch (choice) {
            case 1:
                new_game("users.txt",name);
                return 1;
            case 2:
                clear();
                attron(COLOR_PAIR(7));
                mvprintw(8,10,"write your game name.");
                char s[20];
                scanw("%s",s);
                refresh();
                attroff(COLOR_PAIR(7));
                getchar();
                load_game("users.txt",s,name);
                return 2;
            case 3:
                table("users.txt",name);
                return 3;
            case 4:
                settings_menu(name);
                return 4;
            case 5:
                move(18,62);
                clear();
                attron(COLOR_PAIR(2));
                mvprintw(15, 15, "I hope you enjoy the game.");
                refresh();
                attroff(COLOR_PAIR(2));
                getch();
                endwin();
                exit(0);
            default:
                attron(COLOR_PAIR(2));
                mvprintw(17, 10, "Invalid choice! Please try again.");
                attroff(COLOR_PAIR(2));
                refresh();
                break;
        }
    if(choice>0 && choice<6){
        break;
    }
    }
}
void login(){
    safhe();
    char name[20];
    char password[20];
    attron(COLOR_PAIR(1));
    mvprintw(10,22,"User Name:");
    mvprintw(13,22,"Password:");
    mvprintw(15,22,"If you forgot password,writ 3 in password");
    attroff(COLOR_PAIR(1));
    while (TRUE)
    {
        move(10,34);
        clrtoeol();
        echo();
        scanw("%s",name);safhe();
        move(13,34);
        clrtoeol();
        scanw("%s",password);safhe();
        if(strcmp(password,"3")==0){
            find_pas("users.txt");
        }
        else{
            clrtoeol();
            if(check_login("users.txt" , name , password)){
                move(23,32);
                clrtoeol();
                break;
            }
            else{
                move(23,32);
                clrtoeol();
                attron(COLOR_PAIR(2));
                printw("Your name/password isn't correct");safhe();
                attroff(COLOR_PAIR(2));
            }
        } 
    }
    move(23,32);
    attron(COLOR_PAIR(7));
    printw("press any key to continue");safhe();
    refresh();
    getchar();
    attroff(COLOR_PAIR(7));
    menu(name);
    refresh();
}
void new_user(){
    safhe();
    User user;
    attron(COLOR_PAIR(1));
    mvprintw(10,32,"User Name:");
    mvprintw(15,32,"Password:");
    mvprintw(20,32,"Email Adress:");
    attroff(COLOR_PAIR(1));
    echo();
    while (TRUE)
    {
        move(10,43);
        clrtoeol();
        scanw("%s",user.name);safhe();
        if(check_name("users.txt",user.name)){
            move(11,33);
            clrtoeol();
            break;
        }
        else{
            move(11,33);
            attron(COLOR_PAIR(2));
            printw("your username has taken befor.");safhe();
            clrtoeol();
            attroff(COLOR_PAIR(2));
        }
    }
    move(15,43);
    while(true){
        clrtoeol();
        scanw("%s",user.password);safhe();
        move(16,24);
        if(check_pas(user.password) == 0){
            attron(COLOR_PAIR(2));
            printw("your password isn't correct");safhe();
            clrtoeol();
            attroff(COLOR_PAIR(2));
            move(15,42);
        }
        else{
            clrtoeol();
            break;
        }
    }
    move(20,46);
    while(true){
        clrtoeol();
        scanw("%s",user.email);safhe();
        move(21,22);
        if(check_email(user.email) == 0){
            attron(COLOR_PAIR(2));
            printw("your Email isn't correct");safhe();
            clrtoeol();
            attroff(COLOR_PAIR(2));
            move(20,45);
        }
        else{
            clrtoeol();
            break;
        }
    }
    user.score=0; 
    user.gold=0;
    user.number_of_games=0;
    user.first_Game_Time = time(NULL);
    move(22,28);
    attron(COLOR_PAIR(7));
    save_user("users.txt",&user);
    printw("Your account save succesfully.");
    mvprintw(23,30,"press any key to continue.");
    refresh();
    attroff(COLOR_PAIR(7));
    getch();
    clear();
}
int entery(){
    echo();
    safhe();
    attron(COLOR_PAIR(1));
    move(6,22);
    printw("1-login");
    move(10,22);
    printw("2-Creat New account");
    move(14,22);
    printw("3-Guest");
    move(18,22);
    printw("4-exit");
    attroff(COLOR_PAIR(2));
    int ch;
    while (true) { 
        mvprintw(20, 22, "Please enter your choice: ");
        refresh();
        clrtoeol(); 
        scanw("%d", &ch); safhe();
        if (ch < 1 || ch > 4) { 
            attron(COLOR_PAIR(2));
            mvprintw(23, 22, "Invalid choice! Please try again."); safhe();
            attroff(COLOR_PAIR(2)); 
            refresh(); 
        } 
        else { 
            move(23,22);
            clrtoeol(); 
            break; 
        } 
        }
    switch (ch)
    {
    case 1:
        move(10,22);
        clear();
        return 1;
        break;
    case 2:
        move(10,22);
        clear();
        return 2;
    case 3:
        move(14,22);
        return 3;
        break;
    case 4:
        move(18,22);
        clear();
        attron(COLOR_PAIR(2));
        mvprintw(15, 15, "I hope you enjoy the game.");
        refresh();
        attroff(COLOR_PAIR(2));
        getch();
        break;
    }
}
int main() {
    setlocale(LC_ALL, "");
    initscr();
    srand(time(NULL));
    start_color();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7,COLOR_CYAN,COLOR_BLACK);
    switch(entery()){
        case 1:
            login();
            break;
        case 2:
            new_user();
            login();
            break;
        case 3:
            menu("guset");
            break;
        case 4:
            break;
    }
    refresh();             
    getch();           
    stop_music();  
    endwin();              
    return 0;
}
