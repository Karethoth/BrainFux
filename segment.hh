#ifndef __SEGMENT_HH__
#define __SEGMENT_HH__

#include <iostream>
#include <vector>
#include "command.hh"


class Segment
{
 private:
  std::vector<Segment>  children;
  std::vector<sCommand> commands;
  bool loop;

 protected:
  bool Construct( std::string data );
  size_t CalculateNextSegmentSize( std::string data );
  size_t FindLoopEnd( std::string data );

 public:
  bool Init( std::string data, bool isLoop );

  bool HasChildren();
  bool IsLoop();

  void Print();
};

#endif

