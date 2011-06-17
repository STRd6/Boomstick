
#include "Xbox360ControllerJavaScriptSupportAPI.h"

#include "Xbox360ControllerJavaScriptSupport.h"

#include "OISException.h"
#include "OISInputManager.h"
#include "OISJoyStick.h"
#include "OISEvents.h"

#include <iostream>
#include <vector>
#include <sstream>

const int MAX_JOYSTICKS = 8;

void doStartup();
void handleNonBufferedJoy( OIS::JoyStick* js );
