Boomstick [Alpha] enables HTML5 and JavaScript games to access native joysticks.

By using FireBreath to handle cross-browser, multi-platform plugin generation
and OIS to handle multi-platform joystick input, Boomstick gives JavaScript
applications total access to joysticks and gamepads.

Works on all platforms.

Windows
[Windows Installer][1]

OS X, Linux
[Chrome Extension][2]
TODO: Firefox Extension


Sample HTML

    <object id="plugin" type="application/x-boomstickjavascriptjoysticksupport" width="0" height="0"></object>

    <script>
      var joysticks = JSON.parse(plugin.joysticksJSON());
    </script>

Calling .joysticksJSON() returns a JSON string containing the current state of all joysticks.

    '[
      {"axes":[0,0,0,0,0],"buttons":0,"pov":0},
      {"axes":[0,0],"buttons":0,"pov":0},
      ...
    ]'
    
    // Read thusly
    joysticks = JSON.parse(plugin.joysticksJSON())

The axes property is an array of all the axes. Usually the order is x, y, of primary stick first, but different drivers and gamepads may report them differently.

    joysticks[0].axes[0] // Returns x axis position in range [-32768, 32767]
    joysticks[0].axes[1] // Returns y axis position in range [-32768, 32767]
    joysticks[0].axes[2] // ... likewise for additional axes

The buttons are returned as a bitfield

    BUTTON_0 = 1
    BUTTON_1 = 2
    BUTTON_2 = 4
    BUTTON_3 = 8
    ...

    // Check the buttons as follows
    joysticks[0].buttons & BUTTON_0 // Button 0 is down
    joysticks[0].buttons & BUTTON_2 // Button 2 is down

All joysticks currently return one POV property regardless of how many POV inputs the physical device actually has. Like the buttons is a bitfield.

       UP =    1
     DOWN =   16
    RIGHT =  256
     LEFT = 4096


[1]: https://github.com/downloads/STRd6/Boomstick/windows_install.zip "Windows Installer"
[2]: https://chrome.google.com/webstore/detail/ibghgpidpbpnhdgmncpbhioaohmgkigo
