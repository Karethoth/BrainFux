#ifndef __NASMOUTPUT_HH__
#define __NASMOUTPUT_HH__

#include <iostream>
#include "outputModule.hh"
#include <fstream>


class NASMOutputModule : public OutputModule
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

