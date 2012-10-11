#ifndef __COMMAND_HH__
#define __COMMAND_HH__

enum eCommandType
{
  NOT_DEFINED,
  ADD,
  SUB,
  INC,
  DEC,
  PRINT,
  READ,
  START,
  END
};



struct sCommand
{
  eCommandType type;
  unsigned int count;

  sCommand( char cmd );
};

#endif

