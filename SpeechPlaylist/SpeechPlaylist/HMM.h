// train_model_digit.cpp : Defines the entry point for the console application.
//


#pragma warning(disable:4996)
using namespace std;

#define M 32
#define N 5
#define T 60
#define FILE_DECIMAL_PRECISION_VALUE 30
#define B_I_J_THRESHOLD pow(10.0,-30.0)
#define CONVERGENCE_THRESHOLD pow(10.0,-60.0)
#define TRAIN_ITERATIONS 20
#define ITERATIONS 3
#define WORDS 5

ifstream in,in_obs;
ofstream out;
int flag1=1;
char obs_sequence_file[300];
char* a_file = "a_i_j.txt";
char* b_file = "b_i_j.txt";
char* pi_file = "pi.txt";
char* obs_seq_1_file = "obs_seq_1.txt";
char* obs_seq_2_file = "obs_seq_2.txt";

char* alpha_file = "alpha.txt";
char* beta_file = "beta.txt";
char* qstar1_file = "state_sequence_viterbi.txt";
//char* qstar2_file = "state_sequence_gamma.txt";

char a_file_final[100] = "a_i_j_final.txt";
char b_file_final[100] = "b_i_j_final.txt";
char pi_file_final[100] = "pi_final.txt";

char a_average_file[100] = "a_i_j_final.txt";
char b_average_file[100] = "b_i_j_final.txt";
char pi_average_file[100] = "pi_final.txt";


long double a_i_j[N + 1][N + 1];
long double b_i_j[N + 1][M + 1];
long double pi[N + 1];
int obs[T + 1];

long double a_i_j_average[N + 1][N + 1];
long double b_i_j_average[N + 1][M + 1];
long double pi_average[N + 1];

long double alpha[N + 1][T + 1];
long double beta[N + 1][T + 1];
long double Pobs_model = 0;

long double delta[N + 1][T + 1];
long double pstar = 0;
long double previous_pstar = 0;
long double pstar_difference = 0;
int psi[N + 1][T + 1];
int qstar, qstar1[T + 1];

long double Xi[N + 1][N + 1][T];
long double gamma[N + 1][T + 1];
long double gamma1[N + 1][T + 1];

//TO APPLY THRESHOLD VALUE TO MAKE VALUES NON-ZERO
void apply_threshold_to_Bij(){
	int i, j;
	long double diff;
	long double max;
	int max_i=0;
	int max_j=0;
	
	for (i = 1; i <= N; i++)
	{
		diff = 0;
		max = 0;
		for (j = 1; j <= M; j++)
		{
			if (b_i_j[i][j] > max)
			{
				max = b_i_j[i][j];
				max_i = i; 
				max_j = j;
			}
			if (b_i_j[i][j] < B_I_J_THRESHOLD)
			{
				diff += b_i_j[i][j] - B_I_J_THRESHOLD;
				b_i_j[i][j] = B_I_J_THRESHOLD;
			}
			
		}
		b_i_j[max_i][max_j] = max;
	}
	
	for (i = 1; i <= N; i++)
	{
		
		long double sum5=0;
		for (j = 1; j <= M; j++)
		{
			
			sum5+=b_i_j[i][j];
		}
		//printf(" sum 5 is : %g \n",sum5);
	}


}

//TO PRINT MATRIX OF DIMENSION N*T
void print_matrix(long double matrix[N + 1][T + 1]){
	int i, j;
	for (i = 1; i <= N; i++){
		for (j = 1; j <= T; j++){
			cout << "\n" << matrix[i][j];
			//printf("%.30Lf\n", matrix[i][j]);
		}
		cout << endl << endl;
	}
}

//TO WRITE THE UPDATED A VALUES
void write_final_A_values(char filenam[]){
	out.open(filenam);
	int i, j;
	for (i = 1; i <= N; i++){
		for (j = 1; j <= N; j++){
			out << a_i_j[i][j] << " ";
		}
		out << endl;
	}
	out.close();
}

