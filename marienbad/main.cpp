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
		return conf (1,1);
	}
}

int main()
{
	conf c (1,2);
	cout << play(c);
	return 0; 
}
