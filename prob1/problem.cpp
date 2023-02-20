//brooke west 3025488
//extra credit lab
//feb 17 2023
//eecs348

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;



int score; //creates variable for prefrence score 
int dpref[5][5]; //creates an array for each dept prefrences 
int ppref[5][5]; //creates an array for each programmers prefrences 
int chosen[10]; //creates an array for programmers that have already been chosen 
int dept[5]; //creates array to keep track of each dept and their corresponding programmer (dept 1 = index 0)
int choice; //keeps track of each dept first choice 
int priority; //keeps track of each prog first choice 
int conflict[1][2]; //keeps track of two conflicting deparments 
int k = 0; //flag variable
int a; //1st deparment with conflict 
int b; //2nd department with conflict 


void readInput(std::string fileName) //reads in department and programmer prefrences 
{
    ifstream inFile;
    inFile.open(fileName); //opens input file 

	if(inFile.is_open())
{

       for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				inFile >> score;
				dpref[i][j] = score - 1; //reads in correct score array 
			}
		}

        for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				inFile >> score;
				ppref[i][j] = score - 1; //reads in correct score array 
			}
		}

	inFile.close();

}




    return;
}



void valid(int array[]) //checks if there are conflicts between departments, if so adds to conflict array
{
    for(int i = 0; i < 5; i ++)
    {
        k = 0; 
        for(int j = 0; j < 5; j++)
        {
            if(i != j)
            {
                if (array[i] == array[j])
                {

                    int pair[] = { i, j}; //two departments that have conflict 
                


                        conflict[0][0] = i;
                        conflict[0][1] = j;
                        k = 1; 
                       break;
                    
                }

            }
        }

        if(k == 1)
        {
            break;
        }
    }

   
    
    return;
    
}


void solve()//solves for prefrences 
{


    
    
    for(int i = 0; i < 6; i ++) //run algorithm 5 times
    {
        
        conflict[0][0] = 0; 
        conflict[0][1] = 0;

    
        
        valid(dpref[0]); //creates list of conflicts 
        
        if(conflict[0][0] == 0 && conflict[0][1] == 0) //if there are no conflicts 
        {

            break;
        }
        else
        {
            int programmer = dpref[0][conflict[0][0]]; //sets programmer to the one with the conflict
            a = conflict[0][0]; //first dept
            b = conflict [0][1]; //second dept


             for(int j = 0; j < 5; j++ ) //prog determines which dept they go to 
            {
        
             

                if (ppref[j][programmer] == a)
                {
            
                        dept[a] = programmer; //sets that programmer to dept a 
                        for(int m = 0; m < 5; m ++)
                        {
                            dpref[m][b] = dpref[m + 1][b]; //shifts department bs preference list up 
                        }
                       
                        break;

                }
                else if (ppref[j][programmer] == b)
                {
                    dept[b] = programmer; //sets that programmer to dept b
                    for(int m = 0; m < 5; m ++)
                    {
                        dpref[m][a] = dpref[m + 1][a]; //shifts department as prefrence list up 
                    }
                    
                    break;
                }
                else
                {
                    continue;
                }
            
             }

            
             
             
        }
    }

    
    

}


int main()
{


    readInput("matching-data.txt"); //reads in data
    solve(); //calls solve function 
    
    for(int p = 0; p < 5; p++) //assigns dept to unconflicting top prefrences 
    {
            dept[p] = dpref[0][p];  
    }
    
    for(int i = 0; i < 5; i++) //prints out answer
    {
        cout << "Department # " << i + 1 << " will get Programmer # " << dept[i]  + 1 <<'\n'; 
                        

    }
   



}