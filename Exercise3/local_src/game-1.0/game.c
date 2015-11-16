#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "graphic.h"
#include "efm32gg.h"

#define RESET_SCORE 8888



#define P1 1
#define P2 2

#define P1_LEFT 0x01
#define P1_TOP 0x02
#define P1_RIGHT 0x04
#define P1_BOTTOM 0x08

#define P2_LEFT 0x10
#define P2_TOP 0x20
#define P2_RIGHT 0x40
#define P2_BOTTOM 0x80

__u8 p1_score = 0;
__u8 p2_score = 0;
int p1_time = 0;
int p2_time = 0;
__u8 winner = 0;
int winner_time = 0;
__u8 blink = 0;

sigset_t mask, oldmask;
bool timer_expired = false;
struct itimerval timer;
int random_timer;

bool end_timer  = false;
bool orange_timer = false;

time_t t;

struct timeval time_button_pressed;
struct timeval time_button_appears;
int time_elapsed;
int button_value[2];


int score_player1 = 2663;
int score_player2 = 1245;

__u16 buf;
__u16 button_pressed = 0;
//extern __u16 color;

int file_gamepad_driver;
int random_button;

int init_driver(void);
int setup_handler(void);
void signal_handler(int signum);
void timer_handler(int signum);

 
int init_driver()
{
    file_gamepad_driver = open("/dev/driver-gamepad", O_RDWR);
    if(!file_gamepad_driver) 
    { 
        return EXIT_FAILURE; 
    }
    
    return 0;
} 

int setup_handler()
{
    struct sigaction action;

    memset(&action, 0, sizeof(action));
    action.sa_handler = signal_handler;
    action.sa_flags = 0;

    sigaction(SIGIO, &action, NULL);

    if (fcntl(file_gamepad_driver, F_SETOWN, getpid()) == -1)
        return -1;
        
    if (fcntl(file_gamepad_driver, F_SETFL, fcntl(file_gamepad_driver, F_GETFL) | FASYNC) == -1)
        return -1;
        
    return 0;
}

void time_handler()
{
     struct sigaction sa;
     

     /* Install timer_handler as the signal handler for SIGVTALRM. */
     memset (&sa, 0, sizeof (sa));
     sa.sa_handler = timer_handler;
     sigaction (SIGALRM, &sa, NULL);
}

void startTimer(__u32 sec)
{
    timer.it_value.tv_sec = sec;
    timer.it_value.tv_usec = 0;

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    /* Start a virtual timer. It counts down whenever this process is
      executing. */
    setitimer (ITIMER_REAL, &timer, NULL);
    timer_expired = false;

}

void stopTimer()
{
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 0;

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer (ITIMER_REAL, &timer, NULL);
}

void waitForButton()
{
    /* Set up the mask of signals to temporarily block. */
     sigemptyset(&mask);
     sigaddset(&mask, SIGALRM);

     /* Wait for a signal to arrive. */
     sigprocmask(SIG_BLOCK, &mask, &oldmask);
     sigsuspend(&oldmask);
     sigprocmask (SIG_UNBLOCK, &mask, NULL);
}

void waitForTimer()
{
    /* Set up the mask of signals to temporarily block. */
     sigemptyset (&mask);
     sigaddset (&mask, SIGIO);

     /* Wait for a signal to arrive. */
     sigprocmask (SIG_BLOCK, &mask, &oldmask);
     sigsuspend (&oldmask);
     sigprocmask (SIG_UNBLOCK, &mask, NULL);
}


void reset_score () {
    set_color(BLACK);
    draw_digits(RESET_SCORE, X_COORDINATE_SCORE_PLAYER1, 2*SEGMENT_LENGTH);
    draw_digits(RESET_SCORE, X_COORDINATE_SCORE_PLAYER2, 2*SEGMENT_LENGTH);
}



int playerButtonPressed(int button) 
{
    if (button == LEFT)
    {
        if (buf == P1_LEFT)
            return P1;
        if (buf == P2_LEFT)
            return P2;
    } 
    if (button == TOP)
    {
        if (buf == P1_TOP)
            return P1;
        if (buf == P2_TOP)
            return P2;
    }
    if (button == RIGHT)
    {
        if (buf == P1_RIGHT)
            return P1;
        if (buf == P2_RIGHT)
            return P2;
    }
    if (button == BOTTOM)
    {
        if (buf == P1_BOTTOM)
            return P1;
        if (buf == P2_BOTTOM)
            return P2;
    }
    return 0;
}

