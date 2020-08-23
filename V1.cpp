#include <fstream>
#include <ctime>
#include <cstdlib>
//#include "BT.h"

class CrosswordPuzzle{
private:
	int const SIZE;
	string database[10];
	BT Tree;
public:
	
	CrosswordPuzzle() : SIZE(30)
	{
		bool check[SIZE] = {false};
	}
	
	void ReadFromFile()
	{
		int check[SIZE] = {false};
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
					temp = (rand() % SIZE);
				}
				check[temp] = true;
				for(int i = 0; i < temp; i++){
						fflush(stdin);
						getline(Input_File, input);
				}
				Input_File.seekg(0, ios::beg); 
				database[count] = input;
				Tree.insertNode(Tree.head, database[count]);
				count++;
			}
		}
		else{
			cout << "Input File does not exist";
			exit(1);
		}

		for(int i = 0; i < 10; i++){
			cout << i << ": " << database[i] << endl;
		}
		Input_File.close();
	}
	
	void displayTree()
	{
		Tree.Preorder(Tree.head);
	}
};




int main(){
	CrosswordPuzzle CW;
	CW.ReadFromFile();
	CW.displayTree();
	
}
