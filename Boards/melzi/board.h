
#pragma once
#include <iopins.h>
#include <pinlist.h>
#include <usart.h>
#include <clock.h>
#include <timers.h>
#include <adc.h>
#include <watchdog.h>
#include <tiny_ostream.h>
#include <delay.h>

#include <stepper.h>
#include <endstop.h>

namespace EngineCnc
{
namespace Board
{
using namespace Mcucpp;
using namespace Mcucpp::IO;

typedef Usart1 MainUsart;
typedef Timers::Timer1 StepperTimer;
typedef TimerDelay<StepperTimer> DelayType;

typedef PinList<Pb0, Pb1, Pb2, Pb3> StepPins;
typedef PinList<Pb4, Pb5, Pb6, Pb7> DirPins;
typedef PinList<Pc0, Pc0, Pc0, Pc0> EnablePins;

typedef PinList<Pc1, Pc2, Pc3, NullPin> MinEndstopPins;
typedef PinList<NullPin, NullPin, NullPin, NullPin> MaxEndstopPins;
constexpr int MinStepperPulseDelay = 2;

typedef StepDirStepper<StepPins, DirPins, EnablePins, DelayType, MinStepperPulseDelay> Stepper;
typedef PinEndstop<MinEndstopPins, MaxEndstopPins> Endstops;

class UsartOut
{
public:
	void put(char c)
	{
		MainUsart::Write(c);
	}
};

void Init();

} // namespace Board

typedef Mcucpp::basic_ostream<Board::UsartOut> ostream;
extern ostream cout;
} // namespace EngineCnc