# Server-Client 聊天系統
這是一個使用 C++ 編程語言實現的基本的 Server-Client 聊天系統。

## 功能特色
- 用戶可以通過 Server 進行聊天。
- 使用基於標準 Socket(TCP) 的網絡通信。

## 使用方式

1. 啟動 Server，程式將開始監聽特定的端口，等待 Client 的連接。
2. 啟動 Client，它將連接到 Server 的 IP 地址和端口(8080)。
3. 一旦連接建立，Client 和 Server 之間可以開始進行聊天。
4. 使用者可輸入訊息， Server收到訊息後再將其發送給其他用者。

## 需求
- C++ 編譯器
- 支援標準 Socket 套件之導入




