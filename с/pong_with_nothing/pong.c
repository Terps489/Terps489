#include <stdio.h>

#define HEIGHT 25
#define WIDTH 80
#define BALL_START_X (WIDTH / 2)
#define BALL_START_Y (HEIGHT / 2)
#define WIN 21
#define ROCKET1_START (HEIGHT / 2 - 1)
#define ROCKET2_START (HEIGHT / 2 - 1)

void drawer(int rocket1_coord_x, int rocket1_coord_y, int rocket2_coord_y, int rocket2_coord_x,
            int ball_coord_y, int ball_coord_x);
int ball_mode_changer(int ball_mode, int ball_coord_x, int ball_coord_y, int rocket1_coord_x,
                      int rocket1_coord_y, int rocket2_coord_x, int RACKET_COOR_Y);
int finish_score(int player1_score, int player2_score);
void screen_cleaner(void);
void score_drawer(int player1_score, int player2_score);
void rules(void);

int main() {
    int rocket1_coord_y = HEIGHT / 2 - 1;
    int rocket1_coord_x = 0;

    int rocket2_coord_y = HEIGHT / 2 - 1;
    int rocket2_coord_x = WIDTH;

    int ball_coord_y = BALL_START_Y;
    int ball_coord_x = BALL_START_X;

    int player1_score = 0;
    int player2_score = 0;

    char move;
    int ball_mode = 1;

    while (1) {
        rules();
        score_drawer(player1_score, player2_score);
        drawer(rocket1_coord_x, rocket1_coord_y, rocket2_coord_y, rocket2_coord_x, ball_coord_y,
               ball_coord_x);

        scanf("%c", &move);
        while (getchar() != '\n') {
        }

        if (move != 'a' && move != 'z' && move != 'k' && move != 'm' && move != ' ') {
            screen_cleaner();
            printf("ВВЕДЕНО НЕВЕРНОЕ ЗНАЧЕНИЕ!!!!!!!!!!!!\n");
            continue;
        }

        if (move == 'a' && rocket1_coord_y != 1) {
            rocket1_coord_y -= 1;
        } else if (move == 'z' && rocket1_coord_y != HEIGHT - 3) {
            rocket1_coord_y += 1;
        } else if (move == 'k' && rocket2_coord_y != 1) {
            rocket2_coord_y -= 1;
        } else if (move == 'm' && rocket2_coord_y != HEIGHT - 3) {
            rocket2_coord_y += 1;
        }

        ball_mode = ball_mode_changer(ball_mode, ball_coord_x, ball_coord_y, rocket1_coord_x, rocket1_coord_y,
                                      rocket2_coord_x, rocket2_coord_y);

        if (ball_mode == 1) {
            ball_coord_x += 1;
            ball_coord_y -= 1;
        }
        if (ball_mode == 2) {
            ball_coord_x += 1;
            ball_coord_y += 1;
        }
        if (ball_mode == 3) {
            ball_coord_x -= 1;
            ball_coord_y -= 1;
        }
        if (ball_mode == 4) {
            ball_coord_x -= 1;
            ball_coord_y += 1;
        }

        if (ball_coord_x < 1) {
            player2_score += 1;
            ball_coord_x = BALL_START_X;
            ball_coord_y = BALL_START_Y;
            rocket1_coord_y = ROCKET1_START;
            rocket2_coord_y = ROCKET2_START;
            ball_mode = 2;
        }
        if (ball_coord_x > WIDTH - 1) {
            player1_score += 1;
            ball_coord_x = BALL_START_X;
            ball_coord_y = BALL_START_Y;
            rocket1_coord_y = ROCKET1_START;
            rocket2_coord_y = ROCKET2_START;
            ball_mode = 4;
        }
        screen_cleaner();
        if (finish_score(player1_score, player2_score)) {
            break;
        }
    }
}

