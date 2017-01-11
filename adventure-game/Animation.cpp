#include "Animation.hpp"

Animation::Animation()
{
	initscr();
	getmaxyx(stdscr, height, width);
	endwin();	
}

void Animation::title()
{
	int titlesize = 32;
	int j = 0;
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	
	attron(COLOR_PAIR(1));
	mvprintw(height - 4, width/2 - titlesize/2, " OO  M   M III  CC RR   OO  N  N");
	mvprintw(height - 3, width/2 - titlesize/2, "O  O MM MM  I  C   R R O  O NN N");
	mvprintw(height - 2, width/2 - titlesize/2, "O  O M M M  I  C   RR  O  O N NN");
	mvprintw(height - 1, width/2 - titlesize/2, " OO  M   M III  CC R R  OO  N  N");
	attroff(COLOR_PAIR(1));
	scrollok(stdscr, TRUE);
	
	for(int i = 0; i < (height - height/4); i++)
	{
		scroll(stdscr);
		refresh();
		usleep(175000);
	}
	
	mvprintw(height - 20, width/2 - 11, "PRESS ANY KEY TO START");
	getch();
	endwin();
}

void Animation::addCore()
{
	char core_h[] = "+----+";
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_BLACK, COLOR_CYAN);
	init_pair(4, COLOR_BLACK, COLOR_RED);
	init_pair(5, COLOR_BLACK, COLOR_YELLOW);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
	init_pair(7, COLOR_CYAN, COLOR_BLACK);
	
	for(int i = strlen(core_h); i >= 0; i--)
	{
		clear();
		attron(COLOR_PAIR(2));
		mvvline(0, width/2, '|', height);
		for(int j = 0; j < height; j++)
		{
			mvhline(j, width/2 + 1, ' ', width/2);
		}
		mvprintw((height/2 - 3), (width/2 + 2), "Power");
		attroff(COLOR_PAIR(2));
		attron(COLOR_PAIR(1));
		mvprintw(height/2, width/2 - i, core_h);
		mvprintw(height/2 + 1, width/2 - i, "|    |");
		mvprintw(height/2 + 2, width/2 - i, "|    |");
		mvprintw(height/2 + 3, width/2 - i, "|    |");
		mvprintw(height/2 + 4, width/2 - i, core_h);
		attroff(COLOR_PAIR(1));
		usleep(DELAY);
		refresh();
	}
	
	attron(COLOR_PAIR(3));
	mvprintw(height/2, width/2, core_h);
	mvprintw(height/2 + 1, width/2, "|    |");
	mvprintw(height/2 + 2, width/2, "|    |");
	mvprintw(height/2 + 3, width/2, "|    |");
	mvprintw(height/2 + 4, width/2, core_h);
	attroff(COLOR_PAIR(3));
	
	attron(COLOR_PAIR(7));
	mvprintw(height/2 - 1, width/2 - 1, "\\");
	mvprintw(height/2, width/2 - 1, "\\");
	mvprintw(height/2 + 1, width/2 - 1, "-");
	mvprintw(height/2 + 2, width/2 - 1, "-");
	mvprintw(height/2 + 3, width/2 - 1, "-");
	mvprintw(height/2 + 4, width/2 - 1, "/");
	mvprintw(height/2 + 5, width/2 - 1, "/");
	attroff(COLOR_PAIR(7));
	
	for(int i = 0; i <= 15; i++)
	{
		if(i < 5)
		{
			attron(COLOR_PAIR(4));
		}
		else if(i > 10)
		{
			attron(COLOR_PAIR(6));
		}
		else
		{
			attron(COLOR_PAIR(5));
		}
		mvprintw((height/2 - 2), (width/2 + 2) + i, " ");
		attroff(COLOR_PAIR(4));
		refresh();
		usleep(DELAY);
	}
	endwin();
}

