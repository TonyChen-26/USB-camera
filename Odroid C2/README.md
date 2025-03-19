# README #

### What is this repository for? ###

* Quick summary
    This repository contains the code for the Odroid-C2.The rôle of the Odroid is to act as a server for the client used to exchange data between them. The webcam which is connected tothe Odroid, is used to take pictures that are then sent to the client. If the client detects a QR code in the image, it decodesthe data and sends it back to the server with its content filtered. The filtered text is then transformed into a morse code, thatwould then be played using the buzzer on the PCB of the odroid.

* Version
	v1.0.0
* [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)

### How do I get set up? ###

* Summary of set up
	The server receives the QR code data and plays it on the buzzer
	
* Configuration
	1. Clone the repository : git clone git@bitbucket.org:JayPilon/g3-vlsi407-odroid.git
	2. Configure the build environement using CMAKE/CMAKELISTS
	
* Dependencies
	OpenCV v3.1.0 for the server
	CMAKE v2.8.12 for build configuration

* How to run tests
	1. Compile the source files using CMAKE
	2. F5 to run the program

* Deployment instructions
	1. Deploy the server program on the Odroid using cross compilation
	2. Wait for the client to connect to the server

### Contribution guidelines ###

* Writing tests
	Use system outputs for verifying connection and data transfers between the client and the server
* Code review
	Submit code via feature branches and create pull requests
	Follow the coding standards
* Other guidelines
	Commit with descriptive messages
	Document headers using Doxygen

### Who do I talk to? ###

* Repo owner or admin
	Tony Chen (tony.chen@polymtl.ca)
	Zacharie El-Hachemi (Zacharie.el-hachemi@polymtl.ca)
* Other community or team contact
	Jérémie Pilon (jeremie.pilon@polymtl.ca)