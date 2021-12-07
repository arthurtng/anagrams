#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define BUFFERSIZE 130000
#define WORDSIZE 30

int readfile(char wordslist[][WORDSIZE]);
void test(void);
bool isanagram(char* word1, char* word2);
void printanagram(char wordslist[][WORDSIZE], int max, char* word);

int main(int argc, char* argv[])
{
   if (argc != 2){
     fprintf(stderr, "Incorrect usage, use the following syntax: ./anagrams <word>\n");
     exit(EXIT_FAILURE);
   }
   
   if ((int)strlen(argv[1]) >= WORDSIZE){
     fprintf(stderr, "Please enter a word less than 30 characters long\n");
     exit(EXIT_FAILURE);
   }
   
   test();
   
   char wordslist[BUFFERSIZE][WORDSIZE];      
   int max = readfile(wordslist);    
   printanagram(wordslist, max, argv[1]);  
       
   return 0;
}

void test(void)
{
   assert(isanagram("larry", "yrral"));
   assert(isanagram("nevermore", "ermorveen")); 
   assert(isanagram("sternaig", "angriest"));   
   assert(!isanagram("abc" ,"dba"));
   assert(!isanagram("ddeeee", "dde")); 
     
}

int readfile(char wordslist[][WORDSIZE])
{
   FILE* fp = fopen("eowl_english_words.txt", "r");   
   if(!fp){
      fprintf(stderr, "Cannot read from dictionary file\n");
      exit(EXIT_FAILURE);
   }
   
   int i = 0;
   while(fscanf(fp, "%s", wordslist[i]) != EOF){
      i++;
   }
      
   fclose(fp);
   
   return i;
}

bool isanagram(char* word1, char* word2)
{
   if (strlen(word1) != strlen(word2)){
      return false;
   }
   
   char temp[WORDSIZE];
   strcpy(temp, word2);
   bool match = false;
   
   for (int i=0; i<(int)strlen(word1); i++){
      for (int j=0; j<(int)strlen(word2); j++){
         if (word1[i] == word2[j]){
            temp[j] = '#';
            match = true;
         }        
      }
      if (!match){
            return false;
      } 
      match = false;
   }
   
   return true;          
}

void printanagram(char wordslist[][WORDSIZE], int max, char* word)
{
   for (int i=0; i<max; i++){
      if (isanagram(wordslist[i], word) && strcmp(wordslist[i], word) != 0){
         printf("%s\n", wordslist[i]);
      }
   }
}

