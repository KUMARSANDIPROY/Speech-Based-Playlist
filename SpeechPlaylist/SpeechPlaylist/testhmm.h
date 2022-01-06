// test_model_digit.cpp : Defines the entry point for the console application.
//

#include "fstream"
#include "iostream"
#include "string"
#include"string.h"
#include "string"
#include<vector>
#include<cstdlib>
#include <algorithm>
#include <random>

#include "iostream"
#include "fstream"
#include "string"
#include "math.h"
#include "iomanip"
#include <vector>
#include <map>
#define CODE_BOOK_SIZE 32
#define FRAME_SIZE 320
#define FRAMES 60
#define N 5
#define M 32
#define T 60
#define DIGITS 9
#define UTTERENCES 30
int index1=0;
using namespace std;
int accuracy=0;
#pragma warning(disable:4996)
string playListPaths[5] =  {"bengali","english","hindi","tamil","telugu"};
ifstream innnn, in11;
ofstream outtt, out11;

char* code_book_fileee = "codebook.txt";

char obs_sequence_file3[100] = "observation_sequence_testing.txt" ;

const int total_windowww = (FRAME_SIZE + (FRAMES - 1) * 80);
long double code_bookkk[CODE_BOOK_SIZE][12] = { 0 };
long double c_prime_arrrr[T][12] = { 0 };

int frame_cutting_indexx = 1;
int start_markertt = 0;
int end_markerrr = 0;

int output_model_nameee = 0;

//Used Files
//char input_fileee[100] = "Input/184101035_1_24.txt";
char custom_input_fileee[100] ;
char input_fileee[300] = "input.txt";

char* normalized_fileee = "Normalized.txt";
char* silence_filee = "silence_file.txt";
char* trimmed_filee = "trim.txt";
char* ri_filee = "ri_file.txt";
char* ai_fileee = "ai_file.txt";
char* ci_filee = "ci_file.txt";
char* c_prime_fileee = "c_prime.txt";
char* hamming_filee = "Hamming_window.txt";

char a_average_fileee[100] = "a_i_j_final.txt";
char b_average_fileee[100] = "b_i_j_final.txt"; 
char pi_average_fileee[100] = "pi_final.txt";

char* alpha_fileee = "alpha.txt";
long double Pobs_modelll = 0;
long double max_Pobs_modell = 0;

long double tokhura_weightt[12] = { 1, 3, 7, 13, 19, 22, 25, 33, 42, 50, 56, 61 };
long double tokhura_disttt[5] = { 0 };
const int ppp = 12;
int flagg = 0;
int max_sample_indexx = 0;
int remove_header_counterrr = 5;
long double hamming_windoww[320] = { 0 };
long double current_valuee;
long double sum_sampless = 0;
double dc_shift_valuee = 0;
double normalization_ratioo = 1;
long int zcr_counttt = 0;
long int no_of_sampless = 0;
long int no_of_samples11 = 0;
long double max_sample_valueee = 1;
long double sample_arrayy[total_windowww] = { 0 };
long double rrr[12] = { 0 }, kkk[12] = { 0 }, alphaaa[13][13] = { 0 }, Ee[13] = { 0 }, aaa[13] = { 0 }, ccc[12] = { 0 }, c_primeee[12] = { 0 }, ww[12] = { 0 };
int obs23[T + 1];

long double a_i_jjj[N + 1][N + 1];
long double b_i_jjj[N + 1][M + 1];
long double piii[N + 1];

int count_checkkk = 0;

long double alpha_arrrr[N+1][T+1];

long double hamWww[320];
long double Eneee[8000],smallEE[1000];
int c222=0;
int sss,eee;
int scounttt,fcounttt[31];
long double inp_fileee[80000],ciii[1000][12],temppp[80000];
long double sinWww[]={1,2.552914,4,5.242640,6.196152,6.795554,7,6.795554,6.196152,5.242640,4,2.552914271,1};
void store1()
{                         // this function stores the input data from file to array
	
	innnn.open(input_fileee);
	long double x;
	scounttt=0;
	if(innnn==NULL) cout<<"file not open\n";
	while(innnn>>x)
	{
		//cout<<x<<" ";
	    inp_fileee[scounttt]=x;
		scounttt++;
	}
	innnn.close();
}

