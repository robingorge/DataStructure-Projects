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

string content;

vector<Point> P1;
vector<Point> P0;

vector<Info> minrecord;
vector<Info> tmprecord;

int minrecordstart;
int tmprecordstart;


bool is_digits(const string &str)
{
  return str.find_first_not_of("0123456789 .-") == std::string::npos;
}

//===============================================================================helper functions to caculate triangle area

// P1 a, b  // P0 c
double caculatearea1(int a, int b, int c){
	double x=sqrt((P1[a].x-P1[b].x)*(P1[a].x-P1[b].x)+(P1[a].y-P1[b].y)*(P1[a].y-P1[b].y));
	double y=sqrt(1+(P1[a].x-P0[c].x)*(P1[a].x-P0[c].x)+(P1[a].y-P0[c].y)*(P1[a].y-P0[c].y));
	double z=sqrt(1+(P1[b].x-P0[c].x)*(P1[b].x-P0[c].x)+(P1[b].y-P0[c].y)*(P1[b].y-P0[c].y));
	double s= (x+y+z)/2;
	//cout<<"1"<<endl;
	//cout<<"area    p1    "<<a<<"   "<<b<<"  p0   "<<c<<"   "<<sqrt(s*(s-x)*(s-y)*(s-z))<<endl;
	return sqrt(s*(s-x)*(s-y)*(s-z));
}

// P1 a // P0 b, c
double caculatearea0(int a, int b, int c){
	double x=sqrt((P0[b].x-P0[c].x)*(P0[b].x-P0[c].x)+(P0[b].y-P0[c].y)*(P0[b].y-P0[c].y));
	double y=sqrt(1+(P1[a].x-P0[c].x)*(P1[a].x-P0[c].x)+(P1[a].y-P0[c].y)*(P1[a].y-P0[c].y));
	double z=sqrt(1+(P1[a].x-P0[b].x)*(P1[a].x-P0[b].x)+(P1[a].y-P0[b].y)*(P1[a].y-P0[b].y));
	double s= (x+y+z)/2;
	//cout<<"0"<<endl;
	//cout<<"area    p1    "<<a<<"   p0   "<<b<<"  "<<c<<"   "<<sqrt(s*(s-x)*(s-y)*(s-z))<<endl;
	return sqrt(s*(s-x)*(s-y)*(s-z));
}






void print(int x, int y){

	if ((x>=0)&&(y>=0)){

	int m=P1.size();
	int n=P0.size();


	int lastindex=y*(m+1)+x;

	int start=minrecordstart;


	int px=minrecord[lastindex].pp;
	int py=minrecord[lastindex].pq;

	if (px==x){
		int a,b,c;

		a=px+start;
		if (px+start>=m){
			a=a-m;
		}

		b=y;
		c=py;

		if (b>=n){
			b=b-n;
		}

		if (c>=n){
			c=c-n;
		}
		content=content+to_string(a+1)+" "+to_string(b+m+1)+" "+to_string(c+m+1)+"\n"; 
		cout<< a+1 <<" "<< b+m+1 <<" "<< c+m+1 <<endl;
		print(px,py);
	}
	else if(py==y){
		int a,b,c;

		a=px+start;
		if (px+start>=m){
			a=a-m;
		}

		b=x+start;
		if (b>=m){
			b=b-m;
		}

		c=y;
		if (c>=n){
			c=c-n;
		}
		content=content+to_string(a+1)+" "+to_string(b+1)+" "+ to_string(c+m+1)+"\n";
		cout<< a+1 <<" "<< b+1 <<" "<< c+m+1 <<endl;
		print(px,py);

	}
	else{//cout<<  " errorrrrrrrrrr"  <<endl;
	}

	}
	else{

		//cout<<  " errorrrrrrrrrr"  <<endl;
	}

}


//===============================================================================dynamic functions

