#include "interpreter.hh"

#include <string>
#include <fstream>
#include <streambuf>

using std::string;
using std::cout;


Interpreter::Interpreter()
{
}



Interpreter::~Interpreter()
{
}



bool Interpreter::HandleFile( string path )
{
  std::ifstream stream( path.c_str() );

  string content( (std::istreambuf_iterator<char>( stream )),
                   std::istreambuf_iterator<char>() );

  string stripped = Strip( content );
  cout << stripped << "\n";

  Segment rootSegment;
  rootSegment.Init( stripped, false );
  rootSegment.Print();

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

