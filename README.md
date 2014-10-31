Hand 2D Ground Truth viewer
=================

A tool to view the data set and the ground truth created for the project "Capturing Hands in Action using Discriminative Salient Points and Physics Simulation" Dimitrios Tzionas, Luca Ballan, Abhilash Srikantha, Pablo Aponte, Aparna Taneja, Marc Pollefeys and Juergen Gall. The datasets can be obtained freely in the project page http://files.is.tue.mpg.de/dtzionas/Hand-Object-Capture/ 


Dependencies
=================

Opencv and QT 4 and CMake

Build
=================

    mkdir build
    cd build
    cmake ..
    make

Run
=================

    cd bin
    ./viewer

In the gui window, click in the browse button and select the base folder of the dataset. For example: for dataset 313 you will have to select the subfolder in called "1" that has the folders "rgb", "rgb", etc. below it.
