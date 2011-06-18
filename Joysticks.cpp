#include "Joysticks.h"

using namespace OIS;

const char *g_DeviceType[6] = {
  "OISUnknown", "OISKeyboard", "OISMouse",
  "OISJoyStick", "OISTablet", "OISOther"
};

JoysticksHandler::JoysticksHandler() {}

JoysticksHandler::~JoysticksHandler() {
  if( m_InputManager ) {
    InputManager::destroyInputSystem(m_InputManager);
  }
}

bool JoysticksHandler::buttonPressed( const JoyStickEvent &arg, int button ) {
  std::cout << std::endl << arg.device->vendor() << ". Button Pressed # " << button;

  return true;
}

bool JoysticksHandler::buttonReleased( const JoyStickEvent &arg, int button ) {
  std::cout << std::endl << arg.device->vendor() << ". Button Released # " << button;

  return true;
}

bool JoysticksHandler::axisMoved( const JoyStickEvent &arg, int axis )
{
  //Provide a little dead zone
  if( arg.state.mAxes[axis].abs > 2500 || arg.state.mAxes[axis].abs < -2500 )
    std::cout << std::endl << arg.device->vendor() << ". Axis # " << axis << " Value: " << arg.state.mAxes[axis].abs;

  return true;
}

bool JoysticksHandler::povMoved( const JoyStickEvent &arg, int pov )
{
  std::cout << std::endl << arg.device->vendor() << ". POV" << pov << " ";

  if( arg.state.mPOV[pov].direction & Pov::North ) //Going up
    std::cout << "North";
  else if( arg.state.mPOV[pov].direction & Pov::South ) //Going down
    std::cout << "South";

  if( arg.state.mPOV[pov].direction & Pov::East ) //Going right
    std::cout << "East";
  else if( arg.state.mPOV[pov].direction & Pov::West ) //Going left
    std::cout << "West";

  if( arg.state.mPOV[pov].direction == Pov::Centered ) //stopped/centered out
    std::cout << "Centered";

  return true;
}

bool JoysticksHandler::vector3Moved( const JoyStickEvent &arg, int index)
{
  std::cout.precision(2);
  std::cout.flags(std::ios::fixed | std::ios::right);
  std::cout << std::endl << arg.device->vendor() << ". Orientation # " << index
    << " X Value: " << arg.state.mVectors[index].x
    << " Y Value: " << arg.state.mVectors[index].y
    << " Z Value: " << arg.state.mVectors[index].z;
  std::cout.precision();
  std::cout.flags();

  return true;
}

void JoysticksHandler::capture()
{
  for( int i = 0; i < MAX_JOYSTICKS ; ++i )
  {
    if( m_joys[i] )
    {
      m_joys[i]->capture();
    }
  }
}

std::vector<JoyStickState> JoysticksHandler::joyStickStates() {
  std::vector<JoyStickState> result;

  for( int i = 0; i < MAX_JOYSTICKS ; ++i )
  {
    if( m_joys[i] )
    {
      result.push_back(m_joys[i]->getJoyStickState());
    }
  }

  return result;
}

void JoysticksHandler::initialize()
{
  status = "uninitialized";

  try
  {
    OIS::ParamList pl;

    //This never returns null.. it will raise an exception on errors
    m_InputManager = InputManager::createInputSystem(pl);

    //Lets enable all addons that were compiled in:
    m_InputManager->enableAddOnFactory(InputManager::AddOn_All);

    //Print debugging information
    // unsigned int v = m_InputManager->getVersionNumber();
    // FBLOG_INFO("doStartup()", boost::format("OIS Version: %1%.%2%.%3%") % (v>>16 ) % ((v>>8) & 0x000000FF) % (v & 0x000000FF));
    // FBLOG_INFO("doStartup()", "\nRelease Name: %s", m_InputManager->getVersionName());

    //	<< "\nManager: " << m_InputManager->inputSystemName()
    //	<< "\nTotal JoySticks: " << m_InputManager->getNumberOfDevices(OISJoyStick);

    //List all devices
    // DeviceList list = m_InputManager->listFreeDevices();
    // for( DeviceList::iterator i = list.begin(); i != list.end(); ++i )
    //   std::cout << "\n\tDevice: " << g_DeviceType[i->first] << " Vendor: " << i->second;

    status = "input manager created";

    try
    {
      status = "before initializing joysticks";

      //This demo uses at most 8 joysticks - use old way to create (i.e. disregard vendor)
      int numSticks = std::min(m_InputManager->getNumberOfDevices(OISJoyStick), MAX_JOYSTICKS);
      for( int i = 0; i < numSticks; ++i )
      {
        m_joys[i] = (JoyStick*)m_InputManager->createInputObject( OISJoyStick, true );
        m_joys[i]->setEventCallback( this );
        std::cout << "\n\nCreating Joystick " << (i + 1)
          << "\n\tAxes: " << m_joys[i]->getNumberOfComponents(OIS_Axis)
          << "\n\tSliders: " << m_joys[i]->getNumberOfComponents(OIS_Slider)
          << "\n\tPOV/HATs: " << m_joys[i]->getNumberOfComponents(OIS_POV)
          << "\n\tButtons: " << m_joys[i]->getNumberOfComponents(OIS_Button)
          << "\n\tVector3: " << m_joys[i]->getNumberOfComponents(OIS_Vector3);
      }

      status = (boost::format("Initialized %d joysticks") % numSticks).str();
    }
    catch(OIS::Exception &ex)
    {
      status = ex.eText;
    }
  }
  catch( const Exception &ex )
  {
    status = ex.eText;
  }
  catch(std::exception &ex)
  {
    status = ex.what();
  }
}
