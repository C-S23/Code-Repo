#include <stdio.h>

#define FRAMESIZE 3

int fr[FRAMESIZE];
int fs[FRAMESIZE];

void display() {
    for (int i = 0; i < FRAMESIZE; i++)
        printf("%d\t", fr[i]);
    printf("\n");
}

int main() {
    int i, j;
    int page[12] = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2};
    int flag1, flag2, pf = 0;
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

        if (flag1 == 0) {
            // If frame has an empty slot, use it
            for (i = 0; i < frsize; i++) {
                if (fr[i] == -1) {
                    fr[i] = page[j];
                    flag2 = 1;
                    break;
                }
            }

            if (flag2 == 0) {
                // Find least recently used page
                for (i = 0; i < frsize; i++)
                    fs[i] = 0;
                
                for (int k = j - 1, l = 1; l <= frsize - 1; l++, k--) {
                    for (i = 0; i < frsize; i++) {
                        if (fr[i] == page[k])
                            fs[i] = 1;
                    }
                }

                int index = 0;
                for (i = 0; i < frsize; i++) {
                    if (fs[i] == 0) {
                        index = i;
                        break;
                    }
                }
                fr[index] = page[j];
                pf++;
            }
        }

        display();
    }

    printf("Number of page faults: %d\n", pf + frsize);
    return 0;
}

