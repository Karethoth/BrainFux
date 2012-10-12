#include "asOutput.hh"
#include <vector>

using std::string;
using std::vector;


bool AsOutputModule::Handle( Segment *rootSegment )
{
  out = new std::ofstream( "outp.asm" );

  CreateHeader();
  HandleSegment( rootSegment );
  CreateFooter();

  out->close();

  return true;
}



bool AsOutputModule::CreateHeader()
{
  string header =
    "  .comm mem, 30000, 32\n"
    "  .text\n"
    "  .globl _start\n"
    "_start:\n"
    "  movl $mem, %edx\n";

  *out << header;

  return true;
}



bool AsOutputModule::CreateFooter()
{
  string header =
    "  movl $1, %eax\n"
    "  movl $0, %ebx\n"
    "  int  $0x80\n";

  *out << header;

  return true;
}



bool AsOutputModule::HandleSegment( Segment *segment )
{
  unsigned int id = segment->GetId();

  if( segment->IsLoop() )
  {
    *out << "  xorl %eax, %eax\n";
    *out << "  movzbl  (%edx), %eax\n";
    *out << "  test %eax, %eax\n";
    *out << "  jz seg" << id << "end\n";
    *out << "seg" << id << "start:\n";
  }

  if( segment->HasChildren() )
    HandleChildren( segment );
  else
    HandleCommands( segment );


  if( segment->IsLoop() )
  {
    *out << "  xorl %eax, %eax\n";
    *out << "  movzbl  (%edx), %eax\n";
    *out << "  test %eax, %eax\n";
    *out << "  jnz seg" << id << "start\n";
    *out << "seg" << segment->GetId() << "end:\n";
  }

  return true;
}



bool AsOutputModule::HandleChildren( Segment *segment )
{
  vector<Segment*> *children = segment->GetChildren();
  vector<Segment*>::iterator it;

  for( it = children->begin(); it != children->end(); ++it )
  {
    HandleSegment( *it );
  }

  return true;
}



bool AsOutputModule::HandleCommands( Segment *segment )
{
  vector<sCommand*> *commands = segment->GetCommands();
  vector<sCommand*>::iterator it;

  for( it = commands->begin(); it != commands->end(); ++it )
  {
    switch( (*it)->type )
    {
      case( ADD ):
       *out << "  addl $" << (*it)->count << ", %edx\n";
       break;

      case( SUB ):
       *out << "  subl $" << (*it)->count << ", %edx\n";
       break;

      case( INC ):
       *out << "  xorl %eax, %eax\n";
       *out << "  movzbl  (%edx), %eax\n";
       *out << "  addl    $" << (*it)->count << ", %eax\n";
       *out << "  movb    %al, (%edx)\n";
       break;

      case( DEC ):
       *out << "  xorl %eax, %eax\n";
       *out << "  movzbl  (%edx), %eax\n";
       *out << "  subl    $" << (*it)->count << ", %eax\n";
       *out << "  movb    %al, (%edx)\n";
       break;

      case( PRINT ):
       *out << "  movl $4, %eax\n";
       *out << "  movl $1, %ebx\n";
       *out << "  movl %edx, %ecx\n";
       *out << "  pushl %edx\n";
       *out << "  movl $1, %edx\n";
       *out << "  int  $0x80\n";
       *out << "  popl %edx\n";
       break;
    }
  }

  return true;
}

