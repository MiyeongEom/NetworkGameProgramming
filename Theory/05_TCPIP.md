## TCP/IP
#### 2023. 09. 26 수업

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
  
  [사진참고]([http://github.com "깃허브"](https://github.com/MiyeongEom/NetworkGameProgramming/blob/main/Theory/05_picture.md)

* 간단한 클라이언트 예제
  
  ![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/d22b025e-4009-4760-94f3-b70a94055a24)
  
  [소스코드](http://github.com "깃허브")  