long double energyyy(int sss)
{                                      //energyyy calculation for aaa frame starting from index sss
	   long double sum=0;
	   for(int i=sss;i<(sss+320);i++) sum+=(inp_fileee[i]*inp_fileee[i]);
       return sum/(long double)320;
}
int secframe(int position)
{
	long double rrr= max(smallEE[position-1],smallEE[position+1]);
		if(rrr==smallEE[position+1]) return position+1;
		else return position-1;

}
int largest(long double arr[], int n)
{
    int i=0;
     
    // Initialize maximum element
    int max = arr[0];
	int innnn=0;
    // Traverse array elements
    // from second and compare
    // every element with current max
    for (i = 1; i < n; i++)
	{
        if (arr[i] > max)
       {    
		   max = arr[i];
		   innnn=i;
		}
	}
    return innnn;
}
void trim()
{
	int val,cnt=320,i=0;
    long double E1=0;
    for(int i=0;i<scounttt;i++)
		{
			if(cnt>0)
				{	
					E1=E1+inp_fileee[i]*inp_fileee[i];
					cnt--;
				}
			if(cnt==0)
				{
					E1=E1/320;
					Eneee[c222]=E1;
					E1=0;
					cnt=320;
					c222++;
				}
		}
	int result = largest(Eneee, c222);

	int c4=0;
	for(int i=0;i<c222;)
	{
		long double sum=0;
		for(int j=i;j<(i+30);j++)
		{
			sum+=Eneee[j];
		}
		sum=sum/30;
		smallEE[c4]=sum;
		c4++;
		i=i+30;
	}
	int result3 = largest(smallEE, c4);
	int result4;
	
	result4= secframe(result3);

	if(result3<result4)
	{
			 sss = result3*30*320;
			
	}
	else
	{
		 sss = result4*30*320;
		 
	}

}

//To calculate DC Shift
void calculate_dc_shift()
{
	long double dc=0;
        for(int i=0;i<scounttt;i++) dc+=inp_fileee[i];
        dc/=scounttt;
        for(int i=0;i<scounttt;i++) inp_fileee[i]-=dc;
}


void normalise()
{                                                // normalising input data innnn inp_fileee[] array
        int i; long double max=inp_fileee[0];
        for( i=1;i<scounttt;i++) if(abs(inp_fileee[i])>max) max=abs(inp_fileee[i]);
        for(i=0;i<scounttt;i++)
		{
		 inp_fileee[i]=(long double)(inp_fileee[i]*5000)/(long double)max; 
		}
}


//Calculating Ri'sss
void calculate_R(int start)
{
	//cout << "\n........Writing Ri'sss to file.........." << endl;
	
	int ccc=0;
	
	long double sum=0;

	for(int g=start; g<(start+FRAME_SIZE); ++g)
			{
				temppp[g] = inp_fileee[g]*hamWww[ccc];
				ccc++;
			}

		for (int j = 0; j <= ppp; j++)
		{
			sum = 0;
			for (int i = start; i < (start+FRAME_SIZE) ; i++)
			{
				if(j+i<(start+FRAME_SIZE))
				{
				  sum+=temppp[j+i]*temppp[i];
				}
			}
			rrr[j]=sum;
		}
}




//calling levenson Durbin for 85 frames one after the another
void calculate_A()
{
	//cout << "\n........Writing Ai'sss Frames to file.........." << endl;
	double sum=0;
    int i,j;
    double eee[13];
	double aa[13][13];
	eee[0]=rrr[0];
    for(i=1;i<=ppp;i++)
	{
  	    sum=0;
		for(j=1;j<i;j++)  sum+=aa[j][i-1]*rrr[i-j];
		if(i==1) sum=0;
		aa[i][i]=(rrr[i]-sum)/eee[i-1];
        
		for(j=1;j<i;j++) aa[j][i]=aa[j][i-1]-aa[i][i]*aa[i-j][i-1];
    	eee[i]=(1-aa[i][i]*aa[i][i])*eee[i-1];
    }
  
    for(i=1;i<=ppp;i++)
	{
        aaa[i]=aa[i][ppp];
    }
}

//Calculate Ci'sss
void calculate_C(int index)
{
	double sum=0;
	for(int m=1;m<=ppp;m++)
	{
		sum=0;
		if(m>1) for(int kkk=1;kkk<m;kkk++) sum+=(long double)(kkk*ciii[index][kkk]*aaa[m-kkk])/(long double)m;
		ciii[index][m]=aaa[m]+sum;
	}
	for(int i=1;i<=ppp;i++)
	{
	   ciii[index][i]*=sinWww[i]; //applying raised sine window to cepstral coefficients
	}
}


