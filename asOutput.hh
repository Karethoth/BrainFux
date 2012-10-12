#ifndef __ASOUTPUT_HH__
#define __ASOUTPUT_HH__

#include <iostream>
#include "outputModule.hh"
#include <fstream>


class AsOutputModule : public OutputModule
{
 private:
  std::ofstream *out;

 protected:
  bool CreateHeader();
  bool CreateFooter();
  bool HandleSegment( Segment *segment );
  bool HandleChildren( Segment *segment );
  bool HandleCommands( Segment *segment );

 public:
  virtual bool Handle( Segment *rootSegment );
};

#endif

