# Video Processing Platform

## Introduction
This project offers a simple video processing platform which allow you to perform algorithms on video or image sequence. The project offers a simple demo
which can read from video or image sequence, play the video, fast forward the video and draw boxes on image.

## Requierment
OpenCV(>3.0) To use CMake build system, OpenCV root should be added to $PATH

## Usage
```Shell
VideoProcessingPlatform -v(-l) video(image list) <Command> 
Command:
    -v --video | Get samples from video
    -l --list  | Get samples from image sequence
    -q --quiet | Silent Mode(No Image Show)
    -h --help  | Get Help
```

### Example:

#### Use an video as input
```Shell
    VideoProcessingPlatform -v a.avi
```

#### Use image sequence as input
```Shell
    VideoProcessingPlatform -l seq.txt
```

In seq.txt
```
/path/to/image/0001.jpg
/path/to/image/0002.jpg
/path/to/image/0003.jpg
...
```

## Compilation

### Windows:
Use Cmake-gui to generate Visual Studio Project
1. Create new folder 'build'
2. Open CMake-gui
3. Set source code ${VideoProcessingPlatform}
4. Set Destination ${VideoProcessingPlatform}/build
5. Press Config and set the platform
6. Press Generate
7. Open ${VideoProcessingPlatform}/build/VideoProcessingPlatform.sln
8. Build ALL

### Linux
To be Tested in Linux.

## Others

- Author: Jin Li

