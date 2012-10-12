#ifndef __INTERPRETER_HH__
#define __INTERPRETER_HH__

#include <iostream>
#include "segment.hh"

#define IPMEM 30000

class Interpreter
{
 private:
  unsigned char mem[IPMEM];
  unsigned char *memPoint;

 public:
  Interpreter();
  ~Interpreter();

  bool HandleFile( std::string path );
  std::string Strip( std::string input );
};

#endif