//TO WRITE THE UPDATED B VALUES
void write_final_B_values(char filenam[]){
	out.open(filenam);
	int i, j;
	for (i = 1; i <= N; i++){
		for (j = 1; j <= M; j++){
			out << b_i_j[i][j] << " ";
		}
		out << endl;
	}
	out.close();
}

//TO WRITE THE UPDATED PI VALUES
void write_final_pi_values(char filenam[]){
	out.open(filenam);
	int i, j;
	for (i = 1; i <= N; i++){
		out << pi[i] << " ";
	}
	out.close();
}

//DUMP FINAL MODAL VALUES
void dump_final_model(int iteration,int iteration1)
{
	char index[3];
	
	strcpy(a_file_final, "output/models_");
	sprintf(index, "%d", iteration1);
	strcat(a_file_final, index);
	strcat(a_file_final, "/A_");
	sprintf(index, "%d", iteration);
	strcat(a_file_final, index);
	strcat(a_file_final, ".txt");
	//cout << a_file_final << endl;
	write_final_A_values(a_file_final);

	strcpy(b_file_final, "output/models_");
	sprintf(index, "%d", iteration1);
	strcat(b_file_final, index);
	strcat(b_file_final, "/B_");
	sprintf(index, "%d", iteration);
	strcat(b_file_final, index);
	strcat(b_file_final, ".txt");
	//cout << b_file_final << endl;
	write_final_B_values(b_file_final);

	strcpy(pi_file_final, "output/models_");
	sprintf(index, "%d", iteration1);
	strcat(pi_file_final, index);
	strcat(pi_file_final, "/pi_");
	sprintf(index, "%d", iteration);
	strcat(pi_file_final, index);
	strcat(pi_file_final, ".txt");
	//cout << pi_file_final << endl;
	write_final_pi_values(pi_file_final);
}

//TO READ A MATRIX FROM FILE
void read_Aij_values(char filenam[]){
	in.open(filenam);
	string temp;
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			in >> temp;
			a_i_j[i][j] = stold(temp);
		}
	}
	/*cout << "A:" << endl;
	for (int i = 1; i <= N; i++){
	for (int j = 1; j <= N; j++){
	printf("%.30Lf  ", a_i_j[i][j]);
	}
	cout << endl;
	}*/
	in.close();
}

//TO READ B MATRIX FROM FILE
void read_Bij_valuess(char filenam[]){
	in.open(filenam);
	string temp;
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= M; j++){
			in >> temp;
			b_i_j[i][j] = stold(temp);
		}
	}
	/*cout << "B:" << endl;
	for (int i = 1; i <= N; i++){
	for (int j = 1; j <= M; j++){
	printf("%.30Lf\n", b_i_j[i][j]);
	}
	cout << endl << endl;
	}*/
	in.close();
}

//TO READ PI VALUES FROM FILE
void read_pi_valuess(char filenam[]){
	in.open(filenam);
	string temp;
	int index = 1;
	while (in >> temp){
		pi[index++] = stold(temp);
	}
	in.close();
	/*cout << "Pi values:" << endl;
	for (int i = 1; i <= index; i++)
	printf("%.30Lf\n", pi[i]);*/
}


//TO READ OBSERVATION SEQUENCE FROM FILE
void read_observation_values(ifstream &inn){
	
	string temp;
	for (int i = 1; i <= T; i++){
		inn >> temp;
		obs[i] = stoi(temp);
	}
	/*cout << "\nObservation Sequence:" << endl;
	for (int i = 1; i <= T; i++){
	cout << obs[i] << " ";
	}
	cout << endl;*/
	
}


