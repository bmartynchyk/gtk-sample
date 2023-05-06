# gtk-sample
## What environment
Guide for following setup:
* Oracle VM VirtualBox Ubuntu 18.04.6
* IDE NetBeans
* Libs: Magick++, GTK+

## Tips
- You can setup drag-drop feature and any other tools you wanted  by your own need. Skip stages in instalation guide that you an't gona need it.
- Note you also need a 'pkg-config' installed.

## Setup gide
### Stage 1: Updloading libraries and compilator
* You need to update use following termanal comands:
```
$ sudo apt-get update
$ sudo apt-get upgrade
```
* Upload libraries. First command installs compilator next command - used ligraries:
```
$ sudo apt-get install build-essential
$ sudo apt-get install libgtk-3-dev g++ 
$ sudo apt-get install libmagick++-dev
```

### Stage 2: Installing IDE NetBeans
To install NetBeans first of all you need to install JDK:
```
$ sudo apt-get install default-jdk
```

To instal NetBeans I use 'snap'. You will get last stable version with following command:
```
$ sudo snap install netbeans --classic
```
### Stage 3: Installing IDE NetBeans
Instalation of base kit of NetBeans(to have possibility work with C/C++ you need to install plugins): 
```
$ sudo snap install netbeans --classic
```

### Stage 3: Cloning repo
 Choose folder for git repo.
 Clone git repo:
```
$ git clone https://<link to git repo>
```

### Stage 4: Setuping IDE, run the project

#### 1. You need to instal plugins for C/C++. Here you can follow this guide: 
https://www.youtube.com/watch?v=ZA1iRNznGug&feature=youtu.be 
#### 2. In repo I prepared several image and watermark samples. To get it ready to use goto root directory of project and unzip file samples.tar.gz. Type following comand:
```
$ tar -xzvf pic-samples.tar.gz
```
#### 3. Open repo as a project in NetBeans "File"->"Open Project..." find the roor directory and select it.
#### 4. Configure compilator options: 
Select "Project Poperties", in tab "C++ Compilator" -> "Additional options" set following options (single quotes in parameters are important):
```
`pkg-config --cflags gtk+-3.0` -std=c++11 `Magick++-config --cxxflags --cppflags`
```
In option "Include Directories" you need point path to libraries. In my case I have following paths:
```
/usr/include/Magick++ 
/usr/include/ImageMagick-6/ 
```
And in option "Include Headers":
```
/usr/include/Magick++/Include.h 
```
To find and add required libs you can use: 
```
$ cd :/
$ find . -name lib-name
```

 In tab "Linker" -> "Additional options" set following options (single quotes in parameters are important):
 ```
 `pkg-config --libs gtk+-3.0` `Magick++-config --ldflags --libs`
 ```

## How to use
The application is simple. It consist of 5 buttons. Each of the first three buttons represents process of uploading, processing and saving processed image. I advice to use button "Load image to view" to check up processing results instantly in application.

![image](https://user-images.githubusercontent.com/40026486/236624589-2dc0b8a5-0cc2-4834-bb98-7675a175bdbb.png)

The operations hardcoded to simplify input process. The coveting watermark also hardcoded. And you can change the watermark by replacing file: gtk-master/pic-samples/watermark.png. Each watermark normalized into size of 200x100, so you can apload picture with any size.

## Class diagram
