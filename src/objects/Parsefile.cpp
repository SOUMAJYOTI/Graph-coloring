/* ============================================================
 *
 * This file is developed as part of the Dev-wars contest in Instruo 2014
 * held by Indian Institute of Engineering Science and Technology Shibpur.
 *
 * Date        : 2014-23-04
 * Description : Parses the input file.
 *
 * Copyright (C) 2014 by Sibashis Chatterjee 
 * Copyright (C) 2014 by Soumajyoti Sarkar
 * Copyright (C) 2014 by Anurag Chatterjee
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */
#include<stdio.h>
#include<string>
#include<list>
#include<vector>
using namespace std;


//strips all non-alphabets from str and returns it
string StripNonAlphabets(string str)
{
 int i=0;
 string retStr="";
 while(str[i]!='\0')
  {
   if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z'))
	{
	  retStr+=str[i];
	}
    i++;	
  }
 return retStr;
}

//returns whether the string contains a sentence end character at the end
bool ContainsSentenceEnd(string str)
{
 char lastChar=str[str.length()-1];
 return (lastChar=='.' || lastChar=='!' || lastChar=='?');
}

//coverts a character to lower case
char ToLowerCase(char a)
{
	if(a>='A' && a<='Z')
	{
		return a-'A'+'a';
	}
	return a;
}

//compares two strings by comparing the alphabets and ignoring the case of the alphabets
bool CompareStringAlphabetsIgnoreCase(string str1, string str2)
{
	str1 = StripNonAlphabets(str1);
	str2 = StripNonAlphabets(str2);
	 if(str1.length() == str2.length())
	 {
		 int i;
		 int len = str1.length();
		 for(i=0;i<len;i++)
		 {
			 if(ToLowerCase(str1[i]) != ToLowerCase(str2[i]))
			 {
				 return false;
			 }
		 }
		 return true;
	 }
	 return false;
}


//returns whether this sentence has matched the key sentence's conditions
bool CheckMatch(string * wordsInSentence)
{
 int lengths[]={3,5,5,3,5,4,3,4,3};
 const int requiredWordsInSentence = 9;
 //required for obtaining the character at a particular position
 int characterAtPos[36];
 list<int> presentPositions[26];
 int i,j;
 int prevLength=0;  
 
 //get the positions of each unique alphabet in this sentence
 for(i=0;i<requiredWordsInSentence;i++)
  {
	  //compare lengths
	  if((int)wordsInSentence[i].length() != lengths[i])
	  {
		  return false;
	  }
	  else
	  {
		for(j=0;j<(int)wordsInSentence[i].length();j++)
		{
			characterAtPos[j + prevLength] = ToLowerCase(wordsInSentence[i][j]) - 'a';
			presentPositions[ ToLowerCase(wordsInSentence[i][j]) - 'a' ].push_back(j + prevLength);
		}
		prevLength += lengths[i];  
	  }
  }
  
  //positions in given sentence
  list<int> requiredPositions[26];
  string givenSentence[]={"the","quick","brown","fox","jumps","over","the","lazy","dog"} ;
  prevLength=0;
  for(i=0;i<requiredWordsInSentence;i++)
  {
	  for(j=0;j<(int)givenSentence[i].length();j++)
	  {
		  requiredPositions[ givenSentence[i][j] - 'a' ].push_back(prevLength + j);
	  } 
	  prevLength += givenSentence[i].length();
  }
  
  //foreach letter 
  //check whether the positions at which it occurs in the key string, in only those positions another letter occurs  
  for(i=0;i<26;i++)
  {
	  int letterIndex = characterAtPos[requiredPositions[i].front()];
	  if(presentPositions[letterIndex].size() != requiredPositions[i].size())
	  {
		  return false;
	  }
	  else
	  {
		  list<int>::iterator lit1,lit2;
		  lit1 = presentPositions[letterIndex].begin();
		  lit2 = requiredPositions[i].begin();
		  
		  while(lit1 != presentPositions[letterIndex].end() && lit2 != requiredPositions[i].end())
		  {
			  if((*lit1) != (*lit2))
			  {
				  return false;
			  }
			  lit1++;
			  lit2++;
		  }
	  }
  }
  return true;
}

