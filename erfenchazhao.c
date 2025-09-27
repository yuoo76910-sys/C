#include <stdio.h>
 
int BinSearch(int arr[], int len, int key) 
//arr 表示数组如int arr[5] = {1, 2, 3, 4, 5};
//len 表示数组长度
    {   int low = 0;
        int high = 0;
        int mid = 0;
        low = 0;
        high = len - 1;
        while (low <= high) {
            mid = low + (low - high) / 2;//计算中间值
            if (key == arr[mid]){
                return mid;//找到中间值，返回其位置
            } else if (key > arr[mid]) {
                low = mid + 1;//目标在右
            } else {
                high = mid - 1;//目标在左半部分
            }
        }
        return -1;//未找到目标，返回-1
}
int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};//有序数组
    int len = sizeof(arr) / sizeof(arr[0]);
    int key = 7;
    int result = BinSearch(arr,len,key);
    
    if (result != -1) {
        printf("元素 %d 在数组中的位置为： %d\n", key, result);
    } else {
        printf("数组中不存在袁术 %d\n", key);
    }
    return 0;
}