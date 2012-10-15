#include "nasmOutput.hh"
#include <string>
#include <vector>
#include <fstream>

using std::cout;
using std::string;
using std::vector;


bool NASMOutputModule::Handle( Segment *rootSegment )
{
  out = new std::ofstream( "nasm.asm" );

  CreateHeader();
  HandleSegment( rootSegment );
  CreateFooter();

  out->close();

  return true;
}



bool NASMOutputModule::CreateHeader()
{
  string header =
    "global _start\n"
	"section .bss\n"
	"  mem resb 30000\n"
    "section .text\n"
    "_start:\n"
	"  mov edx, mem\n";

  *out << header;

  return true;
}



bool NASMOutputModule::CreateFooter()
{
  string footer =
    "  mov eax, 0\n"
    "  ret\n";

  *out << footer;

  return true;
}



bool NASMOutputModule::HandleSegment( Segment *segment )
{
  unsigned int id = segment->GetId();

  if( segment->IsLoop() )
  {
    *out << "  xor  eax, eax\n";
    *out << "  mov  al, [edx]\n";
    *out << "  test al, al\n";
    *out << "  jz   seg" << id << "end\n";
    *out << "seg" << id << "start:\n";
  }

  if( segment->HasChildren() )
    HandleChildren( segment );
  else
    HandleCommands( segment );


  if( segment->IsLoop() )
  {
    *out << "  xor  eax, eax\n";
    *out << "  mov  al, [edx]\n";
    *out << "  test al, al\n";
    *out << "  jnz  seg" << id << "start\n";
    *out << "seg" << segment->GetId() << "end:\n";
  }

  return true;
}



bool NASMOutputModule::HandleChildren( Segment *segment )
{
  vector<Segment*> *children = segment->GetChildren();
  vector<Segment*>::iterator it;

  for( it = children->begin(); it != children->end(); ++it )
  {
    HandleSegment( *it );
  }

  return true;
}



bool NASMOutputModule::HandleCommands( Segment *segment )
{
  vector<sCommand*> *commands = segment->GetCommands();
  vector<sCommand*>::iterator it;

  for( it = commands->begin(); it != commands->end(); ++it )
  {
    switch( (*it)->type )
    {
      case( ADD ):
       *out << "  add   edx, " << (*it)->count << "\n";
       break;

      case( SUB ):
       *out << "  sub   edx, " << (*it)->count << "\n";
       break;

      case( INC ):
       *out << "  xor   eax, eax\n";
	   *out << "  mov   al, [edx]\n";
       *out << "  add   al, " << (*it)->count << "\n";
       *out << "  mov   [edx], al\n";
       break;

      case( DEC ):
       *out << "  xor   eax, eax\n";
       *out << "  mov   al, [edx]\n";
       *out << "  sub   al, " << (*it)->count << "\n";
       *out << "  mov   [edx], al\n";
       break;

      case( PRINT ):
       //*out << "  mov   $4, %eax\n";
       //*out << "  mov   $1, %ebx\n";
       //*out << "  mov   %edx, %ecx\n";
       //*out << "  push  %edx\n";
       //*out << "  mov   $1, %edx\n";
       //*out << "  int    $0x80\n";
       //*out << "  popl   %edx\n";
       break;
    }
  }

  return true;
}

