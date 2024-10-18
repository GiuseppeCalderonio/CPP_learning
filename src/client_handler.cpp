#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>    // For close()
#include <arpa/inet.h> // For inet_addr()
#include "logger.hpp"

class ClientHandler
{

public:
  static void handleConnection(int clientSocket)
  {
    Logger *logger = new Logger();
    char buffer[1024] = {0};
    std::string hello = "Hello from server!";

    // Read data from the client
    int bytesRead = read(clientSocket, buffer, 1024);
    if (bytesRead > 0)
    {
      logger->info("Client says: \n" + std::string(buffer));
      // Send a response to the client
      send(clientSocket, hello.c_str(), hello.size(), 0);
    }

    // Close the socket after the communication
    close(clientSocket);
  }
};