# EasyXInput: The simple XInput Wrapper for C++ 

## Overview
EasyXInput is built to read Controller inputs in an easy to use system. The Plug-And-Play nature of this library means that you can start reading and using inputs in under 10 lines of code!

## Usage

### Installation
Installation is very simple. Download the Source files and include "EasyXInput.h" into your respected header file.

### Implementation

On adding the include file, be sure to initialize the system before starting any Input checks.

```
EXI::EasyXInput::Initialize();
```
Afterwards you can discover if a port is active by using the included "IsPortActive" method

```
EXI::IsPortActive(EXI::PortSlot::Port0);
```

The core class for checking / implementing callbacks is the Controller class, which can be gathered as such:

```
EXI::Controller* controller = EXI::EasyXInput::GetController(EXI::PortSlot::Port0);
```

Now that you have access to a controller you can individually check for an input.

```
controller->IsButtonPressed(XINPUT_GAMEPAD_A);
controller->m_lStick.m_y > 0.8;
controller->m_lTrigger.m_pressure > 240;
```

Alternatively, you can also create bindings that can be added to.
Firstly define your callback function, making sure to add the parameter as the type of input you are checking.

```
void ButtonPressedTest(ControllerButton* pressedButton);
void ButtonReleasedTest(ControllerButton* pressedButton);
void AxisChangedTest(ControllerAxis* axis);
void TriggerChangedTest(ControllerTrigger* axis);
```

For binding, you can access a respective button input using the GetButton Method. (These take in XINPUT WORD's)

```
 controller->GetButton(XINPUT_GAMEPAD_A)
```

And binding can be done as so:

```
controller->GetButton(XINPUT_GAMEPAD_A)->m_pressed.Bind(test, &TestClass::ButtonPressedTest);
controller->GetButton(XINPUT_GAMEPAD_A)->m_released.Bind(test, &TestClass::ButtonReleasedTest);

controller->m_lStick.m_axisChanged.Bind(test, &TestClass::AxisChangedTest);
controller->m_rStick.m_axisChanged.Bind(test, &TestClass::AxisChangedTest);

controller->m_lTrigger.m_pressureChanged.Bind(test, &TestClass::TriggerChangedTest);
controller->m_rTrigger.m_pressureChanged.Bind(test, &TestClass::TriggerChangedTest);
```

Finally, you will need an area in your code where you constantly update the controller states. If there is no Update Method, a while(true) will do.
When debugging there is a PrintStates method on the controller which will output all of the current controller states.

```
while (true)
{
    EasyXInput::UpdateStates();
    controller->PrintStates(true);
    Sleep(50);
}
```


## License
This repository uses the MIT License.
