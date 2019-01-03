#include "snake.hpp"
#include "exception.hpp"
#include <unistd.h>

void Snake::Clear(){
  direction_ = RIGHT;
  body_.clear();
  head_.reset();
  tail_.reset();
  food_.reset();
}


bool Snake::IsFood(Pdot & dot){
  return food_->r_co == dot->r_co && food_->c_co == dot->c_co;
}

void Snake::GenerateFood(){
  Pdot temp(nullptr);
  do{
    int food_y = rand() % row_ + 1;
    int food_x = rand() % col_ + 1;
    temp.reset(new Dot(food_y,food_x,nullptr));
  }while(body_.count(Hash(temp)));
  food_ = temp;
}
void Snake::DrawFood(WINDOW * win){
  mvwaddch(win,food_->r_co,food_->c_co,ACS_DIAMOND);
}
void Snake::Init(int h_y, int h_x, int len){
  body_.clear();
  head_ = Pdot(new Dot(h_y,h_x,nullptr));
  body_.insert(Hash(head_));
  Pdot curr = head_;
  for (int i = 1; i < 5; ++i){
    curr->next = Pdot(new Dot(h_y, (h_x + i - 1 + col_) % col_ + 1, nullptr));
    body_.insert(Hash(curr));
    curr = curr.get()->next;
  }
  tail_ = curr;
  GenerateFood();
}

void Snake::DrawDot(WINDOW * win, int y, int x, bool live){
  mvwaddch(win, y, x, (live) ? '#':' ');
}

void Snake::Draw(WINDOW * win){
  Pdot curr = head_;
  while (curr.get() != nullptr){
    DrawDot(win,curr->r_co,curr->c_co, true);
    curr = curr->next;
  }
}

std::pair<int,int> Snake::GetNextTail(){
  int next_x, next_y;
  int cur_x = tail_.get()->c_co; //cols
  int cur_y = tail_.get()->r_co; //rows
  switch(direction_){
  case UP: //move up
    next_y = (cur_y - 2 + row_) % row_ + 1;
    next_x = cur_x;
    break;
  case DOWN: //move down
    next_y = (cur_y + row_) % row_ + 1;
    next_x = cur_x;
    break;
  case LEFT: //move left
    next_x = (cur_x - 2 + col_) % col_ + 1;
    next_y = cur_y;
    break;
  case RIGHT: //move right
    next_x = (cur_x + col_) % col_ + 1;
    next_y = cur_y;
    break;
  }
  return std::make_pair(next_y,next_x);
}
bool Snake::Move(WINDOW * win){
  bool eat_food = false;
  Pdot n_dot(nullptr);
  auto n_tl = GetNextTail();
  n_dot.reset(new Dot(n_tl.first, n_tl.second, nullptr));
  if(IsFood(n_dot)){
    tail_->next = n_dot;
    tail_ = n_dot;
    DrawDot(win,n_dot->r_co,n_dot->c_co,true);
    eat_food = true;
    return true;
  }
  body_.erase(Hash(head_));
  if(body_.count(Hash(n_dot))) throw GameOver();
  DrawDot(win,head_->r_co,head_->c_co,false);
  head_ = head_->next;
  tail_->next = n_dot;
  tail_ = n_dot;
  body_.insert(Hash(tail_));
  DrawDot(win,tail_->r_co,tail_->c_co,true);
  return eat_food;
}
    
