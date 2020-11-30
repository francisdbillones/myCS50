#include <stdio.h>
#include <stdlib.h>

int getHeight();

int main(void){
	int n = getHeight();
	printf("%i\n", n);
	for (int line = 0; line < n; line++){
		for (int spaces = 0; spaces < n - line - 1; spaces++){
			printf(" ");
		}
		for (int hashes = 0; hashes < line + 1; hashes++){
			printf("#");
		}
		printf("\n");	
	}
}

int getHeight(){
	int n;
	printf("height: ");
	scanf("%d", &n);
	return n;
}	
