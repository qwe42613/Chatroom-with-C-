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
  // use port 8080
  serverAddr.sin_port = htons(8080);
  // INADDR_ANY為0.0.0.0，表示socket只綁定port，讓router決定ip address
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
  {
    cerr << "Binding port失敗" << endl;
    close(serverSocket);
    return 1;
  }

  // Listening
  if (listen(serverSocket, 5) == -1)
  {
    cerr << "listening失敗" << endl;
    close(serverSocket);
    return 1;
  }

  cout << "Server 執行中" << endl;

  // Connecting
  sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  int clientSocket = accept(serverSocket, (sockaddr *)&clientAddr, &clientAddrLen);
  if (clientSocket == -1)
  {
    cerr << "與用戶連接失敗" << endl;
    close(serverSocket);
    return 1;
  }

  cout << "用戶已連接" << endl;

  // 傳訊
  char buffer[1024];
  while (true)
  {
    memset(buffer, 0, sizeof(buffer)); // 清空缓冲区
    ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived <= 0)
    {
      cerr << "無法取的用戶的通訊內容" << endl;
      break;
    }
    cout << "用戶:" << buffer << endl;
  }

  // 關閉連接
  close(clientSocket);
  close(serverSocket);

  return 0;
}
