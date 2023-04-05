# Win32API_SC_Functions
This code contains 8 C++ scripts used to imitate sc.exe functions. It utilizes various Win32 API functions to complete the same commands as the service controller. The functions include: Create Service, Start Service, Query Service Status, Stop Service, Query Description of Service, Change config (Start Type), and Delete Service.

# Introduction
The goal of this project was to return equivalent results as the sc.exe binary. The files do not cover every specific command that can be run by sc.exe, but it contains many of the most used queries/command. Users will be able to query and manipulate the way some Windows Services are run. All of these files are written in C++ and utilize Win32 API funciton calls to make the requests work.

# Features & Usage
There are 8 unique C++ scripts ready for compilation. If you are using Visual Studio, please make sure you are running in ADMIN mode, failure to do so will result in a majority of these scripts failing. 
The same if you are using VSCode, please use ADMIN mode. If you need assistance compiling the code directly in VSCode, I recommend following the instructions here: https://www.freecodecamp.org/news/how-to-compile-your-c-code-in-visual-studio-code/. This utilizes the MinGW compiler and has direct links to download for any OS. The proper commands are listed in order for everything to be compiled cleanly within VSCodes built-in terminal. 

A description of functionallity for each file is shown below:

1) config.cpp: Permanently changes the Start Type configuration of the service. The start type determines how the service will start when the machine is booted. The script gives you 3 options: 2=Automatic (starts at system startup), 3=Manual (starts when you tell it to), and 4=Disabled (Disables the service). The reason the numbers start at 2 for clarity, as the registry values for StartType reflect this. 

2) create.cpp: creates a service that you determine the name of. That service is placed in the C:\ directory by default. If you wish to change the directory, just open the file in your preferred editor and re-compile. 

3) delete.cpp: Deletes a service that you determine by name. 

4) failureActions.cpp: Changes the actions taken by a service at failure. You will be prompted with 3 actions: 1=Restart the service, 2=Run a command (If you wish to use this option, you must edit the code to specify the path to the command you would like to run and re-compile), and 3=Reboot the computer.

5) qdescription.cpp: Prompts you for the name of the service you would like the description of and returns that description.

6) start.cpp: Prompts you for a service name, then starts that service.

7) status.cpp: Gets the current status of a service, determined by your input.

8) stop.cpp: Prompts you for a service name, then stops that service.

