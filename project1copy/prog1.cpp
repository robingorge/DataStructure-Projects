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


int k=0;
int kp=0;
double mmmmm=-1000.00;

struct apart{
	Point apart1;
	Point apart2;
	double apartmin;


	apart(): apart1(0,0),apart2(0,0),apartmin(-1000.000) {}

};



bool is_digits(const string &str)
{
  return str.find_first_not_of("0123456789 .-") == std::string::npos;
}



void printxy(double x1, double y1, double x2, double y2, int num){


	if (x1>x2){
		double a=x1;
		double b=y1;

		x1=x2;
		y1=y2;

		x2=a;
		y2=b;

	}
	else if (x1==x2){
		if (y1>y2){
			double c=x1;
			double d=y1;

			x1=x2;
			y1=y2;

			x2=c;
			y2=d;


		}
	}

	cout<<setprecision(7)<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
	//cout<<mindistance<<endl;
	cout<<num<<endl;


}


//===============================================================================brute helper functions
double brute_distance(double x, double y, double x2, double y2){
	k++;
	return (sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2)));
}

void bruteforcesort(double* xlist, double* ylist, int numofpoints){
	double min1x=0;
	double min1y=0;
	double min2x=0;
	double min2y=0;

	double mindistance=-1000.0000000;

	for (int i=0;i<numofpoints;i++){
		for (int j=i;j<numofpoints;j++){
		
			if (i!=j){
				if (mindistance<0){
					mindistance=brute_distance(xlist[i],ylist[i],xlist[j],ylist[j]);
					min1x=xlist[i];
					min1y=ylist[i];
					min2x=xlist[j];
					min2y=ylist[j];
				}
				else{
					double comp = brute_distance(xlist[i],ylist[i],xlist[j],ylist[j]);
					if (comp < mindistance){
						min1x=xlist[i];
						min1y=ylist[i];
						min2x=xlist[j];
						min2y=ylist[j];
						mindistance=comp;
					}
				}

			}
		
		}
	}

	printxy(min1x,min1y,min2x,min2y,k);

	//cout<<setprecision(7)<<min1x<<" "<<min1y<<" "<<min2x<<" "<<min2y<<endl;
	//cout<<mindistance<<endl;
	//cout<<k<<endl;


}

//===============================================================================brute helper functions


double ddistance(Point a, Point b){
	kp++;
	return (sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)));
}



apart process1(vector<Point> &alist){
	apart newone;

	for (int i=0;i < alist.size();i++){
		for (int j=i;j<alist.size();j++){
			if (i!=j){
				Point b=alist.at(i);
				Point c=alist.at(j);
				double m=ddistance(b,c);
				if (newone.apartmin<0){
					newone.apart1=b;
					newone.apart2=c;
					newone.apartmin=m;
					//cout<<b.x<<" "<<c.x<<endl;
					//cout<<min<<endl;
				}
				else{
					if (m<newone.apartmin){
						newone.apart1=b;
						newone.apart2=c;
						newone.apartmin=m;
						//cout<<b.x<<" "<<c.x<<endl;
						//cout<<min<<endl;
					}
				}



			}
		}
	}

	return newone;

}




apart midprocess(double start, double end, vector<Point> &plist){
	vector<Point> midpart;
	apart newone;
	double min=-1000;

	for (int i=0;i<plist.size();i++){
		Point a = plist.at(i);
		if ((a.x>start)&&(a.x<end)){
			midpart.push_back(a);
		}
	}


	std::sort(midpart.begin(), midpart.end(), less_than_y());


	for (int i=0;i < midpart.size();i++){
		for (int j=i;j<i+8;j++){
			if ((j < midpart.size())&&(i!=j)){
				Point b=midpart.at(i);
				Point c=midpart.at(j);
				double m=ddistance(b,c);
				if (min<0){
					min=m;
					newone.apart1=b;
					newone.apart2=c;
					newone.apartmin=min;
					//cout<<b.x<<" "<<c.x<<endl;
					//cout<<min<<endl;
				}
				else{
					if (m<min){
						min=m;
						newone.apart1=b;
						newone.apart2=c;
						newone.apartmin=min;
						//cout<<b.x<<" "<<c.x<<endl;
						//cout<<min<<endl;
					}
				}



			}
		}
	}

	return newone;	
}




