// Copyright (c) 2023 George Humphreys
#pragma once

#define MAXCONTROLLERS 4
#define INPUT_DEADZONE 3276

namespace EXI
{
	typedef int ports;

	enum PortSlot
	{
		Port0 = 0x1000,
		Port1 = 0x0100,
		Port2 = 0x0010,
		Port3 = 0x0001
	};

}