//TO READ THE INTIAL MODEL
void read_initial_model(){

	//read_pi_valuess(pi_file);
	//read_Aij_values(a_file);
	//read_Bij_valuess(b_file);
	
	for(int i=1;i<=N;i++) //assign the given values
		if(i==1) //make the first state as starting state
			pi[i]=1.0;
		else
			pi[i]=0;
    for(int i=1;i<=N;i++) //assign the given values for transition probability distribution
        for(int j=1;j<=N;j++)
			if(i==j&&i!=N)
				a_i_j[i][j]=0.8; //probability of being in current state
			else if(i==j&&i==N)
				a_i_j[i][j]=1; //forcing to end the transition in final state
			else if(j==i+1)
				a_i_j[i][j]=0.2; //probability to transit to next immediate state
			else
				a_i_j[i][j]=0; //probability to move to non immediate states
    for(int i=1;i<=N;i++) //assign the given values for observation symbol probability distribution
        for(int j=1;j<=M;j++)
          b_i_j[i][j]=1.0/M;

	return ;


}

//TO PERFORM THE FORWARD PROCEDURE
void forward_procedure(){
	int i, j, t;
	long double sum = 0;
	for (i = 1; i <= N; i++)
		alpha[i][1] = pi[i] * b_i_j[i][obs[1]];

	//CALCULATING ALPHA MATRIX
	for (t = 1; t <= T -1; t++)
	{
		for (j = 1; j <= N; j++)
		{
			sum = 0;
			for (i = 1; i <= N; i++)
			{
				sum += alpha[i][t] * a_i_j[i][j];
			}
			alpha[j][t + 1] = sum * b_i_j[j][obs[t + 1]];
			//if(alpha[j][t+1] <= 0)
				//alpha[j][t+1] = (ld)(pow((ld)10,(ld)-30)) ;
		}
	}

	//PRINTING ALPHA
	//cout << "\nAlpha Matrix:" << endl;
	/*for (i = 1; i <= N; i++){
	for (j = 1; j <= T; j++){
	printf("%Le\n", alpha[i][j]);
	}
	cout << endl << endl;
	}*/

	//WRITING ALPHA TO FILE
	out.open(alpha_file);
	for (i = 1; i <= T; i++){
		for (j = 1; j <= N; j++){
			out << /*fixed << setprecision(FILE_DECIMAL_PRECISION_VALUE) <<*/ alpha[j][i] << " ";
		}
		out << endl;
	}
	out.close();


	//CALCULATING PROBABILITY OF OBSERVATION SEQUENCE GIVEN MODEL
	sum = 0;
	for (i = 1; i <= N; i++){
		sum += alpha[i][T];
	}

	Pobs_model = sum;
	if(Pobs_model==0) flag1=0;
	//cout << "\nP(obs/model) : " << Pobs_model <<endl;
}

//TO PERFORM THE BACKWARD PROCEDURE
void backward_procedure()
{
	
	int i, j, t;
	long double sum = 0;
	for (i = 1; i <= N; i++)
		beta[i][T] = 1.0;

	//CALCULATING BETA MATRIX
	for (t = T - 1; t >= 1; t--)
	{
		for (i = 1; i <= N; i++)
		{
			beta[i][t] = 0;
			for (j = 1; j <= N; j++)
			{
				beta[i][t] += a_i_j[i][j] * b_i_j[j][obs[t + 1]] * beta[j][t + 1];
			}
			//if(beta[i][t] <= 0)
				//beta[i][t] = (ld)(pow((ld)10,(ld)-30)) ;
		}
	}

	//PRINTING BETA MATRIX
	/*cout << "\Beta Matrix:" << endl;
	for (i = 1; i <= N; i++){
	for (j = 1; j <= T; j++){
	printf("%.30Lf\n", beta[i][j]);
	}
	cout << endl << endl;
	}*/

	//WRITING BETA TO FILE
	out.open(beta_file);
	for (i = 1; i <= T; i++){
		for (j = 1; j <= N; j++){
			out << /*fixed << setprecision(FILE_DECIMAL_PRECISION_VALUE) <<*/ beta[j][i] << " ";
		}
		out << endl;
	}
	out.close();
	
}