apart divideandconquerhelper(vector<Point> &plist, int num){
	apart newone;

	newone.apart1.x=0;
	newone.apart2.x=0;
	newone.apart1.y=0;
	newone.apart2.y=0;
	newone.apartmin=-1000.000;

	
	std::vector<Point> v1(plist.begin(), plist.begin() + plist.size()/2),v2(plist.begin() + plist.size()/2 , plist.end());
		

	if (num<=5){
		newone=process1(plist);
	}
	else{

		std::vector<Point> v1(plist.begin(), plist.begin() + plist.size()/2),v2(plist.begin() + plist.size()/2 +1, plist.end());

		apart leftpart=divideandconquerhelper(v1,v1.size());
		apart rightpart=divideandconquerhelper(v2,v2.size());

		if (leftpart.apartmin<rightpart.apartmin){
			newone=leftpart;
		}
		else{
			newone=rightpart;
		}

		int leftnum=v1.size();
		int rightnum=v2.size();

		double d=newone.apartmin;
		//cout<<d<<endl;

		double midx=0.000;
		if (num%2==0){
			midx= (v1.at(leftnum-1).x + v2.at(0).x) / 2;
		}
		else{
			midx= v1.at(leftnum-1).x;
		}

		if (mmmmm<0){
			mmmmm=d;
		}
		else{
			if (d<mmmmm){
				mmmmm=d;
			}
		}
		//cout<<"mmmmmm   "<<mmmmm<<endl;

		apart midpart=midprocess(midx-mmmmm,midx+mmmmm,plist);
		//kp++;
		if ((midpart.apartmin < d)&&(midpart.apartmin > 0)){
			newone=midpart;
		}



	}


	mmmmm=newone.apartmin;

	return newone;

}





void divideandconquer(vector<Point> &plist,int num){
	std::sort(plist.begin(), plist.end(), less_than_x());// sort vector plist based on x



	apart onelist=divideandconquerhelper(plist, num);

	printxy(onelist.apart1.x ,onelist.apart1.y,onelist.apart2.x,onelist.apart2.y,kp);
	//cout<<setprecision(7)<<onelist.apart1.x<<" "<<onelist.apart1.y<<" "<<onelist.apart2.x<<" "<<onelist.apart2.y<<endl;
	//cout<<onelist.apartmin<<endl;
	//cout<<kp<<endl;


}



//===============================================================================main function

int main(int argc, const char * argv[]){
	string line;
	double firstI, SecondI, third;
	int numofpoints = 0;
    int i = 0;


    //get number of points
    getline(cin, line);
 	while (!(line.find_first_not_of("0123456789") == std::string::npos)){
 		cout << "Invalid number of points. Try again"<<endl;
 		getline(cin, line);
 	}
 	//numofpoints = std::stoi( line );
 	istringstream(line)>>numofpoints;

 	vector<Point> Plist;
 	double* xlist=new double[numofpoints];
 	double* ylist=new double[numofpoints];

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
		  		xlist[i]=firstI;
		  		ylist[i]=SecondI;

		  		Plist.push_back(newp);
				//cout<< "my first number is " << setprecision(7)<< Plist[i].x << "second number is " << Plist[i].y <<endl;
		  		i++;
		
			}
	
		}
		else{
		//printf("not all int\n");
		}

	}


	bruteforcesort(xlist, ylist, numofpoints);


	divideandconquer(Plist,numofpoints);



	delete [] xlist;
	delete [] ylist;

}


