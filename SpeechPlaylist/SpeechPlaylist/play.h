#include <iostream>

using namespace std;
#include <Windows.h>
#include <MMSystem.h>
#include<fstream>



void play()
{
	char audiofile_char[50]="Play.wav";
	string audiofile_str;
	ifstream fp;
	fp.open(audiofile_char);
if (fp != NULL)
    {
    	/* open function doesn't work with a variable of string type and PlaySound function doesn't work with char array hence first we used char array and here we are converting it to a string. so that we can use it in PlaySound function */ 
    	string audiofile_str =audiofile_char;	
    	
  /* PlaySound function is used to play a sound specified by the given file name. */
  /* SND_SYNC : play sound synchronously */
  /* .c_str() function is used to return a pointer to an array that contains a null-terminated sequence of characters representing the current value of the string object. */
  PlaySound(audiofile_str.c_str(), NULL, SND_SYNC);
  }

 fp.close();
}
bool copyFile(const char *SRC, const char* DEST)
{
    std::ifstream src(SRC, std::ios::binary);
    std::ofstream dest(DEST, std::ios::binary);
    dest << src.rdbuf();
    return src && dest;
}
void save(int i, int j)
{
	char audiofile_char[50]="Play.txt";
	char buffer[100];
	sprintf(buffer,"./REC/%d_%d.txt",i,j);
	copyFile(audiofile_char, buffer);
	//cout<<"yes";
}


void update()
{
	
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<=4;j++)
		{
			if(i==0)
			{
				char buffer[100];
				sprintf(buffer,"./output/average_models/A_avg_%d.txt",j);
				char newfil[100];
				sprintf(newfil,"./average_models/A_avg_%d.txt",j);
				copyFile(buffer, newfil);
			}
			if(i==1)
			{
				char buffer[100];
				sprintf(buffer,"./output/average_models/B_avg_%d.txt",j);
				char newfil[100];
				sprintf(newfil,"./average_models/B_avg_%d.txt",j);
				copyFile(buffer, newfil);
			}
			if(i==2)
			{
				char buffer[100];
				sprintf(buffer,"./output/average_models/pi_avg_%d.txt",j);
				char newfil[100];
				sprintf(newfil,"./average_models/pi_avg_%d.txt",j);
				copyFile(buffer, newfil);
			}
			
		}
	}
}

void textplay()
{
	PlaySound(TEXT("SOUNDS\\Welcom1.wav"), NULL, SND_SYNC);
}