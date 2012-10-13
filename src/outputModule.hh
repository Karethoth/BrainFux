#ifndef __OUTPUTMODULE_HH__
#define __OUTPUTMODULE_HH__

#include "segment.hh"

class OutputModule
{
 public:
  virtual bool Handle( Segment *rootSegment ) = 0;
};

#endif

