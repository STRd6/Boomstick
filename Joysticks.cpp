#include "Joysticks.h"

using namespace OIS;

// Globals
InputManager *g_InputManager = 0;	//Our Input System
JoyStick* g_joys[MAX_JOYSTICKS] = {0,0,0,0,0,0,0,0};	//This demo supports up to 8 controllers
bool appRunning = true;				//Global Exit Flag

const char *g_DeviceType[6] = {
  "OISUnknown", "OISKeyboard", "OISMouse",
  "OISJoyStick", "OISTablet", "OISOther"
};

class EventHandler :
  public JoyStickListener
{
public:
	EventHandler() {}
	~EventHandler() {}

	bool buttonPressed( const JoyStickEvent &arg, int button ) {
		std::cout << std::endl << arg.device->vendor() << ". Button Pressed # " << button;

		return true;
	}

	bool buttonReleased( const JoyStickEvent &arg, int button ) {
		std::cout << std::endl << arg.device->vendor() << ". Button Released # " << button;

		return true;
	}

	bool axisMoved( const JoyStickEvent &arg, int axis )
	{
		//Provide a little dead zone
		if( arg.state.mAxes[axis].abs > 2500 || arg.state.mAxes[axis].abs < -2500 )
			std::cout << std::endl << arg.device->vendor() << ". Axis # " << axis << " Value: " << arg.state.mAxes[axis].abs;

		return true;
	}

	bool povMoved( const JoyStickEvent &arg, int pov )
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

	bool vector3Moved( const JoyStickEvent &arg, int index)
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
};

//Create a global instance
EventHandler handler;

int processJoystickInputs()
{
	std::cout << "\n\n*** OIS Console Demo App is starting up... *** \n";
	try
	{
		doStartup();
		std::cout << "\nStartup done... Hit 'q' or ESC to exit.\n\n";

		while(appRunning)
		{
			//Throttle down CPU usage
			#if defined OIS_WIN32_PLATFORM
			  Sleep(90);
			  MSG  msg;
			  while( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
			  {
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			  }
			#elif defined OIS_LINUX_PLATFORM
			  usleep( 500 );
      #elif defined OIS_APPLE_PLATFORM
			  usleep( 500 );
			#endif

			for( int i = 0; i < MAX_JOYSTICKS ; ++i )
			{
				if( g_joys[i] )
				{
					g_joys[i]->capture();
					if( !g_joys[i]->buffered() )
						handleNonBufferedJoy( g_joys[i] );
				}
			}
		}
	}
	catch( const Exception &ex )
	{
		#if defined OIS_WIN32_PLATFORM
		  MessageBox( NULL, ex.eText, "An exception has occurred!", MB_OK |
				MB_ICONERROR | MB_TASKMODAL);
		#else
		  std::cout << "\nOIS Exception Caught!\n" << "\t" << ex.eText << "[Line "
			<< ex.eLine << " in " << ex.eFile << "]\nExiting App";
		#endif
	}
	catch(std::exception &ex)
	{
		std::cout << "Caught std::exception: what = " << ex.what() << std::endl;
	}

	//Destroying the manager will cleanup unfreed devices
	if( g_InputManager )
		InputManager::destroyInputSystem(g_InputManager);

	std::cout << "\n\nGoodbye\n\n";
	return 0;
}

void doStartup()
{
	OIS::ParamList pl;

	//This never returns null.. it will raise an exception on errors
	g_InputManager = InputManager::createInputSystem(pl);

	//Lets enable all addons that were compiled in:
	g_InputManager->enableAddOnFactory(InputManager::AddOn_All);

	//Print debugging information
	unsigned int v = g_InputManager->getVersionNumber();
	std::cout << "OIS Version: " << (v>>16 ) << "." << ((v>>8) & 0x000000FF) << "." << (v & 0x000000FF)
		<< "\nRelease Name: " << g_InputManager->getVersionName()
		<< "\nManager: " << g_InputManager->inputSystemName()
		<< "\nTotal JoySticks: " << g_InputManager->getNumberOfDevices(OISJoyStick);

	//List all devices
	DeviceList list = g_InputManager->listFreeDevices();
	for( DeviceList::iterator i = list.begin(); i != list.end(); ++i )
		std::cout << "\n\tDevice: " << g_DeviceType[i->first] << " Vendor: " << i->second;

	try
	{
		//This demo uses at most 8 joysticks - use old way to create (i.e. disregard vendor)
		int numSticks = std::min(g_InputManager->getNumberOfDevices(OISJoyStick), MAX_JOYSTICKS);
		for( int i = 0; i < numSticks; ++i )
		{
			g_joys[i] = (JoyStick*)g_InputManager->createInputObject( OISJoyStick, true );
			g_joys[i]->setEventCallback( &handler );
			std::cout << "\n\nCreating Joystick " << (i + 1)
				<< "\n\tAxes: " << g_joys[i]->getNumberOfComponents(OIS_Axis)
				<< "\n\tSliders: " << g_joys[i]->getNumberOfComponents(OIS_Slider)
				<< "\n\tPOV/HATs: " << g_joys[i]->getNumberOfComponents(OIS_POV)
				<< "\n\tButtons: " << g_joys[i]->getNumberOfComponents(OIS_Button)
				<< "\n\tVector3: " << g_joys[i]->getNumberOfComponents(OIS_Vector3);
		}
	}
	catch(OIS::Exception &ex)
	{
		std::cout << "\nException raised on joystick creation: " << ex.eText << std::endl;
	}
}

void handleNonBufferedJoy( JoyStick* js )
{
	//Just dump the current joy state
	const JoyStickState &joy = js->getJoyStickState();
	for( unsigned int i = 0; i < joy.mAxes.size(); ++i )
		std::cout << "\nAxis " << i << " X: " << joy.mAxes[i].abs;
}
