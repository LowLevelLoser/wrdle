#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "tc.h"
/*=========================================*/
int mainLoop(char*, char*);
/*=========================================*/

int main(){
	char str1[50];
	char str2[50];
	FILE *flptr;
	flptr = fopen("dictionary.txt", "r");
	srand( time(NULL) );
	
	
	if (flptr == NULL){
		printf("could not find dictionary.txt\n");
		return 1;
	}
	
	//line count
	int count = 0;
	char c;
	for(c = getc(flptr); c != EOF; c = getc(flptr)){
		if(c == '\n'){
			count++;
		}
	}
	if (count == 0){
		printf("empty file\n");
		return 2;
	}

	int readLine = rand() % count;
	readLine++;

	bool keep_reading = true;
	int currentLine = 1;

	fseek(flptr, 0, SEEK_SET);



	// gets word from random line
	do{
		fgets(str1, 49, flptr);
		if(feof(flptr)){
			keep_reading = false;
			printf("couldn't find line");
		}
		else if (currentLine == readLine){
			keep_reading = false;
			//printf("%s%ld\n", str1, strlen(str1));
		}
		currentLine++;

	}while (keep_reading);//*/

	//start of game
	printf("word size %ld\n", strlen(str1 + 1));
	for(int x = 0; x < 6; x++){
		int o = 0;
		printf("\ngive me your guess\n");
		fgets(str2, 20, stdin);
		if(strlen(str2) == strlen(str1)){
			o = mainLoop(str2, str1);
		}
		else{
			printf("wrong size \n");
		}
		if(o == strlen(str1)){
			printf("%s\nYou Win\n%s", TC_GRN, TC_NRM);
			break;
		}
	}

	fclose(flptr);

	return 0;
}

/*============================================================*/

int mainLoop(char *wrt, char *str){
	int com[50];
	int chkS[50];
	int chkW[50];
	int c = 0;

	for(int i = 0; i < strlen(str); i++){
		com[i] = 0;
		chkS[i] = 0;
		chkW[i] = 0;
	}

	for(int i = 0; i < strlen(str); i++){
		if(str[i] == wrt[i]){
			com[i] = wrt[i]*2 + 1;
			chkS[i] = 1;
			chkW[i] = 1;
			c++;
		}
	}

	for(int w = 0; w < strlen(wrt); w++){
		for(int s = 0; s < strlen(str); s++){
			if((chkS[s] == 0) && (chkW[w] == 0)) {
				if(wrt[w] == str[s]){
					com[w] = wrt[w]*2;
					chkS[s] = 1;
					chkW[w] = 1;
				}
				else{
					com[w] = -2*wrt[w];
				}

			}
		}
	}	

	for(int i = 0; i < strlen(str + 1); i++){
		if(com[i] <= 0){
			printf("%s%c%s",TC_RED, -1*com[i]/2, TC_NRM);
		}
		else if(com[i] % 2 == 1){
			printf("%s%c%s",TC_GRN, com[i]/2, TC_NRM);
		}
		else if(com[i] % 2 == 0){
			printf("%s%c%s",TC_YEL, com[i]/2, TC_NRM);
		}
	}

	return c;
}

