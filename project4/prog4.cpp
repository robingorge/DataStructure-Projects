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

struct error{
	int index;
	double err;

	error(): index(-1), err(-1) {}
};




double minmedianerror=-100;
double mina=0;
double minb=0;
vector<error> Elist;


struct error_less
{
    inline bool operator() (const error& struct1, const error& struct2)
    {
        return (struct1.err < struct2.err);
    }
};


//===============================================================================


bool is_digits(const string &str)
{
  return str.find_first_not_of("0123456789 .-") == std::string::npos;
}



//mx+n=y, x0 y0,  distance= |mx0 - y0 + 0| / sqrt(m*m + 1)
double caculateerror(double m, double n, int index){
	double x= Plist[index].x;
	double y= Plist[index].y;

	double a= abs(m*x-y+n);
	double b= sqrt(m*m+1);

	return a/b;

}


int randNum(){
	int min=1;
	int max=Plist.size();

	int x = rand() % min +  max - 1;

	return x;
}



//===============================================================================

void process(){


	srand(time(NULL));
	int times= 10000;
	int i=0;
	while (i<times){

		int numofpoint=Plist.size();	
		// int a = 0 + (rand() % static_cast<int>(numofpoint - 1 - 0 + 1));
		// int b = 0 + (rand() % static_cast<int>(numofpoint - 1 - 0 + 1));


		int minNum=0;
		int maxNum=Plist.size()-1;



		int a=std::rand() % (maxNum-minNum+1)+minNum;
		int b=std::rand() % (maxNum-minNum+1)+minNum;

		//cout<< a <<"   random value  "<<b<<endl;

		while (a==b){
			// b = 0 + (rand() % static_cast<int>(numofpoint - 1 - 0 + 1));
			b=std::rand() % (maxNum-minNum+1)+minNum;
		}


		Point ap=Plist[a];
		Point bp=Plist[b];


		double slope=(ap.y-bp.y)/(ap.x-bp.x);
		double bvalue= ap.y-slope*ap.x;


		vector<error> newlist;


		for (int k=0; k<numofpoint; k++){
			if ((k!=a)&&(k!=b)){
				double tmperr = caculateerror(slope,bvalue,k);
				error tmpone;
				tmpone.index=k;
				tmpone.err=tmperr;
				newlist.push_back(tmpone);
			}
		}

		std::sort(newlist.begin(), newlist.end(), error_less());


		int indexofmederror=(newlist.size()-1)/2;

		double tmpmederror=newlist[indexofmederror].err;

		if ((minmedianerror<0)||(tmpmederror<minmedianerror)){

			Elist=newlist;
			minmedianerror=tmpmederror;
			mina=slope;
			minb=bvalue;

			//cout<<"minnnnnnn"<<mina<<"    "<<minb<<"     "<<minmedianerror<<endl;

		}
		i++;

	}

}



    inline static double sqr(double x) {
        return x*x;
    }


    int linreg(int n, const vector<Point> lsxy, double* m, double* b, double* r)
    {
        double   sumx = 0.0;                        /* sum of x                      */
        double   sumx2 = 0.0;                       /* sum of x**2                   */
        double   sumxy = 0.0;                       /* sum of x * y                  */
        double   sumy = 0.0;                        /* sum of y                      */
        double   sumy2 = 0.0;                       /* sum of y**2                   */

       for (int i=0;i<n;i++)   
          { 
          sumx  += lsxy[i].x;       
          sumx2 += sqr(lsxy[i].x);  
          sumxy += lsxy[i].x * lsxy[i].y;
          sumy  += lsxy[i].y;      
          sumy2 += sqr(lsxy[i].y); 
          } 

       double denom = (n * sumx2 - sqr(sumx));
       if (denom == 0) {
           // singular matrix. can't solve the problem.
           *m = 0;
           *b = 0;
           if (r) *r = 0;
           return 1;
       }

       *m = (n * sumxy  -  sumx * sumy) / denom;
       *b = (sumy * sumx2  -  sumx * sumxy) / denom;
       if (r!=NULL) {
          *r = (sumxy - sumx * sumy / n) /          /* compute correlation coeff     */
                sqrt((sumx2 - sqr(sumx)/n) *
                (sumy2 - sqr(sumy)/n));
       }

       return 0; 
    }








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
 	numofpoints = std::stoi( line );
 	cout<<numofpoints<<endl;



 	//get points value
	while ((i<numofpoints)&&(getline(cin,line))){

			stringstream ss(line);
	  		ss>>firstI>>SecondI;
	  		
				//cout<< "my first number is " << setprecision(7)<< firstI << "second number is " << SecondI <<endl;
				Point newone(firstI,SecondI);				
		  		Plist.push_back(newone);
				//cout<< "my first number is " << Plist[i].x << "   second number is " << Plist[i].y <<endl;
		  		i++;
	

	}



	process();



	int n = (Elist.size()-1)/2;

	vector<Point> lsfit;

	for (int i=0; i<n; i++){
		int thisone=Elist[i].index;
		lsfit.push_back(Plist[thisone]);
	}


    double m,b1,r;

    linreg(lsfit.size(), lsfit ,&m,&b1,&r);

    printf("a=%g b=%g\n",m,b1);

    return 0;


}

//===============================================================================main function

// int main(int argc, const char * argv[]){


// 	// std::ifstream infile1("x_big_moreNoise.txt");
// 	// std::ifstream infile2("y_big_moreNoise.txt");

// 	// std::ifstream infile1("x_big_noNoise.txt");
// 	// std::ifstream infile2("y_big_noNoise.txt");

// 	// std::ifstream infile1("x_big_someNoise.txt");
// 	// std::ifstream infile2("y_big_someNoise.txt");

// 	// std::ifstream infile1("x_moreNoise.txt");
// 	// std::ifstream infile2("y_moreNoise.txt");

// 	std::ifstream infile1("x_someNoise.txt");
// 	std::ifstream infile2("y_someNoise.txt");

// 	// std::ifstream infile1("x_noNoise.txt");
// 	// std::ifstream infile2("y_noNoise.txt");



// 	double a,b;
// 	std::string line1,line2;
// 	while ((std::getline(infile1, line1))&&(std::getline(infile2,line2)))
// 	{
//     	stringstream ss1(line1);
//     	stringstream ss2(line2);
//     	ss1>>a;
//     	ss2>>b;
//     	if ((!ss1)||(!ss2)) { 
//     		break; 
//     		cout<<"error"<<endl;
//     		return 0;
//     	}
//     	else{
//     		cout<<setprecision(7)<<a<<"   "<<b<<endl;
//     		Point newone(a,b);
//     		Plist.push_back(newone);
//     	}
// 	}

// 	process();



// 	int n = Elist.size()/2;

// 	vector<Point> lsfit;

// 	for (int i=0; i<n; i++){
// 		int thisone=Elist[i].index;
// 		lsfit.push_back(Plist[thisone]);
// 	}


//     double m,b1,r;

//     linreg(lsfit.size(), lsfit ,&m,&b1,&r);

//     printf("m=%g b=%g r=%g\n",m,b1,r);

//     return 0;


// }


