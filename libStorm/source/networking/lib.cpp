#include "networking/deps.hpp"

#ifndef STORM_DISABLE_NETWORKING

#ifdef BUILD_TYPE_WINDOWS

#include <WinSock2.h>
#include <ws2tcpip.h>

#endif

#include <stdexcept>

using namespace Storm;

void Networking::init_subsystem()
{
#ifdef BUILD_TYPE_WINDOWS
	static WSADATA wsaData;

	// Start up and check if our winsocket is working.
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		throw std::runtime_error("Could not initialize find WinSocket 2.2!");

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		end_subsystem();
		throw std::runtime_error("Could not find WinSocket 2.2!");
	}
#endif
}

void Networking::end_subsystem()
{
#ifdef BUILD_TYPE_WINDOWS
	// Close this mess.
	WSACleanup();
#endif
}

#endif