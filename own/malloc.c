#include <stdio.h>
#include <stdlib.h>

// 가변길이 배열

// int main(void) {
//     int n;
//     printf("배열의 크기를 지정하세요.: ");
//     scanf("%d", &n);

//     // 동적할당?
//     int int_arr[n];

//     // Testing
//     for (int i = 0; i < n; i++) {
//             int_arr[i] = i * 10;
//     }
//     for (int i = 0; i < n; i++) {
//             printf("%d ", int_arr[i]);
//     }
//     printf("\n");
// }


// 가변길이 배열 malloc 사용 버전

// int main(void) {
//     int n;
//     printf("Enter the number of integers: ");
//     scanf("%d", &n);

//     // malloc
//     int *int_arr = malloc(sizeof(int) * n);

//     // Testing
//     for (int i = 0; i < n; i++) {
//             int_arr[i] = i * 10;
//     }
//     for (int i = 0; i < n; i++) {
//             printf("%d ", int_arr[i]);
//     }
//     printf("\n");
// }



// 지역 변수를 반환하는 함수 (잘못된 예)
// int* createValue() {
//     int local = 42;  // local 변수는 스택에 할당됨.
//     return &local;   // local 변수의 주소를 반환.
// }

// int main(void) {
//     int *p = createValue();  // createValue 함수 호출 후, 함수가 종료되면 함수 내부 변수 local은 사라짐.
//     이제 p는 더 이상 유효하지 않은 메모리를 가리키게 됩니다.
//     printf("p가 가리키는 값: %d\n", *p);  // undefined behavior, 즉 정의되지 않은 동작을 일으킴.
//     return 0;
// }


// malloc를 사용하여 메모리 반환
int* createValue() {
    int *mall = malloc(sizeof(int));  // mall은 힙의 메모리 블럭을 가리킴.
    *mall = 42;
    return mall;   // 힙에 할당한 주소를 반환.
}

int main(void) {
    int *p = createValue();  // createValue 함수 호출 후, 함수 내부 변수 local은 사라짐.
    //이제 p는 더 이상 유효하지 않은 메모리를 가리키게 됩니다.
    printf("p가 가리키는 값: %d\n", *p);  // undefined behavior, 즉 정의되지 않은 동작을 일으킴.
    return 0;
}