bool isQuitGame(char c)
{
        if ((c = getchar()) != EOF)
        {
            if (c == 'q') 
            {
                printf("Pressed: %c\n", c);
                return true;           
            }
        }  
        return false;
}

void quitGame()
{
    destroy_display();
    close(file_gamepad_driver);
    exit(EXIT_SUCCESS);
}

int getGameTime()
{
    double time;
    gettimeofday(&time_button_pressed,NULL); //here time_button_pressed is just use to store the current time, it does not represent the moment when we pressed the button
    time = (time_button_pressed.tv_sec - time_button_appears.tv_sec)*100 + (time_button_pressed.tv_usec - time_button_appears.tv_usec)/10000; //convert to 1/100 s elapsed 
    
    return (int)time;
}

void winner_blink(__u8 player, int time)
{
    printf("winner time: %d\n",time);
    // turn on
    if (blink)
    {
        printf(" blink on");
        blink = 0;
        draw_time(time, GREEN);
        redraw();
        if (player == P1)
            draw_score_p1(5);
        else
            draw_score_p2(5);
    }
    //turn off
    else
    {
        printf("blink off");
        blink = 1;
        clear_time();
        redraw();
        if (player == P1)
            clear_score_p1();
        else
            clear_score_p2();
    }
    redraw();
}
        
    
int main(int argc, char *argv[])
{
    char c;
    int status = 0;
    
    printf("Hello World, I'm game!\n");
    
    status = init_display();
    if (status != 0)
    {
        printf("Error: Failed to init display\n");
        return status;
    }
    
    status = init_driver();
    if (status != 0)
    {
        printf("Error: Failed to init driver\n");
        destroy_display();
        return status;
    }
    
    status = setup_handler();
    if (status != 0)
    {
        printf("Error: Failed to init signal handler\n");
        destroy_display();
        close(file_gamepad_driver);
        return status;
    }
    time_handler();
    
    /* Intializes random number generator */
    srand((unsigned) time(&t));
    
    sigset_t myset;
    (void) sigemptyset(&myset);

    while(1)
    {
        clear_LCD();       
        draw_game();
        draw_score(p1_score, p2_score);
        redraw();
        
        waitForButton();      
        printf("start game\n");
        
        while((p1_score < 5) && (p2_score < 5))
        {
            random_timer = (rand() % 3) + 2;
            startTimer(random_timer);
            waitForTimer();
            
            random_button = (rand() % 4);
            
            draw_button(random_button, true, RED);
            redraw();
            
            gettimeofday(&time_button_appears, NULL);

            // start timer
            startTimer(3);
            buf = 0;
            while((playerButtonPressed(random_button) == 0) && (timer_expired == false))
            {
                waitForButton(); 
            }
            
            stopTimer();
            if (timer_expired == false)
            {
                time_elapsed = getGameTime();
                draw_time(time_elapsed, BLUE);
                redraw();
            }
      
            if (playerButtonPressed(random_button) == P1)
            {
                p1_score++;
                p1_time += time_elapsed;
                
            }
            else if (playerButtonPressed(random_button) == P2)
            {
                p2_score++;    
                p2_time += time_elapsed;
            }
                
            draw_score(p1_score, p2_score);    
            reset_button(random_button);
            redraw();
            
        }
        // draw winner
        button_pressed = 0;
        if (p1_score == 5)
        {
            winner = P1;
            winner_time = p1_time;
        }
        else if (p2_score == 5)
        {
            winner = P2;
            winner_time = p2_time;
        }
        
        while(button_pressed == 0)
        {
            startTimer(1);
            winner_blink(winner, winner_time);
            waitForTimer();
        }
               
        // print waiting
        waitForButton();
        p1_score = 0;
        p1_time = 0;
        p2_score = 0;
        p2_time = 0;
    }

}
    


void timer_handler(int signum)
{
    timer_expired = true;
}

void signal_handler(int signum)
{
    int bytes_read;
    printf("Received interrupt: %d\n", signum);
    bytes_read = read(file_gamepad_driver, &buf, 2);
    printf("Received: 0x%X\n", buf);
    printf("Bytes_read: %d\n", bytes_read);    
    button_pressed = 1;
}

