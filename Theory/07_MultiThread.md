## MultiThread
### 2023. 10. 10 ~ 11 수업  
  
#### 기초  
* 앞서 봤던 예제들의 문제점 -> 이유는? : 
* 1) __다중 처리 문제__ : 두 개 이상의 클라에 대한 서비스 작업 불가
* 2) __교착 상태(DeadLock)__ : 일어나질 않을 사건에 대해 두 프로세스가 기다리는 상태
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/825ad228-c91c-4048-b44d-160e4870d6fb)  
  
  
#### 1에 대한 해결점과 각각의 장/단점  
* 1) 서버가 하나의 클라와 통신하는 시간을 짧게 한다
  * = 매번 데이터를 보내기 전에 서버에 접속하고, 주고받은 후에 곧 바로 접속을 끊는다
  * 장점 : 구현이 가장 쉬움, 서버 시스템 자원 적게 소모
  * 단점 : 대용량 데이터 파일 전송에는 적합하지 않음, 서버에 접속하려는 클라가 많으면 접속 실패 발생률 UP (처리 지연률 증가)  
  
* 2) 서버에 접속한 클라를 스레드를 이용해 독립적으로 처리
  * 장점 : 3보다는 비교적 쉽게 구현 가능
  * 단점 : 접속한 클라 수에 비례해 스레드를 생성함 -> 시스템 자원 소모가 큼  
  
* 3) 소켓 입출력 모델 사용
  * 장점 : 하나/소수의 스레드 사용으로 다수 클라를 처리 가능함 -> 2보단 비교적 시스템 자원 소모 작음
  * 단점 : 구현의 어려움 존재  
  
  
#### 2에 대한 해결점과 각각의 장/단점  
* 1) 데이터 송/수신 부분을 잘 설계하고 교착 상태가 발생하지 않도록 한다
  * 장점 : 특별한 기법을 도입하지 않고 곧바로 구현 가능
  * 단점 : 데이터 송수신 패턴에 따라 교착 상태가 발생할 수도 -> 모든 경우에 적용 불가능함  
  
* 2) 소켓에 timeout 옵션을 적용해 send(), recv() 함수 호출 시 일정 시간이 지나면 리턴하도록 함
  * 장점 : 비교적 구현이 간단함
  * 단점 : 3에 비해 성능이 떨어짐  
  
* 3) 넌블로킹(Non-blocking) 소켓 사용
  * 장점 : 교착상태 막기
  * 단점 : 구현이 복잡, 시스템 자원(CPU 시간)을 불필요하게 낭비할 가능성 있음  
  
* 4) 소켓 입출력 모델을 사용
  * 장점 : 블로킹과 넌블로킹 소켓의 단점 보완, 교착상태 막기 가능
  * 단점 : 1보단 구현이 어려우나, 2~3보다는 쉽고 일관성 있게 구현이 가능  
  
  
#### 기본 개념  
* 윈도우의 프로세스  
  * __프로세스(Process)__ : 메모리를 비롯한 각종 리소스를 담고 있는 컨테이너(container), 정적인 개념
  * __스레드(thread)__ : 실제 CPU 시간을 할당받아 수행되는 실행 단위, 동적인 개념
  * 스레드가 프로세스에 담겨있는 리소스를 가지고 필요한 작업을 수행함
  * 하나의 윈도우 애플리케이션 실행을 위해서 최소 하나 이상의 스레드가 필요하다 -> main()/WinMain()에서 시작되는 스레드가 주 스레드(primary thread)
  * 병렬적으로 수행해야 할 경우 추가적인 스레드를 생성하고 해당 작업을 수행하게 하면 된다 -> 각 스레드의 최종 실행 상태를 저장하고 복원하는 작업을 반복 (실행 상태 : CPU레지스터 값과 스택을 비롯한 각종 정보 의미) -> 이 작업을 __컨텍스트 전환(Context Switch)__
  * 위 작업을 통해 우리의 각 스레드는 다른 스레드의 존재와 무관히 자신의 상태를 유지하며 실행 가능
  * 아래 링크를 참고하도록 하자.  
  * [여러스레드작동사진](https://github.com/MiyeongEom/NetworkGameProgramming/blob/main/Theory/07_Thread%20%EC%8B%A4%ED%96%89%20%EC%82%AC%EC%A7%84%EA%B3%BC%20%EC%84%A4%EB%AA%85.md)  
  
  
#### 스레드 생성
* 주 스레드 이외의 스레드 f()를 생성하면 다음과 같은 정보를 운영체제에게 제공해야 한다
  * __f()함수의 시작 주소__ : 소스코드수준에서는 f() 함수의 이름이 곧 시작 주소 -> 스레드 실행 시작점이 되는 함수를 __스레드 함수(thread function)__ 이라 함
  * __f() 함수 실행 시 사용할 스택 영역 크기__ : 스레드 두 개를 생성하면, 서로 다른 메모리 영역에 두 스레드를 위한 스택이 각각 할당된다  
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/c59ee92f-b8eb-464c-b334-d6b1497522eb)  
  
* 윈도우에서의 스레드 생성 : CreateThread()함수 사용, 스레드 핸들을 리턴함.  
  
