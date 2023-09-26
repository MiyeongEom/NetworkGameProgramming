## TCP/IP
### 2023. 09. 26 수업

* TCP 서버/클라이언트 동작 방식
  * 서버는 먼저 실행해 클라이언트가 접속하길 기다린다 (listen)
  * 클라이언트가 서버에 접속(connect)해 데이터를 보낸다(send)
  * 서버는 클라이언트 접속을 수용(accept), 보낸 데이터를 받아(recv) 처리한다
  * 서버는 처리한 데이터를 다시 보낸다 (send)
  * 클라이언트는 서버가 보낸 데이터를 받아(recv) 자신의 목적에 맞게 사용한다  
  
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/6a320a5d-870d-4a4a-a5de-4eeafda5e798)

* 동작원리
  * 서버 : 소켓 생성 후 클라 접속 대기. 이때 서버 소켓은 특정 포트 번호와 결합되어 있어 이 포트에 접속하는 클라만 수용 가능 (__bind__)
  * 클라가 접속, TCP프로토콜 수준에서 연결 설정을 위해 패킷 교환이 이루어진다.
  * 위 절차가 끝나면, 서버는 클라와 통신 가능한 새로운 생성 (클라와 데이터 교환할 때 이 소켓 사용, 기존 소켓은 새로운 클라 접속을 수용하는 용도로 계속 사용)
  * 두 클라가 접속한 상태면, 서버측에는 3개의 소켓이 존재. 이 중 2개의 소켓이 실제 클라와 통신하는 용도
  * 서버측 소켓과 클라측 소켓이 1대1로 대응. 한 클라가 두 개 이상의 소켓을 사용해 서버 접속도 가능함
  
  [사진참고](https://github.com/MiyeongEom/NetworkGameProgramming/blob/main/Theory/05_picture.md)

* 간단한 클라이언트 예제
  
  ![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/d22b025e-4009-4760-94f3-b70a94055a24)
  
  [기본코드](https://github.com/MiyeongEom/NetworkGameProgramming/tree/main/Example/Network06_TcpIp/%EA%B8%B0%EB%B3%B8%EA%B5%AC%EC%A1%B0)  
  
* TCP 서버/클라이언트 분석
 * 프로토콜 : 소켓을 생성할 때 결정된다
 * 지역 IP주소와 지역 포트 번호 : 서버 또는 클라이언트 자신의 주소를 의미
 * 원격 IP주소와 원 포트 번호 : 서버 또는 클라이언트가 통신하는 상대의 주소 의미
 ![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/e3eaf7cb-93b5-4442-9004-4241ac3cd771)  

---  
  
#### 서버 함수
* socket() -> 소켓 생성
* bind() -> 지역IP 주소와 지역 포트 번호 결정
* listen() -> TCP상태를 Listening 변경
* accpet() -> 자신에 접속한 클라와 통신할 수 있게 새로운 소켓 생성
* send(), recv() -> 클라와 통신
* closesocket() -> 소켓 닫  
* 새로운 클라 접속 -> accept ~ closesocket 반복

![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/4b4b2060-fc6d-49bd-b23e-5cf8bfac2ff3)  


###### bind() 함수  // 성공: 0, 실패: SOCKET_ERROR
 * 서버의 지역 IP주소와 지역 포트 번호를 결정하는 역할
   
```C
int bind(
  SOCKET s,                       // 클라 접속 승인 목적 소켓, IP주소와 지역 포트 번호가 설정되지 X
  const struct sockaddr* name,    // 소켓 구조 구조체 (SOCKADDR_IN) 변수를 지역 IP와 포트로 초기화하고 이 주소값을 대입
  int namelen                     // 소켓 주소 구조체 변수의 길이 대입
);   // 성공: 0, 실패: SOCKET_ERROR
```

###### listen() 함수  // 성공: 0, 실패: SOCKET_ERROR
 * 소켓과 결합된 TCP포트 상태를 listening으로 바꾸는 역할
   
```C
int listen(
  SOCKET s,                       // 클라 접속 승인 목적 소켓, IP주소와 지역 포트 번호가 설정됨
  int backing                     // 접속 가능한 클라이언트 개수
);   // 성공: 0, 실패: SOCKET_ERROR
```

###### accept() 함수  // 성공: 0, 실패: INVALID_ERROR
 * 서버에 접속한 클라와 통신할 수 있도록 새로운 소켓 생성해 리턴, 접속한 크라 ip주소와 포트번호 알려줌
   
```C
int accept(
  SOCKET s,                       // 클라 접속 승인 목적 소켓
  struct sockaddr* addr,          // 소켓 주소 구조체 변수 정의, 변수의 주소값 대입 - addr이 가리키는 메모리 영역을 클라 ip와 포트 번호로 채워 넣음
  int* addrlen                    // 정수형 변수를 addr이 가리키는 메모리 영역의 크기로 초기화한 후 변수의 주소값 대입, 함수가 초기화한 메모리 크기값(바이트 단위)을 가짐
);   // 성공: 0, 실패: SOCKET_ERROR
```

---   
   
#### 클라이언트 함수

* socket() -> 소켓 생성
* connect() -> 서버 접속
* send(), recv() -> 서버와 데이터 통신
* closesocket() -> 소켓닫기  

  
###### connect() 함수  // 성공: 0, 실패: SOCKET_ERROR
 * 클라이언트 서버 접속해 TCP 프로토콜 수준의 연결 이루어지게 함
 * 이를 호출하면 운영체제는 자동으로 지역 IP 주소와 지역 포트 번호를 설정함
   
```C
int connect(
  SOCKET s,                      // 서버 통신 소켓
  const struct sockaddr* name,   // 소켓 주소 구조체 변수를 서버 주소로 초기화하고 이 변수의 주소값 대입
  int namelen                    // 소켓 주소 구조체 변수의 길이 대입 (바이트 단위)
);   // 성공: 0, 실패: SOCKET_ERROR
```

---   
  
#### 데이터 전송 함수 (중요)  
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/1e608bac-c17c-49f0-abc3-92b9c853f8ee)  

* 각자 데이터 송수신 버퍼가 존재
* 송신 버퍼는 데이터를 전송하기 전에 임시로 저장해두고 수신버퍼는 받은 데이터를 애플리케이션이 처리하기 전까지 임시로 저장 -> 이 두개를 통틀어 __소켓버퍼__ 라함
* 데이터 경계 구분을 위한 상호 약속이 필요
* 송신버퍼에 자리가 없다 -> 우리가 배운대로 하면 blocking (기다리다가 송신버퍼에 자리가 생기면 보냄)
* non-blocking (send함수 여러번 불러야 할 수도) : 남은 공간만큼 잘라서 보냄
*  tcp -> 운영체제가 송신 버퍼에서 상대 수신버퍼로  데이터를 보내고(송신버퍼에 무언가 남음)
*  상대 수신버퍼가 잘못되었다 사인하면 다시보내달라고 요청, 잘보냈다고 해야 송신버퍼에 남아있던게 없어짐.  

   
###### send() 함수   // 성공:보낸 바이트수, 실패:SOCKET_ERROR
 * 애플리케이션 데이터를 송신 버퍼에 복사함으로써 궁극적으로 하부 프로토콜(ex) TCP/IP)에 의해 데이터가 전송되게 함
 * send( )함수가 성공했다고 실제 데이터 전송이 완료된 것은 아님
 * 블로킹(blocking) 소켓 : send( )함수를 호출할 때, 송신 버퍼의 여유 공간이 send( )함수의 세 번째 인자인 len보다 작을 경우 해당 프로세스는 대기 상태(wait state)가 된다. 송신 버퍼에 충분한 공간이 생기면 프로세스는 깨어나고, len크기만큼 데이터 복사가 이루어진 후 send( )함수가 리턴한다.
 * 넌블로킹(Nonblocking) 소켓 : ioctlsocket( )함수를 이용하면 블로킹 소켓을 넌블로킹 소켓으로 바꿀 수 있다. 넌블로킹 소켓에 대해 send( )함수를 호출하면, 송신 버퍼의 여유 공간만큼 데이터를 복사한 후 실제 복사한 데이터 바이트 수를 리턴한다. 이 경우 send( )함수의 리턴값은 최소1, 최대 len이 된다.
   
