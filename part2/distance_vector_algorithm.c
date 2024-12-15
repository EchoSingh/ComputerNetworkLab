#include <stdio.h>
#define INF 999
int n,g[10][10],d[10][10],via[10][10];
void input_routing_table(){
    printf("Enter the routing table (%d for no direct connection)",INF);
    printf("\n  ");
    for(int i=0;i<n;i++){
        printf("%c ",'a'+i);
    }
    printf("\n");
    for(int i=0;i<n;i++){
        printf("%c ",'a'+i);
        for(int j=0;j<n;j++){
            scanf("%d",&g[i][j]);
            d[i][j]=(g[i][j]!=INF)?1:0;
        }
    }
}
void computing_routing_tables(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            via[i][j]=i;
        }
    }
    for(int intermediate=0;intermediate<n;intermediate++){
        for(int source=0;source<n;source++){
            for(int destination=0;destination<n;destination++){
                if(g[source][intermediate]+g[intermediate][destination]<g[source][destination]){
                    g[source][destination]=g[source][intermediate]+g[intermediate][destination];
                    via[source][destination]=intermediate;
                }
            }
        }
    }
}

void display_routing_table(){
    for(int router=0;router<n;router++){
        printf("Routing table for router %c:\n",'a'+router);
        printf("Destination\tcost\tVia\n");
        for(int Destination=0;Destination<n;Destination++){
            printf("%c\t\t%d\t\t%c\n",'a'+Destination,g[router][Destination],'a'+via[router][Destination]);
        }
    }
}
int main(){
    printf("Enter the number of nodes:\n");
    scanf("%d",&n);
    input_routing_table();
    computing_routing_tables();
    display_routing_table();
    return 0;
}
