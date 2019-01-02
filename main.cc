#include <cstdlib>
#include <iostream>
#include <cassert>
#include <ncurses.h>
#include "daemon.hpp"
#include "exception.hpp"

int main(int argc, char ** argv){
  if (argc != 1){
    std::cout<<"Usage: ./snake (Don't overthink)\n";
    return (EXIT_SUCCESS);
  }
  else{
    Daemon da;
    //try{
    da.Start();
      //}
    //catch (const Quit & e){}
    //assert(false); //It couldn't be anything else
    return (EXIT_SUCCESS);
  }
}

    
