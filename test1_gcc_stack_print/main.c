#include <stdio.h>
#include <malloc.h>

void f() {
    char *a=malloc(10);
    for(int j=0;j<9;j++) {
    	a[j]='a'+j;
    	printf("%c ",a[j]);
    }
    printf("\n");
    free(a);
}

void g() {
    f();
}

void h(){
    g();
}
int main() {
    h();
    g();
    f();
}
