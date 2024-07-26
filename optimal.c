#include <stdio.h>
#include <limits.h>

#define MAX_PAGES 20
#define FRAMESIZE 3

int fr[FRAMESIZE];
int lg[FRAMESIZE];

void display() {
    for (int i = 0; i < FRAMESIZE; i++)
        printf("%d\t", fr[i]);
    printf("\n");
}

int main() {
    int i, j, n, m;
    int page[MAX_PAGES];
    int max, found, index, pf = 0;

    printf("Enter length of the reference string: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &page[i]);

    printf("Enter number of frames: ");
    scanf("%d", &m);

    for (i = 0; i < m; i++)
        fr[i] = -1;
    
    pf = m; // Initial count of page faults is equal to number of frames

    for (j = 0; j < n; j++) {
        int flag1 = 0;
        int flag2 = 0;

        // Check if page is already in frames
        for (i = 0; i < m; i++) {
            if (fr[i] == page[j]) {
                flag1 = 1;
                flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            // If frame has an empty slot, use it
            for (i = 0; i < m; i++) {
                if (fr[i] == -1) {
                    fr[i] = page[j];
                    flag2 = 1;
                    break;
                }
            }

            if (flag2 == 0) {
                // Find the page that will not be used for the longest time
                for (i = 0; i < m; i++)
                    lg[i] = INT_MAX;
                
                for (i = 0; i < m; i++) {
                    for (int k = j + 1; k < n; k++) {
                        if (fr[i] == page[k]) {
                            lg[i] = k - j;
                            break;
                        }
                    }
                }

                found = 0;
                for (i = 0; i < m; i++) {
                    if (lg[i] == INT_MAX) {
                        index = i;
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    max = lg[0];
                    index = 0;
                    for (i = 0; i < m; i++) {
                        if (lg[i] > max) {
                            max = lg[i];
                            index = i;
                        }
                    }
                }

                fr[index] = page[j];
                pf++;
            }
        }

        display();
    }

    printf("Number of page faults: %d\n", pf);
    printf("Page fault rate = %f%%\n", (float)pf / n * 100);
    return 0;
}

