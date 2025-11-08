#include <stdio.h>

int main() {
    int n, m, i, j, safe=1;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int max[n][m], alloc[n][m], avail[m], need[n][m], finish[n];

    printf("Enter Allocation Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&alloc[i][j]);

    printf("Enter Maximum Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&max[i][j]);

    printf("Enter Available Resources:\n");
    for(i=0;i<m;i++)
        scanf("%d",&avail[i]);

    // calculate Need matrix
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            need[i][j] = max[i][j] - alloc[i][j];

    for(i=0;i<n;i++) finish[i]=0;

    printf("\nSafe sequence: ");
    int count=0;
    while(count<n) {
        int found=0;
        for(i=0;i<n;i++) {
            if(!finish[i]) {
                int flag=1;
                for(j=0;j<m;j++)
                    if(need[i][j]>avail[j]) { flag=0; break; }
                if(flag) {
                    for(j=0;j<m;j++) avail[j]+=alloc[i][j];
                    printf("P%d ",i);
                    finish[i]=1;
                    found=1;
                    count++;
                }
            }
        }
        if(!found) { safe=0; break; }
    }

    if(safe) printf("\nSystem is in a Safe State.\n");
    else printf("\nSystem is in an Unsafe State (Deadlock possible).\n");

    return 0;
}
