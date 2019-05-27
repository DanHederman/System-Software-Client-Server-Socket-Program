# System Software Client Server Socket Program

**Version 1.0.0**

This is the repository for my second assignment from a TUD final year module titled System Software

## Contributers 
- Daniel Hederman <danhederman@gmail.com>

## Licence & Copyright

© Dan Hederman, TUD System Software 2019

## CTO Requirements

* No direct access to the intranet folder for the internal site.
* Multiple users must be able to transfer files at the same time.
* Files transferred must be attrbuted to the transfer user.
* A specific user will have access to either the (Sales/Marketing/Promotions/Offers) folder. All users have access to the root intranet folder.
* If synchronisation is an issue use a C mutex lock for Linux thread synchronisation.

## System Requirements

* Create a Server Socket program to run on the same server as the intranet site.
* Create a client program to connect to the Server Socket program.
* The system must be capable of handling multiple clients and transfers simultaneously.
* Transfer restrictions should be controlled using real and effective ID's functionality.
* The files transferred should be attributed to the transfer user.
* The client must take a filename and path via console and transfer this to the server to be stored (Root/Marketing/Offers/Sales/Promotions).
* The server must inform the client if the transfer was successful or not.

## General Assumptions

* The solution for the problem stated can be developed on a single machine.
* The client will only transfer one file at a time.

## Before Running

This project can be run without making any prior changes to the code. However, code may need to be modified to adhere to a specific file structure.

## How to Run (Linux)

* Download and unzip the code onto the Linux desktop.
* Using a linux terminal, cd into the assignment folder.
* The server can then be started using ./Server.
* Another terminal window can be used to connect a client to the socket server.
* The server will display when a client is successfully connected.
* The client will prompt the user for any necessary input.

## Video Demo

* https://www.youtube.com/watch?v=dj1oerz1f8g&t=2s