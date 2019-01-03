#ifndef _BOARD__HPP
#define _BOARD__HPP
#include <ncurses.h>
#include <vector>
#include <string>
#include "menu.hpp"
#include "snake.hpp"
using std::vector;
using std::string;

class Board{
  void Init();
  void InitSnake();
  void WaitCtrl();
  void UpdateScore();
  void UpdateSnake();
  void PlaceGame();
  void PollInput();
public:
  void GoToMenu();
  void GoToPlay();
  void GoToHelp();
  void Clear();
  Board():cols_num_(70),rows_num_(20),score_(-1),gd_win_(nullptr,&delwin){
    Init();
  }
  ~Board(){}
private:
  int cols_num_;
  int rows_num_;
  int start_x_;
  int start_y_;
  int score_;
  Snake snake_;
  Menu menu_;
  std::unique_ptr<WINDOW, decltype(&delwin)> gd_win_;
  vector<string> help_;
};


#endif
