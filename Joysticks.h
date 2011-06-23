#ifndef Joysticks_H
#define Joysticks_H

#include "OISException.h"
#include "OISInputManager.h"
#include "OISJoyStick.h"
#include "OISEvents.h"

#include <boost/format.hpp>

#include <iostream>
#include <vector>
#include <sstream>

using namespace OIS;

const int MAX_JOYSTICKS = 8;

class JoysticksHandler {
public:
	JoysticksHandler();
	~JoysticksHandler();

  void capture();

  std::vector<JoyStickState> joyStickStates();

  void initialize();

  std::string status;

private:
  InputManager *m_InputManager;
  JoyStick* m_joys[MAX_JOYSTICKS];
};

#endif
