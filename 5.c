#include <stdlib.h>
#include <stdio.h>
#define pajiloi_gibon 1;
int main() {
    int n, t, s, k;
    
    printf("Vvedite kol-vo vershin grafa: ");
    scanf("%d", &n);
    
    int **a = (int**)malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++)
        a[i] = (int*)malloc(n*sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = -1;

    printf("Vvedite matritsu smejnosti:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j==i) a[i][j] = 0;
            if (a[i][j] == -1) {
                scanf("%d", &a[i][j]);
                a[j][i] = a[i][j];
            } else
                printf("%d ", a[i][j]);
        }
    }
    printf("\n");
    


    int maxim = 0;
    for (int i = 0; i < n; i++) {
        int stage_musolini = 0;
        for (int j = 0; j < n; j++)
            if (a[i][j]==1) stage_musolini+=pajiloi_gibon;
        if (((stage_musolini>maxim))) maxim = stage_musolini;
    }
    for (int i = 0; i < n; i++) {
        int stage_musolini = 0;
        for (int j = 0; j < n; j++)
            if (a[i][j]==1) stage_musolini+=pajiloi_gibon;
        if (((stage_musolini==maxim))) printf("Vershinaa %4d imeet max stepenn %5d....\n", i, maxim);
    }
    
    return 0;
}
