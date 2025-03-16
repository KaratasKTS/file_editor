# Image Converter & File Editor Tool

A C++/Qt desktop application designed to streamline image conversion (primarily to WebP) and automate text replacement in HTML files. Built to enhance productivity by eliminating reliance on slow online tools and manual file editing.

"This is a tool that i made for my job, its not fully featured 
or anything like that it just does what i want it to do, change image extentions in html files,
and convert image types"

## Features

- **Image Format Conversion**
  - Convert images between various formats (JPEG, PNG, BMP, WebP, PDF, TIFF,etc.)
  - Optimized for bulk conversion to WebP for web development workflows

- **HTML File Editor**
  - Find and replace text patterns in HTML files (e.g., update image extensions)
  - Simple interface for quick batch operations
    (complex file formats that include xml are not supported)

- WARNING
    YOUR EXPORT DIRECTORY SHOULD BE SET TO 
    A DIFFERENT FOLDER THAN THE INPUT FILE FOR THE PROGRAM TO WORK PROPERLY!
## Prerequisites

- C++17 compatible compiler
- Qt 6 (Core, Gui, Widgets)
- OpenCV 4.x (with imgcodecs  anc core module)
- CMake 3.16+

##  Installation

### Prebuilt Binaries (Recommended)
Just run the installer and it will create a 
short cut in your Desktop, the app is for windows only 

### Build From Source
You'll need to install qt and opencv
open the CMakeList.txt and add your qt and opencv 
installation paths and just run cmake (ninja recommended) on the 
build folder and then run --build on it 

dlls to include in the root folder: 

OpenCV dlls:
Core 
imgcodecs
imgproc

For the QT dlls:
Use the qt tool windeployqt6.exe, 
pass the builds root as an argument and 
windeploy will do the rest for you 