//returns the mapping from the appended string that is accepted as the correct mapping for the key
string GetMappingFromAppendedString(string inputStr)
{
	string mappingStr = "";
	int i;
	list<int> givenPositions[26];
    string givenSentence[]={"the","quick","brown","fox","jumps","over","the","lazy","dog"} ;
    string givenSentenceAppended="";
    
    const int numWords=9;
    
    for(i=0;i<numWords ;i++)
    {
		givenSentenceAppended += givenSentence[i];
	}
	
	i=0;
    while(inputStr[i] != '\0')
    {
		givenPositions[ToLowerCase(inputStr[i]) - 'a'].push_back(i);
		i++; 
	}
    
    for(i=0;i<26;i++)
    {
		mappingStr += givenSentenceAppended[givenPositions[i].front()]; 
	}  
    //inputStr is encoded form of givenSentence(key)
     
	
	return mappingStr;
}


//takes the filename containing the encrypted message as input
//returns the mapping of encrypted to decrypted characters
string ObtainMapping(char* fileName)
{
 FILE *fp;
 fp=fopen(fileName,"r");
 const int requiredWordsInSentence = 9;
 char word[1001];
 
 bool foundFirstWord = false;
 bool foundSecondWord = false;
 bool lineEnd = false;
 
 list<string> wordsInSentence;
 
 while(!feof(fp))
 {
   fscanf(fp,"%s",word);
   string str(word);
   
   //ignore first word
   if(!foundFirstWord)
   {
	   foundFirstWord = true;
	   continue;
   } 
   
   //ignore second word
   if(!foundSecondWord)
   {
	   foundSecondWord = true;
	   continue;
   }
   
   if(ContainsSentenceEnd(str))
   {
	   lineEnd = true;
   }  
   
   string newStr = StripNonAlphabets(str);
   //printf("Read in : %s",newStr.c_str());   

   if(lineEnd)
   {
	   //set lineEnd flag to false
	   lineEnd = false;
	   //push in the last word of the sentence	
	   wordsInSentence.push_back(newStr);
	
	   if((int)wordsInSentence.size() != requiredWordsInSentence)
	   {
		   wordsInSentence.clear();
	   }
	   else
	   {
		   string wordsInSentenceArray[requiredWordsInSentence];
		   list<string>::iterator lit;
		   int i=0;
		   for(lit = wordsInSentence.begin() ; lit!=wordsInSentence.end() ; lit++)
		   {
			   wordsInSentenceArray[i] = *lit;
			   i++;
		   }
		   //if this is the required sentence done
		   if(CheckMatch(wordsInSentenceArray))
		   {
			   string appendedStr="";
			   //append the strings to make the positions clear
			   for(i=0; i<requiredWordsInSentence ;i++)
			   {
				   appendedStr += wordsInSentenceArray[i];
			   }
			 
			   //print the words contained in this line 
			  // printf("%s\n",appendedStr.c_str());						   
			  
			   //get positions of the alphabets
			   return GetMappingFromAppendedString(appendedStr);		   
		   }
		   else
		   {
			   wordsInSentence.clear();
		   }
	   }
   }
   else
   {
	   wordsInSentence.push_back(newStr);
   }
   
 }
 fclose(fp);
 return "";
}


//version 1 decrypted whole file
string DecryptFile(char *fileName, string mappingArray)
{
	FILE *fp;
	fp = fopen(fileName,"r");
	char ch;
	string decryptedOutput="";
	while(!feof(fp))
	{
		ch = fgetc(fp);
		if(ch == EOF)
		 {
			 break;
		 }
		
		if(ch>='A' && ch<='Z')
		{
			decryptedOutput += ('A'+(mappingArray[ch - 'A'] - 'a'));
		}
		else if(ch>='a' && ch<='z')
		{
			decryptedOutput += mappingArray[ch - 'a'];
		}
		else
		{
			decryptedOutput += ch;
		}
	}
	return decryptedOutput;
}

int main(int argc, char *argv[])
{
 if(argc!=3)
 {
   fprintf(stderr,"Usage not correct");
 }
 else
 {
	string mappingArray = ObtainMapping(argv[1]);
	if(mappingArray != "")
	{
   	  string decryptedOutput = DecryptFile(argv[1], mappingArray);
   	  
   	  //writeOutput to a file
   	  FILE *fp = fopen(argv[2],"w");
   	  fprintf(fp, "%s", decryptedOutput.c_str());
   	}
   	else
   	{
		printf("Serious error");
	}
 }
}
