## 도메인 이름 시스템과 이름 변환 함수

* Domain name : IP주소와 대응하는 이름, TCP/IP 프로토콜은 도메인 이름을 인식 X -> IP주소로 변환 필요
* IP주소와 도메인 이름 변환 정보는 DNS에서 관리(분산 데이터베이스)
  
  
* 도메인이름 -> IP주소 (네트워크바이트정렬)
```C
struct hostent* gethostbyname(const char* name); 
```
 
 
* IP주소(네트워크바이트정렬) -> 도메인이름
```C
struct hostent* gethostbyaddr(
    const char* addr, // 네트워크바이트정렬된IP주소
    int len, // IP주소의길이(예:4)
    int type // 주소체계(ex:AF_INET)
    );
```
  
  
* __hostent구조체__
```C
struct hostent {
    char* h_name;      // 공식 도메인 이
    char** h_aliases;  // 한 호스트가 공식 도메인 이름 외에 다른 이름, 별
    short h_addrtype;  // 주소 체계(IPv4에서는 AF_INET)
    short h_length;    // IP주소의 길이(바이트 단위, IPv4에서는 4) 
    char** h_addr_list // 네트워크 바이트 정렬된 IP주소, 이 포인터에서 모든 IP주소를 얻을 수 있
    };
typedef struct hostent HOSTENT;
```

![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/1886b48f-175b-4d66-9a47-27b56c320f07)

