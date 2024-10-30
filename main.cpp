#include <ncurses.h>
#include <fstream>
#include <filesystem>
#include <stdlib.h>
#include <cstring>
namespace fs = std::filesystem;
int main() {
	initscr();
	int ys, xs;
	std::string username = getenv("USER");
	std::string path = "/home/"+username;
	getmaxyx(stdscr, ys, xs);
	refresh();
	for (const auto & entry : fs::directory_iterator(path)){
        printw(entry.path().string().c_str());
	printw("\n");
	refresh();}
	getch();
	endwin();
}
