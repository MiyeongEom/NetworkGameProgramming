## 소켓 주소 구조체
* 네트워크 프로그램에서 필요한 정보를 담음
* 기본형 sockaddr 구조체
```c 
#include <winsock2.h>
struct sockaddr {               // 16 Byte
    unsigned short sa_family;   // 주소 체계
    char           sa_data[14]; // 주소 정보 (IP주소와 포트번호)
};
```
  
* IPv4 소켓 주소 구조체
```c 
#include <winsock2.h>
struct sockaddr_in {               // 16 Byte
    short            sin_family;   // AF_INET
    unsigned short   sin_port;  
    struct in_addr   sin_addr;     // 32비트 in_addr 구조체
    char             sin_zero[8];  // 항상 0으로 설정
};
```
  
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/3ced2311-f075-413d-ba01-28d94ee4f87c)
  
  
* 소켓 주소 구조체 사용 예
```c 
struct sockaddr_in addr;
... //소켓 주소 구조체 초기화
SocketFunc(..., (struct sockaddr *)&addr, sizeof(addr), ...);
```
```c 
struct sockaddr_in addr;
int addrlen = sizeof(addr);
SocketFunc(..., (struct sockaddr *)&addr, &addrlen, ...);
... // 소켓 주소 구조체 사
```
