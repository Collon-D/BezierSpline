# Windows API 공부

### Device Context(DC)란?
WindowsAPI에서 출력에 피룡한 모든 정보를 가지고 있는 구조체.

윈도우는 기본적으로 세 가지 동적 연결 라이브러리(Dynamic Linked Library)로 구성됨.
- Kernel : 메모리를 관리, 프로그램 실행
- User   : 유저 인터페이스(UI)와 윈도우 관리
- GDI    : Graphic Device Interface의 약자, 화면 처리 및 그래픽 등 모든 출력 장치 제어

WindowsAPI의 특징 중 하나는 "디바이스에 비의존적".
이를 가능하게 하는 것이 GDI와 디바이스 드라이버 덕분이다.

GDI는 모니터, 프린터와 같은 모든 출력 장치를 제어하는 인터페이스
이렇게 출력 장치를 제어하고, 그 곳에 출력하는 것을 GDI 오브젝트라고 한다.
펜, 브러시, 비트맵, 폰트 등 화면에 출력하는 요소를 뜻함.
이런 GDI 오브젝트를 모아놓은 곳이 <b>Device Context</b>

### Device Context가 필요한 이유?
화면에 선 하나를 그리기 위해서 필요한 것들:
- 선의 시작점 위치
- 선의 끝점 위치
- 선의 형태(실선, 점선 등)
- 선의 색깔
- 선의 굵기
- 선을 그리는 모드(ROP mode)

단순한 선을 하나 그리는 데에 많은 정보가 필요함.
하지만 DC를 사용한 실제 API 코드는 <b>LineTo(hdc, X, Y);</b>
선이 그어질 위치만 알려주면, 그 외 정보들은 DC에 저장된 정보를 기반으로 자동 처리가 가능

또한 여러 개의 윈도우를 DC를 통해 운영체제가 인지하여 처리할 수 있음.
DC는 다른 프로그램의 윈도우끼리 출력 결과가 서로 방해하지 않도록 완충하는 역할도 가짐.

### 윈도우 프로시저
메시지 처리 전용 함수인 WndProc 함수
HDC는 Handle Device Context의 약자.

WM_LBUTTONDOWN
왼쪽 마우스가 눌렸을 때 발생하는 메시지
GetDC(hWnd) 함수를 통해 해당 윈도우의 DC를 얻을 수 있음. 
화면 출력을 마치고 나면 ReleaseDC를 통해 DC를 반환해야 함.
마치 new와 delete의 관계. 이는 메모리 낭비를 위함.
여기서 TextOut을 통해 문자열을 출력하고 화면 크기를 변경하면 문자열이 지워짐.

WM_PAINT
WM_PAINT 메시지는 발생하는 시점이 여러 개 있음.
- 프로그램이 실행되는 시점

### BeginPaint() vs GetDC()
BeginPaint 함수는 WM_PAINT 메시지에서만 사용하는 함수.
BeginPaint는 윈도우의 Clipping Region을 자동으로 파악하는 특징을 가짐.
Clipping Region이란, 클라이언트 영역의 특정 부분에 그리기를 한정하는 영역을 의미

윈도우가 생성되거나, 움직이거나, 사이즈가 바뀌거나, 스크롤 되는 등 윈도우의 화면 상 변화하는 부분을 Clipping Region이라고 합니다.

GetDC 함수는 WM_PAINT 외에 메시지에서 출력을 하기 위해 해당 클라이언트 영역의 DC를 얻는 함수.
이는 일시적인 출력 방법으로 그 이후의 변화는 책임지지 않음.

결과적으로 BeginPaint는 정적 출력, GetDC는 동적 출력을 하기 위함.
두 함수 모두 사용 후 메모리 반환을 위한 EndPaint, ReleaseDC를 반드시 사용해야 함.

### 긴 문자열 출력하기
DrawText

### 키보드 입력하기
WindowsAPI의 장점 중 하나는 멀티 태스킹 환경을 지원하는 것
하나의 프로그램이 입력을 받기 위해 대기 -> 시스템이 멈추면 안됨.
입력을 기다린다고 다른 것을 못하면 멀티 태스킹이 아님.

따라서 입력이 들어오면 포커스(입력 초점)을 가진 프로그램에 키보드 메시지를 보내게 되고,
프로그램은 키보드 메시지를 받아 입력 처리. 
즉, 포커스를 가진 컨트롤만 키보드 입력이 가능하고, 이와 관련한 메시지도 포커스를 가진 컨트롤에게만 전달

- 포커스 : 입력 초점
- 컨트롤 : 인터페이스를 통해 사용자로부터 명령과 입력을 받아들이고 출력 결과를 보여주는 과정에서 입출력 도구

문자를 입력할 때, 확인해야 하는 함수는 TranslateMessage 함수(메시지 루프)
사용자가 키보드로 입력을 하면, WM_KEYDOWN 메시지 발생

### InvalidateRect 함수와 무효 영역(Invalid Region)
다른 응용 프로그램에 의해 일부 가려져 있는 부분을 무효 영역이라고 함.
InvalidateRect or InvalidateRgn 함수를 사용해 윈도우의 작업 영역을 무효화하여 운영체제로
하여금 WM_PAINT 메시지를 해당 윈도우로 보내도록 하는 것

### 마우스 입력하기
마우스 입력 시 발생하는 메시지
- WM_XBUTTONDOWN   : 눌렀을 때 발생
- WM_XBUTTONUP     : 놓았을 때 발생
- WM_XBUTTONDBLCLK : 더블 클릭
- X 자리에는 L, R, M 각각 왼쪽, 오른쪽, 휠

### 콜백 함수(Callback Function)
일반적인 API 함수 -> 운영체제가 제공하는 함수를 응용 프로그램이 필요할 때 호출해서 사용

콜백 함수 -> 응용 프로그램이 제공하는 함수 중에 운영체제가 필요한 함수가 있으면 호출하는 것

### 작업 영역(Client Area)
작업 영역이란 윈도우가 차지하고 있는 작업을 하고 있는 영역
작업 영역을 얻기 위한 함수 - GetClientRect

BOOL GetClientRect(HWND hWnd, LPRECT lpRect);
- WM_CREATE : 프로그램이 실행될 때 최초 발생하는 메시지
- WM_SIZE   : 윈도우의 크기가 변화하면 발생하는 메시지
- WM_PAINT  : 화면에 변화가 생겼거나 무효 영역(InvalidateRect 함수 등)이 생기면 발생하는 메시지

### GDI 오브젝트
GDI 오브젝트를 만드는 원리
1. 핸들 선언
1. GDI 오브젝트 생성
1. Old 오브젝트에 이전에 사용하던 핸들 저장
1. GDI 오브젝트 사용
1. 선택 해제
1. 메모리에서 삭제
 


