#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int getHeight();

int main(void){
	int n = getHeight();
	
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
	do {
		printf("height: ");
		scanf("%d", &n);
	}
	while (n>8 || n < 1);
	return n;
}	
