#include <stdio.h>
int main() {
    int i = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    for (i = 100; i < 1000; i++) {
        x = i % 10;
        y = (i / 10) % 10;
        z = (i / 100) % 10;
        int sum = x * x * x + y * y * y + z * z * z;
        if (i == sum) {
            printf("%d\n", i);
        }
    }
}