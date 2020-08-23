#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <queue>

using namespace std;

class CrosswordPuzzle{
private:
	int SIZE;
	string database[10];
	
	int x_min , x_max  , y_min  , y_max ;
	
	char largeArray[100][100];
	char **smallArray;

public:
	
	CrosswordPuzzle(){
		SIZE = 30;
		for (int i = 0 ; i < 100 ; i++ ){
			for(int j = 0 ; j < 100 ; j++){

				largeArray[i][j]= ' ';
			}
		}
	}
	
	void ReadFromFile(){
		bool check[SIZE] = {false};
		fstream Input_File;
		Input_File.open("Input.txt", ios::in);
		string input;
		int count = 0;
		int temp;
		
		srand(time(0));
		if(Input_File.is_open()){
			while(count != 10){
				temp = (rand() % SIZE);
				while(check[temp] == true){
//					cout << "repeated temp: " << temp << endl;
					temp = (rand() % SIZE);	
				}
//				cout << "temp: " << temp << endl;
				check[temp] = true;
				for(int i = 0; i <= temp; i++){
						fflush(stdin);
						getline(Input_File, input);
				}
				Input_File.close();
				Input_File.open("Input.txt", ios::in);
				database[count] = input;
				count++;
			}
		}
		else{
			cout << "Input File does not exist";
			exit(1);
		}
//		cout << endl << endl;
		for(int i = 0; i < 10; i++){
			cout << i << ": " << database[i] << endl;
		}
		Input_File.close();
	}
	
	
	void heapify(int n, int i){
	   int largest = i;
	   int l = 2*i + 1;
	   int r = 2*i + 2;
	   if (l < n && database[l].length() < database[largest].length()){
	     largest = l;
	 	}
	    if (r  < n && (database[r].length() < database[largest].length() )){
	     	largest = r;
		}
	    if (largest != i){
	     	swap(database[i], database[largest]);
	     	heapify(n, largest);
	    }
	}
	
	void heapSort(){
	   for (int i = 10 / 2 - 1; i >= 0; i--)
	     heapify(10, i);
	     
	   for (int i=10-1; i>=0; i--)
	   {
	     swap(database[0], database[i]);
	     
	     heapify(i, 0);
	   }
	}
	
	void displayDatabase(){
		cout<<endl;
		for (int i = 0 ; i < 10 ; i++){
			cout<<database[i]<<" ";
		}
	}
	
	void insertInLargeArray(){
		int len = database[0].length();
		int count = 0;
		stack <string> s1;
		for (int j = 49 ; j < 49 + len ; j++){
		 	largeArray[49][j] = database[0][count];
		 	count++;
		}
//		displayDatabase();
//		system("pause");
//		displayLargeArray();
		x_min = y_min = y_max = 49;
		x_max = 49+len;
		bool inserted = false;
		int dcount = 1;
		while(dcount < 10){
			for(int i = y_min; i <= y_max; i++){
				for(int j = x_min; j < x_max; j++){
					
					for (int k = 0 ; k < database[dcount].length() ; k++){
						inserted = false;
						if (largeArray[i][j] == database[dcount][k]){
							if((largeArray[i+1][j+1] != ' ') || (largeArray[i+1][j-1] != ' ') || (largeArray[i-1][j-1] != ' ') || (largeArray[i-1][j+1] != ' ')){
								continue;
							}
							if (largeArray[i][j-1] == ' ' && largeArray[i][j+1] == ' '){
								inserted = checkEmptySpace(i , j , k , database[dcount].length() , database[dcount] , 1);
							}
							else if (largeArray[i-1][j] == ' ' && largeArray[i+1][j] == ' ' ){
								inserted = checkEmptySpace(i , j , k , database[dcount].length() , database[dcount] , 0);
							}
							
							if (inserted == true){
								break;
							}
							else{
								s1.push(database[dcount]);
							}
						}
					}
					
					if (inserted == true){
						break;
					}
				}
				
				if (inserted == true){
						break;
				}
			}
			
			dcount++;
		}
//		displayLargeArray();
//		system("pause");
		insertSmallArray();
	}
	
