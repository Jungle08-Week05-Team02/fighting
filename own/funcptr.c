#include <stdio.h>

// 덧셈 함수
int add(int a, int b) {
    return a + b;
}

// 뺄셈 함수
int subtract(int a, int b) {
    return a - b;
}

int main() {
    // 함수 포인터 선언: int형 반환, 두 개의 int 매개변수
    int (*operation)(int, int);

    int num1 = 10, num2 = 5;
    char op;

    printf("연산자 선택 (+ 또는 -): ");
    scanf(" %c", &op);

    // 사용자 입력에 따라 어떤 함수를 호출할지 결정
    if (op == '+') {
        operation = add;
    } else if (op == '-') {
        operation = subtract;
    } else {
        printf("잘못된 연산자입니다.\n");
        return 1;
    }

    // 함수 포인터를 통해 선택된 함수 호출
    int result = operation(num1, num2);
    printf("결과: %d\n", result);

    return 0;
}








// 프로그램 실행 후, 터미널에서 echo $? 명령어를 입력하면 마지막으로 실행한 프로그램의 종료 코드를 확인할 수 있음 

// 0: 일반적으로 정상 종료를 의미합니다.

// 양의 정수(1 이상): 정상 종료이지만, 실행 중에 특별한 상황(예: 경고, 다른 인자나 옵션이 있음 등)을 나타내기 위해 사용될 수 있습니다.

// 음의 정수(-1, -2 이하): 에러가 발생했음을 나타내며, 음수 값은 구체적인 에러 종류를 표현하는 데 사용될 수 있습니다.