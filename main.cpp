#include <ncurses.h>
#include <fstream>
#include <filesystem>
#include <stdlib.h>
#include <cstring>
#include <vector>
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
	char ppath[100];
	std::string cpath;
	getmaxyx(stdscr, ys, xs);
	refresh();
	int i = 0;
	int strt =  0;
	int slcted = 0;
	bool wtf = false;
	std::string select = "";
	while (true) {
	i = 0;
	clear();
	printw(path.c_str()); printw("   "); printw(select.c_str());
	printw("\n\n");


	start_color();			/* Start color 			*/
	init_pair(1, COLOR_BLACK, COLOR_WHITE);













	for (const auto & entry : fs::directory_iterator(path)){
	if (i >= strt){
		if(i == slcted) {
			attron(COLOR_PAIR(1));}
		if(i == slcted){
			select = entry.path().string();
		}
		
        printw(entry.path().string().c_str());
	if(i == slcted) {
		attroff(COLOR_PAIR(1));
	}
	printw("\n");
	}
	i++;
	if(i >= ys + strt-4) {
	break;
	}
	} if(wtf) {
	getched = getch(); wtf= false;
	} else {getched=(int)'u'; wtf=true;}
	if((char)getched == 'w') {
		slcted--;
	} else if((char) getched == 's') {
	slcted++;
	} else if((char) getched == 'c') {
		echo();
		getstr(ppath);
		cpath = ppath;
		if(cpath[0]!='/') {
				path = path+cpath+'/';
			}
			
		 else{
			path = cpath + '/';		
			}
		noecho();
		while (true){ 
		if(path[path.rfind('/')-1] == '/') {
			path.erase(path.rfind('/'), 1);
		}else{break;}}
	}
	

	if(slcted < strt) {
		slcted++;
		strt--;

	}

	if(slcted < 0) {slcted=0;}
	else if(slcted > ys - (ys-i)-1) {
		slcted = ys - (ys-i)-1;
		strt++;
	}
	



	}
	endwin();
}
