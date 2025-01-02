#include <ncurses.h>
#include<stdio.h>
#include<string.h>
#include <time.h>
#include<stdlib.h>

int check_pas();
int check_email();
void save_user();
int check_login();
int check_name();
void safhe();
void find_pas();
void login();
void new_user();
void entery();
void table(); 
void sort();
void new_game();
void load_game();
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
    move(5,60);
    for(int i=0 ; i<20 ; i++){
        printw("*");
        move(5+i,60);
    }
    move(5,60);
    for(int i=0 ; i<50 ; i++){
        printw("*");
        move(5,60+i);
    }
    for(int i=0 ; i<20 ; i++){
        printw("*");
        move(5+i,110);
    }
    move(24,60);
    for(int i=0 ; i<=51 ; i++){
        printw("*");
        move(24,60+i);
    }
}
void find_pas(const char* filename){
    attron(COLOR_PAIR(3));
    move(17,61);
    clrtoeol();
    mvprintw(16,61,"Email address:");
    char email[50];
    move(20,61);
    clrtoeol();
    scanw("%s",email);
    FILE *file=fopen(filename,"r");
    User user;
    int i=0;
    while (fscanf(file, "%s %s %s",user.name,user.password,user.email) != EOF)
    {
        if(strcmp(user.email , email)==0){
            i++;
            mvprintw(21,61,"Your password is: %s",user.password);
            fclose(file);
            break;
        }
    }
    attroff(COLOR_PAIR(3));
    if(i==0){
        attron(COLOR_PAIR(2));
        mvprintw(20,61,"Your email-address can't be found.");
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
void table(const char* filename){
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
    mvprintw(3, 20, "Rank     username"); mvprintw(3,40,"score  gold  number_of_games  first_Game_Time");
    for(int i=0; i<66 ; i++){
        mvprintw(4,20+i,"-");
    }
    attroff(COLOR_PAIR(2));
    for(int i=0 ; i<count ; i++){
        time_t currentTime = time(NULL);
        double experience = difftime(currentTime, users[i].first_Game_Time) / (60 * 60);
        if(i==0){
            attron(COLOR_PAIR(3) | A_BOLD);
            mvprintw(i+5,20,"Goat      %s",users[i].name);
            mvprintw(i+5,43,"%d    %d",users[i].score,users[i].gold);
            mvprintw(i+5,60,"%d",users[i].number_of_games);
            mvprintw(i+5,73,"%.2f",experience);
            attroff(COLOR_PAIR(3) | A_BOLD);
        }
        else if(i==1){
            attron(COLOR_PAIR(3) | A_BOLD);
            mvprintw(i+5,20,"Legend    %s",users[i].name);
            mvprintw(i+5,43,"%d    %d",users[i].score,users[i].gold);
            mvprintw(i+5,60,"%d",users[i].number_of_games);
            mvprintw(i+5,73,"%.2f",experience);
            attroff(COLOR_PAIR(3) | A_BOLD);
        }
        else if(i==2){
            attron(COLOR_PAIR(3) | A_BOLD);
            mvprintw(i+5,20,"Silver    %s",users[i].name);
            mvprintw(i+5,43,"%d    %d",users[i].score,users[i].gold);
            mvprintw(i+5,60,"%d",users[i].number_of_games);
            mvprintw(i+5,73,"%.2f",experience);
            attroff(COLOR_PAIR(3) | A_BOLD);
        }
        else{
            mvprintw(i+5,20," %d        %s",i+1,users[i].name);
            mvprintw(i+5,43,"%d    %d",users[i].score,users[i].gold);
            mvprintw(i+5,60,"%d",users[i].number_of_games);
            mvprintw(i+5,73,"%.2f",experience);
        }
        
    }
    attroff(COLOR_PAIR(2));
    refresh();
}
void new_game(){
    clear();
}
void load_game(const char*filename){
    clear();
}
void menu(const char*name ){
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(3,5,"Welcome %s",name);
    attroff(COLOR_PAIR(1));
    refresh();
    int choice;
    initscr();
    start_color();
    attron(COLOR_PAIR(3));
    mvprintw(5, 10, "1- New Game");
    mvprintw(7, 10, "2- Load Game");
    mvprintw(9, 10, "3- Table");
    mvprintw(11, 10, "4- Exit");
    attroff(COLOR_PAIR(3));
    mvprintw(13, 10, "Enter your choice: ");
    refresh();
    while (TRUE) {
        move(13,29);
        clrtoeol();
        move(13,29);
        scanw("%d", &choice);
        refresh();
        switch (choice) {
            case 1:
                new_game();
                break;
            case 2:
                load_game("users game");
                break;
            case 3:
                table("users.txt");
                break;
            case 4:
                move(18,62);
                clear();
                attron(COLOR_PAIR(2));
                mvprintw(25, 75, "I hope you enjoy the game.");
                refresh();
                attroff(COLOR_PAIR(2));
                getch();
                break;
            default:
                mvprintw(15, 10, "Invalid choice! Please try again.");
                refresh();
                break;
        }
    if(choice>0 && choice<5){
        break;
    }
    }
}
void login(){
    safhe();
    char name[20];
    char password[20];
    attron(COLOR_PAIR(1));
    mvprintw(10,62,"User Name:");
    mvprintw(13,62,"Password:");
    mvprintw(15,62,"If you forgot password,writ 3 in password");
    attroff(COLOR_PAIR(1));
    while (TRUE)
    {
        move(10,74);
        clrtoeol();
        scanw("%s",name);safhe();
        move(13,74);
        clrtoeol();
        scanw("%s",password);safhe();
        if(strcmp(password,"3")==0){
            find_pas("users.txt");
        }
        else{
            clrtoeol();
            if(check_login("users.txt" , name , password)){
                move(23,72);
                clrtoeol();
                break;
            }
            else{
                move(23,72);
                clrtoeol();
                attron(COLOR_PAIR(2));
                printw("Your name/password isn't correct");safhe();
                attroff(COLOR_PAIR(2));
            }
        } 
    }
    move(23,72);
    attron(COLOR_PAIR(3));
    printw("press any key to continue");safhe();
    refresh();
    getchar();
    attroff(COLOR_PAIR(3));
    menu(name);
    refresh();
}
void new_user(){
    safhe();
    User user;
    attron(COLOR_PAIR(1));
    mvprintw(10,62,"User Name:");
    mvprintw(15,62,"Password:");
    mvprintw(20,62,"Email Adress:");
    attroff(COLOR_PAIR(1));
    while (TRUE)
    {
        move(10,73);
        clrtoeol();
        scanw("%s",user.name);safhe();
        if(check_name("users.txt",user.name)){
            move(11,73);
            clrtoeol();
            break;
        }
        else{
            move(11,73);
            attron(COLOR_PAIR(2));
            printw("your username has taken befor.");safhe();
            clrtoeol();
            attroff(COLOR_PAIR(2));
        }
    }
    move(15,73);
    while(true){
        clrtoeol();
        scanw("%s",user.password);safhe();
        move(16,62);
        if(check_pas(user.password) == 0){
            attron(COLOR_PAIR(2));
            printw("your password isn't correct");safhe();
            clrtoeol();
            attroff(COLOR_PAIR(2));
            move(15,73);
        }
        else{
            clrtoeol();
            break;
        }
    }
    move(20,76);
    while(true){
        clrtoeol();
        scanw("%s",user.email);safhe();
        move(21,62);
        if(check_email(user.email) == 0){
            attron(COLOR_PAIR(2));
            printw("your Email isn't correct");safhe();
            clrtoeol();
            attroff(COLOR_PAIR(2));
            move(20,76);
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
    move(22,68);
    attron(COLOR_PAIR(3));
    save_user("users.txt",&user);
    printw("Your account save succesfully.");
    mvprintw(23,70,"press any key to continue.");
    refresh();
    attroff(COLOR_PAIR(3));
    getch();
    clear();
    entery();
}
void entery(){
    safhe();
    attron(COLOR_PAIR(1));
    move(6,62);
    printw("1-login");
    move(10,62);
    printw("2-Creat New account");
    move(14,62);
    printw("3-Guest");
    move(18,62);
    printw("4-exit");
    attroff(COLOR_PAIR(2));
    int ch;
    while (true) { 
        mvprintw(20, 62, "Please enter your choice: ");
        refresh();
        clrtoeol(); 
        scanw("%d", &ch); safhe();
        if (ch < 1 || ch > 4) { 
            attron(COLOR_PAIR(2));
            mvprintw(23, 62, "Invalid choice! Please try again."); safhe();
            attroff(COLOR_PAIR(2)); 
            refresh(); 
        } 
        else { 
            move(23,62);
            clrtoeol(); 
            break; 
        } 
        }
    switch (ch)
    {
    case 1:
        move(10,62);
        clear();
        login();
        break;
    case 2:
        move(10,62);
        clear();
        new_user();
    case 3:
        move(14,62);
        clear();
        break;
    case 4:
        move(18,62);
        clear();
        attron(COLOR_PAIR(2));
        mvprintw(25, 75, "I hope you enjoy the game.");
        refresh();
        attroff(COLOR_PAIR(2));
        getch();
        break;
    }
}
int main() {
    initscr();
    start_color();
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    init_pair(2,COLOR_RED,COLOR_BLACK);
    init_pair(3,COLOR_YELLOW,COLOR_BLACK);
    entery();
    refresh();             
    getch();               
    endwin();              
    return 0;
}
