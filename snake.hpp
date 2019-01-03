#ifndef _SNAKE__HPP
#define _SNAKE__HPP
#include <set>
#include <memory>
#include <utility>
#include <ncurses.h>
class Snake{
public:
  enum DIR{UP,DOWN,LEFT,RIGHT};
private:
  struct Dot;
  typedef std::shared_ptr<Dot> Pdot;
  struct Dot{
    int r_co;
    int c_co;
    Pdot next;
    int Hash(int col_size){return r_co*col_size + c_co;}
    Dot(int y, int x, Dot * n):r_co(y),c_co(x),next(n){}
    Dot()=default;
  
  };  
  int Hash(Pdot & dot){return dot.get()->Hash(col_);}
public:
  Snake():head_(nullptr),tail_(nullptr),col_(0),row_(0),body_(),direction_(RIGHT){}
  void SetDir(DIR to_set){direction_ = to_set;}
  void SetMeta(int col, int row){ col_ = col; row_ = row;}
  void Move(WINDOW* win);
  void Init(int h_y, int h_x, int len);
  void Draw(WINDOW * win);
  void DrawDot(WINDOW * win, int y, int x, bool live);
  std::pair<int,int> GetNextTail();
private:
  Pdot head_;
  Pdot tail_;
  int col_;
  int row_;
  std::set<int> body_; //store snake body
  DIR direction_;
};
  

#endif
