
#pragma once
#include <iopins.h>
#include <pinlist.h>
#include <usart.h>
#include <clock.h>
#include <timers.h>
#include <adc.h>
#include <watchdog.h>

#include <tiny_ostream.h>

namespace EngineCnc
{
	typedef Mcucpp::Usart1 MainUsart;

	class UsartOut
	{
	public:
		void put(char c)
		{
			MainUsart::Write(c);
		}
	};
	
	typedef Mcucpp::basic_ostream<UsartOut> ostream;
	extern ostream cout;
	
	class Board
	{
	public:
		void Init();
	};
}