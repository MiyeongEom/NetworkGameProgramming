#include "Common.h"

#define SERVERPORT 9000
#define FILENAME_SIZE 256 // OS
#define BUFSIZE 1024 // AVERAGE, 2^n

DWORD WINAPI ProcessClient(LPVOID arg)
{
	int retval;
	SOCKET client_sock = (SOCKET)arg;
	struct sockaddr_in clientaddr;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	char buf[BUFSIZE + 1];

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (struct sockaddr*)&clientaddr, &addrlen);
	inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

	/////////////////////////////////////////////////////////////////
	while (1) {
		// 클라로부터 파일 이름 수신
		char filename[FILENAME_SIZE];
		retval = recv(client_sock, filename, FILENAME_SIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		printf("파일 이름: %s\n", filename);

		// 클라로부터 파일 크기 수신
		long long total_file_size;
		retval = recv(client_sock, (char*)&total_file_size, sizeof(total_file_size), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		// 파일 생성 및 데이터 수신/저장
		FILE* file = fopen(filename, "wb");
		if (!file) {
			err_quit("파일 열기 실패");
			break;
		}

		char buffer[BUFSIZE];
		size_t bytes_received;
		size_t total_received = 0;
		while ((bytes_received = recv(client_sock, buffer, BUFSIZE, 0)) > 0) {
			size_t bytes_written = fwrite(buffer, 1, bytes_received, file); // 파일에 쓰여진 바이트 저장
			if (bytes_written < bytes_received) {
				err_quit("파일 쓰기 실패");
				break;
			}
			total_received += bytes_received;

			// 전송률 표시
			float transfer_percentage = (float)total_received / (float)total_file_size * 100.0;
			printf("\r전송률: %.2f%%", transfer_percentage);
			fflush(stdout);

		}

		printf("\n파일 전송 완료\n");
		fclose(file);
	}

	// 소켓 닫기
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		addr, ntohs(clientaddr.sin_port));
	return 0;
}


int main(int argc, char* argv[])
{

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); // 소켓 생성
	if (sock == INVALID_SOCKET) 
		err_quit("socket()");

	struct sockaddr_in serveraddr; // 서버 주소 설정
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);

	// 소켓에 주소와 포트 바인딩
	int retval = bind(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) 
		err_quit("bind()");

	// 요청 ready
	retval = listen(sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) 
		err_quit("listen()");

	// 데이터 통신에 사용할 소켓, 변수
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread;

	while (1) {
		addrlen = sizeof(clientaddr);
		client_sock = accept(sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_quit("accept()");
			break;
		}

		// 클라 ip, 포트 번호 얻음
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			addr, ntohs(clientaddr.sin_port));

		// 스레드 생성
		hThread = CreateThread(NULL, 0, ProcessClient,
			(LPVOID)client_sock, 0, NULL);
		if (hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }
		
	}

	closesocket(sock);
	WSACleanup();
	return 0;
}