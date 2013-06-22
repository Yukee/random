#include <iostream>
#include "Vector.h"

using namespace std;

typedef Vector<int> conf;

// return true if the configuration c at the end of the current turn makes the current player win
bool is_winning(conf c)
{
	bool win = true;
	
	// stopping condition
	if(c == conf (1,1)) return !win;
	
	// test each move row by row. If a move leads to a winning configuration, then the configuration is not winning.
	else
	{		
		int n = c.size();
		conf temp;
		
		for(int i=0;i<n;i++)
		{
			temp = c;
					
			for(int j=1;j<c[i];j++)
			{
				temp[i] -= 1;
				win *= !is_winning(temp);
			}
			
			// delete the row that has just been tested
			temp = c.drop(i);
			win *= !is_winning(temp);
		}
		return win;
	}
}

// make a winning move if possible
conf play(conf init)
{
	int n = init.size();
	
	if(n == 1) {
		cout << "Fin de partie. J'ai gagné. Comme prévu..." << endl;
		return init.drop(0);
	}
	
	else {
		
		conf temp;
		
		for(int i=0;i<n;i++)
		{
			temp = init;
			
			for(int j=1;j<init[i];j++)
			{
				temp[i] -= 1;
				if(is_winning(temp)) return temp;
			}
			
			temp = init.drop(i);
			if(is_winning(temp)) return temp;
		}
		
		cout << "On dirait bien que tu as gagné, petit fumier. Puisque c'est comme ça je ragequit." << endl;
		return conf (0);
	}
}

// display the state of the game
void print(conf c)
{
	int n = c.size();
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<c[i];j++) cout << "|";
		cout << endl;
	}
}

// game loop
void game(conf c)
{
	conf current = c;
	int move = 0;
	
	int col = 1;
	int num = 0;
	
	while(current.size())
	{		
		// if it is human player's turn
		if(!(move % 2)) {
			
			cout << "*************** DÉBUT DU TOUR " << move/2 << " ***************" << endl;
			
			print(current);

			bool dumbass = true;
			
			while(dumbass) {
				cout << "Numéro de la colonne à jouer : "; cin >> col; col = (int)col;
				cout << "Nombre de bâtons à retirer : "; cin >> num;  num = (int)num;
				
				if( col-1<=(int)current.size() && col > 0) {
					if(num<current[col-1]) { 
						current[col-1] -= num; dumbass = false;
					}
					else if(num==current[col-1]) {
						current = current.drop(col-1); dumbass = false;
					}
				}
				
				else cout << "Tu ne sais même pas jouer correctement, sac à foutre !" << endl;
			}
			
		}
		
		else {
			current = play(current);
		}
		
		move ++;
	}
}

int main()
{
	conf c (3); c[0]=5; c[1]=3; c[2]=1;
	game(c);
	return 0; 
}
