Boomstick [Alpha] enables HTML5 and JavaScript games to access native JoySticks.

By using FireBreath to handle cross-browser, multi-platform plugin generation
and OIS to handle multi-platform joystick input, Boomstick gives JavaScript
applications total access to joysticks and gamepads.

Works on all platforms.

Sample HTML

    <object id="plugin" type="application/x-boomstickjavascriptjoysticksupport" width="0" height="0"></object>

    <script>
      var current states = plugin.joysticks;
    </script>

Calling .joysticks returns an array containing the current state of all joysticks.

    [
      // Joystick 1
      {
        axes: [
          0, 32767,
          0, 0
        ],
        buttons: <bitfield>
      }, 
      // Joystick 2, etc.
      ...
    ]

The axes property is an array of all the axes. Usually the order is x, y, of primary stick first, but different drivers and gamepads may report them differently.

    joysticks[0].axes[0] # Returns x axis position in range [-32768, 32767]
    joysticks[0].axes[1] # Returns y axis position in range [-32768, 32767]
    joysticks[0].axes[2]     ... likewise for additional axes

The buttons are returned as a bitfield and I know what you're thinking "Why not an array?" It used to be an array, but crossing the NPAPI/JS barrier is costly, and even with only five 11-button gamepads it adds up fast. Switching to a bitfield was a 25% speed boost and when joystick communication was taking 24%(!) of my games process time at 30fps it was worth it to get it down to the 16-18% range.

    BUTTON_0 = 1
    BUTTON_1 = 2
    BUTTON_2 = 4
    BUTTON_3 = 8
    ...

    # Check the buttons as follows
    joysticks[0].buttons & BUTTON_0 # Button 0 is down
    joysticks[0].buttons & BUTTON_2 # Button 2 is down