//PERFORMS VIETERBI ALGORITHM
void perform_viterbi()
{
	
	int i, j, t;
	long double max = 0, temp = 0;

	//STEP 1 : INTITIALIZATION
	for (i = 1; i <= N; i++){
		delta[i][1] = pi[i] * b_i_j[i][obs[1]];
		psi[i][1] = 0;
	}

	//STEP 2 : RECURSION 
	for (t = 2; t <= T; t++){
		for (j = 1; j <= N; j++){
			max = 0;
			for (i = 1; i <= N; i++)
			{
				temp = delta[i][t - 1] * a_i_j[i][j];
				if (temp > max)
				{
					max = temp;
					psi[j][t] = i;
				}
			}
			delta[j][t] = max*b_i_j[j][obs[t]];
		}
	}
   

	//PRINTING DELTA VALUES
	//cout << "\nDelta" << endl;
	//print_matrix(delta);


	//PRITING PSI VALUES
	/*cout << "\nPsi" << endl;
	for (i = 1; i <= N; i++){
	for (j = 1; j <= T; j++){
	cout << " " << psi[i][j];
	}
	cout << endl;
	}*/

	//STEP 3 : TERMINATION
	max = 0;
	for (i = 1; i <= N; i++)
	{
		if (delta[i][T] > max)
		{
			max = delta[i][T];
			pstar = delta[i][T];
			qstar = i;
		}
	}


	//cout << "\nQ Star[T]:" << qstar << endl << endl;
	qstar1[T] = qstar;
	for (t = T - 1; t >= 1; t--)
	{
		qstar1[t] = psi[qstar1[t + 1]][t + 1];
	}

	//STEP 4 : PATH
	/*cout << "\nState Seqeuence (Viterbi) : " << endl;
	for (t = 1; t <= T; t++){
		cout << " " << qstar1[t];
	}*/
	//cout << "\nP Star : " << pstar << endl;
	//cout << "\nP Star (Previous) : " << previous_pstar << endl;


	pstar_difference = pstar - previous_pstar;
	//cout << "\nDifference : " << pstar_difference << endl;
	previous_pstar = pstar;


	//WRITING SEQUENCE TO FILE
	out.open(qstar1_file);
	for (t = 1; t <= T; t++){
		out << qstar1[t] << endl;
	}
	/*
	cout<<"\nState seq:\n";
	for (t = 1; t <= T; t++){
		cout << qstar1[t] << "  ";
	}
	*/
	out.close();
	
}

//TO CALCULATE XI VALUES
void calculate_xi_values(){

	int i, j, t;
	long double summation[T];

	//CALCULATING SUMMATION ARRAY
	for (t = 1; t <= T - 1; t++)
	{
		summation[t] = 0;
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= N; j++)
			{
				summation[t] += alpha[i][t] * a_i_j[i][j] * b_i_j[j][obs[t + 1]] * beta[j][t + 1];

			}
			//if(summation[t]<=0) summation[t] = (ld)(pow((ld)10,(ld)-30)) ;
		}
	}

	for (t = 1; t <= T - 1; t++){
		//cout << "Summation:" << summation[t] << endl;
		//printf("%Le\n", summation[t]);
	}


	//CALCULATING XI MATRIX
	for (t = 1; t <= T - 1; t++)
	{
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= N; j++)
			{

				Xi[i][j][t] = (alpha[i][t] * a_i_j[i][j] * b_i_j[j][obs[t + 1]] * beta[j][t + 1]) / summation[t];
				//if(Xi[i][j][t]==0)
					//Xi[i][j][t] = (ld)(pow((ld)10,(ld)-30)) ;
			}
		}
	}

	//PRINTING XI MATRIX
	/*cout << "\nXi Matrix : " << endl;
	for (t = 1; t <= T-1; t++){
	for (i = 1; i <= N; i++){
	for (j = 1; j <= N; j++){
	printf("%Le ", Xi[i][j][t]);
	//cout << Xi[i][j][t] << " ";
	}
	cout << endl;
	}
	cout << endl << endl;
	}*/
}

