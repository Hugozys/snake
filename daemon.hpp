#ifndef _DAEMON__HPP
#define _DAEMON__HPP
#include "board.hpp"
class Daemon{
  enum Status{PLAY,MENU,HELP,QUIT};
public:
  Daemon():bd_(),status_(MENU){}
  void Start();
  ~Daemon();
private:
  Board bd_;
  Status status_;
};



#endif
