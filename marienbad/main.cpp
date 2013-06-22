#include <iostream>
#include <stdlib.h> // random numbers
#include <time.h> // seed
#include "Vector.h"

using namespace std;

typedef Vector<int> conf;

// list all accessible configurations from a configuration c
Vector<conf> list_moves(conf c)
{
	int n = c.size();
	int sum = 0;
	for(int i=0;i<n;i++) sum += c[i];
	
	Vector<conf> list (sum);
	
	conf temp;
	int count = 0;
	
	for(int i=0;i<n;i++)
	{
		temp = c;
				
		for(int j=1;j<c[i];j++)
		{
			temp[i] -= 1;
			
			list[count] = temp;
			count ++;
		}
		
		temp = c.drop(i);
		
		list[count] = temp;
		count ++;
	}
		
	return list;
}

// return true if the configuration c at the end of the current turn makes the current player win
bool is_winning(conf c)
{
	bool win = true;
	
	// stopping condition
	if(c == conf (1,1)) return !win;
	
	// test each accessible configuration. If a move leads to a winning configuration, then the configuration is not winning.
	else
	{		
		Vector<conf> list = list_moves(c);
		int n = list.size();
		
		for(int i=0;i<n && win;i++) win = !is_winning(list[i]);
		
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
		Vector<conf> list = list_moves(init);
		int n = list.size();
		
		for(int i=0;i<n;i++) if(is_winning(list[i])) return list[i];
		
		// if there is no winning configuration avalaible, do a random move
		
		srand(time(NULL));
		
		int col = rand() % init.size();
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
