#ifndef _EXCEPT__HPP
#define _EXCEPT__HPP
#include <exception>

class Quit: public std::exception{};
class Play: public std::exception{};
class Help: public std::exception{};
class GameOver: public std::exception{};
class GoMenu: public std::exception{};
#endif
