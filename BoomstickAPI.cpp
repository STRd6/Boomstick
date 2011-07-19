#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"

#include "BoomstickAPI.h"
#include <json/json.h>

///////////////////////////////////////////////////////////////////////////////
/// @fn BoomstickAPI::BoomstickAPI(const BoomstickPtr& plugin, const FB::BrowserHostPtr host)
///
/// @brief  Constructor for your JSAPI object.  You should register your methods, properties, and events
///         that should be accessible to Javascript from here.
///
/// @see FB::JSAPIAuto::registerMethod
/// @see FB::JSAPIAuto::registerProperty
/// @see FB::JSAPIAuto::registerEvent
///////////////////////////////////////////////////////////////////////////////
BoomstickAPI::BoomstickAPI(const BoomstickPtr& plugin, const FB::BrowserHostPtr& host) : m_plugin(plugin), m_host(host)
{
    registerMethod("echo", make_method(this,
      &BoomstickAPI::echo
    ));
    registerMethod("testEvent", make_method(this,
      &BoomstickAPI::testEvent
    ));

    // Read-write property
    registerProperty("testString", make_property(this,
      &BoomstickAPI::get_testString,
      &BoomstickAPI::set_testString
    ));

    // Read-write property
    registerProperty("maxAxes", make_property(this,
      &BoomstickAPI::get_maxAxes,
      &BoomstickAPI::set_maxAxes
    ));

    // Read-only property
    registerProperty("version", make_property(this,
      &BoomstickAPI::get_version
    ));

    registerProperty("status", make_property(this,
      &BoomstickAPI::get_status
    ));

    registerProperty("joysticks", make_property(this,
      &BoomstickAPI::get_joysticks
    ));

    registerMethod("joysticksJSON", make_method(this,
      &BoomstickAPI::joysticksJSON
    ));

    maxAxes = 6;

    m_joysticksHandler = new JoysticksHandler();
    m_joysticksHandler->initialize();
}

///////////////////////////////////////////////////////////////////////////////
/// @fn BoomstickAPI::~BoomstickAPI()
///
/// @brief  Destructor.  Remember that this object will not be released until
///         the browser is done with it; this will almost definitely be after
///         the plugin is released.
///////////////////////////////////////////////////////////////////////////////
BoomstickAPI::~BoomstickAPI()
{
  if(m_joysticksHandler) {
    delete m_joysticksHandler;
  }
}

///////////////////////////////////////////////////////////////////////////////
/// @fn BoomstickPtr BoomstickAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
BoomstickPtr BoomstickAPI::getPlugin()
{
    BoomstickPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}



// Read/Write property testString
std::string BoomstickAPI::get_testString()
{
    return m_testString;
}
void BoomstickAPI::set_testString(const std::string& val)
{
    m_testString = val;
}

int BoomstickAPI::get_maxAxes()
{
    return maxAxes;
}
void BoomstickAPI::set_maxAxes(const int val)
{
    maxAxes = val;
}

// Read-only property version
std::string BoomstickAPI::get_version()
{
    return "CURRENT_VERSION";
}

std::string BoomstickAPI::get_status()
{
  if(m_joysticksHandler) {
    return m_joysticksHandler->status;
  } else {
    return "No handler!";
  }
}

// Method echo
FB::variant BoomstickAPI::echo(const FB::variant& msg)
{
    static int n(0);
    fire_echo(msg, n++);
    return msg;
}

void BoomstickAPI::testEvent(const FB::variant& var)
{
    fire_fired(var, true, 1);
}

FB::VariantList BoomstickAPI::get_joysticks()
{
    FB::VariantList result;

    if (m_joysticksHandler) {
      m_joysticksHandler->capture();

      std::vector<JoyStickState> states = m_joysticksHandler->joyStickStates();

      int size = states.size();
      for(unsigned int i = 0; i < size; i++) {
        JoyStickState joystick = states[i];

        FB::VariantMap jsJoystickData;

        FB::VariantList jsJoystickAxes;
        int numAxes = joystick.mAxes.size();
        if(numAxes > maxAxes) {
          numAxes = maxAxes;
        }

        for(unsigned int axis = 0; axis < numAxes; axis++) {
          jsJoystickAxes.push_back(joystick.mAxes[axis].abs);
        }

        int jsJoystickButtons = 0;
        int buttonBit = 1;

        int numButtons = joystick.mButtons.size();
        for(unsigned int button = 0; button < numButtons; button++) {
          jsJoystickButtons += joystick.mButtons[button] * buttonBit;
          buttonBit = buttonBit << 1;
        }

        jsJoystickData.insert(std::make_pair( std::string("axes"),  jsJoystickAxes));
        jsJoystickData.insert(std::make_pair( std::string("buttons"),  jsJoystickButtons));

        result.push_back(jsJoystickData);
      }
    }

    return result;
}

std::string BoomstickAPI::joysticksJSON()
{
    Json::Value result(Json::arrayValue);

    if (m_joysticksHandler) {
      m_joysticksHandler->capture();

      std::vector<JoyStickState> states = m_joysticksHandler->joyStickStates();

      int size = states.size();
      for(unsigned int i = 0; i < size; i++) {
        JoyStickState joystick = states[i];

        Json::Value jsJoystickData(Json::objectValue);

        Json::Value jsJoystickAxes(Json::arrayValue);
        int numAxes = joystick.mAxes.size();
        if(numAxes > maxAxes) {
          numAxes = maxAxes;
        }

        for(unsigned int axis = 0; axis < numAxes; axis++) {
          jsJoystickAxes.append(joystick.mAxes[axis].abs);
        }

        int jsJoystickButtons = 0;
        int buttonBit = 1;

        int numButtons = joystick.mButtons.size();
        for(unsigned int button = 0; button < numButtons; button++) {
          jsJoystickButtons += joystick.mButtons[button] * buttonBit;
          buttonBit = buttonBit << 1;
        }

        jsJoystickData["axes"] = jsJoystickAxes;
        jsJoystickData["buttons"] = jsJoystickButtons;

        result.append(jsJoystickData);
      }
    }

    Json::FastWriter writer;
    return writer.write( result );
}
