/**********************************************************\

  Auto-generated Xbox360ControllerJavaScriptSupportAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "Xbox360ControllerJavaScriptSupport.h"
#include "Joysticks.h"

#ifndef H_Xbox360ControllerJavaScriptSupportAPI
#define H_Xbox360ControllerJavaScriptSupportAPI

class Xbox360ControllerJavaScriptSupportAPI : public FB::JSAPIAuto
{
public:
    Xbox360ControllerJavaScriptSupportAPI(const Xbox360ControllerJavaScriptSupportPtr& plugin, const FB::BrowserHostPtr& host);
    virtual ~Xbox360ControllerJavaScriptSupportAPI();

    Xbox360ControllerJavaScriptSupportPtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    FB::VariantList get_joysticks();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    
    // Event helpers
    FB_JSAPI_EVENT(fired, 3, (const FB::variant&, bool, int));
    FB_JSAPI_EVENT(echo, 2, (const FB::variant&, const int));
    FB_JSAPI_EVENT(notify, 0, ());

    // Method test-event
    void testEvent(const FB::variant& s);

private:
    Xbox360ControllerJavaScriptSupportWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;private:
    JoysticksHandler *m_joysticksHandler;
};

#endif // H_Xbox360ControllerJavaScriptSupportAPI

