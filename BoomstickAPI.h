#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "Boomstick.h"
#include "Joysticks.h"

#ifndef H_BoomstickAPI
#define H_BoomstickAPI

class BoomstickAPI : public FB::JSAPIAuto
{
public:
    BoomstickAPI(const BoomstickPtr& plugin, const FB::BrowserHostPtr& host);
    virtual ~BoomstickAPI();

    BoomstickPtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    int get_maxAxes();
    void set_maxAxes(const int val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    std::string get_status();

    FB::VariantList get_joysticks();
    std::string joysticksJSON();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    
    // Event helpers
    FB_JSAPI_EVENT(fired, 3, (const FB::variant&, bool, int));
    FB_JSAPI_EVENT(echo, 2, (const FB::variant&, const int));
    FB_JSAPI_EVENT(notify, 0, ());

    // Method test-event
    void testEvent(const FB::variant& s);

private:
    BoomstickWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;private:
    JoysticksHandler *m_joysticksHandler;
    int maxAxes;
};

#endif // H_BoomstickAPI

