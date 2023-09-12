#define _CRT_SECURE_NO_WARNINGS // 구형 C 함수 사용 시 경고 끄기
#define _WINSOCK_DEPRECATED_NO_WARNINGS // 구형 소켓 API 사용 시 경고 끄기

#include <winsock2.h> // 윈속2 메인 헤더
#include <ws2tcpip.h> // 윈속2 확장 헤더

#include <tchar.h> // _T(), ...
#include <stdio.h> // printf(), ...
#include <stdlib.h> // exit(), ...
#include <string.h> // strncpy(), ...

#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

// message나 box함수 뒤에 A가 붙은 이유 : err_quit는 ANSI버전을 사용하기로 했기에 (A - ANSI 버전, W-유니코드 버전)

// 소켓 함수 오류 출력 후 종료
void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;  // LPVOID : Long Pointer to Void, 어떤 종류의 데이터나 객체의 포인터를 나타내는 일반적인 포인터 형식
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 
		// FORMAT_MESSAGE_ALLOCATE_BUFFER : 이 함수가 알아서 할당한다
		//FORMAT_MESSAGE_FROM_SYSTEM : 운영체제로부터 오류 메세지를 가져온다
		NULL, WSAGetLastError(), // NULL 고정, WSAGetLastError()함수의 리턴값
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //오류 메세지를 표시할 언어, 이처럼쓰면 시스템 기본 언어로 오류 메세지 받음
		(char*)&lpMsgBuf, 0, NULL); // 오류 메세지의 시작 주소 저장 // 주소값을 저장할 변수를 여기에 넣음 -> **밑에서 메모리 반환해야함!!
	MessageBoxA(NULL, (const char*)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf); // 메모리 반환
	exit(1);
}

// 소켓 함수 오류 출력
void err_display(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[%s] %s\n", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// 소켓 함수 오류 출력
void err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[오류] %s\n", (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// err_display(const char* msg) : 지정한 오류 메시지와 함께 최근의 소켓 함수 오류를 출력하는 데 사용
// err_display(int errcode) : 직접 오류 코드를 제공하고 해당 오류 코드에 대한 오류 메시지를 출력하는 데 사용