#include <ncurses.h>
#include <memory>
#include <string>
#include <unistd.h>
#include <algorithm>
#include <cstdlib>
#include "board.hpp"
#include "exception.hpp"

//3 4   2 + (1,2)
//5 6 7 8 9  4 + (1,2,3,4,5)
//[4     10] 10 - 4 = 6  7 -2 
//[2     5] 5-2 = 3
void Board::InitSnake(){
  snake_.SetMeta(cols_num_ - 2, rows_num_ - 2);
  srand(time(NULL));
  int head_y = rand() % (rows_num_ - 2) + 1;
  int head_x = rand() % (cols_num_ - 2) + 1;
  snake_.Init(head_y,head_x,5);
  snake_.Draw(gd_win_.get());
  wrefresh(gd_win_.get());
}

void Board::Init(){
  help_.push_back("b\tGo back to the menu while playing games.");
  help_.push_back("q\tQuit the Game. (This works at anytime)");
  help_.push_back("Use arrow strokes on the keyboard to control how snake moves");
  initscr();
  curs_set(0);
  cbreak();
  keypad(stdscr,TRUE);
  noecho();
  refresh();
  menu_.CreateNewWindow();
  start_y_ = (LINES-rows_num_)/2;
  start_x_ = (COLS-cols_num_)/2;
  InitSnake();
}

void Board::GoToMenu(){
  clear();
  refresh();
  menu_.Show();
  while(true){
    menu_.UserInteract();
  }
}

void Board::UpdateScore(){
  string new_num = std::to_string(score_);
  mvaddstr((LINES-rows_num_)/2 - 1, (COLS-cols_num_)/2 + 7, new_num.c_str()); 
}

void Board::UpdateSnake(){
  
}
void Board::PlaceGame(){
  gd_win_.reset(newwin(rows_num_, cols_num_,start_y_,start_x_));
  box(gd_win_.get(),0,0);
  mvaddstr((LINES-rows_num_)/2 - 1, (COLS-cols_num_)/2, "score: ");
  UpdateScore();
  UpdateSnake();
  wrefresh(gd_win_.get());
  refresh();
}

void Board::GoToPlay(){
  clear();
  refresh();
  PlaceGame();
  InitSnake();
  //WaitCtrl();
  while(true){
    snake_.Move(gd_win_.get());
    wrefresh(gd_win_.get());
    //refresh();
    sleep(2);
  }
    
}

void Board::WaitCtrl(){
  while(true){
    int c = getch();
    switch(c){
    case 'q':
      throw Quit();
    case 'b':
      throw Menu();
    default:
      break;
    }
  }
}

void Board::GoToHelp(){
  clear();
  int start_y = (LINES-help_.size())/2;
  for (auto & str: help_){
    mvaddstr(start_y,(COLS-str.size())/2,str.c_str());
    ++start_y;
  }
  refresh();
  WaitCtrl();
}
