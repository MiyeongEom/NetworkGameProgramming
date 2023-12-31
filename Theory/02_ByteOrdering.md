## 바이트 정렬

* 바이트 정렬 : 메모리에 데이터를 저장할 때의 바이트 순서
    * 빅 엔디안(big-endian) : 최상위 바이트부터 차례대로 저장
    * 리틀 엔디안(little-endian) : 최하위 바이트부터 차례대로저장
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/bf9c215d-e9a2-4174-a43e-fe38d182b2e4)

* 네트워크 애플레케이션에서 바이트 정렬 방식을 고려해야 하는 경우
  * 종단 시스템과 라우터의 __IP주소__ 의 바이트 정렬
  * 두 종단 시스템의 __포트 번호__ 의 바이트 정렬 -> __빅 엔디안__(__네트워크 바이트 정렬__)으로 통일됨
  * 애플리케이션이 주고 받는 __데이터__ (데이터 해석 문제 발생 여지 있음) -> 보통 __빅 엔디안__(__네트워크 바이트 정렬__) 사용

 * 바이트 정렬을 위한 함수 존재
  * __hton*()함수__ : 호스트 바이트 정렬(시스템 고유 바이트 정렬 방식) -> 네트워크 바이트 정렬 변환 값 반환
  * __ntoh*()함수__ : 네트워크 바이트 정렬로 저장된 값 -> 호스트 바이트 정렬 변환 값 반환
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/0b08b5af-3d45-40b0-9952-c045dc834efd)
