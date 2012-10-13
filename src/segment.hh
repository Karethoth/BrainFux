#ifndef __SEGMENT_HH__
#define __SEGMENT_HH__

#include <iostream>
#include <vector>
#include "command.hh"

static unsigned int segmentIdCounter=0;
static unsigned int NewSegmentId()
{
  return segmentIdCounter++;
}


class Segment
{
 private:
  unsigned int id;
  bool loop;

  std::vector<Segment*>  children;
  std::vector<sCommand*> commands;

 protected:
  Segment *parent;

  bool Construct( std::string data );
  size_t CalculateNextSegmentSize( std::string data );
  size_t FindLoopEnd( std::string data );
  bool Exec( unsigned char **p );

 public:
  Segment( Segment *parent );

  bool Init( std::string data, bool isLoop );

  bool HasChildren();
  bool IsLoop();

  void Print( int ident );

  bool Run( unsigned char **p );

  std::vector<Segment*>* GetChildren();
  std::vector<sCommand*>* GetCommands();
  unsigned int GetId();
};

#endif

