// Copyright (c) 2023 George Humphreys
#pragma once

#include "EasyXInputDefinitions.h"
#include "Controller.h"

namespace EXI
{
	class EasyXInput
	{
	public:
		EasyXInput();

		~EasyXInput();

		static void Initialize()
		{
			if (!s_instance)
			{
				s_instance = new EasyXInput();
			}
		}

		static EasyXInput* GetInstance()
		{
			return s_instance;
		}

		static void UpdateStates();
		static ports GetActivePorts();
		static Controller* GetController(PortSlot portSlot);

	private:
		static EasyXInput* s_instance;

		Controller* m_controllerList[MAXCONTROLLERS]{ nullptr };
	};

	bool IsPortActive(ports portList, PortSlot slot);
	bool IsPortActive(PortSlot slot);
	int PortSlotToInt(PortSlot slot);
}
