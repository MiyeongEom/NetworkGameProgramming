## 소켓 주소 구조체
* 네트워크 프로그램에서 필요한 정보를 담음
* 기본형 sockaddr 구조체
```c 
#include <winsock2.h>
struct sockaddr {
    unsigned short sa_family;   // 주소 체계
    char           sa_data[14]; // 주소 정보 (포트번호 - ip)
};
```

