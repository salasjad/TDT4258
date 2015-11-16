#include "graphic.h"
#include <stdio.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
//#include <linux/kernel.h>
//#include <linux/module.h>
//#include <linux/timer.h>



unsigned long volatile time_button_appears;
unsigned long volatile time_button_pressed;

struct fb_copyarea rect;
int fb;
__u16 *screen;
__u16 color = BLUE; 


void init_rect()
{
    rect.dx = 0;
    rect.dy = 0;
    rect.width = 0;
    rect.height = 0;
}

void update_rect(__u16 x1, __u16 y1, __u16 x2, __u16 y2)
{
    // first call after init
    if (rect.width == 0)
    {
        rect.dx = x1;
        rect.dy = y1;
        rect.width = x2 - x1;
        rect.height = y2 - y1;
    }      
    else
    {
        // extend width to the left
        if (x1 < rect.dx)
            rect.dx = x1;
        // extend width to the right
        if (x2 > (rect.dx + rect.width))
            rect.width = x2 - rect.dx;
            
        // extend height to the top
        if (y1 < rect.dy)
            rect.dy = y1;
        // extend height to the top
        if (y2 > (rect.dy + rect.height))
            rect.height = y2 - rect.dy;
            
    }
}               

void clear_LCD()
{
    __u16 previous_color = color;
    set_color(BLACK);
    draw_fill_rect(0, 0, WIDTH, HEIGHT);
    set_color(previous_color);
}

void clear_score()
{
    __u16 previous_color = color;
    set_color(BLACK);
    draw_fill_rect(0, 0, WIDTH, MENU_SIZE_FROM_TOP);
    set_color(previous_color);
} 

void clear_score_p1()
{
    __u16 previous_color = color;
    set_color(BLACK);
    draw_fill_rect(X_COORDINATE_SCORE_PLAYER1, 0, X_COORDINATE_SCORE_PLAYER2 - X_COORDINATE_SCORE_PLAYER1, MENU_SIZE_FROM_TOP);
    set_color(previous_color);
}

void clear_score_p2()
{
    __u16 previous_color = color;
    set_color(BLACK);
    draw_fill_rect(X_COORDINATE_SCORE_PLAYER2, 0, WIDTH - X_COORDINATE_SCORE_PLAYER2, MENU_SIZE_FROM_TOP);
    set_color(previous_color);
}

void clear_time()
{
    __u16 previous_color = color;
    set_color(BLACK);
    draw_fill_rect(X_COORDINATE_TIME_ELAPSED, Y_COORDINATE_TIME_ELAPSED - 2*SEGMENT_LENGTH, 
                   4*SPACE_BETWEEN_DIGITS, 2*SEGMENT_LENGTH + 2);
    set_color(previous_color);
}
/*
void score_rect()
{
    rect.dx = X_COORDINATE_SCORE_PLAYER1;
    rect.dy = -2*SEGMENT_LENGTH;
    rect.width = WIDTH - X_COORDINATE_SCORE_PLAYER1;
    rect.height = 2*SEGMENT_LENGTH;
}

void time_rect()
{
    rect.dx = X_COORDINATE_TIME_ELAPSED;
    rect.dy = Y_COORDINATE_TIME_ELAPSED - 2*SEGMENT_LENGTH;
    rect.width = 4*SPACE_BETWEEN_DIGITS;
    rect.height = 2*SEGMENT_LENGTH + 2 ;
}

void button_rect()
{
    rect.dx = LEFT_X;
    rect.dy = TOP_Y;
    rect.width = WIDTH-LEFT_X;
    rect.height = HEIGHT-TOP_Y;
}*/

void set_color(__u16 COLOR){
    color = COLOR;
}

int init_display(void)
{
    init_rect();

    fb = open("/dev/fb0", O_RDWR);
    if(!fb) 
    { 
        return EXIT_FAILURE; 
    }

    // memory map driver
    screen = mmap(0, WIDTH*HEIGHT*2, PROT_READ|PROT_WRITE, MAP_SHARED, fb, 0);
    if(screen == MAP_FAILED) 
    { 
        return EXIT_FAILURE; 
    }
    
    return 0;
}



