#include "Networking.h"

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")

#include <iostream>

#include "Logger.h"

namespace Networking {

bool Intialize()
{
    int err = 0;

    auto* sd = &Logger::log_callback_functions;
    std::cout << "NETWORK : " << sd << "\n";

    WSADATA wsaData;
    err = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (err != 0) {
        Logger::Error("WSA Startup Failed : " + std::to_string(err));
        Shutdown();
        return 0;
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {

        Logger::Error("WSA Found no useable Winsock DLL");
        Shutdown();
        return 0;
    }

    return 1;
}

void Shutdown()
{
    WSACleanup();
}

}
