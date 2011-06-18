/**********************************************************\

  Auto-generated Xbox360ControllerJavaScriptSupportAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"

#include "Xbox360ControllerJavaScriptSupportAPI.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn Xbox360ControllerJavaScriptSupportAPI::Xbox360ControllerJavaScriptSupportAPI(const Xbox360ControllerJavaScriptSupportPtr& plugin, const FB::BrowserHostPtr host)
///
/// @brief  Constructor for your JSAPI object.  You should register your methods, properties, and events
///         that should be accessible to Javascript from here.
///
/// @see FB::JSAPIAuto::registerMethod
/// @see FB::JSAPIAuto::registerProperty
/// @see FB::JSAPIAuto::registerEvent
///////////////////////////////////////////////////////////////////////////////
Xbox360ControllerJavaScriptSupportAPI::Xbox360ControllerJavaScriptSupportAPI(const Xbox360ControllerJavaScriptSupportPtr& plugin, const FB::BrowserHostPtr& host) : m_plugin(plugin), m_host(host)
{
    registerMethod("echo",      make_method(this, &Xbox360ControllerJavaScriptSupportAPI::echo));
    registerMethod("testEvent", make_method(this, &Xbox360ControllerJavaScriptSupportAPI::testEvent));

    // Read-write property
    registerProperty("testString", make_property(this,
      &Xbox360ControllerJavaScriptSupportAPI::get_testString,
      &Xbox360ControllerJavaScriptSupportAPI::set_testString
    ));

    // Read-only property
    registerProperty("version", make_property(this,
      &Xbox360ControllerJavaScriptSupportAPI::get_version
    ));

    registerProperty("status", make_property(this,
      &Xbox360ControllerJavaScriptSupportAPI::get_status
    ));

    registerProperty("joysticks", make_property(this,
      &Xbox360ControllerJavaScriptSupportAPI::get_joysticks
    ));

    m_joysticksHandler = new JoysticksHandler();
    m_joysticksHandler->initialize();
}

///////////////////////////////////////////////////////////////////////////////
/// @fn Xbox360ControllerJavaScriptSupportAPI::~Xbox360ControllerJavaScriptSupportAPI()
///
/// @brief  Destructor.  Remember that this object will not be released until
///         the browser is done with it; this will almost definitely be after
///         the plugin is released.
///////////////////////////////////////////////////////////////////////////////
Xbox360ControllerJavaScriptSupportAPI::~Xbox360ControllerJavaScriptSupportAPI()
{
  if(m_joysticksHandler) {
    delete m_joysticksHandler;
  }
}

///////////////////////////////////////////////////////////////////////////////
/// @fn Xbox360ControllerJavaScriptSupportPtr Xbox360ControllerJavaScriptSupportAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
Xbox360ControllerJavaScriptSupportPtr Xbox360ControllerJavaScriptSupportAPI::getPlugin()
{
    Xbox360ControllerJavaScriptSupportPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}



// Read/Write property testString
std::string Xbox360ControllerJavaScriptSupportAPI::get_testString()
{
    return m_testString;
}
void Xbox360ControllerJavaScriptSupportAPI::set_testString(const std::string& val)
{
    m_testString = val;
}

// Read-only property version
std::string Xbox360ControllerJavaScriptSupportAPI::get_version()
{
    return "CURRENT_VERSION";
}

std::string Xbox360ControllerJavaScriptSupportAPI::get_status()
{
  if(m_joysticksHandler) {
    return m_joysticksHandler->status;
  } else {
    return "No handler!";
  }
}

// Method echo
FB::variant Xbox360ControllerJavaScriptSupportAPI::echo(const FB::variant& msg)
{
    static int n(0);
    fire_echo(msg, n++);
    return msg;
}

void Xbox360ControllerJavaScriptSupportAPI::testEvent(const FB::variant& var)
{
    fire_fired(var, true, 1);
}

FB::VariantList Xbox360ControllerJavaScriptSupportAPI::get_joysticks()
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
