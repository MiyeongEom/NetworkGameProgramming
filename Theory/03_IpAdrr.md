## IP주소 변환 함수

* IP주소를 문자열 형태 전달받게 될 때 이를 32비트 숫자, 네트워크 바이트 정렬로 변환할 필요가 있다
    *  inet_addr() : 문자열 형태로 IP를 입력받아 32비트 숫자로 리턴   unsigned long inet_addr(const char* cp);
    *  inet_ntoa() : 32비트 숫자로 IP주소를 입력받아 문자열로 리턴    char* inet_ntoa(struct in_addr in);

 * 소켓 주소 구조체를 초기화한 후 소켓 함수에 넘겨주는 경우
```C
// 소켓 주소 구조체 초기화
SOCKADDR_IN addr;

ZeroMemory(&addr, sizeof(addr));    // 0으로 초기화
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = inet_addr("147.46.114.70");
addr.sin_port = htons(9010);

// 소켓 함수 호출
f((SOCKADDR*)&addr, ...);
```

* 소켓 함수가 소켓 주소 구조체를 입력받아서 값을 채우면, 애플리케이션이 이를 출력 등의 목적으로 사용하는 경우
```C
// 소켓 주소 구조체 선언
SOCKADDR_IN addr;

// 소켓 함수 호출
g((SOCKADDR*)&addr, ...);

// IP주소와 포트 번호 출력
printf("IP주소 = %s, 포트번호 = %d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
```
