#include <ncurses.h>
#include <memory>
#include <string>
#include <unistd.h>
#include <algorithm>
#include <cstdlib>
#include "board.hpp"
#include "exception.hpp"
#include <sstream>
void Board::InitSnake(){
  snake_.SetMeta(cols_num_ - 2, rows_num_ - 2);
  srand(time(NULL));
  int head_y = rand() % (rows_num_ - 2) + 1;
  int head_x = rand() % (cols_num_ - 2) + 1;
  snake_.Init(head_y,head_x,5);
  snake_.Draw(gd_win_.get());
  snake_.GenerateFood();
  snake_.DrawFood(gd_win_.get());
  wrefresh(gd_win_.get());
}

void Board::Init(){
  help_.push_back("b\tGo back to the menu while playing games.");
  help_.push_back("q\tQuit the Game. (This works at anytime)");
  help_.push_back("Use arrow strokes on the keyboard to control how snake moves");
  initscr();
  menu_.InitMenu();
  curs_set(0);
  cbreak();
  keypad(stdscr,TRUE);
  noecho();
  refresh();
  menu_.CreateNewWindow();
  start_y_ = (LINES-rows_num_)/2;
  start_x_ = (COLS-cols_num_)/2;
  gd_win_.reset(newwin(rows_num_, cols_num_,start_y_,start_x_));
  keypad(gd_win_.get(),true);
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
  ++score_;
  string new_num = std::to_string(score_);
  mvaddstr((LINES-rows_num_)/2 - 1, (COLS-cols_num_)/2 + 7, new_num.c_str()); 
}

void Board::PlaceGame(){
  box(gd_win_.get(),0,0);
  mvaddstr((LINES-rows_num_)/2 - 1, (COLS-cols_num_)/2, "score: ");
  UpdateScore();
  wrefresh(gd_win_.get());
  refresh();
}

void Board::PollInput(){
  int ch;
  ch = wgetch(gd_win_.get());
  switch(ch){
  case 'b':
    cbreak();
    throw GoMenu();
  case 'q':
    throw Quit();
  case KEY_DOWN:
    if (snake_.GetDir() != Snake::UP)
      snake_.SetDir(Snake::DOWN);
    break;
  case KEY_UP:
    if (snake_.GetDir() != Snake::DOWN)
      snake_.SetDir(Snake::UP);
    break;
  case KEY_LEFT:
    if (snake_.GetDir() != Snake::RIGHT)
      snake_.SetDir(Snake::LEFT);
    break;
  case KEY_RIGHT:
    if (snake_.GetDir() != Snake::LEFT)
      snake_.SetDir(Snake::RIGHT);
    break;
  default:
    break;
  }
}

void Board::GoToPlay(){
  clear();
  wclear(gd_win_.get());
  refresh();
  wrefresh(gd_win_.get());
  PlaceGame();
  InitSnake(); 
  while(true){
    try{
      if(snake_.Move(gd_win_.get())){
	UpdateScore();
	snake_.GenerateFood();
	snake_.DrawFood(gd_win_.get());
      }
      wrefresh(gd_win_.get());
      refresh();
      halfdelay(4);
      PollInput();
    }
    catch(const GameOver & e){
      std::stringstream ss;
      ss <<"Game Over. You Lose! Score: "<<score_;
      auto words(ss.str());
      Clear();
      mvwaddstr(gd_win_.get(), rows_num_/2, (cols_num_ - static_cast<int>(words.size()))/2, words.c_str());
      wrefresh(gd_win_.get());    
      WaitCtrl();
      throw GoMenu();
    }
  }
}

void Board::WaitCtrl(){
  while(true){
    int c = getch();
    switch(c){
    case 'q':
      throw Quit();
    case 'b':
      throw GoMenu();
    case 10:
      throw Play();
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

void Board::Clear(){
  cbreak();
  score_ = -1;
  wclear(gd_win_.get());
  wrefresh(gd_win_.get());
  clear();
  refresh();
  snake_.Clear();
  
}
