#include "Common.h"

int main(int argc, char* argv[]) {

	WSADATA wsa;
	char domainName[256] = {};
	struct hostent* ptr;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	printf("도메인 : ");
	scanf_s("%s", domainName,256);
	ptr = gethostbyname(domainName);

	printf("공식 이름 %: %s\n", ptr->h_name);

	for (int i = 0; ptr->h_aliases[i]; i++){
			printf("별명 %d : %s\n",  i + 1, ptr->h_aliases[i]);
	}

	for (int i = 0; ptr->h_addr_list[i]; i++) {
		printf("IP주소 %d : %s\n", i + 1, inet_ntoa(*(struct in_addr*)ptr->h_addr_list[i]));
	}

	WSACleanup();

	return 0;
}


