#include <iostream>
#include <WinSock2.h>
#include <cstring>
#include <Ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

int main() {
	try {
		WSADATA wsaData;
		int iResult;
		SOCKET clientSocket = INVALID_SOCKET;
		struct sockaddr_in serverAddr;
		char buffer[1024] = { 0 };
		const char* message = "Hello from client";


		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			std::cout << "WSAStartup failed: " << iResult << std::endl;
			return 1;
		}

		// Create a socket for the client
		clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (clientSocket == INVALID_SOCKET) {
			std::cout << "Error creating client socket: " << WSAGetLastError() << std::endl;
			WSACleanup();
			return 1;
		}

		// Connect to the server
		memset(&serverAddr, 0, sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(8080);
		iResult = inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
		if (iResult <= 0) {
			std::cout << "Error converting server IP address: " << WSAGetLastError() << std::endl;
			closesocket(clientSocket);
			WSACleanup();
			return 1;
		}
		iResult = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
		if (iResult == SOCKET_ERROR) {
			std::cout << "Error connecting to server: " << WSAGetLastError() << std::endl;
			closesocket(clientSocket);
			WSACleanup();
			return 1;
		}

		// Send a message to the server
		iResult = send(clientSocket, message, strlen(message), 0);
		if (iResult == SOCKET_ERROR) {
			std::cout << "Error sending data to server: " << WSAGetLastError() << std::endl;
			closesocket(clientSocket);
			WSACleanup();
			return 1;
		}
		std::cout << "Sent message to server" << std::endl;

		// Receive a response from the server
		iResult = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (iResult > 0) {
			std::cout << "Received response from server: " << buffer << std::endl;
		}
		else if (iResult == 0) {
			std::cout << "Server disconnected" << std::endl;
		}
		else {
			std::cout << "Error receiving response from server: " << WSAGetLastError() << std::endl;
			closesocket(clientSocket);
			WSACleanup();
			return 1;
		}

		system("pause");

		// Clean up
		closesocket(clientSocket);
		WSACleanup();
		return 0;
	}
	catch (int myNum) {
		std::cout << "Access denied - You must be at least 18 years old.\n";
		std::cout << "Error number: " << myNum;
		system("pause");
	}
}