#include <stdio.h>
 
int main(){
    int arr[10];
    int len = sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i < len;i++){
        scanf("%d",arr + i);
    }

    int temp;
    for(int i = 0;i < len;i++){
        printf("===第%d轮排序开始===\n\t",i+1);
        for (int j = 0;j < len - 1 - i; j++){
            printf ("比较arr[%d]=%d和arr[%d]=%d:\n\t",j,arr[j],j+1,arr[j+1]);
            if(arr[j] > arr[j + 1]){
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("排序好的数组为\n");
    for(int i = 0; i < len; i++){
        printf("%d",arr[i]);
    }
    return 0;
}