#include "ServerSocketManager.h"
#include <string>
#include <vector>
#include <ctime>
#include <assert.h>
#include <winsock.h>

#pragma comment(lib, "Ws2_32.lib")

namespace ServerSocketManager {

	inline std::vector<SocketPlayer> socketPlayerList;
	inline SOCKET listenSocket = {};

	void InitManager() {
		int result = 0;
		socketPlayerList.resize(2);

		//WSADATAの参考：https://learn.microsoft.com/ja-jp/windows/win32/api/winsock2/ns-winsock2-wsadata
		WSADATA wsa = {};
		result = WSAStartup(MAKEWORD(2, 2), &wsa); //WinSockDLLの使用を開始する関数
		assert(result == 0 && "WSAのセットアップに失敗しました");

		listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (listenSocket == INVALID_SOCKET) {
			assert(listenSocket != INVALID_SOCKET);
			ReleaseApp();
		}
		socketPlayerList[0].socket = listenSocket;
		socketPlayerList[0].id = 0;
		socketPlayerList[0].connected = true;

		SOCKADDR_IN addr = {};
		addr.sin_family = AF_INET;
		addr.sin_port = htons(10000);
		addr.sin_addr.s_addr = INADDR_ANY;

		result = bind(listenSocket, reinterpret_cast<SOCKADDR*>(&addr), sizeof(addr));
		if (result == SOCKET_ERROR) {
			assert(result != SOCKET_ERROR && "バインドに失敗しました");
			ReleaseApp();
		}

		result = listen(listenSocket, SOMAXCONN); //接続待ち状態にする
		if (result == SOCKET_ERROR) {
			assert(result != SOCKET_ERROR && "listenに失敗しました");
			ReleaseApp();
		}

		std::cout << "プレイヤーを待機しています..\n";
		for (int i = 1; i < 2; i++) {
			SOCKADDR_IN clientAddr = {};
			int size = sizeof(clientAddr);
			SOCKET clientSocket = accept(listenSocket, reinterpret_cast<SOCKADDR*>(&clientAddr), &size);
			if (clientSocket == INVALID_SOCKET) {
				assert(clientSocket != INVALID_SOCKET);
				ReleaseApp();
			}
			u_long flag = 1;
			ioctlsocket(clientSocket, FIONBIO, &flag);
			socketPlayerList[i].socket = clientSocket;
			socketPlayerList[i].id = i + 1;
			socketPlayerList[i].connected = true;
			sendText(clientSocket, std::string("ようこそ" + std::to_string(socketPlayerList[i].id) + "さん。\n"));
			std::cout << "プレイヤー" << socketPlayerList[i].id << "さんがログインしました\n";
		}

		while (true) {

			for (auto& player : socketPlayerList) {
				if (!player.connected) {
					continue;
				}

				char buf[256] = {};
				result = recv(player.socket, buf, sizeof(buf) - 1, 0);
				if (result == SOCKET_ERROR) {
					int error = WSAGetLastError();
					if (error == WSAECONNRESET) {
						std::cout << "プレイヤー" << player.id << "が切断されました。";
						player.connected = false;
						broadcast(socketPlayerList, ("プレイヤー" + std::to_string(player.id) + "は切断されました。"));
					}
				}
				else if (result > 0) {
					buf[result] = '\0';

					std::cout << "プレイヤー" << player.id << ": " << buf << "\n";
					broadcast(socketPlayerList, "プレイヤー" + std::to_string(player.id) + ": " + std::string(buf));
				}

			}

			Sleep(10);
		}

		ReleaseApp();
	}

	bool sendText(const SOCKET& socket, const std::string& text) {
		int result = SOCKET_ERROR;
		result = send(socket, text.c_str(), static_cast<int>(text.size()), 0);
		return result != SOCKET_ERROR;
	}

	void broadcast(const std::vector<SocketPlayer>& players, const std::string& text) {
		for (const auto& player : players) {
			if (player.connected) {
				sendText(player.socket, text);
			}
		}
	}

	void ReleaseApp() {
		for (auto& player : socketPlayerList) {
			if (player.socket != INVALID_SOCKET) {
				closesocket(player.socket);
			}
		}

		closesocket(listenSocket);
		WSACleanup();
	}
}