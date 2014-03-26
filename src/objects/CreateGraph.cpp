/* ============================================================
 *
 * This file is developed as part of the Dev-wars contest in Instruo 2014
 * held by Indian Institute of Engineering Science and Technology Shibpur.
 *
 * Date        : 2014-23-04
 * Description : Decrypts the input file.
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
#include<list>
#include<vector>
#include<utility>
#include<string>
#include<map>
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

//converts character to lower case
char ToLowerCase(char a)
{
	if(a>='A' && a<='Z')
	{
		return a-'A'+'a';
	}
	return a;
}

//compare strings by ignoring case of the alphabets
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

//Communication channels as a vetor of pairs
vector<pair<string, string> > CommChannels;

//returns the adjacency list representation of the graph as a map of string and list of strings
map<string, list<string> > GetGraphFromDecryptedFile(char *decryptedFileName)
{
	FILE *fp = fopen(decryptedFileName,"r");
	char word[101];
	bool foundComm = false;
	bool foundChannel = false;
	map<string, list<string> > adjacencyList; //adjacency list for the graph
	
	while(!feof(fp))
	{
		fscanf(fp,"%s",word);
		string str(word);
		
		if(!foundComm && CompareStringAlphabetsIgnoreCase(str,"communication"))
		{
			foundComm = true;
			if(!foundChannel)
			{
				fscanf(fp,"%s",word); //ensure that communication channels occurs together
				str = word;
				if(CompareStringAlphabetsIgnoreCase(str,"channels"))
				{
					foundChannel = true;
					continue;
				}
			}
			
			foundComm = false;
			continue;
		}
		
		if(CompareStringAlphabetsIgnoreCase(str,"messages"))
		{
			break;
		}
		
		if(foundComm && foundChannel)
		{
			//take input in pairs
			//str is the destination
			string source = str;
			fscanf(fp,"%s",word);
			str = word;
			
			//since undirecteed graph push each element into the other's adjacency list
			adjacencyList[source].push_back(str);
			adjacencyList[str].push_back(source);
			
			//add the communication channels in the vector
			CommChannels.push_back(make_pair(source, str));
		}
		
	}
	
	return adjacencyList;
}

/*

//testing
int main(int argc, char *argv[])
{
	if(argc==2)
	{
		map<string, list<string> > graphAdjacencyList = GetGraphFromDecryptedFile(argv[1]);
		map<string, list<string> > :: iterator mit;
		list<string> :: iterator lit;
		for(mit = graphAdjacencyList.begin() ; mit!= graphAdjacencyList.end() ; mit++)
		{
			printf("%s: ",(mit->first).c_str());
			for(lit=(mit->second).begin() ; lit != (mit->second).end() ; lit++)
			{
				printf("%s ",(*lit).c_str());
			}
			printf("\n");
		}
	}
}
*/
