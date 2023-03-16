#include <iostream>
#include <WinSock2.h>
#include <cstring>
#include <thread>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

void handleClient(SOCKET clientSocket) {
	char buffer[1024] = { 0 };
	int iResult;

	// Receive data from the client
	iResult = recv(clientSocket, buffer, sizeof(buffer), 0);
	if (iResult > 0) {
		std::cout << "Received message from client: " << buffer << std::endl;

		// Echo the message back to the client
		iResult = send(clientSocket, buffer, iResult, 0);
		if (iResult == SOCKET_ERROR) {
			std::cout << "Error sending data to client: " << WSAGetLastError() << std::endl;
		}
	}
	else if (iResult == 0) {
		std::cout << "Client disconnected" << std::endl;
	}
	else {
		std::cout << "Error receiving data from client: " << WSAGetLastError() << std::endl;
	}

	// Clean up
	closesocket(clientSocket);
}

int main() {
	WSADATA wsaData;
	int iResult;
	SOCKET listenSocket = INVALID_SOCKET;
	std::vector<SOCKET> clientSockets;
	struct sockaddr_in serverAddr, clientAddr;
	int clientAddrLen = sizeof(clientAddr);

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cout << "WSAStartup failed: " << iResult << std::endl;
		return 1;
	}

	// Create a socket for the server to listen for incoming connections
	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET) {
		std::cout << "Error creating listen socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}

	// Bind the socket to a specific IP address and port
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	iResult = bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if (iResult == SOCKET_ERROR) {
		std::cout << "Error binding listen socket: " << WSAGetLastError() << std::endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	// Start listening for incoming connections
	iResult = listen(listenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		std::cout << "Error listening for incoming connections: " << WSAGetLastError() << std::endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}
	std::cout << "Server listening on port 8080" << std::endl;

	// Handle incoming connections in a loop
	while (true) {
		// Accept a new client connection
		SOCKET clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
		if (clientSocket == INVALID_SOCKET) {
			std::cout << "Error accepting incoming connection : " << WSAGetLastError() << std::endl;
			continue;
		}
		else {
			std::cout << "Accepted new client connection" << std::endl;
		}

		// Create a new thread to handle the client
		std::thread clientThread(handleClient, clientSocket);
		clientThread.detach();

		// Add the client socket to the vector of client sockets
		clientSockets.push_back(clientSocket);
	}

	// Clean up
	for (SOCKET clientSocket : clientSockets) {
		closesocket(clientSocket);
	}
	closesocket(listenSocket);
	WSACleanup();
	return 0;
}