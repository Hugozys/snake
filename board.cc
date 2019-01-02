#include <ncurses.h>
#include "board.hpp"
#include "exception.hpp"
void Board::Init(){
  initscr();
  curs_set(0);
  cbreak();
  keypad(stdscr,TRUE);
  noecho();
  refresh();
  menu_.CreateNewWindow();
}

void Board::GoToMenu(){
  clear();
  refresh();
  menu_.Show();
  try{
    while(true){
      menu_.UserInteract();
    }
  }
  catch(std::exception & e){
    menu_.Hide();
  }
}

void Board::GoToPlay(){
  clear();
  addstr("PLAY");
  refresh();
  getch();
  throw Quit();
}


void Board::GoToHelp(){
  clear();
  addstr("Help");
  refresh();
  getch();
  throw Quit();
}
