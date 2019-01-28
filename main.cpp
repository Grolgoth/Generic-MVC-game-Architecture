#include "game.h"
#include <iostream>

int main( int argc, char * argv[] )
{
	try
	{
		Game game;
		game.start();
	} catch (const char* c)
	{
		std::string b = c;
		std::cout << b << std::endl;
    } catch(std::string a)
    {
    	std::cout << a << std::endl;
    }
	return 0;
}
