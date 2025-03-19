# README #

### What is this repository for? ###

* Quick summary
	This repository contains the client side of the implementation of a Odroid used to receive images sent from the server. The client then
	saves the picture and sends data if it detects a QR code.

* Version
	v1.0.0
* [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)

### How do I get set up? ###

* Summary of set up
	The client side receives iamges from the server over a socket connection
	
* Configuration
	1. Clone the repository : git clone git@bitbucket.org:JayPilon/g3-vlsi407-poste.git
	2. Configure the build environement using CMAKE/CMAKELISTS
	
* Dependencies
	OpenCV v3.4.6 for the client
	ZBar for QR code detection
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