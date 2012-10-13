#include <iostream>
#include "interpreter.hh"

using std::string;


int main( int argc, char **argv )
{
  Interpreter ip;
  ip.HandleFile( "input" );

  return 0;
}

