
#include"string"
#include <windows.h>
using namespace std;

int recording1(int i,int j)
{
	string s="Recording_Module.exe 3 ";
	string s1="Play";
	
	//char buffer[10];
	//sprintf(buffer,"%d_%d",i,j);
	string s2=s1+".txt";
	string s3=s1+".wav";

	
	string sfin= s+s3+" "+s2;
	cout<<"\n"<<sfin<<endl;
	system(sfin.c_str());
	
	return 0;
}