//TO CALULATE PROBABILITY OF ENDING AT STATE I : GAMMA MATRIX
void calculate_gamma_values(){
	int i, j, t;

	//CALCULATING GAMMA MATRIX
	for (t = 1; t <= T - 1; t++){
		for (i = 1; i <= N; i++)
		{
			gamma[i][t] = 0;
			for (j = 1; j <= N; j++)
			{
				gamma[i][t] += Xi[i][j][t];
			}
		}
	}

	//PRINTING GAMMA MATRIX
	/*cout << "\nGamma Matrix : " << endl;
	for (t = 1; t <= T - 1; t++){
	for (i = 1; i <= N; i++){
	cout << gamma[i][t] << " ";
	}
	cout << endl;
	}*/
}

//TO CALCULATE GAMMA MATRIX (BASED ON ALPHA-BETA)
void calculate_gamma(){
	int i, j, k, t;
	long double summation = 0;
	//CALCULATING GAMMA MATRIX
	for (i = 1; i <= T; i++){
		for (j = 1; j <= N; j++){
			summation = 0;
			for (k = 1; k <= N; k++){
				summation += alpha[k][i] * beta[k][i];
			}
			if(summation<=0) summation=(long double)(pow((long double)10,(long double)-30)) ;
			gamma[j][i] = (alpha[j][i] * beta[j][i]) / summation;
			//if(	gamma[j][i]==0) gamma[j][i]=(ld)(pow((ld)10,(ld)-30)) ;
		}

	}
	/*cout << "\nGamma Matrix : " << endl;
	for (t = 1; t <= T - 1; t++){
	for (i = 1; i <= N; i++){
	cout << gamma[i][t] << " ";
	}
	cout << endl;
	}*/
}

//TO UPDATE MODEL PARAMTERS
void update_model_parameters(){
	int i, j, t;
	long double summation = 0;
	long double summation1 = 0;

	//UPDATING THE PI VALUES
	for (i = 1; i <= N; i++)
	{
		pi[i] = gamma[i][1];
	}

	//PRINTING NEW PI VALUES
	/*cout << "\nNew Pi Values:" << endl;
	for (i = 1; i <= N; i++){
	cout <<" "<< pi[i];
	}*/

	//UPDATING THE A MATRIX VALUES
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			summation = 0;
			summation1 = 0;
			for (t = 1; t <= T - 1; t++){
				summation += Xi[i][j][t];
				summation1 += gamma[i][t];
			}
			a_i_j[i][j] = summation / summation1;
		}

	}
	/*
	for (i = 1; i <= N; i++)
	{	
		long double sum10=0;
		ld maxim=0;
		int ind=0,jnd=0;
		for (j = 1; j <= N; j++)
		{
			if(maxim<a_i_j[i][j])
			{
				maxim=a_i_j[i][j];
				ind=i;
				jnd=j;
			}
			sum10+=a_i_j[i][j] ;
		}
		if(sum10 >= 1)
		{
			long double diffe= sum10-1;
			 a_i_j[ind][jnd]= a_i_j[ind][jnd]-diffe;
		}
	}

	
	//PRINTING THE A MATRIX VALUES
	/*cout << "\nNew A:" << endl;
	for (i = 1; i <= N; i++){
	for (j = 1; j <= N; j++){
	cout << a_i_j[i][j] << " ";
	}
	cout << endl;
	}*/
	
	//UPDATING THE B MATRIX VALUES
	
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= M; j++)
		{
			summation = 0;
			summation1 = 0;
			for (t = 1; t <= T; t++){
				if (obs[t] == j)
					summation1 += gamma[i][t];
			}
			for (t = 1; t <= T; t++){
				summation += gamma[i][t];
			}
			b_i_j[i][j] = summation1 / summation;
			//if(b_i_j[i][j]<=0) b_i_j[i][j]=(ld)(pow((ld)10,(ld)-30)) ;
		}
	}
	/*
	for (i = 1; i <= N; i++)
	{	
		long double sum11=0;
		ld maximm=0;
		int indd=0,jndd=0;
		for (j = 1; j <= M; j++)
		{
			if(maximm<a_i_j[i][j])
			{
				maximm=b_i_j[i][j];
				indd=i;
				jndd=j;
			}
			sum11+=b_i_j[i][j] ;
		}
		if(sum11>= 1)
		{
			long double differ= sum11-1;
			 b_i_j[indd][jndd]= b_i_j[indd][jndd]-differ;
		}
	}
	//APPLYING THRESHOLD FUNCTION TO UPDATE B MATRIX

	/*cout << "\n::New B:" << endl;
	for (i = 1; i <= N; i++){
	for (j = 1; j <= M; j++){
	printf("%Le ", b_i_j[i][j]);
	//cout << b_i_j[i][j] << " ";
	}
	cout << endl;
	}*/

	apply_threshold_to_Bij();

	//PRINTING THE FINAL B MATRIX
	/*cout << "\n::New B:" << endl;
	for (i = 1; i <= N; i++){
	for (j = 1; j <= M; j++){
	printf("%Le ", b_i_j[i][j]);
	//cout << b_i_j[i][j] << " ";
	}
	cout << endl;
	}*/

}

