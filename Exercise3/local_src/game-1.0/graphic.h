#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <asm/types.h>

#define LEFT 0
#define TOP 1
#define RIGHT 2
#define BOTTOM 3

#define WIDTH 320
#define HEIGHT 240
#define BUTTONS_DISPLAYED 4

#define MENU_SIZE_FROM_TOP 60
#define GAME_HEIGHT (HEIGHT - MENU_SIZE_FROM_TOP)

#define RECT_WIDTH 40
#define RECT_HEIGHT 20

#define X_GRID_6 (WIDTH / 6)
#define Y_GRID_6 (GAME_HEIGHT / 6)

#define TOP_X (X_GRID_6 * 3 - RECT_WIDTH / 2)
#define TOP_Y ((Y_GRID_6 * 1 - RECT_HEIGHT / 2) + MENU_SIZE_FROM_TOP)

#define LEFT_X (X_GRID_6 * 1 - RECT_WIDTH / 2)
#define LEFT_Y ((Y_GRID_6 * 3 - RECT_HEIGHT / 2) + MENU_SIZE_FROM_TOP)

#define RIGHT_X (X_GRID_6 * 5 - RECT_WIDTH / 2)
#define RIGHT_Y ((Y_GRID_6 * 3 - RECT_HEIGHT / 2) + MENU_SIZE_FROM_TOP)

#define BOTTOM_X (X_GRID_6 * 3 - RECT_WIDTH / 2)
#define BOTTOM_Y ((Y_GRID_6 * 5 - RECT_HEIGHT / 2) + MENU_SIZE_FROM_TOP)

#define FB_DRAW 0x4680

#define BLUE 0x000F
#define GREEN 0x07F0
#define RED 0xF800
#define ORANGE 0x7FFF
#define BLACK 0

#define X_COORDINATE_SCORE_PLAYER1 80
#define X_COORDINATE_SCORE_PLAYER2 230
#define X_COORDINATE_TIME_ELAPSED 100
#define Y_COORDINATE_TIME_ELAPSED 145

#define SEGMENT_LENGTH 15 
#define SPACE_BETWEEN_DIGITS 20

int init_display(void);
void time_rect(void);
void update_rect(__u16 x1, __u16 y1, __u16 x2, __u16 y2);
void destroy_display(void);
void clear_LCD(void);
void clear_score(void);
void clear_score_p1(void);
void clear_score_p2(void);
void clear_time(void);
void draw_score(__u8 score1, __u8 score2);
void draw_score_p1(__u8 score);
void draw_score_p2(__u8 score);
void draw_game(void);
void draw_time(int time, __u16 time_color);
void draw_button(__u8 id, bool filled, __u16 circle_color);
void reset_button (int button);
void draw_rect(int x, int y, int width, int height);
void draw_fill_rect(int x, int y, int width, int height);
void draw_line(int x0, int y0, int x1, int y1);
void draw_circle(int xm, int ym, int r);
void draw_fill_circle(int xm, int ym, int r, __u16 circle_color);
void plot(int x, int y);
void redraw(void);
void draw_digits (int number, int x, int y);
void digit_switch (int digit, int x, int y);
void draw_nine (int x, int y);
void draw_eight (int x, int y);
void draw_seven (int x, int y);
void draw_six (int x, int y);
void draw_five (int x, int y);
void draw_four (int x, int y);
void draw_three (int x, int y);
void draw_two (int x, int y);
void draw_zero (int x, int y);
void draw_one (int x, int y);
void set_color(__u16 COLOR);