	void displayLargeArray(){
		cout<<endl;
		for (int i = 0 ; i < 100 ; i++){
			for (int j = 0 ; j < 100 ; j++){
				cout<<largeArray[i][j];
			}
			cout<<endl;
		}
	}
	
<<<<<<< HEAD
	int string_index(){
		for(int i = 0; i < str.length())
	}
	
=======
	bool checkEmptySpace(int i , int j , int k , int len , string newWord , int direction){
		bool es = true;
		int count = 0;
		
		int tempk = 0;
		char temp = largeArray[i][j];
//		cout<<"temp: "<< temp <<endl;
//		cout << "direction: " << direction << endl;
		largeArray[i][j] = ' ';
//		system("cls");
//		cout<<i<<" "<<j<<" "<<k<<" "<<len<<endl;
//		system("pause");
>>>>>>> 9aa3bc2f6fb901cab9472ce11db5d43ce78d4614

		if (direction == 1){
			for (int x = j - k ; x < j + len - k  ; x++){
//				cout<<"array value: "<<largeArray[i][x]<<endl;
//				system("pause");
				if(x == j+len - k - 1) // checking last letter of incoming new string
				{
					if (largeArray[i][j + len - k] != ' '){  //checking next letter after  last letter of incoming string
						largeArray[i][j] = temp;
						return false;
					}
					
					if ( largeArray[i][x] != ' ' ){
						if (largeArray[i][x] != newWord[len -1 ]){
							largeArray[i][j] = temp;
							return false;
						}
					}
					else if (largeArray[i][x] == ' ') {
						if (largeArray[i-1][x] != ' ' || largeArray[i+1][x] != ' '){
							largeArray[i][j] = temp;
							return false;
						}
					}
				}
				else if (x == j - k) { // checking first letter of incoming new string
					if (largeArray[i][j-k-1] != ' '){
						largeArray[i][j] = temp;
						return false;
					}
					
					if ( largeArray[i][x] != ' ' ){
						if (largeArray[i][x] != newWord[0] ){
							largeArray[i][j] = temp;
							return false;
						}
					}
					else if (largeArray[i][x] == ' ') {
						if (largeArray[i-1][x] != ' ' || largeArray[i+1][x] != ' '){
							largeArray[i][j] = temp;
							return false;
						}
					}
				}
				else if ( x == j){
					if (largeArray[i][x] != ' '){
						largeArray[i][j] = temp;
						return false;
					}
				}
				else{  	// checking middle letters of incoming new string
					if (largeArray[i][x] != ' '){
						if (largeArray[i][x] != newWord[tempk]){
							largeArray[i][j] = temp;
							return false;
						}
					}
					else if (largeArray[i][x] == ' '){
						if (largeArray[i-1][x] != ' ' || largeArray[i+1][x] != ' '){
							largeArray[i][j] = temp;
							return false;
						}
					}
				}
				
				tempk++;
			}
			if (es == true){
				if (j - k < x_min){
					x_min = j - k;
				}
				if ( j - k + len > x_max){
					x_max = j - k + len;
				}
				
//				cout<<"here1b"<<endl;
				for (int x = j - k ; x < j + len - k ; x++){
					
					largeArray[i][x] = newWord[count];
					count++;
				}
			}
		}
		else {
			for (int x = i - k ; x < i + len - k  ; x++){
//				cout<<"array value: "<<largeArray[x][j]<<endl;
//				system("pause");
				if(x == i + len - k - 1) // checking last letter of incoming new string
				{
					if (largeArray[x + 1][j] != ' '){
						largeArray[i][j] = temp;
						return false;
					}
					
					if ( largeArray[x][j] != ' ' ){
						if (largeArray[x][j] != newWord[len - 1]){
							largeArray[i][j] = temp;
							return false;
						}
					}
					else if (largeArray[x][j] == ' ') {
						if (largeArray[x][j-1] != ' ' || largeArray[x][j+1] != ' '){
							largeArray[i][j] = temp;
							return false;
						}
					}
				}
				
				else if (x == i - k) { // checking first letter of incoming new string
					if (largeArray[x-1][j] != ' '){
						largeArray[i][j] = temp;
						return false;
					}
					
					if ( largeArray[x][j] != ' ' ){
						if (largeArray[x][j] != newWord[0] ){
							largeArray[i][j] = temp;
							return false;
						}
					}
					else if (largeArray[x][j] == ' ') {
						if (largeArray[x][j-1] != ' ' || largeArray[x][j+1] != ' '){
							largeArray[i][j] = temp;
							return false;
						}
					}
				}
				else if ( x == i){
					if (largeArray[x][j] != ' '){
						largeArray[i][j] = temp;
						return false;
					}
				}
				else{  	// checking middle letters of incoming new string
					if (largeArray[x][j] != ' '){
						if (largeArray[x][j] != newWord[tempk]){
							largeArray[i][j] = temp;
							return false;
						}
					}
					else if (largeArray[x][j] == ' '){
						if (largeArray[x][j-1] != ' ' || largeArray[x][j+1] != ' '){
							largeArray[i][j] = temp;
							return false;
						}
					}
				}
				
				tempk++;
				
				
			}
			if (es == true){
				if (i - k < y_min){
					y_min = i - k;
				}
				if ( i - k + len > y_max){
					y_max = i - k + len;
				}
				
//				cout<<"here0b"<<endl;
				for (int x = i - k ; x < i + len - k ; x++){
					largeArray[x][j] = newWord[count];
					count++;
				}
			}
		}
		
		
//		system("pause");
//		system("pause");
//		displayLargeArray();
		return true;
	}
	
