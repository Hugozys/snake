#include <cstdlib>
#include <iostream>
#include "daemon.hpp"

int main(int argc, char ** argv){
  if (argc != 1){
    std::cout<<"Usage: ./snake (Don't overthink)\n";
    return (EXIT_SUCCESS);
  }
  else{
    Daemon da;
    da.Start();
    return (EXIT_SUCCESS);
  }
}

    
