# 42Barcelona_04_Minitalk
_This project features a communication program with both client and server components. The program's main functionalities are as follows:_

## Server
* The server must be started first, and upon launch, it prints its Process ID (PID).

* It is designed to rapidly receive and display incoming strings from clients.

* The server can receive strings from multiple clients in succession without requiring a restart.

## Client
* The client takes two parameters when invoked:
> _The server's PID (Process ID)._

> _The string to send to the server._


* Once the client sends the specified string, the server promptly prints it.

## Communication Method
* The communication between the client and the server is achieved exclusively through UNIX signals.
  
* This program enables clients to send strings to the server, with the server swiftly processing and displaying the received data.

## Bonus List:
* The server acknowledges every message received by sending back a signal to the client.

* Unicode characters support!

## Compilation
* **To compile the main program, use the following command:**
> _make_

* **To compile the bonus part, use:**
> _make bonus_
   
