#include "Common.h"

// release ����
// -> ����� ��忡���� �ϸ� �׽�Ʈ�� �� �� �ִ� ȯ���� ���� ��


WORD MyWord (BYTE lowByte, BYTE highByte) {
	return ((WORD)highByte << 8) | lowByte;
}

int main(int argc, char* argv[])
{
	printf("��Ʈ��ũ �������α׷��� ���� 1\n");
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MyWord(2, 2), &wsa) != 0)
		return 1;
	printf("[�˸�] ���� �ʱ�ȭ ����\n");

	printf("wVersion: %d\n", wsa.wVersion);
	printf("wHighVersion: %d\n", wsa.wHighVersion);
	printf("szDescription: %s\n", wsa.szDescription);
	printf("szSystemStatus: %s\n", wsa.szSystemStatus);

	// ���� ����
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");
	printf("[�˸�] ���� ���� ����\n");

	// ���� �ݱ�
	closesocket(sock);

	// ���� ����
	WSACleanup();
	return 0;
}
