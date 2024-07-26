#include <stdio.h>

#define FRAMESIZE 3

int fr[FRAMESIZE];

void display() {
    for (int i = 0; i < FRAMESIZE; i++)
        printf("%d\t", fr[i]);
    printf("\n");
}

int main() {
    int i, j;
    int page[12] = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2};
    int top = 0, flag1, flag2, pf = 0;
    int frsize = FRAMESIZE;

    // Initialize frame array
    for (i = 0; i < frsize; i++)
        fr[i] = -1;

    for (j = 0; j < 12; j++) {
        flag1 = 0;
        flag2 = 0;

        // Check if page is already in frames
        for (i = 0; i < frsize; i++) {
            if (fr[i] == page[j]) {
                flag1 = 1;
                flag2 = 1;
                break;
            }
        }

        if (flag2 == 0) {
            // Replace page using FIFO
            fr[top] = page[j];
            top++;
            pf++;
            if (top >= frsize)
                top = 0;
        }

        display();
    }

    printf("Number of page faults: %d\n", pf);
    return 0;
}

