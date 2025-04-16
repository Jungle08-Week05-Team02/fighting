#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        printf("hello, %s\n", argv[0]);
    }
    else
    {
        printf("명령행 인자를 입력하세요!!!\n");
    }
}

// 자주 쓰이진 않음, 시작과 동시에 읽어야할 파일이나, 경로정보를 전달해야할 때 사용

//         for (int i = 0; i < n; i++){
//            printf("%s\n", argv[i]);
//        }

// int n;
// scanf("%d", &n);