# Kostull
 
Kostull is a C++ project for fast startup of new projects.  

# TODO
- [ ] How to turn this into a nice git submodule
- [ ] Create a UE5 plugin for server interfacing
- [ ] Research plotting libraries

# Content
- [Building](#building)
- [Running](#running)
- [Configuration](#configuration)
- [Modules](#modules)
	- [Networking](#configuration)
	- [Graphics](#graphics)
	- [Core](#core)
    - [Logger](#logger)
- [Third-Party Packages](#third-party-packages)

# Usage
 
main.cpp
```c++
#include <iostream>

#include "Logger.h"
#include "Networking.h"
#include "Graphics.h"


int main(int argc, char** argv) {
	Logger::Initalize(Logger::L_INFO, Logger::L_CONSOLE);
	Networking::Intialize();

	Logger::Info("Welcome To Kostull");

	Graphics graphics;
	graphics.Init("Kostull");

	bool running = true;
	while (running) {
		int result = graphics.Frame();
		if (result == 0) {
			running = false;
		}
	}

	graphics.Shutdown();

	Networking::Shutdown();
	Logger::Shutdown();
	return 0;
}
```

# Building
Cmake must be installed for building the project. 
scripts/generate.bat can automatically build the project with cmake 
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

# Running
```bash
./src/VERSION/Template.exe
```

# Configuration
[CMakeLists.txt](CMakeLists.txt)
`project(YOUR_PROJECT_NAME_HERE)`

[src/Config.h.in](src/Config.h.in)
`#define YOUR_PROJECT_NAME_VERSION_MAJOR @YOUR_PROJECT_NAME_VERSION_MAJOR@`
`#define YOUR_PROJECT_NAME_VERSION_MINOR @YOUR_PROJECT_NAME_VERSION_MINOR@`

# Modules
/deps/...

## Networking
- [ ] IPv6 networking
- [ ] Non-blocking client

Static IPv4 Winsock networking library.  

### Server
```cpp
#include "Server.h"

Server server;
server.Initialize(IPEndpoint("localhost", 8000));
while(true){
    server.Frame();
}
```
### Client

Scripts/tcp_client.py implements a simple client with string-packet parsing and creation. 
```cpp
#include "Client.h"
 Client client;
 client.Connect(IPEndpoint("localhost", 12345));
 while (true) {
     client.Frame();
 }
```

## Graphics
Graphics is a static library utilizing GLFW, GLAD, GLM, and ImGUI.
```cpp
Graphics graphics;
graphics.Init("Template");
while(true){
    server.Render();
}
```

## Logger
Logger is a static library.  
This is a wrapper for [Spdlog](https://github.com/gabime/spdlog). (Use precompiled version)

If no SPDLOG library is found, this is a simple logging library. 
```cpp
#include "Logger.h"
Logger::Initalize(L_INFO, L_CONSOLE)
Logger::RegisterCallback([](const Logger::Log log){ std::cout << log.payload << std::endl;})
Logger::Info("Something happend!");
Logger::Error("An error occured...");
Logger::Shutdown(); //Only necassery when logging to file 
```

# Third-Party Packages

- [Spdlog Logger](https://github.com/gabime/spdlog)

- [NLOHMANN JSON](https://github.com/nlohmann/json)

- [Eigen](https://gitlab.com/libeigen/eigen)

- [GLFW](https://www.glfw.org/)

- [GLM](https://github.com/g-truc/glm)

- [ImGui](https://github.com/ocornut/imgui)

- [GLAD](https://github.com/Dav1dde/glad)

- [GLEW](https://github.com/nigels-com/glew)
