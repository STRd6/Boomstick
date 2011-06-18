#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"

#include "BoomstickAPI.h"

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
    registerMethod("echo",      make_method(this, &BoomstickAPI::echo));
    registerMethod("testEvent", make_method(this, &BoomstickAPI::testEvent));

    // Read-write property
    registerProperty("testString", make_property(this,
      &BoomstickAPI::get_testString,
      &BoomstickAPI::set_testString
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

      for(int i = 0; i < states.size(); i++) {
        JoyStickState joystick = states[i];

        // FB::VariantMap jsJoystickData;

        FB::VariantList jsJoystickAxes;
        for(int axis = 0; axis < joystick.mAxes.size(); axis++) {
          jsJoystickAxes.push_back(joystick.mAxes[axis].abs);
        }

        FB::VariantList jsJoystickButtons;
        for(int button = 0; button < joystick.mButtons.size(); button++) {
          jsJoystickButtons.push_back(joystick.mButtons[button]);
        }

        result.push_back(jsJoystickAxes);
        result.push_back(jsJoystickButtons);
      }
    }

    return result;
}
