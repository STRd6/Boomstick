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
          0, 32767      
        ],
        buttons: [
          1, 0, 0, 0, 1, 0
        ]
      }, 
      // Joystick 2, etc.
      ...
    ]

