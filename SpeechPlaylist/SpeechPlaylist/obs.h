
#define CODE_BOOK_SIZE 32
#define FRAME_SIZE 320
#define FRAMES 60
#define N 5
#define M 32
#define T 60
#define WORDS 5
#define UTTERENCES 30

using namespace std;
#pragma warning(disable:4996)
long double Ene[8000],smallE[1000];
int c2=0;
ifstream inn, in1;
ofstream outt, out1,uni;

char* code_book_file = "codebook.txt";
int utterence_counter = 0;

int total_window ;
long double code_book[CODE_BOOK_SIZE][12] = { 0 };
long double c_prime_arr[150][12] = { 0 };

int frame_cutting_index = 1;
int start_marker = 0;
int end_marker = 0;

int output_model_name = 0;
int s,e;
int scount,fcount[31];
long double inp_file[80000],ci[1000][12],temp[80000];
long double sinW[]={1,2.552914,4,5.242640,6.196152,6.795554,7,6.795554,6.196152,5.242640,4,2.552914271,1};
//Used Files
//char input_file[100] = "Input/184101035_1_24.txt";
char custom_input_file[100] ;
char input_file[100] = "input.txt";
char output_file[100] ="./Input/";
char* normalized_file = "Normalized.txt";
char* silence_file = "silence_file.txt";
char* trimmed_file = "trim.txt";
char* ri_file = "ri_file.txt";
char* ai_file = "ai_file.txt";
char* ci_file = "ci_file.txt";
char* c_prime_file = "c_prime.txt";
char* hamming_file = "Hamming_window.txt";

char a_average_filee[100] = "a_i_j_final.txt";
char b_average_filee[100] = "b_i_j_final.txt";
char pi_average_filee[100] = "pi_final.txt";

char* alpha_filee = "alphaa.txt";
long double Pobs_modell = 0;
long double max_Pobs_model = 0;

long double tokhura_weight[12] = { 1, 3, 7, 13, 19, 22, 25, 33, 42, 50, 56, 61 };
long double tokhura_dist[5] = { 0 };
const int p = 12;
int flag = 0;
int max_sample_index = 0;
int remove_header_counter = 5;
long double hamming_window[320] = { 0 };
long double current_value;
long double sum_samples = 0;
double dc_shift_value = 0;
double normalization_ratio = 1;
long int zcr_count = 0;
long int no_of_samples = 0;
long int no_of_samples1 = 0;
long double max_sample_value = 1;
long double sample_array[80000] = { 0 };
long double r[12] = { 0 }, k[12] = { 0 }, alphaa[13][13] = { 0 }, E[13] = { 0 }, a[13] = { 0 }, c[12] = { 0 }, c_prime[12] = { 0 }, w[12] = { 0 };
int obss[T + 1];

long double a_i_jj[N + 1][N + 1];
long double b_i_jj[N + 1][M + 1];
long double pii[N + 1];

int count_check = 0;

long double alpha_arr[N+1][T+1];

long double hamW[320];

//To get Hamming Windows values to array from the pre-calculated File
void get_hamming_window(){
	int index_count = 0;
	inn.open(hamming_file);
	string temp = "";
	while (inn >> temp){
		hamming_window[index_count++] = stod(temp);
	}
	inn.close();
}

void store(){                         // this function stores the input data from file to array
	
	inn.open(input_file);
	long double x;
	scount=0;
	if(inn==NULL) cout<<"file not open\n";
	while(inn>>x)
	{
		//cout<<x<<" ";
	    inp_file[scount]=x;
		scount++;
	}
	inn.close();
}

long double energy(int s)
{                                      //energy calculation for a frame starting from index s
	   long double sum=0;
	   for(int i=s;i<(s+320);i++) sum+=(inp_file[i]*inp_file[i]);
       return sum/(long double)320;
}

