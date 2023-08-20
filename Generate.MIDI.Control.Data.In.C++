GPT-4

User:

On a Windows x86 64 bit platform I want to develop a C++ application which generates MIDI control data to send to an application listening for MIDI control data. Should I register my application as a MIDI IN or a MIDI OUT application in order to generate and send this data?

ChatGPT:

If you want your C++ application to generate MIDI control data and send it to another application, you should register your application as a MIDI OUT application. Here's the breakdown:

    MIDI OUT: This refers to applications or devices that produce or send MIDI data. If you're generating MIDI control data, your application is a source of MIDI data, so it should be registered as a MIDI OUT.

    MIDI IN: This refers to applications or devices that receive or listen for MIDI data. The application that you want to send the data to (i.e., the one that is listening for the data) should be registered as a MIDI IN.

So in summary, your C++ application should be registered as a MIDI OUT application, and the target application should be registered as a MIDI IN application.
