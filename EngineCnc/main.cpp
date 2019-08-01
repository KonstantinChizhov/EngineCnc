#include <board.h>


int main()
{
	using namespace EngineCnc;
	
	MainUsart::Init(9600);
	MainUsart::SelectTxRxPins(0, 0);
	sei();
	
	cout << "Hello, world!\r\n";
	cout << "Clock = " << Mcucpp::Clock::SysClock::ClockFreq() << "\r\n";
		
	
	return 0;
}

