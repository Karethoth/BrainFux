#include "segment.hh"

using std::cout;
using std::string;
using std::vector;


bool Segment::Init( string data, bool isLoop )
{
  loop = isLoop;
  Construct( data );
}



bool Segment::Construct( string data )
{
  cout << "Constructing loop(" << loop << ") segment using data '" << data << "'\n";
  string dataLeft = data;
  
  while( dataLeft.length() > 0 )
  {
    size_t segmentSize;

    // If the segment is a loop
    if( dataLeft.c_str()[0] == '[' )
    {
      segmentSize = FindLoopEnd( dataLeft );

      Segment newSegment;
      newSegment.Init( dataLeft.substr( 1, segmentSize-1 ), true );

      children.push_back( newSegment );
      segmentSize += 1;
    }
    // If the segment is not a loop
    else
    {
      segmentSize = CalculateNextSegmentSize( dataLeft );

      if( segmentSize == dataLeft.length() &&
          dataLeft    == data )
      {
        string::iterator it;
        for( it = dataLeft.begin(); it != dataLeft.end(); ++it )
        {
          commands.push_back( sCommand( *it ) );
        }
        break;
      }
      else
      {
        Segment newSegment;
        newSegment.Init( dataLeft.substr( 0, segmentSize ), false );

        children.push_back( newSegment );
      }
    }

    dataLeft = dataLeft.substr( segmentSize );
  }
}



bool Segment::HasChildren()
{
  if( children.size() > 0 )
    return true;

  return false;
}



void Segment::Print()
{
  vector<sCommand>::iterator it;
  for( it = commands.begin(); it != commands.end(); ++it )
  {
    cout << (*it).type;
  }
  cout << "\n";
}



size_t Segment::CalculateNextSegmentSize( string data )
{
  size_t loopStart = data.find( '[' );
  if( loopStart == string::npos )
    return data.length();

  return loopStart;
}



size_t Segment::FindLoopEnd( string data )
{
  unsigned counter = 0;

  string::iterator it;
  for( it = data.begin(); it != data.end(); ++it )
  {
    if( *it == '[' )
      ++counter;
    else if( *it == ']' )
      --counter;
    
    if( counter <= 0 )
      break;
  }

  return it - data.begin();
}