void calculate_cepstral_valuesss(int u)
{
	int start=sss;
	int index;
	index=1;
	calculate_dc_shift();
	normalise();
	for(int i=1;i<=T;i++)
	{
		calculate_R(start);
		start=start+320;
		calculate_A();
		calculate_C(index);
		index++;
	}
}

//TO READ CODEBOOK FROM FILE
void read_code_bookkk(){
	innnn.open(code_book_fileee);
	for (int i = 0; i < CODE_BOOK_SIZE; i++){
		for (int j = 0; j < 12; j++){
			innnn >> code_bookkk[i][j];
		}
	}
	innnn.close();
}

//TO PRINT CODEBOOK
void print_code_book(){
	cout << "\n**************** Code Book **************" << endl;
	for (int i = 0; i < CODE_BOOK_SIZE; i++){
		for (int j = 0; j < 12; j++){
			cout << " " << code_bookkk[i][j];
		}
		cout << endl;
	}
}

//Calculating Tokhura'sss Distance Using Code Book
void calculate_tokhura_distance(long double ccc[12], int index){
	int  min_index = 0;
	long double min = 99999;
	long double sum[CODE_BOOK_SIZE] = { 0 };
	string temppp, temp1;

	for (int j = 0; j < CODE_BOOK_SIZE; j++){
		for (int i = 0; i < 12; i++){
			sum[j] += tokhura_weightt[i] * (ccc[i] - code_bookkk[j][i])*(ccc[i] - code_bookkk[j][i]);
		}
		if (sum[j] < min){
			min = sum[j];
			min_index = j;
		}
	}

	obs23[index+1] = min_index + 1;

	//cout << obs23[index+1] << " ";
}

void read_ci_valuesss(){
	int i, j;
	
	
	for (i = 0; i < T; i++)
	{
		for (j = 0; j < 12; j++)
		{
			
			c_prime_arrrr[i][j] = ciii[i+1][j+1];
			
		}
		if(i>=150) break;
		
	}
	
}

void generate_observation_sequence(){
	read_ci_valuesss();
	int i;
	//cout << "\nObservation Sequence:" << endl;
	for (i = 0; i < FRAMES; i++){
		calculate_tokhura_distance(c_prime_arrrr[i], i);
	}
	//write_observation_sequence();
}
void hammingWin()
{                    //it calculates hamming window 
	for(int i=0;i<320;i++){
	    hamWww[i]=0.54-(0.46*(cos((2*3.14159265*i)/319)));
	}
}
void write_observation_sequence(){

	int i;
	for (i = 0; i < T; i++)
		outtt << obs23[i] << "\t";
	outtt << endl;
}

//TO READ A MATRIX FROM FILE
void read_Aij_valuesss(char fn[]){
	innnn.open(fn);
	string temppp;
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			innnn >> temppp;
			a_i_jjj[i][j] = stold(temppp);
		}
	}
	/*cout << "A:" << endl;
	for (int i = 1; i <= N; i++){
	for (int j = 1; j <= N; j++){
	printf("%.30Lf  ", a_i_jjj[i][j]);
	}
	cout << endl;
	}*/
	innnn.close();
}

//TO READ B MATRIX FROM FILE
void read_Bij_valuesf(char fn[]){
	innnn.open(fn);
	string temppp;
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= M; j++){
			innnn >> temppp;
			b_i_jjj[i][j] = stold(temppp);
		}
	}
	/*cout << "B:" << endl;
	for (int i = 1; i <= N; i++){
	for (int j = 1; j <= M; j++){
	printf("%.30Lf\n", b_i_jjj[i][j]);
	}
	cout << endl << endl;
	}*/
	innnn.close();
}

//TO READ PI VALUES FROM FILE
void read_pi_valuesss(char fn[]){
	innnn.open(fn);
	string temppp;
	int index = 1;
	while (innnn >> temppp){
		piii[index++] = stold(temppp);
	}
	innnn.close();
	/*cout << "Pi values:" << endl;
	for (int i = 1; i < index; i++)
	printf("%.30Lf\n", piii[i]);*/
}


