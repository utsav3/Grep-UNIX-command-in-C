/* * Utsav Dhungel
   * Linux CS 306 Lab 1
   * Assignment 
   * Grep function in C
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define buff_size 1024			//Defining a constant

char* get_next_line(FILE *fp); //Declaring function at the header to avoid conflicting errors.
int grep_stream(FILE *fp, char* search_String, char* file_Name); //Declaring the function at the header to avoid conflicting errors


int main(int argc, char *argv[]) 
{
char *search_String=NULL;
char *file_Name=NULL;
FILE *fp=NULL;

	printf("Total Number of Arguements=%d\n",argc); 		//Prints the number of argument enterted by the user
		
	if(argc>1 && argc<4)									//The number of arguments has to be either 2 or 3. The first being the executable the second the search string and third the file.
	{
	
	int i=0;
	for(i=0;i<argc;i++)
	{
		printf("argument %d=%s\n",i,argv[i]);				//Prints the arguments pointed by the array pointer argv.
		switch(i)											
		{
			case 1:	
			search_String=argv[i];							//takes in the argument entered by the user and stores in the variable search_String
			break;
			case 2:
			if((fp=fopen(argv[i],"r"))==NULL)
			{
			printf("The file does not exist\n");
			exit(EXIT_FAILURE);
			}//This if statement displays and terminates the porgram if it encounters error opening the file.
			break;
			default:
			break;
		}
		
	}
	}
	 else
		{
			fprintf(stderr, "Usage: mygrep PATTERN[FILE]");
			exit(EXIT_FAILURE);
			//done parsing
		}	//Case when the number of arguments does not match terminated the program.
			
			if(fp)
			  {
				file_Name=argv[2];
				printf("Sucessfully opened file: %s\n",file_Name);
			}//Displays the message when the file is sucessfully opened.
			else
			{
				fp=stdin;
				
			}//Error handling
			
			
			
			int retval=grep_stream(fp,search_String,file_Name);			//When the search string is found the retval is set to 1 or else 0
			if(0==retval)
			{
				fprintf(stderr,"Searched string %s is not present in this file: %s\n",search_String,file_Name);
			}//Displays if the string is not found in the program.			

			return 0;

		}//End of the main function. 
	 
	
	int grep_stream(FILE *fp, char* search_String, char* file_Name)
	{
		int Found=0;
		char *line=NULL;
		
		while((line=get_next_line(fp))!=NULL)
		{
			printf("Line read: %s\n",line);
			//int string_present=strstr(line, search_String) !=NULL? 1: 0;
			char *string_present=strstr(line, search_String);			//strstr  function searches the string in the line and returns the pointer to the first occurance of the string.
				if(string_present!=NULL)
				{
					fprintf(stdout,"\t Found string: %s in above line : %s\n",search_String,line);		  //Prints the line that contains the string.
					Found++;			//Found is set to 1 if the string is found or else it remains zero.
				}
				
		}
		return Found;			//Found is set 1 or 0 depending on whether the string is found or not.
	}   //The function takes in the line form the file and returns 1 if the string is found and prints the line that contains the string or else returns 0.
	
	
	
	
	char* get_next_line(FILE *fp)
	{
		int ch;
		static char buff[buff_size];  			
		char *temp=buff;
		char *ret_buff=NULL;	
		
		while((ch=fgetc(fp)) != EOF)  //Checks if the pointer has encountered the end of file which has a integer value -1.
		{
			if(ch=='\n')			  //Executes when the file has a new line.
			{
			*temp="\0";				  //Inputs null pointer at the end of string of characters.
			int result = temp - buff + 1;  
			ret_buff=(char *) malloc((temp-buff+1)*sizeof(char));	//+1 so it has enough memory to sore the string and the null byte. using last space of memory for null byte.
			memcpy(ret_buff,buff,temp-buff+1);						//copies the string that contains the string from the buffer to the variable ret_buffer.
			ret_buff[result]='\0';									//After every string of characters it inserts null in the buffer.
			return ret_buff;
			} 
			else 
			  {
				*temp++=ch;
			  }
		}	
		if(temp!=buff) //If we encounter EOF in the file
		{
			*temp='\0';
			ret_buff=(char *)malloc((temp-buff+1)*sizeof(char));	
			memcpy(ret_buff,buff,temp-buff+1);						//These function exactly same as above the only difference is the condition that it executed in. EOF before \n.
		    return ret_buff;
		}//If we encounter EOF before the next line character in the file. 
		
		return NULL;
	}//This function is used to read the next line in the file and return the line. 
