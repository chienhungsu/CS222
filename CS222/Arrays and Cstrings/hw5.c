#include<stdio.h>
#include<string.h>
/* deifne constant size */
#define MY_BUFFER_SIZE 1000
/* function prototype */
int search_and_count(FILE *fp, char* word, int* length);
int character_count(char *str);
int word_search(char* myword, char* mystring);
int main()
{
	/* the number of characters */ 
	int count;
	/* file pointer */
	FILE *fp;
	/* define string array for filename and search name */
	char filename[200],search_name[200];
	/* variable for indicator */ 
	int indicator=0;
	/* define character length */
	int character_length=0;
	/* show up "please input a file name */
	printf("please input a file name\n");
	/* store the input from keyboard */
	scanf("%s", &filename);
	/* ensure the file exist or not */
	if((fp = fopen(filename,"r"))==NULL)
	{
		/* not exist printf error */
		printf("open file error!\n");
		return NULL;
	}
	/* file exist */
	else
	{
	/* show up "please input the word to search" */
	printf("please input the word to search:");
	/* store the searching name in variable */
	scanf("%s",&search_name);
	/* make equal to search_and_count's return value */
	indicator= search_and_count(fp, search_name, &character_length);
	/* file close */
	fclose(fp);
	/* find the same word or not */ 
	if(indicator==1)

       {
	/* show up the word was found */
	printf("\nWord was found. (%s)\n", search_name);
	}
/* the word was not found */
	else
	{
	printf("\nWord not found. (%s)\n", search_name);
	}
/* the number of characters */
	printf("\nCharacter count: %d\n", character_length);
	}
	return 0;
}
/* sub program search and count */
int search_and_count(FILE *fp, char* word, int* length)
{
/* define variables */
	int i, found, count, c;
	char buffer[MY_BUFFER_SIZE];
	found=0;
	count=0;
	i=0;
	c=0;
/* show up search word */
	printf("\nSearch word: %s \n", word);
/* read the characters in the file if it does not equal to end of file */
	while ((c = fgetc(fp)) != EOF)
	{
/* if character is a-z or A-Z */
	if( (c>=65 && c<=90) || (c>=97 && c<=122) )
	{
	buffer[i] = (char)c;
	i++;
	}
	else if(i > 0)
	{
	buffer[i]=0;
/* call function character_count to get the value of count */
	count += character_count(buffer);
	i=0;
/* search the word's requirement */
	if(found != 1)
	{
/* call function word_search */
	found = word_search(word, buffer);
	}
	}
	}
/* length points to count */
	*length = count;
/* return value found */
	return (found);
}
/* sub program character count */
int character_count(char *str)
{	
	int j;
	j=0;
/* for loop to count the character */
	for(j=0; j<MY_BUFFER_SIZE; j++)
	{
/* if string no character then break */
	if(str[j]==0){break;}
	}
/* return vlaue of number of characters */
	return(j);
}
/* sub program word search */
int word_search(char* myword, char* mystring)
{
	/* if myword is not different from my string */
	if(strcmp(myword, mystring)==0)
	{
	/* found it so return value 1 */
	return (1);
	}
	else
	{
	//not found.
	return (0);
	}
}
