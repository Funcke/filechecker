#include "killnewline.h"
#include <stdio.h>
#include <stdbool.h>
/*
*Function: killnewline
*Header: killnewline.h
*Purpose: deletes the newline in a string read by fgets
*Parameters: string read by fgets
*return value: true if succeeded can be ignored
*/
bool killnewline (char* string){
	int i;
	bool newline, rc;
	for(i=0; string[i]!='\0'&&string[i]!='\n'; i++){
		if(string[i]=='\n'){
			newline=true;
		}
	}
	if(newline){
		string[i]='\0';
		rc=true;
	}else{
		rc=false;
	}
}