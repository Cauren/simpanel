# simpanel
Flight Simulator autopilot and general switch panel.

This is very much work-in-progress; it works, but the build process for the components requires manual steps and programming. The device is a functioning HID providing 37 buttons and four linear encoders exposed as relative dials; those should be usable as-is in well-written software.

The leds and numeric displays are controlled by HID output reports which most flight simulators are unable to use directly, but there are software tools to interface simulator panels with flight simulators that can do the required; in particular SPAD.neXt (https://spadnext.com) has support for the panels and will interface with at least FSX, MSFS2020, X-Plane and Prepar3D.

The hardware is in a decent state and the CADs for the PCBoard are included.  Do note there isn't a proper BOM for assembly right now, you'll have to inventory the schematics for the list of parts.

If you really like the idea and want to fiddle with it, you almost certainly want to drop me an email for help and guidance for now.
