현재까지 BSP 진행상황
 - 트리 구조를 이용하여 맵을 나누고 각 노드를 이어주는 함수 개발 완료
 - 함수 하나로 맵을 만들 수 있음
 - Tiny Keep 알고리즘 비슷하게 만들어보기 위해 랜덤으로 방을 선택하여 직사각형 느낌의 맵을 좀 없앴음
 - 방에 조금 소실을 주어 맵 디자인에 변화를 줘 봤음.

앞으로 만들어야 할 것
 - Input 간결화 - 어느정도 완료(원하는 방 개수를 입력하면 그에 맞게 방이 생성 됨), 게임 제작 팀에서 원하는 구체적인 부분을 충족하기 위해선 개선이 필요함
 - 방 크기 사이즈에 대한 오류 문제 해결 - 해결함. 단 테스트를 통해 방의 비율 조정이 필요 - 비율을 40~60%로 조정하면 오류가 거의 발생하지 않음 단점은 복잡도가 좀 줄어듬.
 - 부모 노드들의 연결 함수 생성 - 완료, 다만 버그가 좀 있어서 이 문제를 해결해야 함
 - 방 모양 현재는 직사각형인데 모양 다양화
 - GUI(MFC로 얼추 해봤는데 너무 별로임 개선 필요, 그래픽스 팀에서 만들 툴로 극복하지 않을까라는 약간의 기대)

현재까지 진행상황 모습
![image](https://user-images.githubusercontent.com/37788658/127624893-4ac5cb9c-6b1c-444b-bdb8-6f7548ffe5fc.png)
![image](https://user-images.githubusercontent.com/37788658/129198350-5e2e41a5-61eb-4100-bbbb-5af4a8c5105b.png)
아래쪽은 함수를 일일이 사용한 것이 아닌 하나의 함수로 맵을 생성한 모습. 다만 Leaf 노드들끼리 연결하는 함수까지는 만들었으나 그 위의 부모 노드끼리 연결하는 함수를 만들어야 
![image](https://user-images.githubusercontent.com/37788658/129476793-b6ce72d1-c1c2-4244-bba3-edf879ab343c.png)
경로 자동생성
![image](https://user-images.githubusercontent.com/37788658/130612650-a29ef8e6-3b08-40bb-876f-5d602a8e9eef.png)
걍로 생성 복잡화
![image](https://user-images.githubusercontent.com/37788658/131242576-6bba715d-15f6-4e1d-85a7-d83bea92079e.png)

