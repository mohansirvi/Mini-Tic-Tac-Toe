/*MOHAN SIRVI NIT SRINAGAR*/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define pr_nl cout<<'\n'
#define nl '\n'
#define fast_IO ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
char board[5][5];
string name;

//For checking the remaining move
bool any_move_remaining(){

	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(board[i][j]=='_') return true;
	return false;
}


int function()
{
	// Checking for Rows for X or O victory.
	for(int row = 0; row<3; row++)
	{
		if (board[row][0]==board[row][1] && board[row][1]==board[row][2])
		{
			if (board[row][0]=='x')
				return +100;
			else if (board[row][0]==name[0])
				return -100;
		}
	}
	// Checking for Columns for X or O victory.
	for (int col = 0; col<3; col++)
	{
		if (board[0][col]==board[1][col] && board[1][col]==board[2][col])
		{
			if (board[0][col]=='x')
				return +100;

			else if (board[0][col]==name[0])
				return -100;
		}
	}
	// Checking for Diagonals for X or O victory.
	if (board[0][0]==board[1][1] && board[1][1]==board[2][2])
	{
		if (board[0][0]=='x')
			return +100;
		else if (board[0][0]==name[0])
			return -100;
	}

	if (board[0][2]==board[1][1] && board[1][1]==board[2][0])
	{
		if (board[0][2]=='x')
			return +100;
		else if (board[0][2]==name[0])
			return -100;
	}

	// Else if none of them have won then return 0
	return 0;
}

//print the board at the instance
void board_print(){


	cout<<"B O A R D"<<"  C O N T R O L L E R S   "<<nl;
	for(int i=0;i<3;i++)
	{
		cout<<nl;
		for(int j=0;j<3;j++)
			cout<<board[i][j]<<" ";
		cout<<" | ";
		for(int j=0;j<3;j++)
			cout<<"("<<i+1<<","<<j+1<<")";

		cout<<nl;
	}
	cout<<nl;
}

//Min-Max Algorithm of Game Theory
int minmax(int depth,bool Is){

	int points=function();
	if(points== +100 || points== -100 )
		return points;
	if(any_move_remaining()==false)
		return false;

	if (Is)
	{
		int best = -10000000;
		// Traverse all cells
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				// Check if cell is empty
				if (board[i][j]=='_')
				{
					// Make the move
					board[i][j] = 'x';
					// Call minimax recursively and choose
					// the maximum value
					best = max( best,
							minmax( depth+1, !Is) );

					// Undo the move
					board[i][j] = '_';
				}
			}
		}
		return best;
	}

	// If this minimizer's move
	else
	{
		int best = 1000;
		// Traverse all cells
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				// Check if cell is empty
				if (board[i][j]=='_')
				{
					// Make the move
					board[i][j] = name[0];
					// Call minimax recursively and choose
					// the minimum value
					best = min(best,minmax(depth+1, !Is));
					// Undo the move
					board[i][j] = '_';
				}
			}
		}
		return best;
	}
}

//Checking for the best move of system
void best_move(){
	int X=-1,Y=-1,BEST=-1;

	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			if(board[i][j]=='_')
			{
				board[i][j]='x';
				int Val = minmax(0,false);
				board[i][j]='_';

				if(Val>BEST){
					X=i,Y=j,BEST=Val;
				}
			}

		}

	cout<<"Bot's Move :  "<<X+1<<"  "<< Y+1<<nl;

	board[X][Y]='x';
}


int main()
{
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			board[i][j]='_';
		}
	}
	// name[0] = user
	// x = bot

	cout<<"ENTER YOUR NAME : "<<nl;
	cin>>name;
	cout<<nl;
	cout<<" FIRST LETTER OF YOUR NAME DENOTES YOUR PLAYER "<<nl;
	cout<<nl;
	cout<<" X DENOTES SYSTEMS PLAYER "<<nl;
	cout<<nl;
	cout<<"FIRST TURN IS YOURS "<<nl;
		board_print();
	while(function()==false && any_move_remaining()==true){
		int x,y;

		// player movers
		int correct_input=false;
		do{

		cout<<name<<"'s  Move : ";
		cin>>x>>y;
		x--,y--;
		if(board[x][y]=='_')
		{
			correct_input=true;
			board[x][y]=name[0];
		}
		else continue;

		}while(correct_input==false);
		if(function()) break;
		else  board_print();

		// bot moves
		best_move();
		if(function()) break;
		else  board_print();

	}

	if(function()== -100)
	{
		cout<<nl;
		cout<<nl;
		cout<<name<<"       WINS !!!! "<<nl;
		board_print();
		cout<<"      G A M E     O V E R    "<<nl;

	}
	else if(function()== 100)
	{
		cout<<nl;
		cout<<nl;
		cout<<"           BOT WINS !!!! "<<nl;
		board_print();
		cout<<"      G A M E     O V E R    "<<nl;
	}
	else{
		cout<<nl;
		cout<<nl;
		cout<<"TIE !!!!"<<nl;
		board_print();
		cout<<"      G A M E     O V E R    "<<nl;

	}
	return 0;
}