//TO PERFORM EM PROCEDURE
void expectation_maximization(){
	
	calculate_xi_values();
	calculate_gamma();
	//calculate_gamma_values();
	update_model_parameters();
	
}

//SOLUTION TO PROBLEM 1 USING FORWARD AND BACKWARD PROCEDURES
void solution_to_problem1(){
	forward_procedure();
	if(flag1){
	backward_procedure();
	}
	
}

//SOLUTION TO PROBLEM 2 USING VITERBI ALGORITHM
void solution_to_problem2(){

	perform_viterbi();
	

}

//SOLUTION TO PROBLEM 3 USING EM PROCEDURE
void solution_to_problem3(){
	
	expectation_maximization();
	
}

void add_values_to_average_model()
{
	
	
		int i, j;
		//cout<<"\na matrix:\n";
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= N; j++)
			{
			
				a_i_j_average[i][j] += a_i_j[i][j];	
				//cout<<a_i_j_average[i][j]<<"   ";
			}		
			//cout<<endl;
		}
		//cout<<"\nb matrix:\n";
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= M; j++)
			{
				b_i_j_average[i][j] += b_i_j[i][j];
				//cout<<b_i_j_average[i][j]<<"   ";
			}
			//cout<<endl;
		}

		//cout<<endl;
		for (i = 1; i <= N; i++){
			pi_average[i] += pi[i];
		}
	
}

void average_of_average_model(){
	int i, j;
	for (i = 1; i <= N; i++){
		for (j = 1; j <= N; j++){			
			a_i_j_average[i][j] /= TRAIN_ITERATIONS;
			
		}
	}
	for (i = 1; i <= N; i++){
		for (j = 1; j <= M; j++){
			b_i_j_average[i][j] /= TRAIN_ITERATIONS;
		}
	}
	for (i = 1; i <= N; i++){
		pi_average[i] /= TRAIN_ITERATIONS;
	}
}

