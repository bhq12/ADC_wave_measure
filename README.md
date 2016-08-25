WAVEFORM ANALYSER

This is a simple waveform analysis program implemented using the Stellaris LM3S1968 development board and the FreeRTOS real time operating system. It takes input sine waves on the ADC0 pin and input square waves on the ADC1 pin and displays properties of the waves to the user. The waveform must be in the  0 - 3V range.

To use this project make sure you have the StellarisWare software library installed in "C:/SteallarisWare". 
The project can then be improted into the Code Composer studio IDE for easy compilation/loading onto the device.
Importing the project can be done by clicking  "project -> Import CCS Projects..."

Alternatively, if you have StellarisWare installed in another directory. In Code Composer Studio click:

 project -> properties -> Build -> Arm Compiler -> include options, and edit the StellariWare related paths. Then also edit the StellarisWare include library at:

project -> properties -> Build -> Arm Linker -> File Search Path
