# simpanel
Flight Simulator autopilot and general switch panel (intended, at the moment, for FS2020 but would likely work with most/all other flight simulators with a bit of tweaking).

This is very much work-in-progress; it works, but the build process for the components requires manual steps and programming. With no driver software, the device is a functioning HID providing 37 buttons and two linear encoders exposed as relative dials and as up/down extra buttons (for increase and decrease); those should be usable as-is in well-written software.

The leds and numeric displays are controlled by HID output reports; there is a Windows application that bridges between that interface and the SimConnect interface provided by modern flight simulators with a major caveat: the SimConnect API is not sufficient by itself to properly control modern autopilot panels completely (and FS2020's implementation of it is even more lacking in particular).

For FS2020, there is a Webasembly module that provides the missing part of the interface to the autopilot panel.  FSX and P3D at least provide comparable interfaces, it should not be overly hard to port the module to suitable DLLs for those simulators.

The hardware is in a decent state and the CADs for the PCBoard are included.  Do note there isn't a proper BOM for assembly right now, you'll have to inventory the schematics for the list of parts.

If you really like the idea and want to fiddle with it, you almost certainly want to drop me an email for help and guidance for now.
