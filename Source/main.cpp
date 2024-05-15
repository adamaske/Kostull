#include <iostream>

#include "Logger.h"
#include "Networking.h"
#include "Graphics.h"
#include "Server.h"

int main(int argc, char** argv) {
	Logger::Initalize(Logger::L_INFO, Logger::L_CONSOLE);
	Networking::Intialize();

	Logger::Info("Welcome To Kostull");

	Graphics graphics;
	graphics.Init("Kostull");

	Server server;
	server.Initialize(IPEndpoint("127.0.0.1", 8000));

	bool running = true;
	while (running) {

		server.Frame();

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