int largesttt(long double arr[], int n)
{
    int i=0;
     
    // Initialize maximum element
    int max = arr[0];
	int in=0;
    // Traverse array elements
    // from second and compare
    // every element with current max
    for (i = 1; i < n; i++)
	{
        if (arr[i] > max)
       {    
		   max = arr[i];
		   in=i;
		}
	}
    return in;
}
int secframe1(int position)
{
	long double rrr= max(smallEE[position-1],smallEE[position+1]);
		if(rrr==smallEE[position+1]) return position+1;
		else return position-1;

}
void trimmm()
{
	int val,cnt=320,i=0;
    long double E1=0;
    for(int i=0;i<scount;i++)
		{
			if(cnt>0)
				{	
					E1=E1+inp_file[i]*inp_file[i];
					cnt--;
				}
			if(cnt==0)
				{
					E1=E1/320;
					Ene[c2]=E1;
					E1=0;
					cnt=320;
					c2++;
				}
		}
	int result = largesttt(Ene, c2);

	int c4=0;
	for(int i=0;i<c2;)
	{
		long double sum=0;
		for(int j=i;j<(i+30);j++)
		{
			sum+=Ene[j];
		}
		sum=sum/30;
		smallE[c4]=sum;
		c4++;
		i=i+30;
	}
	int result3 = largesttt(smallE, c4);
	int result4;
	
	result4= secframe1(result3);

	if(result3<result4)
	{
			 s = result3*30*320;
			 e = (result4+1)*30*320;
	}
	else
	{
		 s = result4*30*320;
		 e = (result3+1)*30*320;
	}

}

//To calculate DC Shift
void calculate_dc_shifttt()
{
	long double dc=0;
        for(int i=0;i<scount;i++) dc+=inp_file[i];
        dc/=scount;
        for(int i=0;i<scount;i++) inp_file[i]-=dc;
}


void normalisess()
{                                                // normalising input data in inp_file[] array
        int i; long double max=inp_file[0];
        for( i=1;i<scount;i++) if(abs(inp_file[i])>max) max=abs(inp_file[i]);
        for(i=0;i<scount;i++)
		{
		 inp_file[i]=(long double)(inp_file[i]*5000)/(long double)max; 
		}
}


//Calculating Ri's
void calculate_Ris(int start)
{
	//cout << "\n........Writing Ri's to file.........." << endl;
	
	int c=0;
	
	long double sum=0;

	for(int g=start; g<(start+FRAME_SIZE); ++g)
			{
				temp[g] = inp_file[g]*hamW[c];
				c++;
			}

		for (int j = 0; j <= p; j++)
		{
			sum = 0;
			for (int i = start; i < (start+FRAME_SIZE) ; i++)
			{
				if(j+i<(start+FRAME_SIZE))
				{
				  sum+=temp[j+i]*temp[i];
				}
			}
			r[j]=sum;
		}
}

//Calculate Ai's using Levenson-Durbin
void levenson_durbin(long double r[]){
	int i, j;
	long double summation = 0;

	E[0] = r[0];
	for (i = 1; i <= p; i++){
		summation = 0.0;
		for (j = 1; j <= i - 1; j++){
			summation += alphaa[j][i - 1] * r[i - j];
		}
		k[i] = (r[i] - summation) / E[i - 1];
		alphaa[i][i] = k[i];
		for (j = 1; j <= i - 1; j++){
			alphaa[j][i] = alphaa[j][i - 1] - (k[i] * alphaa[i - j][i - 1]);
		}
		E[i] = (1 - (k[i] * k[i]))*E[i - 1];
	}
	//cout << endl;

	//Calculating the Ai's as the last last column of index i.e. 12th column of matrix alphaa
	outt.open(ai_file, std::ios_base::app);
	a[0] = 0.0;
	outt << a[0] << " ";
	for (int i = 1; i <= p; i++){
		a[i] = alphaa[i][12];
		//printf("\nA[%d] : %Lf ", i, a[i]);
		outt << fixed << a[i] << " ";
	}
	outt << endl;
	outt.close();
}

//calling levenson Durbin for 85 frames one after the another
void calculate_Ais(){
	//cout << "\n........Writing Ai's Frames to file.........." << endl;
	double sum=0;
    int i,j;
    double e[13];
	double aa[13][13];
	e[0]=r[0];
    for(i=1;i<=p;i++)
	{
  	    sum=0;
		for(j=1;j<i;j++)  sum+=aa[j][i-1]*r[i-j];
		if(i==1) sum=0;
		aa[i][i]=(r[i]-sum)/e[i-1];
        
		for(j=1;j<i;j++) aa[j][i]=aa[j][i-1]-aa[i][i]*aa[i-j][i-1];
    	e[i]=(1-aa[i][i]*aa[i][i])*e[i-1];
    }
  
    for(i=1;i<=p;i++)
	{
        a[i]=aa[i][p];
    }
}

//Calculate Ci's
void calculate_Cis(int index)
{
	double sum=0;
	for(int m=1;m<=p;m++)
	{
		sum=0;
		if(m>1) for(int k=1;k<m;k++) sum+=(long double)(k*ci[index][k]*a[m-k])/(long double)m;
		ci[index][m]=a[m]+sum;
	}
	for(int i=1;i<=p;i++)
	{
	   ci[index][i]*=sinW[i]; //applying raised sine window to cepstral coefficients
	}
}

