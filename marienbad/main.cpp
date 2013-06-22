#include <iostream>
#include <stdlib.h> // random numbers
#include <time.h> // seed
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
		if(init[0] == 0) cout << "Tu as gagné petit fumier. Je le savais depuis le début mais je t'ai laissé jouer pour te faire plaisir." << endl;
		else cout << "Fin de partie. J'ai gagné. Comme prévu..." << endl;
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
		
		// if there is no winning configuration avalaible, do a random move
		
		srand(time(NULL));
		
		int col = rand() % n;
		int num = rand() % init[col] + 1;
		
		if(num<init[col]) init[col] -= num;
		else init = init.drop(col);
		
		return init;
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
