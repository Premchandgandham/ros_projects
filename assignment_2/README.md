Summary:
1.It includes two packages drive_bot and ball_chaser to chase white ball 
1.build a drive_bot package in workspace, which holds robot model in urdf format,model folder for building and ball model,world file and launch file
2.build a ball_chaser package in same workspace, which holds src folder for C++ program file, srv folder service definitio and launch file

Folder content: Assignment_2:
  
 drive_bot:
 
    urdf : This folder contains differential robot file in urdf format
       trail_robo.urdf
       
    model : This folder contains model files 
        ball : floder contains differential white ball files
            model config
            model.sdf
            
        my_building: floder contains single floor wall structure files
            model.config
            model.sdf
            
    world: contains world file which includes model files to import robot and structure at an instance
        my_world.world
        
    urdf.rviz : This file is rviz file with pre-defined configuration required for this project
    
    launch : launch folder consists files with .launch extension 
    
      rviz.launch : launch only robot model with pre-defined configuartion
      
      gazebo_urdf.launch : launch whole world with robo,building,ball and also simultaneous launch rviz
      
    CmakeLists.txt: File to link the C++ code to libraries and build it.
    
    package.xml : to build dependencies
    
    run.sh : To run to models in gazebo
