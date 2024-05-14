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