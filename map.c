
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
    return !(r1.x + r1.width +2 < (r2.x) || 
             r2.x + r2.width +2 < (r1.x) || 
             r1.y + r1.height+2 < (r2.y) ||
             r2.y + r2.height+2 < (r1.y));
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

void dar(Room room, int dar[][2], int index) {
    int t1 = rand() % 4;
    int t2 = rand() % 4;
    if (t1 == t2) {
        t2 = (t1 + 1) % 4;
    }
    int pos;
    switch (t1) {
        case 0:
            pos = rand() % room.width;
            mvprintw(room.y, room.x + pos, "+");
            dar[index][0] = room.x + pos;
            dar[index][1] = room.y;
            break;
        case 1:
            pos = rand() % room.height;
            mvprintw(room.y + pos, room.x + room.width, "+");
            dar[index][0] = room.x + room.width;
            dar[index][1] = room.y + pos;
            break;
        case 2:
            pos = rand() % room.width;
            mvprintw(room.y + room.height, room.x + pos, "+");
            dar[index][0] = room.x + pos;
            dar[index][1] = room.y + room.height;
            break;
        default:
            pos = rand() % room.height;
            mvprintw(room.y + pos, room.x, "+");
            dar[index][0] = room.x;
            dar[index][1] = room.y + pos;
            break;
    }
}

void soton(Room room, int soton[][2], int index) {
    int x, y;
    x = (rand() % room.width);
    y = (rand() % room.height);
    if (x == 0)
        x++;
    if (y == 0)
        y++;
    x = room.x + x; 
    y = room.y + y;
    mvprintw(y, x, "O");
    soton[index][0] = x;
    soton[index][1] = y;
}

void draw(Room room, int soton_positions[][2], int *soton_index, int dar_positions[][2], int *dar_index) {
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
    dar(room, dar_positions, *dar_index);
    (*dar_index)++;
    soton(room, soton_positions, *soton_index);
    (*soton_index)++;
    attroff(COLOR_PAIR(4));
}

int check_move(int x, int y, Room room, int soton_positions[][2], int soton_index, int dar_positions[][2], int dar_index) {
    for (int i = 0; i < dar_index; i++) {
        if (x == dar_positions[i][0] && y == dar_positions[i][1]) {
            return 1;
        }
    }
    if (x > room.x && x < (room.x + room.width) && y > room.y && y < (room.y + room.height)) {
        for (int i = 0; i < soton_index; i++) {
            if (x == soton_positions[i][0] && y == soton_positions[i][1]) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int move_character(Room room, int *x, int *y, int soton_positions[][2], int soton_index, int dar_positions[][2], int dar_index) {
    int ch = getch();
    int newx = *x;
    int newy = *y;
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
    if (check_move(newx, newy, room, soton_positions, soton_index, dar_positions, dar_index)) {
        attron(COLOR_PAIR(3));
        mvprintw(*y, *x, ".");
        attroff(COLOR_PAIR(3));
        *x = newx;
        *y = newy;
        mvprintw(*y, *x, "I");
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

    int t = rand() % 3;
    int num_rooms = 6 + t;
    int max_x = 80;
    int max_y = 40;
    int soton_positions[num_rooms * 2][2]; 
    int dar_positions[num_rooms * 2][2]; 
    int soton_index = 0;
    int dar_index = 0;
    Room rooms[num_rooms];
    create_random_rooms(rooms, num_rooms, max_x, max_y);
    for (int i = 0; i < num_rooms; i++) {
        draw(rooms[i], soton_positions, &soton_index, dar_positions, &dar_index);
        refresh();
    }

    int x = rooms[0].x + 1;
    int y = rooms[0].y + 1;
    mvprintw(y, x, "I");
    refresh();

    while (1) {
        if (move_character(rooms[0], &x, &y, soton_positions, soton_index, dar_positions, dar_index) == 0) {
            break;
        }
        refresh();
    }
    refresh();
    getch();
    endwin();
    return 0;
}
