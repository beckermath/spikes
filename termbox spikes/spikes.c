#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../termbox.h"

#define PLAYER '*'
#define SPIKE '^'
#define OPEN ' '
#define PASS '@'
#define PORTAL 'O'

void drawBoard(int l1, int l2, int l3){
    int r, c;

    for(c = 0; c < tb_width(); c++){
        for(r = 3; r < tb_height(); r++){
            int num = rand() % 1000 +1;

            if(num > l1){
                tb_change_cell(c, r, '^', TB_RED, TB_DEFAULT);
            }
        }
    }
}

int main(int argc, char **argv) {
    int level = 1;
    int score = 100;

    int lim1 = 955;
    int lim2 = 10000;
    int lim3 = 10000;
    int pass = 0;

    srand(time(NULL));

	(void)argc; (void)argv;
	int ret = tb_init();
	if (ret) {
		fprintf(stderr, "tb_init() failed with error code %d\n", ret);
		return 1;
	}

    tb_select_input_mode(TB_INPUT_ESC);
    tb_select_output_mode(TB_OUTPUT_NORMAL);
    tb_clear();

    drawBoard(lim1, lim2, lim3);

    int i = 0;
    int cx = tb_width()/2;
    int cy = 1;

    tb_set_cursor(cx, cy);
    tb_change_cell(cx, cy, '*', TB_BLUE, TB_DEFAULT);

    tb_present();

	struct tb_event ev;
	while (tb_poll_event(&ev)) {
        if(ev.key == TB_KEY_ARROW_UP){
            tb_change_cell(cx, cy, ' ', TB_BLUE, TB_DEFAULT);
            cy--;
            tb_set_cursor(cx, cy);
            tb_change_cell(cx, cy, '*', TB_BLUE, TB_DEFAULT);
            score -= 100;
        }
        if(ev.key == TB_KEY_ARROW_DOWN){
            tb_change_cell(cx, cy, ' ', TB_BLUE, TB_DEFAULT);
            cy++;
            tb_set_cursor(cx, cy);
            tb_change_cell(cx, cy, '*', TB_BLUE, TB_DEFAULT);
            score += 10;
        }
        if(ev.key == TB_KEY_ARROW_RIGHT){
            tb_change_cell(cx, cy, ' ', TB_BLUE, TB_DEFAULT);
            cx++;
            tb_set_cursor(cx, cy);
            tb_change_cell(cx, cy, '*', TB_BLUE, TB_DEFAULT);
            score -= 20;
        }
        if(ev.key == TB_KEY_ARROW_LEFT){
            tb_change_cell(cx, cy, ' ', TB_BLUE, TB_DEFAULT);
            cx--;
            tb_set_cursor(cx, cy);
            tb_change_cell(cx, cy, '*', TB_BLUE, TB_DEFAULT);
            score -= 20;
        }

        if(ev.key == TB_KEY_ESC){
            goto done;
        }

        if(cy >= tb_height()){
            tb_change_cell(cx, cy, ' ', TB_BLUE, TB_DEFAULT);
            cy = 1;
            tb_set_cursor(cx, cy);
            tb_change_cell(cx, cy, '*', TB_BLUE, TB_DEFAULT);
            level += 1;
            score += 100;
            lim1 -= 6;
            lim2 -= 2;
            lim3 -= 20;
            drawBoard(lim1, lim2, lim3);
        }

        tb_present();
	}
done:
	tb_shutdown();
	return 0;
}


