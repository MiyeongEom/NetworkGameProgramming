#include "Common.h"
#define SERVERIP "127.0.0.1"
#define SERVERPORT 9000
#define FILENAME_SIZE 256
#define BUFSIZE 1024

int main(int argc, char* argv[])
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		err_quit("socket()");

	struct sockaddr_in serveraddr; // 서버 주소 설정
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);

    // 서버 연결
	if (connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR)
        err_quit("connect()");

     char filename[FILENAME_SIZE];
     printf("전송할 파일 이름 : ");
     fgets(filename, sizeof(filename), stdin);
     filename[strcspn(filename, "\n")] = '\0';

     // 파일 열기
     FILE* file = fopen(filename, "rb"); // 데이터 보존 -> 이진파일, 파일 핸들 저장?
     if (!file)
         err_quit("파일 열기 실패");

     // 파일 이름 전송 (고정 길이 데이터)
     send(sock, filename, FILENAME_SIZE, 0);

	 // 파일 크기 전송 (고정 길이 데이터)
	 long long total_file_size = _filelengthi64(_fileno(file));
     send(sock, (char*)&total_file_size, sizeof(total_file_size), 0);

     // 데이터 전송 -> 파일 내용은 가변 길이 데이터
     char buffer[BUFSIZE];
     size_t bytes_read;
     size_t total_sent = 0;
     while ((bytes_read = fread(buffer, 1, BUFSIZE, file)) > 0) {
         size_t bytes_sent = send(sock, buffer, bytes_read, 0);
         if (bytes_sent == SOCKET_ERROR)
             err_quit("send()");
         total_sent += bytes_sent;

         // 전송률 표시
         float transfer_percentage = (float)total_sent / (float)total_file_size * 100.0;
         printf("\r전송률: %.2f%%", transfer_percentage);
         fflush(stdout);
     }
     printf("\n파일 전송 완료\n");


	// 소켓 닫기
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}

// _fileno 함수는 파일 스트림을 파일 디스크립터(파일 핸들)로 변환하는 함수
// _filelengthi64 함수는 파일 핸들을 받아 해당 파일의 크기를 반환하는 함수로 64비트 -> 정확함
// long long 64비트
// size_t는 부호 없는 정수 타입이라 파일크기는 양의 정수 값으로 나타내기에 사용
// fread : 바이트 수 읽기 

// size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
     // 읽어온 데이터 저장될 메모리 버퍼 포힌터, 바이트 수, 읽어올 데이터 항목 개수, 파일 포인터)