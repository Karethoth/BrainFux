#include "command.hh"


sCommand::sCommand( char cmd )
{
  count = 1;

  switch( cmd )
  {
    case '>': type = ADD;   break;
    case '<': type = SUB;   break;
    case '+': type = INC;   break;
    case '-': type = DEC;   break;
    case '.': type = PRINT; break;
    case ',': type = READ;  break;
    case '[': type = START; break;
    case ']': type = END;   break;

    default: type = NOT_DEFINED;
  }
}