	void insertSmallArray(){
		
		smallArray = new char* [y_max - y_min];
		for (int i = 0 ; i < y_max - y_min ; i++){
			smallArray[i] = new char [x_max - x_min ];
		}
		
		
		for (int i =  y_min ;  i < y_max ; i++){
			for (int j = x_min ; j < x_max ; j++ ){
				smallArray[i-y_min][j-x_min] = largeArray[i][j];
			}
		}
		
		y_max = y_max - y_min;
		x_max = x_max - x_min;
		
	}
	
	void displaySmallArray(){
		
//		system("cls");
		
		for (int i = 0 ; i < y_max ; i++){
			for (int j = 0 ; j < x_max ; j++){
				cout<<smallArray[i][j]<<"  ";
			}
			cout<<endl<<endl;
		}
	}
	
	void displayCrossword(){
		
//		system("cls");
		cout<<endl<<endl<<endl;
		cout<<"      CROSSWORD"<<endl;
		cout<<" ";
		for (int i = 0 ; i < x_max ; i++){
			cout<<"___";
		}
		cout<<endl;
		cout<<"|";
		for (int i = 0 ; i < x_max ; i++){
				cout<<"   ";
			}
		cout<<"|"<<endl;
		
		for (int i = 0 ; i < y_max ; i++){
			
			for (int j = -1 ; j < x_max ; j++){
				if (j != -1){
					if (smallArray[i][j] >= 'a' && smallArray[i][j] <= 'z' ){
						cout<<"-  ";
					}
					else cout<<"   ";
				}
				else cout<<"|";
			}
			cout<<"|"<<endl;
			if (i == y_max -1){
				cout<<"|";
				for (int i = 0 ; i < x_max ; i++){
					cout<<"___";
				}
				cout<<"|";
			}
			else{
				cout<<"|";
				for (int i = 0 ; i < x_max ; i++){
					cout<<"   ";
				}
				cout<<"|"<<endl;
				
			}	
		}
		cout<<endl;	
	}
	
};




int main(){
	CrosswordPuzzle CW;
	CW.ReadFromFile();
	CW.heapSort();
	CW.insertInLargeArray();
	system("cls");
	CW.displaySmallArray();
	CW.displayCrossword();

	
}