void clear_average_model_array(){
	int i, j;
	for (i = 1; i <= N; i++){
		for (j = 1; j <= N; j++){
			a_i_j_average[i][j] = 0;
		}
	}
	for (i = 1; i <= N; i++){
		for (j = 1; j <= M; j++){
			b_i_j_average[i][j] = 0;
		}
	}
	for (i = 1; i <= N; i++){
		pi_average[i] = 0;
	}
}
void dump_average_model(int iteration){
	int i, j;
	char index[3];

	strcpy(a_average_file, "output/average_models/A_avg_");
	sprintf(index, "%d", iteration);
	strcat(a_average_file, index);
	strcat(a_average_file, ".txt");
	//cout << a_average_file << endl;
	out.open(a_average_file);	
	for (i = 1; i <= N; i++){
		for (j = 1; j <= N; j++){
			out << a_i_j_average[i][j] << " ";
		}
		out << endl;
	}
	out.close();
	
	strcpy(b_average_file, "output/average_models/B_avg_");
	sprintf(index, "%d", iteration);
	strcat(b_average_file, index);
	strcat(b_average_file, ".txt");
	//cout << b_average_file << endl;
	out.open(b_average_file);
	for (i = 1; i <= N; i++){
		for (j = 1; j <= M; j++){
			out << b_i_j_average[i][j] << " ";
		}
		out << endl;
	}
	out.close();

	strcpy(pi_average_file, "output/average_models/pi_avg_");
	sprintf(index, "%d", iteration);
	strcat(pi_average_file, index);
	strcat(pi_average_file, ".txt");
	//cout << pi_average_file << endl;
	out.open(pi_average_file);
	for (i = 1; i <= N; i++){
		out << pi_average[i] << " ";		
	}
	out.close();
}

void read_average_model(int iteration){
	char index[3];
	strcpy(a_average_file, "output/average_models/A_avg_");
	sprintf(index, "%d", iteration);
	strcat(a_average_file, index);
	strcat(a_average_file, ".txt");
	//cout << a_average_file << endl;
	read_Aij_values(a_average_file);

	strcpy(b_average_file, "output/average_models/B_avg_");
	sprintf(index, "%d", iteration);
	strcat(b_average_file, index);
	strcat(b_average_file, ".txt");
	//cout << b_average_file << endl;
	read_Bij_valuess(b_average_file);

	strcpy(pi_average_file, "output/average_models/pi_avg_");
	sprintf(index, "%d", iteration);
	strcat(pi_average_file, index);
	strcat(pi_average_file, ".txt");
	//cout << pi_average_file << endl;
	read_pi_valuess(pi_average_file);
}

void HMM()
{
	int i,j,k,l;	
	
		//cout << "\n....... Iteration No : " << l <<" ........"<<endl;
		for (k = 0; k <WORDS; k++)
		{
			cout << "\nCalculating Average Model for : " << k << endl;
			cout << "Training for " << TRAIN_ITERATIONS <<" Iterations"<< endl;
			char index[3];

			strcpy(obs_sequence_file, "Input/OBS_");
			//strcpy(obs_sequence_file, "observation_sequences/observation_sequence_");
			sprintf(index, "%d", k);
			strcat(obs_sequence_file, index);
			strcat(obs_sequence_file, ".txt");
			//cout << obs_sequence_file << endl;

			in_obs.open(obs_sequence_file);

			for (j = 1; j <= TRAIN_ITERATIONS; j++)
			{
				flag1=1;
				read_observation_values(in_obs);

				
					read_initial_model();
				
					//200 Iterations
				for (i = 1; i <= 200; i++)
				{
					/*
					cout << "\nObservation Sequence:" << endl;
					for (int i = 1; i <= T; i++)
					{
					cout << obs[i] << " ";
					}
					*/
					solution_to_problem1();
					if(1){
					solution_to_problem2();
					solution_to_problem3();
					}
				}
				cout<<"*****************************************************************************"<<endl;
			    cout << "\nDigit : "<<k <<" file name :"<<obs_sequence_file<<" j "<<j<< endl;	
			    cout<<"\n P* = "<<previous_pstar;
				cout<<"\n p(o/model) = "<<Pobs_model;
				cout<<"\nState seq:\n";
				for (int t = 1; t <= T; t++)
				{
					cout << qstar1[t] << "  ";
				}
				if(1){
				add_values_to_average_model();
				}
				dump_final_model(j, k);
				
			}
			
			average_of_average_model();
			dump_average_model(k);
			clear_average_model_array();

			in_obs.close();
		}
	
	
	
}
