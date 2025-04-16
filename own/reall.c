#include <stdlib.h>
#include <stdio.h>

int main(void) {
    // 1. 초기 메모리 할당 (예: 10개의 int를 위한 공간)
    int *arr = malloc(10 * sizeof(int));
    if (arr == NULL) {
        perror("초기 메모리 할당 실패");
        return 1;
    }
    
    // 예제: 초기 배열 초기화
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }
    
    // 2. 메모리 블록 크기 재조정 (예: 20개의 int를 위한 공간으로 확장)
    int *temp = realloc(arr, 20 * sizeof(int));
    if (temp == NULL) {
        // 새로운 메모리 할당이 실패하면, 원래의 메모리 블록은 여전히 유효함
        perror("메모리 재할당 실패");
        free(arr);   // 실패 시 기존 메모리는 반드시 해제
        return 1;
    }
    arr = temp;  // 재할당 성공 후, 포인터를 새 메모리 블록으로 갱신
    
    // 새로운 공간에 추가 데이터 저장
    for (int i = 10; i < 20; i++) {
        arr[i] = i;
    }
    
    // 결과 출력
    for (int i = 0; i < 20; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // 사용이 끝난 후에는 메모리 해제
    free(arr);
    return 0;
}
