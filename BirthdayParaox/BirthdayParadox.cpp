//============================================================================
// Name        : BirthdayParadox.cpp
// Author      : Rishi Khetan
// Version     :
// Copyright   : Dota 2
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include <math.h>
#include <cstdlib>
using namespace std;

int BP(int n)
{
	int birthday[23];
	int i;
	for(i=0;i<23;i++)
	{
		birthday[i]=rand()%365+1;
		cout<<"Birthday of Person "<<i+1<<" :: "<<birthday[i]<<"\n";
	}

	double p=(n*(n-1))/2;
	cout<<p<<"\n";
    double u=(364.0/365.0);
    cout<<fixed<<setprecision(4)<<u*100.0<<"\n";
    double cp=pow(u,p);
    cout<<cp*100.0<<"\n";
    double cm=1-cp;
    cout<<cm*100.0<<"\n";

    int j;
    int c=0,m=0;
    for(i=0;i<23;i++)
    {
    	for(j=i+1;j<23;j++)
    	{
    		c++;
    		if( (birthday[i]==birthday[j]) )
    		{
    			cout<<"Comparison Number :: "<<c<<"\n";
    			cout<<"Birthday ["<<i<<"] = "<<birthday[i]<<"\tBirthday ["<<j<<"] = "<<birthday[j];
    			cout<<"\n Match Number :: "<<++m<<"\n";
    		}
    	}
    }
    if(m>0)
    	return 1;
    else
    	return 0;
}

int main()
{
	cout << "Gamester" << endl; // prints Gamester
	int t=0; // number of trials
	int rm=0; // result for match
	int sm=0; // successful match
	float am; // actual match
	int i;
	cout<<"\n Enter the number of trials :: \n";
	cin>>t;
	for(i=1;i<=t;i++)
	{
		cout<<"Trial Number :: "<<i<<"\n";
		rm=BP(23);
		if(rm==1)
			sm++;
		else
			cout<<"No match found in Trial Number :: "<<i<<"\n";
		am=(float)sm/(float)i;
		cout<<"\n Actual Match % ::  "<<am*100.0<<" = ("<<sm<<"/"<<i<<") \n";
	}
	cout<<"Deviation of Actual Match from the Theoertical Probability Value :: "<<fabs(((am*100.0)-50.0477))<<"\n";
	return 0;
}
