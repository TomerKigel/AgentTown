<h1>Agent town</h1>

<h2>The project</h2>
The project is an attempt to create a modular network supporting distributed constraint optimization problems research and development.

<h2>The Idea</h2>
The world of computer science has gone through many iterations in the past. First Computers were big and expensive thus computing was centralized,
and it was done mainly in universities and large corporations.
After that, a new era of personal computers has begun as computers became cheaper and more viable. Then the birth of the Internet gave rise to 
centralized servers. Finally, we arrive at today to the age of microservices and distributed computing. 
The fluctuation between centralized and distributed computing never stops. Each new iteration brings new challenges and advantages.

---

In this project, the focus is to create an infrastructure for solving distributed constraint optimization problems(DCOPs). 
Both for research and for the development of a real-world application for that type of computation.
More on the subject of DCOPs can be found on this [wikipedia page](https://en.wikipedia.org/wiki/Distributed_constraint_optimization)

<h3>DSA</h3>
To demonstrate the problems this project aims to solve and one approach to solving them I've decided to record the following introduction
that focuses on an algorithm called: 'Distributed stochastic algorithm' or DSA.

In the video below I am explaining DSA and concepts in distributed calculation.

Youtube:

[![DSA](https://img.youtube.com/vi/8pCxg9HOu_M/0.jpg)](https://www.youtube.com/watch?v=8pCxg9HOu_M)

github:

https://user-images.githubusercontent.com/88850793/233045187-52e70f97-3c1a-41af-b4f4-a588574fec66.mp4


<h2>The goal</h2>

The goal is to create a central server that can be set up to monitor traffic within the network, collect data, display progress, and simulate an environment 
that is as close to a real-life environment as possible.

Simultaneously, clients simulating a single or a collection of agents operating independently must be implemented to allow them to run algorithms that can solve DCOPs.

Ideally in the future, virtual and simulated should become physical and real.

<h2>How to</h2>

To compile and run the project few things are required:

Download and install Boost library. An explanation can be found here: [tutorial](https://www.boost.org/doc/libs/1_82_0/more/getting_started/windows.html)

(mandatory for CAI project) Download SFML <b>64x(not 32bits!)</b>
version 2.5.1 or newer. link: [download](https://www.sfml-dev.org/download/sfml/2.5.1/) 


<h3>On Windows</h3>
all settings are already set up properly in the .vcxproj files accordingly. After cloning You only need to add the path to the sfml and boost
directories you have installed.

The project was developed in Visual Studio 2019 and uses toolset v142 but should work fine with any newer toolset.
If you are trying to build on a newer version of Visual Studio (2022 or higher) you should change the toolset from v142 to the new toolset(v143 or higher).

In the 

```
Project settings -> C/C++ -> General -> Additional Include Directories
```

you should add the include paths that look like: 

```
C:\Program Files\boost\boost_1_81_0\;
I:\SFML-2.5.1\Include
```

In the 

```
Project settings -> Linker -> General -> Additional Library Directories
```

you should add the lib paths that look like: 

```
C:\Program Files\boost\boost_1_81_0\stage\lib;
I:\SFML-2.5.1\lib
```

For more information about the installation and setup, you can check SFML and BOOST official websites.

<h3>On Linux(Ubuntu)</h3>
all settings are already set up properly in the CMakeLists.txt files in each project. After cloning You only need to change the paths to boost and sfml
in each CMakelists.txt in each project as you can see below:

```
set(BOOST_ROOT "/home/runner/work/AgentTown/boost")
set(SFML_DIR "$ENV{GITHUB_WORKSPACE}/sfml_install/usr/local/lib/cmake/SFML")
```

You can then open the terminal and make a build directory inside the AgentTown directory, build, and run from it:

```
mkdir build
cd build
cmake ..
make
./Framework_exe
```

building with cmake requires building with g++11 as this project uses the c++20 standard.
verify your system is up to date.

here is a tutorial as to how to update gcc to allow use of cpp20 if it isn't g++11 or higher:
[g++11](https://www.cyberithub.com/how-to-update-or-upgrade-gcc-to-latest-version-on-ubuntu-debian/)

<h2>Stay in touch</h2>

•[Tomer Kigel](https://www.linkedin.com/in/tomer-kigel/ "Tomer Kigel") on Linkedin

•[Tomer Kigel](https://www.facebook.com/suminona.a) on Facebook