void drawer(int rocket1_coord_x, int rocket1_coord_y, int rocket2_coord_y, int rocket2_coord_x,
            int ball_coord_y, int ball_coord_x) {
    int string, col;
    for (string = 0; string <= HEIGHT; string++) {
        for (col = 0; col <= WIDTH; col++) {
            if (col == rocket1_coord_x && (string == rocket1_coord_y || string == rocket1_coord_y + 1 ||
                                           string == rocket1_coord_y + 2)) {
                printf("|");
                continue;
            }
            if (col == rocket2_coord_x && (string == rocket2_coord_y || string == rocket2_coord_y + 1 ||
                                           string == rocket2_coord_y + 2)) {
                printf("|");
            }
            if (string == ball_coord_y && col == ball_coord_x) {
                printf("0");
                continue;
            }
            if (col == WIDTH / 2 && string != 0 && string != HEIGHT) {
                printf("|");
                continue;
            }

            if (string == 0 || string == HEIGHT) {
                printf("-");
                continue;
            }

            printf(" ");
        }
        printf("\n");
    }
}

int ball_mode_changer(int ball_mode, int ball_coord_x, int ball_coord_y, int rocket1_coord_x,
                      int rocket1_coord_y, int rocket2_coord_x, int rocket2_coord_y) {
    int res = ball_mode;
    if (ball_coord_y == 1 && ball_mode == 1 && ball_coord_x == rocket2_coord_x - 1 &&
        ball_coord_y == rocket2_coord_y) {
        res = 4;
    }

    else if (ball_coord_y == HEIGHT - 1 && ball_mode == 2 && ball_coord_x == rocket2_coord_x - 1 &&
             ball_coord_y == rocket2_coord_y + 2) {
        res = 3;
    }

    else if (ball_coord_y == 1 && ball_mode == 3 && ball_coord_x == rocket1_coord_x + 1 &&
             ball_coord_y == rocket1_coord_y) {
        res = 2;
    }

    else if (ball_coord_y == HEIGHT - 1 && ball_mode == 4 && ball_coord_x == rocket1_coord_x + 1 &&
             ball_coord_y == rocket1_coord_y + 2) {
        res = 1;
    } else if (ball_coord_y == 1 && ball_mode == 1) {
        res = 2;
    }

    else if (ball_coord_y == 1 && ball_mode == 3) {
        res = 4;
    }

    else if (ball_coord_y == HEIGHT - 1 && ball_mode == 2) {
        res = 1;
    }

    else if (ball_coord_y == HEIGHT - 1 && ball_mode == 4) {
        res = 3;
    }

    else if (ball_mode == 4 && ball_coord_x == rocket1_coord_x + 1 &&
             (ball_coord_y == rocket1_coord_y || ball_coord_y == rocket1_coord_y + 1 ||
              ball_coord_y == rocket1_coord_y + 2))

    {
        res = 2;
    }

    else if (ball_mode == 3 && ball_coord_x == rocket1_coord_x + 1 &&
             (ball_coord_y == rocket1_coord_y || ball_coord_y == rocket1_coord_y + 1 ||
              ball_coord_y == rocket1_coord_y + 2)) {
        res = 1;
    }

    else if (ball_mode == 2 && ball_coord_x == rocket2_coord_x - 1 &&
             (ball_coord_y == rocket2_coord_y || ball_coord_y == rocket2_coord_y + 1 ||
              ball_coord_y == rocket2_coord_y + 2)) {
        res = 4;
    }

    else if (ball_mode == 1 && ball_coord_x == rocket2_coord_x - 1 &&
             (ball_coord_y == rocket2_coord_y || ball_coord_y == rocket2_coord_y + 1 ||
              ball_coord_y == rocket2_coord_y + 2)) {
        res = 3;
    }
    return res;
}

int finish_score(int player1_score, int player2_score) {
    int flag = 0;
    if (player1_score == WIN) {
        printf("\n\tПоздравляю! Игрок 1 Выиграл со счетом %d / %d.\n", player1_score, player2_score);
        flag = 1;
    } else if (player2_score == WIN) {
        printf("\n\tПоздравляю! Игрок 2 Выиграл со счетом %d / %d.\n", player2_score, player1_score);
        flag = 1;
    }
    return flag;
}

void screen_cleaner(void) { printf("\33[0d\33[2J"); }

void score_drawer(int player1_score, int player2_score) {
    printf("Игрок 1: %d | Игрок 2: %d\n", player1_score, player2_score);
}

void rules(void) {
    printf(
        "Управлять ракетками можно при помощи клавиш az и km или ' ', игра идет до "
        "счета %d.\n",
        WIN);
}
