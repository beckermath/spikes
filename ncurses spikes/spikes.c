//
//  spikes.c
//  
//
//  Created by Becker Mathie on 1/8/19.
//

#include <stdlib.h>
#include <curses.h>
#include <math.h>
#include <time.h>

#define PLAYER '*'
#define SPIKE '^'
#define OPEN ' '
#define PASS '@'
#define PORTAL 'O'
#define EXPLO '#'

int canMove(int y, int x);
void drawMap(int bor1, int bor2, int bor3);
int isPass(int y, int x);
int isExplo(int y, int x);


int main(void)
{
    srand(time(NULL));
    
    int level = 1;
    int score = 0;
    int y, x;
    int ch;
    int border1 = 955;
    int border2 = 10000;
    int border3 = 10000;
    int pass = 0;
    
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    clear();
    
    drawMap(border1, border2, border3);
    
    y = 0;
    x = COLS/2;
    
    do
    {
        mvaddch(y, x, PLAYER);
        move(y, x);
        refresh();
        ch = getch();

        if(y == LINES-1)
        {
            mvaddch(y, x, OPEN);
            y = 0;
            mvaddch(y, x, PLAYER);
            level +=1;
            score += level*100;
            border1 -= 6;
            border2 -= 2;
            border3 -= 20;
            drawMap(border1, border2, border3);
        }
        
//        if(x == COLS-1 || x == 1)
//        {
//            mvaddch(y, x, OPEN);
//            if(x == 1)
//            {
//                x = COLS-2;
//            }
//            else
//            {
//               x = 2;
//            }
//
//            mvaddch(y, x, PLAYER);
//        }
        
        
        
        switch (ch) {
            case 'w':
            case KEY_UP:
                if ((y > 0) && canMove(y - 1, x)) {
                    mvaddch(y, x, OPEN);
                    y = y - 1;
                    score -= 125;
                    mvprintw(0, 0, "Score: %d", score);
                    mvprintw(1, COLS-9, "Level: %d", level);
                    mvprintw(2, COLS-16, "C4: %d", pass);
                    if(score < 0)
                    {
                        mvprintw(0, (COLS/2) - 12, "GAMEOVER - Press q to quit");
                        break;
                    }
                    if(isPass(y, x))
                    {
                        pass+=1;
                    }
                    if(isExplo(y, x))
                    {
                        for(int i = y; i< 15; i++)
                        {
                            mvaddch(y, x, OPEN);
                        }
                        
                    }
                    
                    
                }
                break;
                
            case 's':
            case KEY_DOWN:
                if ((y < LINES - 1) && canMove(y + 1, x)) {
                    mvaddch(y, x, OPEN);
                    y = y + 1;
                    score += 10;
                    mvprintw(0, 0, "Score: %d", score);
                    mvprintw(0, COLS-10, "Level: %d", level);
                    mvprintw(0, COLS-17, "C4: %d", pass);
                    if(score < 0)
                    {
                        mvprintw(0, (COLS/2) - 12, "GAMEOVER - Press q to quit");
                        break;
                    }
                    if(isPass(y, x))
                    {
                        pass+=1;
                    }
                    if(isExplo(y, x))
                    {
                        for(int i = y; i< 15; i++)
                        {
                            mvaddch(y, x, OPEN);
                        }
                        
                    }
                    
                }
                break;
                
            case 'a':
            case KEY_LEFT:
                if ((x > 0) && canMove(y, x - 1)) {
                    mvaddch(y, x, OPEN);
                    x = x - 1;
                    score -= 10;
                    mvprintw(0, 0, "Score: %d", score);
                    mvprintw(0, COLS-10, "Level: %d", level);
                    mvprintw(0, COLS-17, "C4: %d", pass);
                    if(score < 0)
                    {
                        mvprintw(0, (COLS/2) - 12, "GAMEOVER - Press q to quit");
                        break;
                    }
                    if(isPass(y, x))
                    {
                        pass+=1;
                    }
                    if(isExplo(y, x))
                    {
                        for(int i = y; i< 15; i++)
                        {
                            mvaddch(y, x, OPEN);
                        }
                        
                    }
                   
                }
                break;
                
            case 'd':
            case KEY_RIGHT:
                if ((x < COLS - 1) && canMove(y, x + 1)) {
                    mvaddch(y, x, OPEN);
                    x = x + 1;
                    score -= 10;
                    mvprintw(0, 0, "Score: %d", score);
                    mvprintw(0, COLS-10, "Level: %d", level);
                    mvprintw(0, COLS-17, "C4: %d", pass);
                    if(score < 0)
                    {
                        mvprintw(0, (COLS/2) - 12, "GAMEOVER - Press q to quit");
                        break;
                
                    }
                    if(isPass(y, x))
                    {
                        pass+=1;
                    }
                    if(isExplo(y, x))
                    {
                        for(int i = y; i< 15; i++)
                        {
                            mvaddch(y, x, OPEN);
                        }
                        
                    }
                   
    
                }
                break;
            
            case ' ':
                if(!(canMove(y+1, x)) && pass >=1)
                {
                    mvaddch(y+1, x, OPEN);
                    pass -= 1;
                }
                
                break;
        }
    }while ((ch != 'q') && (ch != 'Q'));
    
    
    
    endwin();
    exit(0);
}

int canMove(int y, int x)
{
    int testch;
    
    testch = mvinch(y, x);
    return ((testch == OPEN) || (testch == PASS) || (testch == PORTAL) || (testch == EXPLO));
}

int isPass(int y, int x)
{
    int testch;
    
    testch = mvinch(y, x);
    return (testch == PASS);
}
int isExplo(int y, int x)
{
    int testch;
    
    testch = mvinch(y, x);
    return (testch == EXPLO);
}

int isPortal(int y, int x)
{
    int testch;
    
    testch = mvinch(y, x);
    return (testch == PORTAL);
}

void drawMap(int bor1, int bor2, int bor3)
{
    int y, x;
    
    for (y = 3; y < LINES; y++) {
        for(x= 0; x < COLS; x++){
            int num = rand() % 1000 +1;
        
            if(num > bor1)
            {
                mvhline(y, x, SPIKE, 1);
            }
        }
    }
    
    for (y = 3; y < LINES; y++) {
        for(x= 0; x < COLS; x++){
            int num2 = rand() % 10000 +1;
            
            if(num2 > bor2)
            {
                mvhline(y, x, PASS, 1);
            }
        }
    }
    
//    for (y = 3; y < LINES-15; y++) {
//        for(x= 0; x < COLS; x++){
//            int num3 = rand() % 10000 +1;
//
//            if(num3 > bor3)
//            {
//                mvhline(y, x, EXPLO, 1);
//            }
//        }
//    }
    
    
    
//    int portal1x = rand() % COLS +1;
//    int portal1y = rand() % LINES +1;
//    int portal2x = rand() % COLS +1;
//    int portal2y = rand() % LINES +1;
//
//    mvaddch(portal1y, portal2x, PORTAL);
//    mvaddch(portal2y, portal2x, PORTAL);
    
}