```C
HANDLE CreateThread(
  LPSECURITY_ATTRIBUTES lpThreadAttributes,   
  // SECURITY_ATTRIBUTES 구조체 변수의 주소값 (핸들 상속과 보안 디스크립터 정보 전달 용도)
  SIZE_T dwStackSize,        // 새로 생성할 스레드에 할당되는 스택 크기 (디폴드 1MB)
  LPTHREAD_START_ROUTINE lpStartAddress,        // 스레드 함수의 시작 주소 
  LPVOID lpParameter,         // 스레드 함수에 전달할 임자 (32비트 크기의 값 하나, 없다면 NULL)
  DWORD dwCreationFalgs,      
  // 스레드 생성을 제어하는 값 (0  또는 CREATE_SUSPENDED, 전자 즉시 실행 후자는 ResumeThread( )함수 호출 후 실행)
  LPDWORD lpThreadID          //  DWORD형 변수 주소값
); // 성공: 스레드 핸들, 실패:NULL
```
  
  
#### 스레드 종료  
* 1) 스레드 함수가 리턴
* 2) 스레드 함수 내에서 ExitThread() 호출
* 3) TerminateThread()함수 호출
* 4) 주 스레드가 종료하면 모든 스레드가 종료됨
* 일반적으로 1 / 2에 의해 스레드가 종료됨. 3은 극단적 경우, 4는 주 스레드의 특성
* 3의 극단적인 경우 : 외부에서 스레드를 종료하고자 하는 경우  
  
```C
void ExitThread(
  DWORD dwExitCod   // 종료코드
);

BOOL TerminateThread(
  HANDLE hThread,   // 종료할 스레드를 가리키는 핸들
  DWORD dwExitCode  // 종료코드
); // 성공:0이 아닌 값, 실패:0
```
  
  
#### 스레드 조작 함수  
* 스레드는 윈도우 애플리케이션 실행 단위 -> 관련 작업을 윈도우 API수준에서 지원함  
* 1. 우선순위 변경
  * 각 스레드에 CPU 시간을 적절히 분배하기 위해 스레드 스케줄링(CPU 스케줄링)이 존재
  * 스케줄링은 우선 순위에 기반한 것으로 우선 순위가 높을 수록 우선적으로 CPU 시간을 할당함
  * 우선 순위 결정 요소: __프로세스 우선 순위(우선 순위 클래스), 스레드 우선 순위 (우선 순위 레벨)__
  * 우선 순위 클래스와 우선 순위 레벨을 결합하면 스레드의 기초 우선 순위가 결정된다. (같은 순위 스레드가 여러 개면 교대로 CPU 시간을 할당함)
  * 우선 순위가 높은 스레드가 계속 CPU 시간을 요구하는 경우 -> 낮은 스레드들은 CPU 시간을 할당 받지 못함 -> 기아 상태 : 윈도우는 동적으로 우선 순위를 상황에 따라 바꿈
  * 멀티스레드를 사용할 때는 주로 우선 순위 레벨을 변경함.  
  
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/ff7f47c7-68e3-4f5e-a2c9-15d49bbd343d)  
  
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/532f1515-f4f3-4b11-a8b4-88f9188f04aa)  
  
![image](https://github.com/MiyeongEom/NetworkGameProgramming/assets/112458035/0c6d67e0-528a-49db-9eba-bf1f4c7bafff)  
  
```C
OOL SetThreadPriority(
  HANDLE hThread, // 스레드 핸들
  int nPriority // 우선 순위 레벨 값
); // 성공: 0이 아닌 값, 실패 : 0

int GetThreadPriority(
  HANDLE hThread // 스레드 핸들
); // 성공: 우선 순위 레벨 값, 실패: THREAD_PRIORITY_ERROR_RETURN
```
  
* 2. 스레드 종료 기다리기  
  * 스레드 생성시 CPU시간을 사용하기 위해 다른 스레드와 경쟁하며 독립적으로 실행됨
  * 때로는 스레드가 작업을 완료하고 종료했는지의 여부를 확인해야 할 상황이 존재
  * 특정 스레드 종료 확인은 WaitForSingleObject, 다수의 스레드 확인은 WaitForMultipleObjects.  
  
```C
DWORD WaitForSingleObject(
  HANDLE hHandle,        // 종료 기다릴 스레드 핸들
  DWORD dwMilliseconds   // 대기 시간으로 밀리초 사용, INFINITE값을 사용시 스레드 종료 때까지 무한 대기
); // 성공:WAIT_OBJECT_0 또는 WAIT_TIMEOUT, 실패 : WAIT_FAILED

DWORD WiatForMultipleObjects(
  DWORD nCount,        // 스레드 핸들을 모두 배열에 저장하는데 그 배열 원소 개수, 최대 MAXIMUM_WAIT_OBJECTS(=64)
  const HANDLE* lpHandles,    // 배열의 시작 주소
  BOOL bWaitAll,       // TRUE : 모든 스레드 종료 때까지 대기, FALSE : 한 스레드가 종료하는 즉시 리턴
  DWORD dwMilliseconds
);
성공 : WAIT_OBJECT_0 ~ WAIT_OBJECT_0 + nCount-1 또는 WAIT_TIMEOUT, 실패 : WAIT_FAILED
```
  
* 3. 실행 중지와 재실행  
  * 스레드 실행을 일시 중지하고, 재실행 할 수 있다.
  * 중지횟수가 0보다 크면 스레드 실행이 중지된다.
  * Sleep() : 스레드가 실행을 멈추고 일정 시간 대기하도록 함. 지정한 시간이 지나야 깨어남.  
  
```C
DWORD SuspendThread(
  HANDLE hThread // 스레드 핸들
); // 성공: 중지 횟수 + 1, 실패:-1

DWORD ResumeThread(
  HANDLE hThread // 스레드 핸들
); // 성공: 중지 횟수 - 1, 실패:-1

void Sleep(
  DWORD dwMilliseconds // 밀리초(ms)
);
```
