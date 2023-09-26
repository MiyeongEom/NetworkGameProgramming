#define _CRT_SECURE_NO_WARNINGS // ���� C �Լ� ��� �� ��� ����
#define _WINSOCK_DEPRECATED_NO_WARNINGS // ���� ���� API ��� �� ��� ����

#include <winsock2.h> // ����2 ���� ���
#include <ws2tcpip.h> // ����2 Ȯ�� ���

#include <tchar.h> // _T(), ...
#include <stdio.h> // printf(), ...
#include <stdlib.h> // exit(), ...
#include <string.h> // strncpy(), ...

#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ

// message�� box�Լ� �ڿ� A�� ���� ���� : err_quit�� ANSI������ ����ϱ�� �߱⿡ (A - ANSI ����, W-�����ڵ� ����)

// ���� �Լ� ���� ��� �� ����
void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;  // LPVOID : Long Pointer to Void, � ������ �����ͳ� ��ü�� �����͸� ��Ÿ���� �Ϲ����� ������ ����
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 
		// FORMAT_MESSAGE_ALLOCATE_BUFFER : �� �Լ��� �˾Ƽ� �Ҵ��Ѵ�
		//FORMAT_MESSAGE_FROM_SYSTEM : �ü���κ��� ���� �޼����� �����´�
		NULL, WSAGetLastError(), // NULL ����, WSAGetLastError()�Լ��� ���ϰ�
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //���� �޼����� ǥ���� ���, ��ó������ �ý��� �⺻ ���� ���� �޼��� ����
		(char*)&lpMsgBuf, 0, NULL); // ���� �޼����� ���� �ּ� ���� // �ּҰ��� ������ ������ ���⿡ ���� -> **�ؿ��� �޸� ��ȯ�ؾ���!!
	MessageBoxA(NULL, (const char*)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf); // �޸� ��ȯ
	exit(1);
}

// ���� �Լ� ���� ���
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

// ���� �Լ� ���� ���
void err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[����] %s\n", (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// err_display(const char* msg) : ������ ���� �޽����� �Բ� �ֱ��� ���� �Լ� ������ ����ϴ� �� ���
// err_display(int errcode) : ���� ���� �ڵ带 �����ϰ� �ش� ���� �ڵ忡 ���� ���� �޽����� ����ϴ� �� ���