void Animation::putOutFire()
{
	char base[] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	initscr();
	cbreak();	
	noecho();
	curs_set(0);
	scrollok(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	
	for(int i = 0; i < 8; i++)
	{
		clear();
		attron(COLOR_PAIR(1));
		mvprintw(height - 7+i, width/2 - strlen(base)/2, "   X       X             X       X              X     ");
		mvprintw(height - 6+i, width/2 - strlen(base)/2, "    X      XX     X       X     X      X        XX    ");
		mvprintw(height - 5+i, width/2 - strlen(base)/2, "   XX      XXX    XX    XXXX    XX    XXX      XXX    ");
		mvprintw(height - 4+i, width/2 - strlen(base)/2, "  XXXX   XXXXXX  XXX   XXXXXX  XXXX  XXXXX   XXXXX    ");
		mvprintw(height - 3+i, width/2 - strlen(base)/2, "  XXXXX XXXXXXXXXXXXX XXXXXXX XXXXXXXXXXXXX XXXXXXX   ");
		mvprintw(height - 2+i, width/2 - strlen(base)/2, " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX ");
		mvprintw(height - 1+i, width/2 - strlen(base)/2, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
		refresh();
		usleep(DELAY);
		clear();
		mvprintw(height - 7+i, width/2 - strlen(base)/2, "    X              X                  X               ");
		mvprintw(height - 6+i, width/2 - strlen(base)/2, "   X       XX     X      XX      X     XX       X     ");
		mvprintw(height - 5+i, width/2 - strlen(base)/2, "   XX     XXXX    XX    XXX     XX    XXX      XXX    ");
		mvprintw(height - 4+i, width/2 - strlen(base)/2, "   XXX   XXXXXX  XXX   XXXXX    XXX  XXXXX    XXXXX   ");
		mvprintw(height - 3+i, width/2 - strlen(base)/2, "  XXXXX XXXXXXXXXXXXX XXXXXXX  XXXXXXXXXXXX   XXXXXX  ");
		mvprintw(height - 2+i, width/2 - strlen(base)/2, " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX ");
		mvprintw(height - 1+i, width/2 - strlen(base)/2, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
		attroff(COLOR_PAIR(1));
		refresh();
		usleep(DELAY);
		
	}

	endwin();
}

void Animation::end()
{
	initscr();
	cbreak();	
	noecho();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_CYAN);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	
	for(int i = 0; i <= width; i++)
	{
		clear();
		attron(A_UNDERLINE);
		mvprintw( 1, 24+i, "           ");
		
		attroff(A_UNDERLINE);	
		mvprintw(2, 23+i, "/           \\");
		attron(COLOR_PAIR(1));
		mvprintw(2, 33+i, "  ");
		attroff(COLOR_PAIR(1));
		mvprintw(3, 22+i, "(");
		attron(A_UNDERLINE);
		mvprintw(3, 23+i, "             ");
		attroff(A_UNDERLINE);
		mvprintw(3, 36+i, ")");
		mvprintw(4, 27+i, "/  |");
		attron(A_UNDERLINE);
		mvprintw(5, 6+i, "                          ");
		mvprintw(5, 26+i, "/   |");	
		attroff(A_UNDERLINE);
		mvprintw(6, 5+i, "/                          \\");
		mvprintw(7, 4+i, "{                            }");
		mvprintw(8, 5+i, "\\");
		attron(A_UNDERLINE);
		mvprintw(8, 6+i,"                          ");
		attroff(A_UNDERLINE);
		mvprintw(8, 32+i,"/");
		attron(A_UNDERLINE);
		mvprintw(3, 3+i, "         ");
		attroff(A_UNDERLINE);
		attron(COLOR_PAIR(2));
		mvprintw(4, 0+i, "::(");
		attroff(COLOR_PAIR(2));
		attron(A_UNDERLINE);
		mvprintw(4, 3+i, "         ");
		attroff(A_UNDERLINE);
		mvprintw(4, 12+i, ")");
		mvprintw(5, 7+i, "\\  \\");
		mvprintw(6, 8+i, "\\  \\");
		if(i > 30){
			mvhline(1, 0, ' ', 30);
			mvhline(2, 0, ' ', 30);
			mvhline(3, 0, ' ', 30);
			mvhline(4, 0, ' ', 30);
			mvhline(5, 0, ' ', 30);
			mvhline(6, 0, ' ', 30);
			mvhline(7, 0, ' ', 30);
			mvhline(8, 0, ' ', 30);
			mvhline(9, 0, ' ', 30);
		}
		refresh();
		
		usleep(175000);
	}
	clear();
	mvprintw(height/2 - 1, width/2 - 4, "THE END");
	refresh();
	usleep(DELAY);
	endwin();
}