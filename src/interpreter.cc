#include "interpreter.hh"
#include "gasOutput.hh"
#include "nasmOutput.hh"

#include <string>
#include <fstream>
#include <streambuf>

using std::string;
using std::cout;


Interpreter::Interpreter()
{
  memPoint = &mem[0];
  for( int i=0; i < IPMEM; ++i )
  {
    mem[i] = 0x00;
  }
}



Interpreter::~Interpreter()
{
}



bool Interpreter::HandleFile( string path )
{
  std::ifstream stream( path.c_str() );

  if( !stream.is_open() )
  {
	  cout << "Couldn't open file '" << path << "'\n";
  }

  string content( (std::istreambuf_iterator<char>( stream )),
                   std::istreambuf_iterator<char>() );

  string stripped = Strip( content );

  Segment rootSegment( NULL );
  rootSegment.Init( stripped, false );

  GASOutputModule gasOut;
  gasOut.Handle( &rootSegment );

  NASMOutputModule nasmOut;
  nasmOut.Handle( &rootSegment );

  rootSegment.Run( &memPoint );

  return true;
}



string Interpreter::Strip( string input )
{
  string stripped = "";

  string::iterator it;
  for( it=input.begin(); it != input.end(); ++it )
  {
    if( *it == '>' ||
        *it == '<' ||
        *it == '+' ||
        *it == '-' ||
        *it == '.' ||
        *it == ',' ||
        *it == '[' ||
        *it == ']' )
    {
      stripped += *it;
    }
  }

  return stripped;
}

