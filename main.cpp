#include <iostream>
#include <ncurses.h>

void config() {
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    curs_set(0);
}

void shape(int size, int y, int x, char ch) {
    clear();
    size *= 2;
    for(int i = 1; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(i == size / 2) {
                mvaddch(y - i, x - size - j + 2, ch);
            }
            else if(j == 2 * i) {
                // Bottom part
                mvaddch(y - i, x - j + 1, ch);
            }
            else if(j - size == 2 * (i - size)) {
                // Upper part
                mvaddch(y - i, x - size + j + 1, ch);
            }

        }
    }
}

void move_shape(int& size, int& y, int& x, int key) {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    switch(key) {
        case KEY_UP:
            if(y >= size * 2)
                --y;
            break;
        case KEY_DOWN:
            if(y < yMax)
                ++y;
            break;
        case KEY_LEFT:
            if(x >= size * 2)
                --x;
            break;
        case KEY_RIGHT:
            if(x < xMax)
                ++x;
            break;
        case '-':
            if( size >= 3)
                --size;
            break;
        case '+':
        case '=':
            if(x >= size * 2 && y > size * 2)
                ++size;
            break;
        case KEY_RESIZE:
            if(size * 2 >= yMax || size * 2 >= xMax)
                --size;
            if(y >= yMax || x >= xMax) {
                y = yMax - 1;
                x = xMax - 1;
            }
            break;
    }
}

void draw(int& size, int& y, int& x, int ch) {
    while(true) {
        shape(size, y, x, ch);
        refresh();

        int key = getch();
        move_shape(size, y, x, key);
        refresh();

        if(key == 'q')
            break;
    }
}

int main() {
    std::cout << "Press Q to quit" << std::endl;

    int size;
    std::cout << "Size: ";
    std::cin >> size;

    char ch;
    std::cout << "ASCII character: ";
    std:: cin >> ch;

    initscr();
    config();

    int y, x;
    getmaxyx(stdscr, y, x);

    draw(size, y, x, ch);

    endwin();
    return 0;
}