#define _DEFAULT_SOURCE
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>
#include <string.h>

void listFiles(const char *dirname)
{
	int input;							//navigation var
	int counter;							//file counting var
	int file_index = 0;						//inverse counter var
	int curs_position_y = 0;					
	struct dirent **file;						
	counter = scandir(dirname, &file, NULL, alphasort);
	
	while (counter--){						//output all names
		move(file_index, 2);
		printw("%s", file[file_index]->d_name);
		file_index++;
	}
	
	refresh();
	move(0, 2);
	
	do								//moving cursor until user press ESC or open other directory
	{
		if (input == KEY_UP){
			curs_position_y--;
			move(curs_position_y, 2);
		}
		else if (input == KEY_DOWN){
			curs_position_y++;
			move(curs_position_y, 2);
		}
		else if (input == KEY_RIGHT){
			if (file[curs_position_y]->d_type == DT_DIR){
				char path[100] = { 0 };
				strcat(path, dirname);
				strcat(path, "/");
				strcat(path, file[curs_position_y]->d_name);
				clear();
				listFiles(path);
			}
		}
	}
	while ((input = getch()) != 27);
	
	free(file);
}

int main()
{	
	initscr();
	noecho();
	curs_set(TRUE);
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	attron(COLOR_PAIR(1) | A_BOLD);
	
	listFiles(".");
	
	endwin();
	exit(EXIT_SUCCESS);
}