void draw_score(__u8 score1, __u8 score2)
{
    __u16 previous_color = color;
    clear_score();
    set_color(GREEN);
    draw_digits(score1, X_COORDINATE_SCORE_PLAYER1, 2*SEGMENT_LENGTH);
    draw_digits(score2, X_COORDINATE_SCORE_PLAYER2, 2*SEGMENT_LENGTH);
    set_color(previous_color);
}

void draw_score_p1(__u8 score)
{
    __u16 previous_color = color;
    clear_score_p1();
    set_color(GREEN);
    draw_digits(score, X_COORDINATE_SCORE_PLAYER1, 2*SEGMENT_LENGTH); 
    set_color(previous_color);
}

void draw_score_p2(__u8 score)
{
    __u16 previous_color = color;
    clear_score_p2();
    set_color(GREEN);
    draw_digits(score, X_COORDINATE_SCORE_PLAYER2, 2*SEGMENT_LENGTH); 
    set_color(previous_color);
}

void draw_game()
{
    int i;
    for (i = 0; i < BUTTONS_DISPLAYED; i++)
    {
        draw_button(i, false, BLACK);
    }
}


void draw_button(__u8 id, bool filled, __u16 circle_color)
{
    if (id == LEFT)
    { 
        if (filled) draw_fill_circle(LEFT_X, LEFT_Y, RECT_HEIGHT, circle_color);
        else draw_circle(LEFT_X, LEFT_Y, RECT_HEIGHT);
        printf("Drawing circle from %d, %d with width: %d and height: %d\n", LEFT_X, LEFT_Y, RECT_WIDTH, RECT_HEIGHT);
    }
    if (id == TOP)
    {
        if (filled) draw_fill_circle(TOP_X, TOP_Y, RECT_HEIGHT, circle_color);
        else draw_circle(TOP_X, TOP_Y, RECT_HEIGHT);
        printf("Drawing circle from %d, %d with width: %d and height: %d\n", TOP_X, TOP_Y, RECT_WIDTH, RECT_HEIGHT);
    }
    if (id == RIGHT)
    {
        if (filled) draw_fill_circle(RIGHT_X, RIGHT_Y, RECT_HEIGHT, circle_color);
        else draw_circle(RIGHT_X, RIGHT_Y, RECT_HEIGHT);
        printf("Drawing circle from %d, %d with width: %d and height: %d\n", RIGHT_X, RIGHT_Y, RECT_WIDTH, RECT_HEIGHT);
    }
    if (id == BOTTOM)
    {
        if (filled) draw_fill_circle(BOTTOM_X, BOTTOM_Y, RECT_HEIGHT, circle_color);
        else draw_circle(BOTTOM_X, BOTTOM_Y,  RECT_HEIGHT);
        printf("Drawing circle from %d, %d with width: %d and height: %d\n", BOTTOM_X, BOTTOM_Y, RECT_WIDTH, RECT_HEIGHT);
    }
    
}

void reset_button (int button) 
{
    __u16 previous_color = color;
    set_color(BLACK);
    draw_button(button, true, BLACK);
    set_color(previous_color);
    draw_button(button, false, BLACK);
    
}


void draw_rect(int x, int y, int width, int height)
{
    int i = 0;
    int x2 = x + width;
    int y2 = y + height;
    int y_index = y * WIDTH;
    int y2_index = y2 * WIDTH;
    
    update_rect(x, y, x2, y2);
    
    draw_line(x, y, x2, y);
    draw_line(x, y2, x2, y2);
    draw_line(x, y, x, y2);
    draw_line(x2, y, x2, y2);
    
}

void draw_fill_rect(int x, int y, int width, int height)
{
    int i = 0;
    int x2 = x + width;
    int y2 = y + height;
    
    update_rect(x, y, x2, y2);  

    for (i = y; i < y2; i++)
    {
        draw_line(x, i, x2, i);
    }  
    
}

// x and y are the coordinates on left top side of the numeral (segments)
void draw_one (int x, int y) {
    draw_line (x+SEGMENT_LENGTH, y, x+SEGMENT_LENGTH, y-2*SEGMENT_LENGTH);
}

