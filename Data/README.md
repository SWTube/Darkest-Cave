# Darkest-Cave Data texture making

# Compair Model Paramter 

## 모델 리스트

 1. VGG19 (Block1_conv1 ~ Block5_conv1, Block1_conv2)
![Details on the VGG19 architecture. For each layer, number of filters,... |  Download Table](https://www.researchgate.net/profile/Ferran-Pares/publication/314237915/figure/tbl1/AS:667100565745668@1536060577444/Details-on-the-VGG19-architecture-For-each-layer-number-of-filters-parameters-and.png)

 2. AdaIN (VGG19, Relu 4-1)

|  Operation|Filter|Parameters|Activations|
|:--:|:--:|:--:|:--:|
| Conv2d|64| 1.7K| 3.2M |
| ReflectionPad2d|
| Conv2d|64| 36K| 3.2M |
| **ReLu 1-1**|
| Conv2d|64| 36K| 3.2M |
| **ReLu 1-2**|
| MaxPool2d|
| ReflectionPad2d|

### ... until Relu 4-1

|  Operation|Filter|Parameters|Activations|
|:--:|:--:|:--:|:--:|
| ReflectionPad2d|
| Conv2d|256| 600K| 802K |
| **ReLu 3-4**|
| Conv2d|512| 2.3M| 100K |
| **ReLu 4-1**|
---
 3. Inception-V3

|  Operation|Kernel size|Stride|Feature maps|Padding|Nonlinearity|
|:--:|:--:|:--:|:--:|:--:|:--:|
| Convolution |9| 1 | 32 |SAME	|ReLU	|
| Convolution |3| 2 | 64 |SAME	|ReLU	|
| Convolution |3| 2 | 128|SAME	|ReLU	|
| Residual block|  |  | 128 |	|	|
| Residual block|  |  | 128 |	|	|
| Residual block|  |  | 128 |	|	|
| Residual block|  |  | 128 |	|	|
| Residual block|  |  | 128 |	|	|
| Upsampling|  |  | 64|	|	|
| Upsampling|  |  | 32|	|	|
| Convolution|9| 1 | 3|SAME	|Sigmoid|
| **Residual block**| **C feature maps** |
| Convolution |3| 1 | C|SAME	|ReLU	|
| Convolution |3| 1 | C|SAME	|Linear|
| **Upsampling**| **C feature maps** |
| Convolution |3| 1 | C|SAME	|Linear|

# 1. 커밋 내역 공유

## 1.1 절차적 맵생성

### 1.1.1 BSP 알고리즘
```
CPP로 간단하게 구현해보았음
일단 이걸로 계속 가보면서 GUI를 입힐 예정
```
### 1.1.2 셀룰러 오토마타
```
1. 기계학습과 조금 비슷한 것 같음
2. 잘 짜여진 코드인 것 같음
```

## DAG 그래프를 활용한 2D 던전 생성 (김영송)
### 2d platformer 절차적 생성 위주 DAG 그래프 바탕의 맵을 만드는 방법 선택
### 랜덤 dag그래프는 함수로 구현 완료
### 우선 빈 방으로 맵 연결, 추후 미로 알고리즘 또는 방 형식 추가 예정

## 1.2 베이스 모델
### 1.2.1 colabcode 추가
```
1. 다소 속도가 느린 것 같음
2. 매번 Extension을 설치해줘야 하는 불편함
3. 매번 작업 영역 설정해줘야 하는 불편함
4. Colab GPU와 구글 드라이브가 연동되는 장점이 있음
```
### 1.2.2 Base Model 오타 수정
```
 8번째 셀에서 except 들여쓰기 오류 발생
```
### 1.2.3 이미지 처리
### 1.2.4 필요없는 셀들 정리

### 1.2.5 기존 VGG모델에서 EfficientNet 변경안
```
 vgg 모델에서 efficientB7 모델로 변환해봄. 근데 Content와 Style의 레이어를 적절히 선택하지 못 했는지 스타일 전이가 잘 안 됐음(뿌옇게 나옴). 추후 수정하겠음.
```
## 이미지 Pool 증대 (최윤영)
### 이미지 원본의 최대 2배의 해상도까지만
### 한 폴더에 한 개체 이미지만 따로 분류

## 스타일 크롤러 (최인열, 윤동주)
### 예외처리, 오류 처리 진행 중

## AdaIN 모델 (노혜능, 최인열)
### 자동화 완료 (주 모델이 될 수도 있을 듯)

## Magenta(MoblieNet) 모델 (이준혁, 최인열)
### 기괴한 면에서 보면 괜찮아 보이지만 원본 이미지의 틀을 해치는 경향이 있음

## efficientB7 모델 (홍성은, 윤동주, 최인열)
### 오류 해결 중
### 뒷 배경 제거하면 흰 색으로만 나오는 오류
### 뿌옇게 이미지 변환되는 오류

## 1.3 Git 강의
### 1.3.1 1주차 강의
```
1. SSH 원격 접속 설정 방법, 파일 상태
2. branch, clone, pull push 기초
3. 효과적인 git log 조회 방법
```
### 1.3.2 2주차 강의
```
1. 파일 삭제, gitignore, 브랜치 종류
2. 브랜치 분기 및 병합
```