```C
int send(
  SOCKET s,            // 통신할 대상과 연결된 소켓
  const char* buf,     // 보낼 데이터를 담고 있는 애플리케이션 버퍼 주소
  int len,             // 보낼 데이터 크기 (바이트 단위)
  int flags            // send함수의 동작을 바꿈, 대부분 0
);   
```

  
  
###### recv( )함수  // 성공: 받은 바이트 수 또는 0, 실패: SOCKET_ERROR
 * 수신 버퍼에 도착한 데이터를 애플리케이션 버퍼로 복사하는 역할을 한다
  
```C
int recv(
  SOCKET s,            // 통신할 대상과 연결된 소켓
  char* buf,           // 받은 데이터를 저장할 애플리케이션 버퍼 주소
  int len,             // 수신버퍼로부터 복사할 최대 데이터크기, buf보다 크면 안됨
  int flags            // recv()함수의 동작을 바꿈, 대부분 0
);   // 성공: 0, 실패: SOCKET_ERROR
```

* 수신 버퍼에 데이터가 도달한 경우 : len보다 크지 않은 범위 내에서 가능한 많은 데이터를 애플리케이션 버퍼로 복사한다. 이 경우 복사한 바이트 수가 리턴되며, 최대 리턴값은 len이 된다  
  
* 접속이 정상 종료된 경우 : 상대 애플리케이션이 closesocket( )함수를 사용하여 접속을 종료하면, TCP프로토콜 수준에서 접속 종료를 위한 패킷 교환 절차가 이루어진다. 이 경우 recv( )함수는 0을 리턴한다. 리턴값이 0인 경우를 정상 종료(normal close = graceful close)라 부른다