void draw_zero (int x, int y) {
    draw_rect(x, y-2*SEGMENT_LENGTH, SEGMENT_LENGTH, 2*SEGMENT_LENGTH);
}

void draw_five (int x, int y) {
    draw_line (x, y, x+SEGMENT_LENGTH, y);
    draw_line (x+SEGMENT_LENGTH, y, x+SEGMENT_LENGTH, y-SEGMENT_LENGTH);
    draw_line (x+SEGMENT_LENGTH, y-SEGMENT_LENGTH, x, y-SEGMENT_LENGTH);
    draw_line (x, y-SEGMENT_LENGTH, x, y-2*SEGMENT_LENGTH);
    draw_line (x, y-2*SEGMENT_LENGTH, x+SEGMENT_LENGTH, y-2*SEGMENT_LENGTH); 
}
  
void draw_three (int x, int y) {
    draw_line (x, y, x+SEGMENT_LENGTH, y);
    draw_line (x+SEGMENT_LENGTH, y, x+SEGMENT_LENGTH, y-2*SEGMENT_LENGTH);
    draw_line (x+SEGMENT_LENGTH, y-SEGMENT_LENGTH, x, y-SEGMENT_LENGTH);
    draw_line (x, y-2*SEGMENT_LENGTH, x+SEGMENT_LENGTH, y-2*SEGMENT_LENGTH); 
}

void draw_four (int x, int y) {
    draw_line (x, y-SEGMENT_LENGTH, x, y-2*SEGMENT_LENGTH);
    draw_line (x+SEGMENT_LENGTH, y, x+SEGMENT_LENGTH, y-2*SEGMENT_LENGTH);
    draw_line (x+SEGMENT_LENGTH, y-SEGMENT_LENGTH, x, y-SEGMENT_LENGTH);
    
}

void draw_two (int x, int y) {
    draw_line (x, y, x+SEGMENT_LENGTH, y);
    draw_line (x, y, x, y-SEGMENT_LENGTH);
    draw_line (x+SEGMENT_LENGTH, y-SEGMENT_LENGTH, x, y-SEGMENT_LENGTH);
    draw_line (x+SEGMENT_LENGTH, y-SEGMENT_LENGTH, x+SEGMENT_LENGTH, y-2*SEGMENT_LENGTH);
    draw_line (x, y-2*SEGMENT_LENGTH, x+SEGMENT_LENGTH, y-2*SEGMENT_LENGTH);
}

void draw_six (int x, int y) {
    draw_line (x, y, x+SEGMENT_LENGTH, y);
    draw_line (x+SEGMENT_LENGTH, y, x+SEGMENT_LENGTH, y-SEGMENT_LENGTH);
    draw_line (x+SEGMENT_LENGTH, y-SEGMENT_LENGTH, x, y-SEGMENT_LENGTH);
    draw_line (x, y, x, y-2*SEGMENT_LENGTH);
    draw_line (x, y-2*SEGMENT_LENGTH, x+SEGMENT_LENGTH, y-2*SEGMENT_LENGTH); 
}

void draw_seven (int x, int y) {
    draw_line (x, y-2*SEGMENT_LENGTH, x+SEGMENT_LENGTH, y-2*SEGMENT_LENGTH);
    draw_line (x+SEGMENT_LENGTH, y, x+SEGMENT_LENGTH, y-2*SEGMENT_LENGTH);
    }

void draw_eight (int x, int y) {
    draw_rect(x,y-2*SEGMENT_LENGTH,SEGMENT_LENGTH, 2*SEGMENT_LENGTH);
    draw_line (x+SEGMENT_LENGTH, y-SEGMENT_LENGTH, x, y-SEGMENT_LENGTH);
}

void draw_nine (int x, int y) {
    draw_line (x, y-2*SEGMENT_LENGTH, x+SEGMENT_LENGTH, y-2*SEGMENT_LENGTH);
    draw_line (x, y-2*SEGMENT_LENGTH, x, y-SEGMENT_LENGTH);
    draw_line (x+SEGMENT_LENGTH, y, x+SEGMENT_LENGTH, y-2*SEGMENT_LENGTH);
    draw_line (x+SEGMENT_LENGTH, y-SEGMENT_LENGTH, x, y-SEGMENT_LENGTH);
    
}

