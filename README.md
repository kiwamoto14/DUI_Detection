# DUI_Detection
Real-time DUI Detection program through camera using facial landmark feature from OpenCV Library. Computers eye aspect ratio to detect potential DUI.

# Usage
Download OpenCV and OpenCV_contrib from OpenCV's Github and extract onto a directory in any chosen directory (NOT program files)
Download Cmake
Create a build directory in your directory with the OpenCV files downloaded in it
Open Cmake and select base OpenCV file as your source code and the build directory as the target directory for binary
Click Configure and select Visual Studio 2019 
Scroll to OpenCV_Extra_Modules_Path and add opencv_contrib\modules to the path and configure again
After it finishes, check that there are no red lines and click generate
Go to the build directory and open OpenCV.sln in Visual Studio
Build the solutions for both debug and release
Build the "INSTALL" files in the CMakeTargets folder
Add the build\install\x64\vc16\bin directory to system path in environment variables
Open the solution file on Visual Studio, go to Properties of the solution, and set the configuration to All Configurations and the platform to your platform (x64 for me)
Go to VC++ directories under Configuration Properties and add OpenCV\build\install\include to include directories
Go to Library Directories under Configuration Properties and add OpenCV\build\install\x64\vc16\lib to the path
Refer to Linker Input Direction Section below
Open the debugLibs.txt text file that is now created in your ...x64\vc16\lib directory with VS Code and delete all text that isn't lib or dlib files
Hit Alt+Shift+I and Home to bring cursor for all rows to beginning of the row. Shift the cursor to the beginning of the second column and hit Enter
All the files should now be in one column. Copy all of the names of the files and go back to Visual Studio. Change configuration to Debug and paste it in the Additional Dependencies Section.
Go back to the debugLibs.txt file in VSCode and use the find and replace feature to change all d.lib to simply .lib. 
Copy all of the names of the files, go to Visual Studio, change configuration to Release, and paste it in the Additional Dependencies Section.
Apply all of the changes and you should now be able to use OpenCV. (Make sure the configuration is x64 when compiling)



#Linker Input Direction Section
Open command prompt and follow directions below
```cmd
cd \
cd OpenCV\build\install\x64\vc16\lib
dir /w *d.lib > debugLibs.txt
```
