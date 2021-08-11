# GaugeConnect

This is a mostly trivial stand-alone WASM module for FS2020 which does exactly one thing: allow registering Gauge calculator expressions and invoke them at runtime via SimConnect user events.

This circumvents the issue that the SimConnect API lacks a method by which to access most plane's variables directly (specifically L: variables and H: events) that are often necessary to control much of the planes' avionics.  Also, once Asobo corrects/improves execute_calculator_code() in the SDK so that it can invoke B: input events, this will provide an infinitely better means of remotely controlling cockpit instruments.
