//Jonas Funcke 2016
//includes
#include <sys\stat.h>
#include <stdio.h>
#include <string.h>
//main
int main(void){
	//deklarations
	int i;//Counting variable used in for-loop looking for the '\n'
	char line[10000];//file-path
	char ch;//
	struct stat puffer;//file-attributes
	printf("Welcome to the file-accesstester:\n");
	do{
		printf("Put in the file path\n");
		fgets(line, 100000, stdin);
		if(line!=NULL){//Test for empty String
			for(i=0; line[i]!='\n'; i++){
				;
			}
			line[i]='\0';//Killling the newline
			//Getting target-attributes
			if(stat(line, &puffer)==0){
				if(puffer.st_mode & S_IWRITE){//write access
					printf("You got writing-access\n");
				}else if(puffer.st_mode & S_IREAD){//read access
					printf("You got reading-access\n");
				}else if(puffer.st_mode & S_IEXEC){//execution access
					printf("You got executing-access\n");
				}else{//no access
					printf("It looks like you don't got any permission for this\n"
						"'Do'h' - Homer J. Simpson\n");	
				}
			}else{
				printf("There was a problem with your path!\n");
			}
		}else{
			printf("There was nothing on your path");
		}
		printf("For closing the program please press ENTER(or else press any key)...");
		ch=getchar();
	}while(ch!='\n');
	return 0;
}