void read_average_modeles(int iteration){
	char index[3];
	strcpy(a_average_fileee, "average_models/A_avg_");
	sprintf(index, "%d", iteration);
	strcat(a_average_fileee, index);
	strcat(a_average_fileee, ".txt");
	//cout << a_average_fileee << endl;
	read_Aij_valuesss(a_average_fileee);

	strcpy(b_average_fileee, "average_models/B_avg_");
	sprintf(index, "%d", iteration);
	strcat(b_average_fileee, index);
	strcat(b_average_fileee, ".txt");
	//cout << b_average_fileee << endl;
	read_Bij_valuesf(b_average_fileee);

	strcpy(pi_average_fileee, "average_models/pi_avg_");
	sprintf(index, "%d", iteration);
	strcat(pi_average_fileee, index);
	strcat(pi_average_fileee, ".txt");
	//cout << pi_average_fileee << endl;
	read_pi_valuesss(pi_average_fileee);
}

//TO PERFORM THE FORWARD PROCEDURE
void forward_procedure(int iteration){

	int i, j, t;
	long double sum = 0;
	//for (i = 0; i < T; i++)
		//cout << "OBSss:" << obs23[i] << " ";

	for (i = 1; i <= N; i++){
		alpha_arrrr[i][1] = piii[i] * b_i_jjj[i][obs23[1]];		
		//cout << alphaaa[i][1] << endl;
	}

	//CALCULATING ALPHA MATRIX
	for (t = 1; t <= T - 1; t++){
		for (j = 1; j <= N; j++){
			sum = 0;
			for (i = 1; i <= N; i++){
				
				sum += alpha_arrrr[i][t] * a_i_jjj[i][j];
			}

			alpha_arrrr[j][t + 1] = sum * b_i_jjj[j][obs23[t + 1]];
		}
	}

	//PRINTING ALPHA
	/* << "\nAlpha Matrix:" << endl;
	for (i = 1; i <= N; i++){
	for (j = 1; j <= T; j++){
	printf("%Le\n", alphaaa[i][j]);
	}
	cout << endl << endl;
	}*/



	//WRITING ALPHA TO FILE
	outtt.open(alpha_fileee);
	for (i = 1; i <= T; i++){
		for (j = 1; j <= N; j++){
			outtt << /*fixed << setprecision(FILE_DECIMAL_PRECISION_VALUE) <<*/ alpha_arrrr[j][i] << " ";
		}
		outtt << endl;
	}
	outtt.close();


	//CALCULATING PROBABILITY OF OBSERVATION SEQUENCE GIVEN MODEL
	sum = 0;
	for (i = 1; i <= N; i++){
		sum += alpha_arrrr[i][T];
	}

	Pobs_modelll = sum;
	if (Pobs_modelll > max_Pobs_modell){
		max_Pobs_modell = Pobs_modelll;
		output_model_nameee = iteration;
	}
	cout << "Digit:"<<iteration<<"\tP(obs/model) : " << Pobs_modelll <<endl;
}


void solution_to_problem1(int iteration){	
	forward_procedure(iteration);
}
/*
void openFolder(int spokenWord)
{
	char explorer[100];
	strcpy(explorer, "start explorer ");
	const char* path = playListPaths[spokenWord].c_str() ;
	string command = strcat( explorer,path);
	system(command.c_str());
}*/
void check_detection(int digit){	
	cout << "\nActual Digit File:" << digit<<endl;
	cout << "Detected Digit:" << output_model_nameee << endl;
	if (digit == output_model_nameee){
		count_checkkk++;
		accuracy++;
	}
}
void openFolder(int spokenWord)
{
	
	string s= "SOUNDS\\"+playListPaths[spokenWord]+".wav";
	PlaySound(s.c_str(), NULL, SND_SYNC);
	char explorer[100];
	strcpy(explorer, "start explorer ");
	const char* path = playListPaths[spokenWord].c_str() ;
	string command = strcat( explorer,path);
	system(command.c_str());
}

