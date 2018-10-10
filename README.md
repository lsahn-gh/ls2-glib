Summary
-------
A GObject based library wrapping luna-service2

Description
-----------
The library wraps luna-service2 with GObject system. It provides Object-Oriented Programming concept for C Programming and manages the instance of LSHandle struct of luna-service2. When Gls2Handle class instantiates by gls2_handle_new method, it initializes LSHandle with service name and LSError automatically. Also, when the instance of Gls2Handle destroys, it finalizes the instance of LSHandle, LSError and any resources initialized by the class.
