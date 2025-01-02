#include <ncurses.h>
#include<stdio.h>
#include<string.h>
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
typedef struct {
    char name[50];
    char password[50];
    char email[50];
    int score;
    int gold;
} User;
void save_user(const char *filename, User *user) {
    FILE *file = fopen(filename, "a");
    fprintf(file, "%s %s %s %d\n", user->name, user->password, user->email,user->score);
    fclose(file);
}
int check_login(const char *filename , const char* name , const char* password){
    FILE *file =fopen(filename,"r");
    User user;
    while(fscanf(file, "%s %s %s", user.name, user.password, user.email) != EOF){
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
    while (fscanf(file, "%s %s %s %d", users[count].name, users[count].password, users[count].email, &users[count].score) != EOF)
    {
        count++;
    }
    fclose(file);
    sort(users, count);
    mvprintw(3, 10, "Rank - Username Score"); 
    mvprintw(4, 10, "---------------------------");
    for(int i=0 ; i<count ; i++){
        mvprintw(i+6,10,"%d-%s       %d",i+1,users[i].name ,users[i].score);
    }
    refresh();
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
        scanw("%s",name);
        move(13,74);
        clrtoeol();
        scanw("%s",password);
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
                printw("Your name/password isn't correct");
                attroff(COLOR_PAIR(2));
            }
        } 
    }
    move(23,72);
    attron(COLOR_PAIR(3));
    printw("press any key to continue");
    refresh();
    getchar();
    attroff(COLOR_PAIR(3));
    table("users.txt");
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
        scanw("%s",user.name);  
        if(check_name("users.txt",user.name)){
            move(11,73);
            clrtoeol();
            break;
        }
        else{
            move(11,73);
            attron(COLOR_PAIR(2));
            printw("your username has taken befor.");
            clrtoeol();
            attroff(COLOR_PAIR(2));
        }
    }
    move(15,73);
    while(true){
        clrtoeol();
        scanw("%s",user.password);
        move(16,62);
        if(check_pas(user.password) == 0){
            attron(COLOR_PAIR(2));
            printw("your password isn't correct");
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
        scanw("%s",user.email);
        move(21,62);
        if(check_email(user.email) == 0){
            attron(COLOR_PAIR(2));
            printw("your Email isn't correct");
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
    move(22,70);
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
        scanw("%d", &ch); 
        if (ch < 1 || ch > 4) { 
            attron(COLOR_PAIR(2));
            mvprintw(23, 62, "Invalid choice! Please try again."); 
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
    init_pair(3,COLOR_BLACK,COLOR_YELLOW);
    entery();
    clear();
    refresh();             
    getch();               
    endwin();              
    return 0;
}