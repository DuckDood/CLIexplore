#include <ncurses.h>
#include <fstream>
#include <filesystem>
#include <stdlib.h>
#include <cstring>
namespace fs = std::filesystem;
int main() {
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	int ys, xs;
	int getched;
	std::string username = getenv("USER");
	std::string path = "/home/"+username+"/";
	char cpath[100];
	getmaxyx(stdscr, ys, xs);
	refresh();
	int i = 0;
	int strt =  0;
	while (true) {
	i = 0;
	clear();
	printw(path.c_str());
	printw("\n\n");
	for (const auto & entry : fs::directory_iterator(path)){
	if (i >= strt){
        printw(entry.path().string().c_str());
	printw("\n");
	}
	i++;
	if(i >= ys + strt) {
	break;
	}
	}
	getched = getch();
	if((char)getched == 'w') {
		strt--;
	} else if((char) getched == 's') {
	strt++;
	} else if((char) getched == 'c') {
		echo();
		getstr(cpath);
		if(cpath[0]!='/') {
			path = path + cpath;
		} else {
			path=cpath;
		}

		if(path[path.length()] != '/') {
			path += '/';
		}
		noecho();
	}

	if(strt < 0) {
		strt =0;

	}
	else if(strt > ys - (ys-i)-1) {
		strt = ys - (ys-i)-1;
	}
	}
	endwin();
}
