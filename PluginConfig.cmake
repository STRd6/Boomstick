#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for Xbox 360 Controller JavaScript Support
#
#\**********************************************************/

set(PLUGIN_NAME "Xbox360ControllerJavaScriptSupport")
set(PLUGIN_PREFIX "X3CJS")
set(COMPANY_NAME "STRd6")

# ActiveX constants:
set(FBTYPELIB_NAME Xbox360ControllerJavaScriptSupportLib)
set(FBTYPELIB_DESC "Xbox360ControllerJavaScriptSupport 1.0 Type Library")
set(IFBControl_DESC "Xbox360ControllerJavaScriptSupport Control Interface")
set(FBControl_DESC "Xbox360ControllerJavaScriptSupport Control Class")
set(IFBComJavascriptObject_DESC "Xbox360ControllerJavaScriptSupport IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "Xbox360ControllerJavaScriptSupport ComJavascriptObject Class")
set(IFBComEventSource_DESC "Xbox360ControllerJavaScriptSupport IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID fd20b991-df53-58a5-87bd-eea5a37e1c8c)
set(IFBControl_GUID 0462e107-93ea-53e9-9816-a3380cb10fd3)
set(FBControl_GUID 2ae8831a-d3fb-5490-a041-57c4930e48de)
set(IFBComJavascriptObject_GUID 62bd414e-acbb-5f3f-8260-e8a66a4ea4d0)
set(FBComJavascriptObject_GUID e89c707b-9d1b-5201-9784-2125f59c4bbb)
set(IFBComEventSource_GUID b320c6a2-3b97-5d2b-b432-061e7d4c1c51)

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "STRd6.Xbox360ControllerJavaScriptSupport")
set(MOZILLA_PLUGINID "strd6.com/Xbox360ControllerJavaScriptSupport")

# strings
set(FBSTRING_CompanyName "STRd6")
set(FBSTRING_FileDescription "Provides support to JavaScript for handling Xbox 360 controllers")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2011 STRd6")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "Xbox 360 Controller JavaScript Support")
set(FBSTRING_FileExtents "")
set(FBSTRING_PluginName "Xbox 360 Controller JavaScript Support")
set(FBSTRING_MIMEType "application/x-xbox360controllerjavascriptsupport")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 0)
set(FBMAC_USE_COCOA 0)
set(FBMAC_USE_COREGRAPHICS 0)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)

add_firebreath_library(log4cplus)
