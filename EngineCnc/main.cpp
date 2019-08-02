#include <board.h>
#include <stepper_controller.h>

using namespace EngineCnc;
typedef StepperController<Board::Stepper, Board::Endstops, int32_t> TheStepperController;
TheStepperController stepperController;

int main()
{
	Board::Init();	
	stepperController.Init();
	
	cout << "Hello, world!\r\n";
	cout << "Clock = " << Mcucpp::Clock::SysClock::ClockFreq() << "\r\n";
	
	
	return 0;
}