//To calculate C Prime(Raised Sine wave)
void calculate_c_prime(){
	//cout << "\n........Writing Ci Prime Frames to file.........." << endl;
	string temp;
	int count = 0;
	inn.open(ci_file);
	
	//Calculting CiPrimes by reading Ci values from File
	out1.open(c_prime_file);
	
	for (int k = 0; k < T; k++){
		while (count < 12){
			inn >> temp;
			c[count] = stod(temp);
			count++;
		}
		for (int m = 1; m <= p; m++){
			w[m] = 1.0 + 6.0 * sin((22.0 / 7.0)*m / 12.0);
			c_prime[m] = c[m - 1] * w[m];
		}
		for (int m = 1; m <= p; m++){
			//printf("\nC_Prime[%d] : %Lf ", m, c_prime[m]);
			outt << c_prime[m] << " ";
			out1 << c_prime[m] << " ";
			//out1 << c_prime[m] << " ";
			c[m] = 0;
			c_prime[m] = 0;
		}
		//cout << endl;
		outt << endl;
		out1 << endl;
		//out1 << endl;
		count = 0;
	}
	inn.close();
	outt.close();

	//out1.close();
}

void calculate_cepstral_values(int u)
{
	int start=s;
	int index;
	index=1;
	calculate_dc_shifttt();
	normalisess();
	for(int i=1;i<=T;i++)
	{
		calculate_Ris(start);
		start=start+320;
		calculate_Ais();
		calculate_Cis(index);
		index++;
	}
}

//TO READ CODEBOOK FROM FILE
void read_code_book(){
	inn.open(code_book_file);
	for (int i = 0; i < CODE_BOOK_SIZE; i++){
		for (int j = 0; j < 12; j++){
			inn >> code_book[i][j];
		}
	}
	inn.close();
}

//TO PRINT CODEBOOK


//Calculating Tokhura's Distance Using Code Book
void calculate_tokhura_distancess(long double c[12], int index)
{
	int  min_index = 0;
	long double min = 99999;
	long double sum[CODE_BOOK_SIZE] = { 0 };
	string temp, temp1;

	for (int j = 0; j < CODE_BOOK_SIZE; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			sum[j] += tokhura_weight[i] * (c[i] - code_book[j][i])*(c[i] - code_book[j][i]);
		}
		if (sum[j] < min){
			min = sum[j];
			min_index = j;
		}
	}

	obss[index+1] = min_index + 1;

	//cout << obss[index+1] << " ";
}

void read_ci_values(){
	int i, j;
	
	
	for (i = 0; i < T; i++)
	{
		for (j = 0; j < 12; j++)
		{
			
			c_prime_arr[i][j] = ci[i+1][j+1];
			
		}
		if(i>=150) break;
		
	}
	
}
void write_observation_sequence(ofstream &outb){

	int i;
	for (i = 1; i <= T ; i++)
		outb << obss[i] << "\t";
	outb << endl;
}
void generate_observation_sequence(ofstream &outb)
{
	read_ci_values();
	int i;
	//cout << "\nObservation Sequence:" << endl;
	for (i = 0; i < T; i++)
	{
		calculate_tokhura_distancess(c_prime_arr[i], i);
	}
	write_observation_sequence(outb);
}

void hammingW()
{                    //it calculates hamming window 
	for(int i=0;i<320;i++){
	    hamW[i]=0.54-(0.46*(cos((2*3.14159265*i)/319)));
	}
}
void obsgenerate()
{
	int i, j ,k;
	hammingW();
	uni.open("NewUnivesres.txt");
	for (i = 0; i < WORDS; i++)
	{
			char index[3];
			char buffer[30];
			strcpy(output_file, "./Input/");
			sprintf(buffer,"OBS_%d.txt",i);
            strcat(output_file, buffer);
			ofstream outb;
			outb.open(output_file);
			for ( j = 1; j <= 20; j++)
			{
				utterence_counter++;
				strcpy(input_file, "REC/");
				sprintf(index, "%d", i);
				strcat(input_file, index);
				strcat(input_file, "_");
				sprintf(index, "%d", j);
				strcat(input_file, index);
				strcat(input_file, ".txt");
				cout << "\n.................................................................................................." << endl;
				cout << "Reading Input from : " << input_file << endl;
				store();
				trimmm();
				calculate_cepstral_values(utterence_counter-1);
				read_code_book();
				//print_code_book();
				generate_observation_sequence(outb);
				c2=0;

			}
			utterence_counter=0;
			outb.close();
		}
}