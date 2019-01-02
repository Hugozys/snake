#include <ncurses.h>
#include "daemon.hpp"
#include "exception.hpp"

Daemon::~Daemon(){endwin();}
void Daemon::Start(){
  while(true){
    try{
      switch(status_){
      case MENU:
	bd_.GoToMenu();
      case HELP:
	bd_.GoToHelp();
      case PLAY:
	bd_.GoToPlay();
      case QUIT:
	throw Quit();
      }
    }
    catch(const Menu & e){
      status_ = MENU;
    }
    catch(const Play & e){
      status_ = PLAY;
    }
    catch (const Help & e){
      status_ = HELP;
    }
    catch(const Quit & e){
      break;
    }
  }
}





