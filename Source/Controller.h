// Copyright (c) 2023 George Humphreys
#pragma once
#include "EasyXInputDefinitions.h"
#include "EXICallbacks.h"
#include <map>
#include <windows.h>
#include <Xinput.h>

#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")

namespace EXI
{
	struct ControllerButton
	{
	public:
		void SetPressed() 
		{ 
			if (!m_isPressed && m_pressed.IsBound())
			{
				m_isPressed = true;
				m_pressed.m_callback(this);
				return;
			}

			m_isPressed = true;
		}

		void SetReleased() 
		{ 
			if (m_isPressed && m_released.IsBound())
			{
				m_isPressed = false;
				m_released.m_callback(this);
				return;
			}

			m_isPressed = false;
		}

		bool m_isPressed{ false };

		ControllerButtonCallback m_pressed;
		ControllerButtonCallback m_released;
	};

	struct ControllerAxis
	{
	public:
		ControllerAxis() {}

		void SetAxis(SHORT x, SHORT y)
		{
			float xTemp = 0;
			float yTemp = 0;
			float magnitude = sqrt(x * x + y * y);

			if (magnitude > INPUT_DEADZONE)
			{
				// Should do something here
				xTemp = x / 32767.0f;
				yTemp = y / 32767.0f;
			}
			else
			{
				xTemp = 0;
				yTemp = 0;
			}

			if (m_axisChanged.IsBound())
			{
				if (m_x != xTemp || m_y != yTemp)
				{
					m_x = xTemp;
					m_y = yTemp;
					m_axisChanged.m_callback(this);
					return;
				}
			}

			m_x = xTemp;
			m_y = yTemp;
		}

		float m_x{ 0.0 };
		float m_y{ 0.0 };

		ControllerAxisCallback m_axisChanged;
	};

	struct ControllerTrigger
	{
	public:
		ControllerTrigger() {}

		void SetPressure(BYTE pressure) 
		{ 
			if (m_pressure != pressure && m_pressureChanged.IsBound())
			{
				m_pressure = pressure;
				m_pressureChanged.m_callback(this);
				return;
			}

			m_pressure = pressure; 
		}

		BYTE m_pressure{ 0 };

		ControllerTriggerCallback m_pressureChanged;
	};

	class Controller
	{
	public:
		Controller();
		Controller(XINPUT_GAMEPAD controllerState);
		void BuildControllerMap();

		void UpdateFromState(XINPUT_GAMEPAD controllerState);
		void SetPortNum(int num) { m_portNum = num; }

		void PrintStates(bool clearConsole = false) const;

		bool IsButtonPressed(WORD button) const
		{
			return m_buttonMap.at(button).m_isPressed;
		}

		ControllerButton* GetButton(WORD button)
		{
			return &m_buttonMap.at(button);
		}

		ControllerAxis m_lStick;
		ControllerAxis m_rStick;
		ControllerTrigger m_lTrigger;
		ControllerTrigger m_rTrigger;

	private:
		std::map<WORD, ControllerButton> m_buttonMap;
		int m_portNum{ 0 };
	};

	const char* GetControllerInputAsString(WORD input);
}

