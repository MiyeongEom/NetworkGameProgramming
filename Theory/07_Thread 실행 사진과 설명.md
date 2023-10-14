* 스레드1 실행 중, 명령을 처리할 때마다 CPU레지스터 값과 스택 내용 변경  
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/5e2b4031-1ac3-49c2-9bc7-7bb13978aa0d)  
  
* 스레드 1의 실행을 중지하고 실행 상태 저장, 이전에 저장해둔 스레드 2의 상태 복원  
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/a4f141c2-d913-4dc2-9042-c28d606b5d7d)  
  
* 스레드2를 실행한다. 명령을 처리할 때마다 CPU 레지스터 값과 내용 변경  
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/21df22ce-4166-4a34-8bb4-b8ca7118b56b)  
  
* 스레드 2의 실행을 중지하고 실행 상태 저장, 이전에 저장해둔 스레드 1의 상태 복원  
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/aeeb8c99-2025-4bda-b2d5-0fd3aa1141e6)  
  
* 스레드 1을 다시 실행, 이전 상태가 복원되어 스레드 1은 마지막으로 수행한 명령 다음 위치부터 실행  
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/86d64440-4ef9-4905-8e95-6b75b6edb4b8)  
  
