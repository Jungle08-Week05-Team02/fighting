#include <stdio.h>

void func(int *arr, int n){
    for (int i = 0; i < n; i++){
        arr[i]++;
    }
    return;
}

int main() {
    // int arr[] = {10, 20, 30, 40, 50};

    // // 배열 인덱스를 사용한 접근
    // printf("arr[2] = %d\n", arr[2]);

    // // 포인터 산술을 사용한 접근
    // *(arr + 2) = 2;
    // printf("*(arr+2) = %d\n", arr[2]);

    // return 1;
    int arr[5] = {1,2,3,4,5};
    func(arr,5);

    for (int i = 0; i < 5; i++){
        printf("%d ",arr[i]);
        
    }
    return 0;

}