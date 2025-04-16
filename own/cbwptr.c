#include <stdio.h>

// 콜백 함수: 정수 값을 받아 출력하는 함수
void printResult(int result) {
    printf("콜백 사용: 결과는 %d입니다.\n", result);
}

// processWithCallback 함수는 정수와 콜백 함수를 인자로 받습니다.
// 여기서 콜백 함수의 타입은 "반환형이 void이고, int 타입 인자를 받는 함수의 포인터"입니다.
void processWithCallback(int number, void (*callback)(int)) {
    int result = number + 10;  // number에 10을 더한 결과를 계산합니다.
    callback(result);          // 인자로 전달된 함수 포인터를 통해 콜백 함수를 호출합니다.
}

int main() {
    int value = 5;
    // processWithCallback 함수 호출시, 값과 함께 printResult 함수의 이름(주소)를 인자로 전달합니다.
    processWithCallback(value, printResult);
    return 0;
}
