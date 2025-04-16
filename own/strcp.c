#include <stdio.h>
#include <stdlib.h>

// int main(void){

//     char *s;
//     scanf("%s", s);

//     char *t = s;

//     s[0] = 'j';

//     printf("s: %p\n", s);
//     printf("t: %p\n", t);

// }







int main(void){
    char *s = malloc(100 *sizeof(char));
    scanf("%99s", s);

    char *t = malloc(sizeof(s));

    for (int i = 0; i < sizeof(s); i++){
        t[i] = s[i];
    }

    t[0] = 'j';

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(s);
    free(t);

}








// #include <string.h>

// 충분한 크기의 버퍼 할당
// char *s = malloc(100 * sizeof(char));

//폭 제한을 적용하여 안전하게 입력받기
//scanf("%99s", s);
//%s 앞의 숫자 99는 입력받을 최대 문자 수를 지정합니다.

// 문자열 길이에 기반하여 t에 메모리 할당


// 동적 할당된 메모리 해제

