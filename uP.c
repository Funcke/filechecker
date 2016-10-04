//includes

#include <stdio.h>
#include <string.h>
#include <errno.h>
#ifdef __unix__
	#include <sys/stat.h>
	#include <sys/types.h>
#else
	#include <sys\stat.h>
#endif



//main

int main(void){
	//deklarations
	int i, renameReturn;//Counting variable used in for-loop looking for the '\n'
	char line[10000];//file-path
	char newName[10000];//new filename
	char ch;
    char renamectrl;//Answer for rename question
	FILE *lfp;//pointer on log-file
	struct stat puffer;//file-attributes

	printf("Welcome to the file-accesstester:\n");
	lfp=fopen("history.log", "wt");
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
                        printf("Do you want to rename the file?(y or n)");
                        renamectrl=getchar(); getchar();
                        if(renamectrl=='y'|| renamectrl=='Y'){//answer was yes
                            printf("please enter the new name for the file:\n");
							fgets(newName, 10000, stdin);
							if(newName!=NULL){//Test for empty String
								for(i=0; newName[i]!='\n'; i++){
									;
								}
								newName[i]='\n';
							}else{
								printf("Error! There was a something with your new file-name\n");
							}
							renameReturn=rename(line, newName);
							if(renameReturn==0){
								printf("Everything went fine: %s\n", newName);
							}else{
								printf("There's something wrong with the rename action\n");
								printf("%s\n", strerror(errno));
							}
                        }
					}else if(puffer.st_mode & S_IREAD){
						printf("You got reading-access\n");
					}else if(puffer.st_mode & S_IEXEC){
						printf("You got executing-access\n");
					}else{
						printf("It looks like you don't got any permission for this\n"
							"'Do'h' - Homer J. Simpson\n");
					}
                    printf("%d bytes\n", puffer.st_size);
					fprintf(lfp, "%s\n", line);
				}else{
					printf("There was a problem with your path!\n");
					fprintf(lfp, "problem with path\n");
				}
			}else{
				printf("There was nothing on your path");
				fprintf(lfp, "empty path\n");
			}
			printf("For closing the program please press 'j' (or else press 'n')...");
			ch=getchar(); getchar();
		}while(ch!='\n');
        fclose(lfp);
	}else{

		fprintf(stderr, "Eror occured opening the log.txt file");
	}
	return 0;
}