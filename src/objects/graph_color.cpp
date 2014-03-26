/* ============================================================
 *
 * This file is developed as part of the Dev-wars contest in Instruo 2014
 * held by Indian Institute of Engineering Science and Technology Shibpur.
 *
 * Date        : 2014-23-04
 * Description : Implements the Welsh Powell algorithm for vertex coloring in a connected graph.
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

#include <iostream>
#include <map>
#include <utility>
#include <list>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <fstream>

#include "CreateGraph.cpp"

using namespace std;

typedef pair<string, int> PSI;
typedef list<string> LS;
typedef pair<string, LS> SLP;
typedef pair<int, SLP> SLI;
typedef vector< SLI > VPL;
typedef map<string, list<string> > MSL;
typedef map<string, int> MSI;

/* 'vertices' is an ADT containing three fields: degree of the city, city name, list of connected cities
   'city_color' is an array of pairs containing each city name and the color of the city
   'city_number' maps a city to a partciular number sorted by the degrees of the cities.
*/
SLP pair_city;
SLI city_degrees;
VPL vertices;
PSI city_color[1000];
MSI city_number;

// find the first non-colored vertex in a list of vertices sorted by descending order of vertices
int find_non_colored(PSI cities[], int cnt)
{
    for( int i=0; i<cnt; i++)
         if(cities[i].second == -1)
                             return i;
    return -1;
}                      

// create the adjacency list graph from the decrypted file from the previous stage
MSL createG(char *filename)
{
    map<string, list<string> > graphAdjacencyList = GetGraphFromDecryptedFile(filename);
    return graphAdjacencyList;		
}

// main code starts
int main(int argc, char *argv[])
{
    //------- Represent the graph in an adjacency List
    MSL adjacencyList = createG(argv[1]);
    MSL::iterator it_msl;
    SLP temp_node;
    SLI temp_pair;
    for(it_msl = adjacencyList.begin(); it_msl!=adjacencyList.end(); it_msl++){
               temp_node = make_pair(it_msl->first, it_msl->second);
               temp_pair = make_pair( (it_msl->second).size(), temp_node);
               vertices.push_back( temp_pair );
    }
    PSI temp;
    string city_name, city;
    vector<SLI >::iterator it;
    
    // Step 1: Sort the vertices/cities in descending order of their degrees.
    sort(vertices.rbegin(), vertices.rend());
    

//    for (it=vertices.begin(); it!=vertices.end(); it++){    
//        cout<<(it->second).first<<endl;
//    }

    int cnt_cities=0;  // keeps count of the number of nodes in the graph
    for (it=vertices.begin(); it!=vertices.end(); it++){    
        PSI temp_color = make_pair((it->second).first, -1);
        city_color[cnt_cities++] = temp_color;
    }
    
//  Ste 2: Find the first vertex in the sorted list that is not colored
    int first_vertex = find_non_colored(city_color, cnt_cities);
    int color_min_left = 1;  // clor assigned to a vertex in an iteration
    
    cout<<"Outputs:"<<endl<<endl;
    string city_store;
    while(first_vertex !=-1){
	vector<SLI >::iterator it_sl;
	MSI map_color, map_wrong;	
	list<string> connected_cities; 
	for (it_sl=vertices.begin(); it_sl!=vertices.end(); it_sl++){    
		map_wrong[it_sl->second.first] = 0;      // 'map_wrong' keeps list of vertices in the graph that cannot be colored 
							// with the color given to first_vertex in this iteration.
    	}
	
	city_store = city_color[first_vertex].first; //stores the city of the 'first_vertex' index in vertices ADT
	map_color[city_store] = color_min_left;
	city_color[first_vertex].second = color_min_left;

	vector<SLI>::iterator it;
	list<string>::iterator it_list;
	 
	for (it=vertices.begin(); it<vertices.end(); it++){
		if(it->second.first == city_store)
                	connected_cities = it->second.second;
    }

	for(it_list = connected_cities.begin(); it_list!=connected_cities.end(); it_list++)
		map_wrong[*it_list] = -1;

                                                                  
        int val;
     	int flag =0;
        map<string, int> traversed;
        for(int i=0;i<cnt_cities;i++){
		        string city_current = city_color[i].first;
          		if( map_wrong[city_current] == -1 || city_color[i].second != -1 ) continue;
          		else {
			         map_color[city_current] = color_min_left;
         			 city_color[i].second = color_min_left;
          			 for (it=vertices.begin(); it<vertices.end(); it++){
				     if(it->second.first == city_current)
	                		connected_cities = it->second.second;
                     }
      			for(it_list = connected_cities.begin(); it_list!=connected_cities.end(); it_list++)
		    		map_wrong[*it_list] = -1;
		        }	
        }
        color_min_left++;

        first_vertex = find_non_colored(city_color, cnt_cities);              
     }
	
 // Write the colors of the nodes to a file in a format that is read by the 'Plot Graph' method in Java in the next stage.
     ofstream myfile;
     myfile.open (argv[2]);
     myfile << cnt_cities<< endl;
     
     for(int i=0;i<cnt_cities;i++){
             cout<<city_color[i].first<<" " <<city_color[i].second<<endl;
	  
     city_number[city_color[i].first] = i+1;
	     myfile<<i+1<<" "<<	city_color[i].first <<" "<<city_color[i].second<<endl;
     }
    
     myfile<<CommChannels.size()<<endl;
     vector<pair<string, string> >::iterator it_v;
     for( it_v = CommChannels.begin(); it_v!= CommChannels.end(); it_v++){
		myfile<< city_number[it_v->first]<<" "<<city_number[it_v->second]<<endl;

     }
         
     return 0;
}

