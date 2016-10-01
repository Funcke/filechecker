//includes
#include <sys\stat.h>
#include <stdio.h>
#include <string.h>

//main
int main(void){
	//deklarations
	int i;//Counting variable used in for-loop looking for the '\n'
	char line[10000];//file-path
	char ch;
	FILE *lfp;//pointer on log-file
	struct stat puffer;//file-attributes

	printf("Welcome to the file-accesstester:\n");
	lfp=fopen("log.txt", "wt");
	if(lfp!=NULL){
		do{
			printf("Put in the file-path\n");
			fgets(line, 100000, stdin);
			if(line!=NULL){//Test for empty String
				for(i=0; line[i]!='\n'; i++){
					;
				}
				line[i]='\0';//Killling the newline
				//Getting target-attributes
				if(stat(line, &puffer)==0){
					if(puffer.st_mode & S_IWRITE){
						printf("You got writing-access\n");
					}else if(puffer.st_mode & S_IREAD){
						printf("You got reading-access\n");
					}else if(puffer.st_mode & S_IEXEC){
						printf("You got executing-access\n");
					}else{
						printf("It looks like you don't got any permission for this\n"
							"'Do'h' - Homer J. Simpson\n");		
					}
					fprintf(lfp, "%s\n", line);
				}else{
					printf("There was a problem with your path!\n");
					fprintf(lfp, "problem with path\n");
				}
			}else{
				printf("There was nothing on your path");
				fprintf(lfp, "empty path\n");
			}
			printf("For closing the program please press ENTER(or else press any key)...");
			ch=getchar();
		}while(ch!='\n');
	flcose(lfp);
	}else{
		fprintf(stderr, "Eror occured opening the log.txt file");
	}
	return 0;
}
