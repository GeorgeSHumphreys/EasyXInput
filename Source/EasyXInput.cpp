// Copyright (c) 2023 George Humphreys
#include "EasyXInput.h"

namespace EXI
{
	EasyXInput* EasyXInput::s_instance{ nullptr };

	EasyXInput::EasyXInput()
	{
		for (int i = 0; i < MAXCONTROLLERS; i++)
		{
			m_controllerList[i] = new Controller();
		}
	}

	EasyXInput::~EasyXInput()
	{
		for (int i = 0; i < MAXCONTROLLERS; i++)
		{
			delete m_controllerList[i];
		}

		delete s_instance;
	}

	void EasyXInput::UpdateStates()
	{
		EasyXInput* instance = GetInstance();
		if (!instance)
			return;

		XINPUT_STATE state;
		for (int i = 0; i < MAXCONTROLLERS; i++)
		{
			ZeroMemory(&state, sizeof(XINPUT_STATE));

			if (XInputGetState(i, &state) == ERROR_SUCCESS)
			{
				instance->m_controllerList[i]->UpdateFromState(state.Gamepad);
			}
		}
	}

	ports EasyXInput::GetActivePorts()
	{
		ports portList = 0;
		XINPUT_STATE state;
		PortSlot slots[MAXCONTROLLERS] = { PortSlot::Port0, PortSlot::Port1, PortSlot::Port2, PortSlot::Port3 };

		for (int i = 0; i < MAXCONTROLLERS; i++)
		{
			if (XInputGetState(i, &state) == ERROR_SUCCESS)
			{
				portList = portList | slots[i];
			}
		}

		return portList;
	}

	Controller* EasyXInput::GetController(PortSlot portSlot)
	{
		if (!IsPortActive(portSlot))
			return nullptr;

		int portNum = PortSlotToInt(portSlot);
		if (portNum < 0 && portNum >= MAXCONTROLLERS)
			return nullptr;

		EasyXInput* instance = GetInstance();
		if (instance == nullptr)
			return nullptr;

		return instance->m_controllerList[portNum];
	}

	bool IsPortActive(ports portList, PortSlot slot)
	{
		return (portList & slot) != 0;
	}

	bool IsPortActive(PortSlot slot)
	{
		return IsPortActive(EasyXInput::GetActivePorts(), slot);
	}

	int PortSlotToInt(PortSlot slot)
	{
		int index = 0;
		int buffer = 4096;

		while (buffer > 0) // Bit shift magic :D
		{
			if ((buffer | slot) != 0)
			{
				return index;
			}

			buffer = buffer >> 4;
			index++;
		}

		return -1;
	}
}