int testing(int choice)
{
	int i, j ,kkk;
	int utterence_counter = 0;
//	int choice = 0;
	hammingWin();
	//cout << ".....Recording will be for 3 seconds......" << endl;
	//cout << "....... Recording Silence......" << endl;
	//system("Recording_Module.exe 3 silence.wav silence_filee.txt");
	//cout << "\nSilence recorded. **Press Enter to record your DIGIT**" << endl;
	//system("Recording_Module.exe 3 input.wav input.txt");
	//cout << "\nRecording successfull **Press ENTER to proceed with program**" << endl;

	//cout << "\nSELECT A CHOICE:" << endl;
	//cout << "Press 1. To Test using TEST DATA innnn Test Folder" << endl;
	//cout << "Press 2. To Give Your Filename (*File Must be innnn 'recorded digits' Folder*)" << endl;
	//cout<< "Press 3. LIve test"<<endl;
	//cout << "Enter Your Choice ?" << endl;
	//cin >> choice;

	if (choice == 1){
		count_checkkk = 0;
		for (i = 0; i <= 4; i++)
		{
			char index[30];

			for (j = 21; j <= 30; j++)
			{
				utterence_counter++;
				strcpy(input_fileee, "recordings/21401026_");
				//sprintf(index, "%d", i);
				//strcat(input_fileee, index);
				if(i==0)
					strcat(input_fileee, "Bengali");
				else if(i==1)
					strcat(input_fileee, "English");
				else if(i==2)
					strcat(input_fileee, "Hindi");
				else if(i==3)
					strcat(input_fileee, "Tamil");
				else if(i==4)
					strcat(input_fileee, "Telugu");
				strcat(input_fileee, "_");
				sprintf(index, "%d", j);
				strcat(input_fileee, index);
				strcat(input_fileee, ".txt");

				cout << "\n.................................................................................................." << endl;
				cout << "Reading Input from : " << input_fileee << endl;
				store1();
				trim();
				calculate_cepstral_valuesss(utterence_counter-1);
				read_code_bookkk();
				//print_code_book();
				generate_observation_sequence();
				outtt.open(obs_sequence_file3);
				write_observation_sequence();
				outtt.close();
				output_model_nameee = 0;
				max_Pobs_modell = 0;
				for (kkk = 0; kkk <= 4; kkk++){
					read_average_modeles(kkk);
					solution_to_problem1(kkk);
					
				}

				check_detection(i);
				
				c222=0;
			}
		}
		cout << "\n\nTotal Files Checked:" << utterence_counter << endl;
		cout << "Correct Recognized:" << accuracy << endl;
		return accuracy*2;
	}
	else if (choice == 2){
		strcpy(input_fileee, "recorded_digits/");
		cout << "\nEnter File Name:" << endl;
		cin >> custom_input_fileee;
		strcat(input_fileee, custom_input_fileee);
		cout << "\n.................................................................................................." << endl;
		cout << "Reading Input from : " << input_fileee << endl;
		
		calculate_cepstral_valuesss(0);
		read_code_bookkk();
		//print_code_book();
		generate_observation_sequence();
		outtt.open(obs_sequence_file3);
		write_observation_sequence();
		outtt.close();
		output_model_nameee = 0;
		max_Pobs_modell = 0;
		for (kkk = 0; kkk <= 9; kkk++){
			read_average_modeles(kkk);
			solution_to_problem1(kkk);
		}

		cout << "Detected Digit:" << output_model_nameee << endl;
	}
	else if(choice==3)
	{
			string sss="Recording_Module.exe 3 ";
	       string s1="./test_data/";
			char buffer[10];
			sprintf(buffer,"test");
			string s2=s1+buffer+".txt";
			string s3=s1+buffer+".wav";
			cout<<"\n"<<s2<<endl;
			string sfin= sss+s3+" "+s2;
			system(sfin.c_str());
			
		//strcpy(input_fileee, "recorded_digits/");
		strcpy(input_fileee, "test_data/test.txt");
		//cout << "\nEnter File Name:" << endl;
		//cin >> custom_input_fileee;
		//strcat(input_fileee, custom_input_fileee);
		cout << "\n.................................................................................................." << endl;
		cout << "Reading Input from : " << input_fileee << endl;
		store1();
		trim();
				
		calculate_cepstral_valuesss(0);
		read_code_bookkk();
		//print_code_book();
		generate_observation_sequence();
		outtt.open(obs_sequence_file3);
		write_observation_sequence();
		outtt.close();
		output_model_nameee = 0;
		max_Pobs_modell = 0;
		for (kkk = 0; kkk <= 4; kkk++){
			read_average_modeles(kkk);
			solution_to_problem1(kkk);
		}

		cout << "Detected Digit:" << output_model_nameee << endl;
	
		openFolder(output_model_nameee);
			
      
	}
	else{
		cout << "\nPlease Enter aaa Valid Choice" << endl;
	}
	return output_model_nameee ;
	
}




