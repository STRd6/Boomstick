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

class JoysticksHandler :
  public JoyStickListener
{
public:
	JoysticksHandler();
	~JoysticksHandler();

	bool buttonPressed( const JoyStickEvent &arg, int button );
	bool buttonReleased( const JoyStickEvent &arg, int button );
	bool axisMoved( const JoyStickEvent &arg, int axis );
	bool povMoved( const JoyStickEvent &arg, int pov );
	bool vector3Moved( const JoyStickEvent &arg, int index);

  void capture();

  std::vector<JoyStickState> joyStickStates();

  void initialize();

  std::string status;

private:
  InputManager *m_InputManager;
  JoyStick* m_joys[MAX_JOYSTICKS];
};

#endif