void digit_switch (int digit, int x, int y) {

            switch (digit) {
            case 0:
            draw_zero(x,y);
            break;
            
            case 1:
            draw_one(x,y);
            break;

            case 2:
            draw_two(x,y);
            break;

            case 3:
            draw_three(x,y);
            break;

            case 4:
            draw_four(x,y);
            break;

            case 5:
            draw_five(x,y);
            break;

            case 6:
            draw_six(x,y);
            break;

            case 7:
            draw_seven(x,y);
            break;

            case 8:
            draw_eight(x,y);
            break;

            case 9:
            draw_nine(x,y);
            break;
        }
}

void draw_time(int time, __u16 time_color)
{
    __u16 previous_color = color;
    set_color(time_color);
    clear_time();
    draw_digits(time, X_COORDINATE_TIME_ELAPSED, Y_COORDINATE_TIME_ELAPSED);
    set_color(previous_color);
}

//Print on the screen a 4 digit score (we assume that we will not play more than ten thousands games in a row)
void draw_digits (int number, int x, int y) {
    int fourth_digit = number % 10;
    int third_digit = ((number - fourth_digit)% 100) / 10 ;
    int second_digit = ((number - fourth_digit - 10*third_digit) / 100) %10;
    int first_digit = (number - second_digit*100 - fourth_digit - 10*third_digit) / 1000;

   // printf("score is %d%d\n", third_digit, fourth_digit);


        digit_switch(first_digit,x,y);
        x+=SPACE_BETWEEN_DIGITS;
        digit_switch(second_digit,x,y);
        x+=SPACE_BETWEEN_DIGITS;
        digit_switch(third_digit,x,y);
        x+=SPACE_BETWEEN_DIGITS;
        digit_switch(fourth_digit,x,y);
        x+=SPACE_BETWEEN_DIGITS;

}
    

void draw_line(int x0, int y0, int x1, int y1)
{
   int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
   int err = dx+dy, e2;                                   /* error value e_xy */
   update_rect(x0, y0, x1, y1); 
                                                    
   for (;;){                                                          /* loop */
      plot(x0, y0);                              
      e2 = 2*err;                                   
      if (e2 >= dy) {                                         /* e_xy+e_x > 0 */
         if (x0 == x1) break;                       
         err += dy; x0 += sx;                       
      }                                             
      if (e2 <= dx) {                                         /* e_xy+e_y < 0 */
         if (y0 == y1) break;
         err += dx; y0 += sy;
      }
   }
   
   
}
     
void draw_circle(int xm, int ym, int r)
{
   update_rect(xm-r, ym-r, xm+r, ym+r);
   int x = -r, y = 0, err = 2-2*r;                /* bottom left to top right */
   do {                                          
      plot(xm-x, ym+y);                            /*   I. Quadrant +x +y */
      plot(xm-y, ym-x);                            /*  II. Quadrant -x +y */
      plot(xm+x, ym-y);                            /* III. Quadrant -x -y */
      plot(xm+y, ym+x);                            /*  IV. Quadrant +x -y */
      r = err;                                   
      if (r <= y) err += ++y*2+1;                             /* e_xy+e_y < 0 */
      if (r > x || err > y)                  /* e_xy+e_x > 0 or no 2nd y-step */
         err += ++x*2+1;                                     /* -> x-step now */
   } while (x < 0);
   
}

// TO-DO: needs testing
// written without board
// brute force algorithm - may be interesting to try changed version of draW_circle from above
void draw_fill_circle(int xm, int ym, int r,  __u16 circle_color)
{
    int y;
    int x;
    int r2 = r * r;
    
    __u16 previous_color = color;
    set_color(circle_color);

    update_rect(xm-r, ym-r, xm+r, ym+r);
    for(y = -r; y <= r; y++)
        for(x = -r; x <= r; x++)
            if( (x*x + y*y) <= r2)
                plot(xm + x, ym + y);
    set_color(previous_color);                      
}

void plot(int x, int y)
{
    screen[y * WIDTH + x] = color;
}

void redraw()
{
    ioctl(fb, 0x4680, &rect);
    init_rect();
}

void destroy_display()
{
    close(fb);
}
