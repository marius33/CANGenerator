# CANGenerator
C code for generating CAN (Controller Area Network) messages to simulate a real situation
This project used an Atmel ATSAM4E16C microcontroller on a custom board.
ASF libraries used:
  IOPORT, USB Device - CDC STDIO (not really needed), CAN - SN65HVD234, AFEC, CAN, TC, WDT.

This is part of the code written for a real car company to use on a bench test. Because of confidentiality, no actual values were used.
However, all the other parts remained as they were, so this can be used as a skeleton for another CAN message generator. 

Will add a script to auto-fill the required CAN messages and signals from a .dbc file.
