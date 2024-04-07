#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

// Socket流程 建立->連接(binding)->監聽(listening)->連接->傳訊->關閉通訊

int main()
{
  // 建立socket，通訊協定選擇AF_INET，SOCK_STREAM(TCP)
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  if (serverSocket == -1)
  {
    cerr << "Server Socket連結失敗" << endl;
    return 0;
  }

  // Binding
  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  // use port 8000
  serverAddr.sin_port = htons(8000);
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
  {
    cerr << "Error: Failed to bind port" << endl;
    close(serverSocket);
    return 1;
  }

  // Listening
  if (listen(serverSocket, 5) == -1)
  {
    cerr << "Error: Failed to listen for connections" << endl;
    close(serverSocket);
    return 1;
  }

  cout << "Server is running..." << endl;

  // Connecting
  sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  int clientSocket = accept(serverSocket, (sockaddr *)&clientAddr, &clientAddrLen);
  if (clientSocket == -1)
  {
    cerr << "Error: Failed to accept client connection" << endl;
    close(serverSocket);
    return 1;
  }

  cout << "Client connected" << endl;

  // 傳訊
  char buffer[1024];
  while (true)
  {
    memset(buffer, 0, sizeof(buffer)); // 清空缓冲区
    ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived <= 0)
    {
      cerr << "Error: Failed to receive message from client" << endl;
      break;
    }
    cout << "Received from client: " << buffer << endl;
  }

  // 關閉連接
  close(clientSocket);
  close(serverSocket);

  return 0;
}
