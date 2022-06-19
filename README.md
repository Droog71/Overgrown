Overgrown
===============

Overgrown is a real time strategy game in which your enemy is a mold-like organic substance.<br />
Inspired by Creeper World and FortressCraft Evolved.<br />
Overgrown is a free, open source game developed using C++ and SFML.<br />
The code is licensed AGPL-3.0 and the artwork and sound effects are licensed CC BY 3.0.<br />

<img src="https://i.imgur.com/or7svzt.png" alt="Overgrown" width="427" height="240">

**Playing the Game** <br />

Clone this repository and run the executable in the<br />
'OverGrown_Windows', 'OverGrown_Linux' or 'OverGrown_Mac' directory<br />

To run the game in a window, use the command line argument '-window' <br />
ie: './Overgrown -window 1280 720' <br />
The window cannot be smaller than 1280x720 <br />

Click the 'NEW GAME' or 'TUTORIAL' button at the main menu <br />

Key bindings can be reassigned by editing the bindings.list file in the game directory <br />
All possible key aliases can be found at the following link <br />
https://github.com/Droog71/Overgrown/blob/main/src/key_bindings.cpp

**Compiling from Source** <br />

_Windows:_ <br />

Download SFML and GCC here https://www.sfml-dev.org/download/sfml/2.5.1/ <br />
You will need 'MinGW Builds 7.3.0 (64-bit)' and SFML 'GCC 7.3.0 MinGW (SEH) - 64-bit' <br />
For 32 bit systems you will need 'MinGW Builds 7.3.0 (32-bit)' and 'GCC 7.3.0 MinGW (DW2) - 32-bit' <br />

Clone this repository to C:\ so the source code is present at C:\Overgrown <br />
Extract the downloaded SFML package to C:\ so SFML is present at C:\SFML-2.5.1 <br />
Run the compile_windows.bat script <br />
Run Overgrown.exe to play the game <br />
To run the game in a window, use the command line argument '-window' <br />
ie: 'Overgrown.exe -window 1280 720' <br />
The window cannot be smaller than 1280x720 <br />

_Mac:_ <br />

Clone this repository. <br />
Install g++ as described here http://www.edparrish.net/common/macgpp.php#installg++ <br />
Download SFML here https://www.sfml-dev.org/download/sfml/2.5.1/ <br />
Copy the contents of the SFML Frameworks and extlibs directories to /Library/Frameworks <br />
Run the compile_mac.sh script <br />
Run the Overgrown executable to play the game <br />
To run the game in a window, use the command line argument '-window' <br />
ie: './Overgrown -window 1280 720' <br />
The window cannot be smaller than 1280x720 <br />

_Linux:_ <br />

Clone this repository. <br />
Install SFML, ie: 'sudo apt-get install libsfml-dev' <br />
Run the compile_linux.sh script <br />
Run the Overgrown executable to play the game <br />
To run the game in a window, use the command line argument '-window' <br />
ie: './Overgrown -window 1280 720' <br />
The window cannot be smaller than 1280x720 <br />