Summary:
1.Build a differential drive robot using the model editor tool in gazebo
2.using building editor tool in gazebo, built a single floor wall structure and applied texture, color and feature to the structure
3.from online libaray imported a models like oak tree,book shelf.
4.Wrote a C++ World Plugin to interact with my world. which display “Welcome to my World” message as soon as lauching world file.

Folder content:
Assignment_1:
* model : This folder contains model files (differential drive robot and structure)
    * robo : floder contains differential drive robot files
        * model config
        * model.sdf
     * my_building: floder contains single floor wall structure files
        * model.config
        * model.sdf
* script: Contains plugin file
    * welcome_message.cc
* world: contains world file which includes model files to import robot and structure at an instance 
    * my_world.world
* CmakeLists.txt: File to link the C++ code to libraries and build it.
* build.sh :To build the plugin in the build directory
* run.sh : To run the gzserver in verbose mode to diplay message given in plugin

 Building the project

    Give executable permission by using chmod 777 build.sh
    Run the build.sh(./build.sh) file to build the plugin in the build directory

To Run the demo

    Give executable permission by using the command chmod 777 run.sh
    After building the plugin run the run.sh file(./run.sh). This will run the gserver in verbose mode so that the message can be seen
    open another terminal and type gzclient to open gazebo.
