#ifndef _BOARD__HPP
#define _BOARD__HPP
#include <ncurses.h>
#include "menu.hpp"
#include "snake.hpp"
class Board{
  enum DIR{UP,DOWN,LEFT,RIGHT};
  void Init();
public:
  void GoToMenu();
  void GoToPlay();
  void GoToHelp();
  Board():cols_num_(50),rows_num_(50){
    Init();
  }
  ~Board(){}
private:
  int cols_num_;
  int rows_num_;
  int score_;
  Snake snake_;
  Menu menu_;
};


#endif
