#include <stdio.h>

// 결과를 출력하는 함수
void printResultDirect(int result) {
    printf("직접 호출: 결과는 %d입니다.\n", result);
}

// 정수를 받아 10을 더한 후, 내부에서 직접 결과를 출력하는 함수
void processWithoutCallback(int number) {
    int result = number + 10;
    printResultDirect(result);  // 직접 호출
}

int main() {
    int value = 5;
    processWithoutCallback(value);
    return 0;
}
