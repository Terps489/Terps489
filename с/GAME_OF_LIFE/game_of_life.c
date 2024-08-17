#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define size1 25
#define size2 80

void print();
int start();
void functions(int mass_c[size1 + 2][size2 + 2], int mass_b[size1 + 2][size2 + 2], int *speed);
void output(int mass[size1 + 2][size2 + 2]);
void movement(int mass_c[size1 + 2][size2 + 2], int mass_b[size1 + 2][size2 + 2]);
void newmove(int mass_c[size1 + 2][size2 + 2], int mass_b[size1 + 2][size2 + 2], int *speed);
void matrixDOP(int mass[size1 + 2][size2 + 2]);
int movecheck(int mass[size1 + 2][size2 + 2], int i, int j);

int main() {
    if (start())
        return 1;
    else
        return 0;
}

int start() {
    int flag = 1;
    int mass_c[size1 + 2][size2 + 2], mass_b[size1 + 2][size2 + 2];
    for (int i = 1; i < size1 + 1; i++)
        for (int j = 1; j < size2 + 1; j++)
            if (scanf("%d", &mass_c[i][j]) != 1) flag = 0;
    initscr();
    noecho();
    timeout(0);
    if (freopen("/dev/tty", "r", stdin) != NULL) {
        if (flag) {
            int speed = 1000000;
            functions(mass_c, mass_b, &speed);
        }
    }
    endwin();
    return flag;
}

void functions(int mass_c[size1 + 2][size2 + 2], int mass_b[size1 + 2][size2 + 2], int *speed) {
    char move;
    move = getch();
    if (move == 'w') {
        *speed /= 2;
    } else if (move == 's') {
        *speed *= 2;
    } else if (move == 'q') {
        return;
    }
    print();
    matrixDOP(mass_c);
    output(mass_c);

    usleep(*speed);
    clear();

    movement(mass_c, mass_b);
    newmove(mass_c, mass_b, speed);
}

void newmove(int mass_c[size1 + 2][size2 + 2], int mass_b[size1 + 2][size2 + 2], int *speed) {
    int count = 0;
    for (int i = 1; i < size1 + 1; i++) {
        for (int j = 1; j < size2 + 1; j++) {
            mass_c[i][j] = mass_b[i][j];
            if (mass_c[i][j] == 1) count++;
        }
    }
    if (count > 0) functions(mass_c, mass_b, speed);
}

void output(int mass[size1 + 2][size2 + 2]) {
    for (int i = 1; i < size1 + 1; i++) {
        for (int j = 1; j < size2 + 1; j++) {
            if (mass[i][j] == 1) {
                printw("#");
            } else {
                printw(" ");
            }
        }
        if (i != size1) printw("\n");
    }
    refresh();
}

void movement(int mass_c[size1 + 2][size2 + 2], int mass_b[size1 + 2][size2 + 2]) {
    for (int i = 1; i < size1 + 1; i++)
        for (int j = 1; j < size2 + 1; j++) mass_b[i][j] = movecheck(mass_c, i, j);
}

void matrixDOP(int mass[size1 + 2][size2 + 2]) {
    mass[0][0] = mass[size1][size2];
    mass[0][size2 + 1] = mass[size1][1];
    mass[size1 + 1][0] = mass[1][size2];
    mass[size1 + 1][size2 + 1] = mass[1][1];
    for (int i = 1; i <= size1; i++) {
        mass[i][0] = mass[i][size2];
        mass[i][size2 + 1] = mass[i][1];
    }
    for (int j = 1; j <= size2; j++) {
        mass[0][j] = mass[size1][j];
        mass[size1 + 1][j] = mass[1][j];
    }
}

int movecheck(int mass[size1 + 2][size2 + 2], int i, int j) {
    int count = 0;
    for (int a = -1; a <= 1; a++) {
        for (int b = -1; b <= 1; b++) {
            if (a != 0 || b != 0) {
                count += mass[i + a][j + b];
            }
        }
    }

    if (mass[i][j] == 1) {
        return (count == 2 || count == 3);
    } else {
        return (count == 3);
    }
}

void print() { printw("speed: w - increase, s - decrease, q - quit\n"); }
