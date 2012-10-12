#include "segment.hh"
#include <cstdio>

using std::cin;
using std::cout;
using std::string;
using std::vector;



Segment::Segment( Segment *parent )
{
  parent = parent;
  id = NewSegmentId();
}


bool Segment::Init( string data, bool isLoop )
{
  loop = isLoop;
  return Construct( data );
}



bool Segment::Construct( string data )
{
  string dataLeft = data;
  
  while( dataLeft.length() > 0 )
  {
    size_t segmentSize;

    // If the segment is a loop
    if( dataLeft.c_str()[0] == '[' )
    {
      segmentSize = FindLoopEnd( dataLeft );

      Segment *newSegment = new Segment( this );
      newSegment->Init( dataLeft.substr( 1, segmentSize-1 ), true );

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
        sCommand cmd;
        sCommand tmp;

        string::iterator it;

        for( it = dataLeft.begin(); it != dataLeft.end(); ++it )
        {
          tmp = sCommand( *it );
          if( cmd.type == tmp.type )
          {
            cmd.count++;
          }
          else if( cmd.type == NOT_DEFINED )
          {
            cmd = tmp;
          }
          else
          {
            sCommand *newCmd = new sCommand();
            newCmd->type = cmd.type;
            newCmd->count = cmd.count;

            commands.push_back( newCmd );
            cmd = tmp;
          }
        }

        sCommand *newCmd = new sCommand();
        newCmd->type = cmd.type;
        newCmd->count = cmd.count;

        commands.push_back( newCmd );
        break;
      }
      else
      {
        Segment *newSegment = new Segment( this );
        newSegment->Init( dataLeft.substr( 0, segmentSize ), false );

        children.push_back( newSegment );
      }
    }

    dataLeft = dataLeft.substr( segmentSize );
  }

  return true;
}



bool Segment::HasChildren()
{
  if( children.size() > 0 )
    return true;

  return false;
}



void Segment::Print( int ident )
{
  if( loop )
  {
    for( int i=0; i<ident; ++i )
      cout << "  ";
    cout << "[\n";
  }

  if( HasChildren() )
  {
    vector<Segment*>::iterator it;
    if( loop )
      ++ident;
    for( it = children.begin(); it != children.end(); ++it )
    {
      (*it)->Print( ident );
    }
    if( loop )
      --ident;
  }
  else
  {
    vector<sCommand*>::iterator it;
    for( int i=0; i<ident; ++i )
      cout << "  ";
    if( loop )
      cout << "  ";
    for( it = commands.begin(); it != commands.end(); ++it )
    {
      cout << (*it)->type << "(" << (*it)->count << ")";
    }
  }

  if( loop )
  {
    cout << "\n";
    for( int i=0; i<ident; ++i )
      cout << "  ";
    cout << "]";
  }
  cout << "\n";
}



vector<Segment*>* Segment::GetChildren()
{
  return &children;
}



vector<sCommand*>* Segment::GetCommands()
{
  return &commands;
}



unsigned int Segment::GetId()
{
  return id;
}



bool Segment::IsLoop()
{
  return loop;
}



bool Segment::Run( unsigned char **p )
{
  if( loop )
  {
    while( **p )
    {
      Exec( p );
    }
  }
  else
  {
    Exec( p );
  }

  return true;
}



inline
size_t Segment::CalculateNextSegmentSize( string data )
{
  size_t loopStart = data.find( '[' );
  if( loopStart == string::npos )
    return data.length();

  return loopStart;
}



inline
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



inline
bool Segment::Exec( unsigned char **p )
{
  if( HasChildren() )
  {
    vector<Segment*>::iterator it;
    for( it = children.begin(); it != children.end(); ++it )
    {
      (*it)->Run( p );
    }
  }
  else
  {
    vector<sCommand*>::iterator it;
  
    for( it = commands.begin(); it != commands.end(); ++it )
    {
      switch( (*it)->type )
      {
        case ADD:
          *p += (*it)->count;
          break;

        case SUB:
          *p -= (*it)->count;
          break;

        case INC:
          **p += (*it)->count;
          break;

        case DEC:
          **p -= (*it)->count;
          break;

        case PRINT:
          cout << string( (*it)->count, **p );
          break;

        case READ:
          **p = getchar();
          break;
      }
    }
  }
}

