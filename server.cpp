#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>     // For close()
#include <netinet/in.h> // For sockaddr_in
#include <arpa/inet.h>  // For inet_addr()
#include "client_handler.cpp"
#include "logger.hpp"

#define PORT 8081
#define MAX_CLIENTS 5

int createServer(Logger *logger)
{
  int serverSocket, clientSocket;
  struct sockaddr_in serverAddr; // ip addresses

  // Create a socket
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == 0)
  {
    logger->error("Socket creation failed!");
    exit(-1);
  }

  return serverSocket;
}

/**
 * Bind the server socket to the specified port
 * @param serverSocket The server socket to bind
 */
void bindServer(int serverSocket, Logger *logger)
{
  struct sockaddr_in serverAddr;

  // Prepare the sockaddr_in structure
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(PORT);

  // Bind the socket
  if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
  {
    logger->error("Bind failed!");
    exit(-1);
  }
}

void listenSocket(int serverSocket, Logger *logger)
{
  // Listen for incoming connections
  if (listen(serverSocket, MAX_CLIENTS) < 0)
  {
    logger->error("Listen failed!");
    exit(-1);
  }
}

int acceptClient(int serverSocket, Logger *logger)
{

  struct sockaddr_in clientAddr;                // ip addresses
  socklen_t clientAddrLen = sizeof(clientAddr); // length of client address, uint32_t
  int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
  if (clientSocket < 0)
  {
    logger->warning("Accept failed!");
    return -1;
  }
  logger->info("Connected with client having IP: " + std::string(inet_ntoa(clientAddr.sin_addr)));
  return clientSocket;
}

void handleClientThread(int clientSocket)
{
  // Create a thread to handle the client
  std::thread clientThread(ClientHandler::handleConnection, clientSocket);
  clientThread.detach(); // Detach the thread to let it run independently
}

int main()
{
  // Create a logger
  Logger *logger = new Logger();
  // Create a socket
  int serverSocket = createServer(logger);
  // binds the server
  bindServer(serverSocket, logger);
  // listen for incoming connections
  logger->info("Server is listening on port " + std::to_string(PORT));
  int i = 0;
  listenSocket(serverSocket, logger);

  // Main loop to accept clients
  while (i < 20)
  {
    // Accept a client
    int clientSocket = acceptClient(serverSocket, logger);
    if (clientSocket < 0)
    {
      i++;
      continue;
    }
    // Handle the client in a separate thread
    handleClientThread(clientSocket);
  }

  // Close the server socket (this point is never reached in this example)
  close(serverSocket);
  return 0;
}
