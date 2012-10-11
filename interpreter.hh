#ifndef __INTERPRETER_HH__
#define __INTERPRETER_HH__

#include <iostream>
#include "segment.hh"


class Interpreter
{
 private:
 public:
  Interpreter();
  ~Interpreter();

  bool HandleFile( std::string path );
  std::string Strip( std::string input );
};

#endif

