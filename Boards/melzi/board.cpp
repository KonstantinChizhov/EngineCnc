#include <board.h>

using namespace Mcucpp;
namespace EngineCnc
{

ostream cout;
namespace Board
{
void Init()
{
    MainUsart::Init(9600);
	MainUsart::SelectTxRxPins(0, 0);
	sei();
}
}
}