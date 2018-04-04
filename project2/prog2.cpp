#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <map>
#include <set>
#include <limits>
#include <vector>
#include "helper.h"
#include <algorithm>
#include <iomanip>

using namespace std;




vector<Point> Plist;


double ddistance(Point a, Point b){
	return (sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)));
}



struct Edge
{
  int fir,sec;
  double weight;

  Edge(): fir(-1),sec(-1),weight(-1.000) {}

  Edge(int x, int y): fir(x),sec(y),weight(ddistance(Plist.at(x),Plist.at(y))) {} 

};

struct less_than_weight
{
    inline bool operator() (const Edge& struct1, const Edge& struct2)
    {
        return (struct1.weight < struct2.weight);
    }
};

struct less_than_fir
{
    inline bool operator() (const Edge& struct1, const Edge& struct2)
    {
    	if (struct1.fir==struct2.fir){
        	return (struct1.sec < struct2.sec);
        }
        else{
        	return (struct1.fir < struct2.fir);
        }

    }
};


vector<Edge> Elist;


vector<Edge> needed;

//vector<Edge> left;


vector<int> used;











bool is_digits(const string &str)
{
  return str.find_first_not_of("0123456789 .-") == std::string::npos;
}


//===============================================================================Prim's algorithm



void print(){

	std::sort(needed.begin(), needed.end(), less_than_fir());

	for (int i=0;i<needed.size();i++){
		Edge a=needed.at(i);
		cout<<setprecision(7)<<a.fir<<" "<<a.sec<<endl;
	}



}




void primhelper(int m,vector<Edge> left){

	if ((m>0)&&(left.size()>0)&&(used.size()<Plist.size())){
		for (int i=0;i<left.size();i++){
			Edge curr=left.at(i);
			int a=curr.fir;
			int b=curr.sec;

			if ((std::find(used.begin(), used.end(), a) != used.end())&&(std::find(used.begin(), used.end(), b) == used.end())){
				used.push_back(b);
				needed.push_back(curr);
    			left.erase (left.begin()+i);
    			
    			m--;
				primhelper(m,left);
    			break;				
			}
			else if ((std::find(used.begin(), used.end(), b) != used.end())&&(std::find(used.begin(), used.end(), a) == used.end())){
				used.push_back(a);
				needed.push_back(curr);
    			left.erase (left.begin()+i);

    			m--;
				primhelper(m,left);
    			break;			
			}		
		}
	}


}





void primalgorithm(){
	int current=0;
	used.push_back(current);
	vector<Edge> left=Elist;
	std::sort(left.begin(), left.end(), less_than_weight());

	int m=Plist.size()-1;
	if ((m>0)&&(left.size()>0)&&(used.size()<Plist.size())){
		for (int i=0;i<left.size();i++){
			Edge curr=left.at(i);
			int a=curr.fir;
			int b=curr.sec;

			if ((std::find(used.begin(), used.end(), a) != used.end())&&(std::find(used.begin(), used.end(), b) == used.end())){
				used.push_back(b);
				needed.push_back(curr);
    			left.erase (left.begin()+i);
    			m--;
				primhelper(m,left);
    			break;
			}
			else if ((std::find(used.begin(), used.end(), b) != used.end())&&(std::find(used.begin(), used.end(), a) == used.end())){
				used.push_back(a);
				needed.push_back(curr);
    			left.erase (left.begin()+i);
    			m--;
				primhelper(m,left);
    			break;
			}
		
		}
	}


	if (needed.size()!=Plist.size()-1){
		cout<<"error, not enough edge"<<endl;
	}
	else{
		print();
	}


}

//===============================================================================main function

int main(int argc, const char * argv[]){
	string line;
	double firstI, SecondI, third;
	int fi,si,ti;
	int numofpoints = 0;
    int i = 0;


    //get number of vertices
    getline(cin, line);
 	while (!(line.find_first_not_of("0123456789") == std::string::npos)){
 		cout << "Invalid number of points. Try again"<<endl;
 		getline(cin, line);
 	}
 	//numofpoints = std::stoi( line );
 	istringstream(line)>>numofpoints;


 	//get points value
	while ((i<numofpoints)&&(getline( cin, line ))){

		if (is_digits(line)) {
			stringstream ss(line);
	  		ss>>firstI>>SecondI;
	  		
	  		if (!ss || ss>>third){
				cout << "Invalid point. Try again\n";
	  		}
	  		else{
				//cout<< "my first number is " << setprecision(7)<< firstI << "second number is " << SecondI <<endl;
				Point newp(0,0);
				newp.x = firstI;
				newp.y = SecondI;				
		  		Plist.push_back(newp);
				//cout<< "my first number is " << setprecision(7)<< Plist[i].x << "second number is " << Plist[i].y <<endl;
		  		i++;
			}
	
		}
		else{
		//printf("not all int\n");
		}

	}


	int numofedges=0;
	//get number of vertices
    getline(cin, line);
 	while (!(line.find_first_not_of("0123456789") == std::string::npos)){
 		cout << "Invalid number of points. Try again"<<endl;
 		getline(cin, line);
 	}
 	istringstream(line)>>numofedges;

 	i=0;


 	//get edges pair
 	if (numofedges!=0){

		while ((i<numofedges)&&(getline( cin, line ))){

			if (is_digits(line)) {
				stringstream ss(line);
		  		ss>>fi>>si;
	  		
	  			if (!ss || ss>>ti){
					cout << "Invalid edge. Try again\n";
		  		}
	  			else{
					//cout<< "my eeeeeeee number is " << setprecision(7)<< firstI << "second number is " << SecondI <<endl;
				
	  				if (fi>si){
	  					int temmmm=fi;
	  					fi=si;
	  					si=temmmm;
	  				}

					Edge newedge(fi,si);
		  			Elist.push_back(newedge);
					//cout<< "my eeeeee number is " << setprecision(7)<< Elist[i].fir << "second number is " << Elist[i].sec <<"third value is"<<Elist[i].weight<<endl;
		  			i++;
				}	
			}
			else{
			//printf("not all int\n");
			}
		}

	}
	else{
		for (int j=0;j<numofpoints;j++){
			for (int k=j+1;k<numofpoints;k++){
				Edge newedge(j,k);
		  		Elist.push_back(newedge);				
			}
		}
	}

	primalgorithm();



}