//x is the start P1 number
//m is the size of p1, n is the size of p0
void dphelper(int x, int m, int n){
	//cout<<"aaa"<< endl;
	Info newone;
	for (int j=0 ; j<=n ; j++){
		int p0index=j;
		if (j==n){
			p0index=0;
		}
		for (int i=0 ; i<=m ; i++){
			int p1index=i+x;
			if (i+x>=m){
				p1index=i+x-m;
			}

			if ((i==0)&&(j==0)){
				newone=Info(-1,-1,0);
				tmprecord.push_back(newone);
			}
			else{
				int upj=j-1;//i stay the same
				int lefti=i-1;//j stay the same

				if ((upj>=0)&&(lefti>=0)){

					int upindex=upj;
					if(upindex>=n){
						upindex=upindex-n;
					}

					int leftindex=lefti+x;
					if (leftindex>=m){
						leftindex=leftindex-m;
					}

					double upcost=tmprecord[upj*(m+1)+i].cost;
					double leftcost=tmprecord[j*(m+1)+lefti].cost;

					double upsum=upcost + caculatearea0(p1index,p0index,upindex);
					double leftsum=leftcost + caculatearea1(leftindex,p1index,p0index);

					if (upsum<leftsum){
						newone=Info(i,j-1,upsum);
						//cout<<newone.cost<<endl;/////////
					}
					else{
						newone=Info(i-1,j,leftsum);
						//cout<<newone.cost<<endl;/////////
					}
					tmprecord.push_back(newone);
				}
				else if ((upj>=0)&&(lefti<0)){

					int upindex=upj;
					if(upindex>=n){
						upindex=upindex-n;
					}

					double upcost=tmprecord[(j-1)*(m+1)+i].cost;
					double upsum=upcost+caculatearea0(p1index,p0index,upindex);
					newone=Info(i,j-1,upsum);
					tmprecord.push_back(newone);
				}
				else if ((lefti>=0)&&(upj<0)){

					int leftindex=lefti+x;
					if (leftindex>=m){
						leftindex=leftindex-m;
					}

					double leftcost=tmprecord[(j)*(m+1)+i-1].cost;
					double leftsum=leftcost+caculatearea1(leftindex,p1index,p0index);
					newone=Info(i-1,j,leftsum);
					tmprecord.push_back(newone);
				}

			}
		
					//cout<<i<<"    "<<j<<"     "<<newone.pp<<"    "<<newone.pq<<"    "<<newone.cost<<endl;

		}//for j
	}//for i
	int ttrl=(m+1)*(n+1)-1;
	//cout<<tmprecord[ttrl].cost<<"     //////////////////////"<<endl;


	if (minrecord.size()>0){
		int mrl=minrecord.size()-1;
		int trl=tmprecord.size()-1;

		if (minrecord[mrl].cost>tmprecord[trl].cost){
			minrecordstart=tmprecordstart;
			minrecord=tmprecord;
		}
	}
	else{
		minrecordstart=x;
		minrecord=tmprecord;
	}


}



void dynamicprogram(){

	int m=P1.size();
	int n=P0.size();
	int lastindex= (m+1)*(n+1)-1;
	for (int start=0;start<m;start++){
		tmprecord.clear();
		tmprecordstart=start;
		dphelper(start,m,n);
	}

	//cout << minrecord[lastindex].cost << endl;
	//cout<< "end of dp"<< endl;
	ofstream myfile;
	myfile.open("output.txt");
	print(m,n);
	myfile<<content;
	myfile.close();
}



//===============================================================================main function

int main(int argc, const char * argv[]){
	string line;
	double firstI, SecondI, thirdI,fourthI;
	int p1number=0;
	int p0number=0;
    int i = 0;


    //get number of points
    int first,second,third;
    getline(cin, line);
 	while (!(is_digits(line))){
 		cout << "Invalid number of points. Try again"<<endl;
 		getline(cin, line);
 	}
 	stringstream ss(line);
 	ss>>first>>second;
 	if (!ss || ss>>third){
		cout << "Invalid number of points. Try again\n";
	}
 	p1number = first;
 	p0number = second;
 	//cout<<p1number<<"    "<<p0number<<endl;



 	//get P1 points value
	while ((i<p1number)&&(getline( cin, line ))){

		if (is_digits(line)) {
			stringstream ss(line);
	  		ss>>firstI>>SecondI>>thirdI;
	  		
	  		if (!ss || ss>>fourthI){
				cout << "Invalid point. Try again\n";
	  		}
	  		else{
	  			if (thirdI==1.0){
				//cout<< "my first number is " << setprecision(7)<< firstI << "second number is " << SecondI <<endl;
				Point newp(0,0);
				newp.x = firstI;
				newp.y = SecondI;				

		  		P1.push_back(newp);
				//cout<< "my first number is " << setprecision(7)<< P1[i].x << "second number is " << P1[i].y <<endl;
		  		i++;

		  		}
		
			}
	
		}
		else{
		//printf("not all int\n");
		}

	}

	i=0;


 	//get P0 points value
	while ((i<p0number)&&(getline( cin, line ))){

		if (is_digits(line)) {
			stringstream ss(line);
	  		ss>>firstI>>SecondI>>thirdI;
	  		
	  		if (!ss || ss>>fourthI){
				cout << "Invalid point. Try again\n";
	  		}
	  		else{
	  			if (thirdI==0.0){
				//cout<< "my first number is " << setprecision(7)<< firstI << "second number is " << SecondI <<endl;
				Point newp(0,0);
				newp.x = firstI;
				newp.y = SecondI;				

		  		P0.push_back(newp);
				//cout<< "my first number is " << setprecision(7)<< P0[i].x << "second number is " << P0[i].y <<endl;
		  		i++;

		  		}
		
			}
	
		}
		else{
		//printf("not all int\n");
		}

	}

	dynamicprogram();


	//cout<<"done"<<endl;





}


