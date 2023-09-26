#include "Common.h"

// release 버전
// -> 디버그 모드에서만 하면 테스트를 할 수 있는 환경이 제한 됨


WORD MyWord (BYTE lowByte, BYTE highByte) {
	return ((WORD)highByte << 8) | lowByte;
}

int main(int argc, char* argv[])
{
	printf("네트워크 게임프로그래밍 과제 1\n");
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MyWord(2, 2), &wsa) != 0)
		return 1;
	printf("[알림] 윈속 초기화 성공\n");

	printf("wVersion: %d\n", wsa.wVersion);
	printf("wHighVersion: %d\n", wsa.wHighVersion);
	printf("szDescription: %s\n", wsa.szDescription);
	printf("szSystemStatus: %s\n", wsa.szSystemStatus);

	// 소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");
	printf("[알림] 소켓 생성 성공\n");

	// 소켓 닫기
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}
