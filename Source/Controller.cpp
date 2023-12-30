// Copyright (c) 2023 George Humphreys
#include "Controller.h"

#include <iostream>

namespace EXI
{
	Controller::Controller()
		: m_lStick()
		, m_rStick()
		, m_lTrigger()
		, m_rTrigger()
	{
		BuildControllerMap();
	}

	Controller::Controller(XINPUT_GAMEPAD controllerState)
		: m_lStick()
		, m_rStick()
		, m_lTrigger()
		, m_rTrigger()
	{
		BuildControllerMap();
	}

	void Controller::BuildControllerMap()
	{
		ControllerButton tempButton;
		m_buttonMap.insert({ XINPUT_GAMEPAD_DPAD_UP, tempButton });
		m_buttonMap.insert({ XINPUT_GAMEPAD_DPAD_DOWN, tempButton });
		m_buttonMap.insert({ XINPUT_GAMEPAD_DPAD_LEFT, tempButton });
		m_buttonMap.insert({ XINPUT_GAMEPAD_DPAD_RIGHT, tempButton });
		m_buttonMap.insert({ XINPUT_GAMEPAD_START, tempButton });
		m_buttonMap.insert({ XINPUT_GAMEPAD_BACK, tempButton });
		m_buttonMap.insert({ XINPUT_GAMEPAD_LEFT_THUMB, tempButton });
		m_buttonMap.insert({ XINPUT_GAMEPAD_RIGHT_THUMB, tempButton });
		m_buttonMap.insert({ XINPUT_GAMEPAD_LEFT_SHOULDER, tempButton });
		m_buttonMap.insert({ XINPUT_GAMEPAD_RIGHT_SHOULDER, tempButton });
		m_buttonMap.insert({ XINPUT_GAMEPAD_A, tempButton });
		m_buttonMap.insert({ XINPUT_GAMEPAD_B, tempButton });
		m_buttonMap.insert({ XINPUT_GAMEPAD_X, tempButton });
		m_buttonMap.insert({ XINPUT_GAMEPAD_Y, tempButton });
	}

	void Controller::UpdateFromState(XINPUT_GAMEPAD controllerState)
	{
		// Buttons First
		for (auto& x : m_buttonMap)
		{
			bool lastState = x.second.m_isPressed;
			bool newState = (controllerState.wButtons & x.first) != 0;

			if (lastState != newState)
			{
				if (newState)
				{
					x.second.SetPressed();
				}
				else
				{
					x.second.SetReleased();
				}
			}
		}

		// Control Sticks
		m_lStick.SetAxis(controllerState.sThumbLX, controllerState.sThumbLY);
		m_rStick.SetAxis(controllerState.sThumbRX, controllerState.sThumbRY);

		// Triggers
		m_lTrigger.SetPressure(controllerState.bLeftTrigger);
		m_rTrigger.SetPressure(controllerState.bRightTrigger);
	}

	void Controller::PrintStates(bool clearConsole) const
	{
		if (clearConsole)
			system("cls");

		for (auto& button : m_buttonMap)
		{
			std::cout << GetControllerInputAsString(button.first) << ": " << button.second.m_isPressed << std::endl;
		}

		std::cout << "LStick: " << m_lStick.m_x << "/" << m_lStick.m_y << std::endl;
		std::cout << "RStick: " << m_rStick.m_x << "/" << m_rStick.m_y << std::endl;

		std::cout << "LTrigger: " << m_lTrigger.m_pressure << std::endl;
		std::cout << "RTrigger: " << m_rTrigger.m_pressure << std::endl;
	}


	// Globals
	const char* GetControllerInputAsString(WORD input)
	{
		switch (input)
		{
		case XINPUT_GAMEPAD_DPAD_UP: return "DPAD_UP";
		case XINPUT_GAMEPAD_DPAD_DOWN: return "DPAD_DOWN";
		case XINPUT_GAMEPAD_DPAD_LEFT: return "DPAD_LEFT";
		case XINPUT_GAMEPAD_DPAD_RIGHT: return "DPAD_RIGHT";
		case XINPUT_GAMEPAD_START: return "START";
		case XINPUT_GAMEPAD_BACK: return "BACK";
		case XINPUT_GAMEPAD_LEFT_THUMB: return "LEFT_THUMB";
		case XINPUT_GAMEPAD_RIGHT_THUMB: return "RIGHT_THUMB";
		case XINPUT_GAMEPAD_LEFT_SHOULDER: return "LEFT_SHOULDER";
		case XINPUT_GAMEPAD_RIGHT_SHOULDER: return "RIGHT_SHOULDER";
		case XINPUT_GAMEPAD_A: return "GAMEPAD_A";
		case XINPUT_GAMEPAD_B: return "GAMEPAD_B";
		case XINPUT_GAMEPAD_X: return "GAMEPAD_X";
		case XINPUT_GAMEPAD_Y: return "GAMEPAD_Y";
		}
		return "";
	}
}



