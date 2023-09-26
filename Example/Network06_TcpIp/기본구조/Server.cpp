#include "Common.h"
#define SERVERPORT 9000
#define BUFSIZE    512

int main(int argc, char* argv[])
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성 : 클라이언트를 받아 들이는 역할
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM : TCP 소켓
	if (listen_sock == INVALID_SOCKET) 
		err_quit("socket()");

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  
	serveraddr.sin_port = htons(SERVERPORT);  // 포트번호 바인드
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) 
		err_quit("bind()");
	// INADDR_ANY를 사용하면 서버 소켓을 모든 사용 가능한 네트워크 인터페이스에 바인딩하고,
	// 클라이언트가 어떤 네트워크 인터페이스를 통해 서버에 연결하더라도 수신할 수 있습니다
	
	// listen()
	// SOMAXCONN은 소켓 라이브러리에서 사용되는 상수로, TCP 서버 소켓의 대기 큐 크기를 지정하는 데 사용
	// 이는 시스템 라이브러리에서 정의된 상수로, 운영 체제에 따라 다를 수 있다
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) 
		err_quit("listen()");

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1]; // 보통 NULL 문자 포함하기 위해 +1

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// 접속한 클라이언트 정보 출력
		// INET_ADDRSTRLEN : IPv4 주소를 문자열로 표현할 때 필요한 문자열 버퍼의 크기를 나타내는 상수
		// 대부분의 경우 이 값은 16으로 정의되며, 이는 네 개의 숫자와 세 개의 점(마침표) 그리고 널 종료 문자('\0')를 저장할 수 있는 충분한 크기
		// inet_ntop : 네트워크 주소를 문자열로 반환 (반대 inet_pton)
		// ntohs : 호스트 바이트 순서를 네트워크 바이트 순서로
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			addr, ntohs(clientaddr.sin_port));

		// 클라이언트와 데이터 통신
		while (1) {
			// 데이터 받기
			retval = recv(client_sock, buf, BUFSIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv()");
				break;
			}
			else if (retval == 0)
				break;

			// 받은 데이터 출력
			buf[retval] = '\0';
			printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), buf);

			// 데이터 보내기
			retval = send(client_sock, buf, retval, 0);
			if (retval == SOCKET_ERROR) {
				err_display("send()");
				break;
			}
		}

		// 소켓 닫기
		closesocket(client_sock);
		printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
			addr, ntohs(clientaddr.sin_port));
	}

	// 소켓 닫기
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}


