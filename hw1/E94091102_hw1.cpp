#include <iostream>
#include <stack>
#include <fstream>
#include <string>
using namespace std;

int main() {
	char file_name[10]; // only accept filename not over 10 character
	char maze [17][17]; // default the maze size is 17 * 17
	int start_x, start_y, exit_x, exit_y, step;
	cout<<"enter filename : ";
	cin>>file_name;
	cout<<"\n";
	fstream maze_file;
	maze_file.open(file_name,ios::in); // open the maze.txt
	char get_maze[305]; // read the maze.txt 305 character
	maze_file.read(get_maze, 305);
	cout<<get_maze<<endl;
	maze_file.close(); // close the maze.txt
	int k = 0; // put the maze in the maze 2D array 
	for(int i = 0; i < 17; i++){
		for(int j = 0; j < 17; j++){
			while (get_maze[k] != '1' && get_maze[k] != '0'){
				k++;
			}
		maze [j][i] = get_maze[k];
		k++;
		}
	}
	while (true){
		cout<<"enter start position : ";
		cin>>start_y>>start_x;
		if (start_x == -1 && start_y == -1){
			break;
		} // when start_x == -1 && start_y == -1 end the code
		cout<<"enter exit position : ";
		cin>>exit_y>>exit_x;
		struct item{
			int x, y, dir;
		}; // use struct to record x, y coordinate and direction
		int mark_maze [17][17] = {0}; // use mark_maze 2D array to record the coordinate had been passed
		stack<int> st_x; // use stack to record x coordinate had been passed
		stack<int> st_y; // use stack to record y coordinate had been passed
		stack<int> st_dir; // use stack to record direction coordinate had been passed
		item location = {start_x, start_y, 1}; // set the start coordinate and direction
		step = 0; // set step from 0
		st_x.push(location.x); // stack store the start coordinate 
		st_y.push(location.y);
		st_dir.push(location.dir);
		int end = 0; // set end variable to end loop whan finish the maze
		while (!st_x.empty()) 
		{ 
			if (end == 1 || end == -1){
				break;
			} // end variable = 1 (successfully escaped!!)¡B = -1 ( Fail to escape.) end the while loop
			mark_maze[location.x][location.y] = 1; // mark the coordinate we have passed
			location.x = st_x.top(); // get the last coordinate and direction we have paased
			location.y = st_y.top();
			location.dir = st_dir.top();
			if (step != 0){
				step++;
			} // increase step when coordinate changed
			cout<<step<<":"<<location.y<<","<<location.x<<endl; // print the step and cooodinate now
			st_x.pop(); // remove the fail coodinate from the stack
			st_y.pop();
			st_dir.pop();
			while (location.dir < 5) // set while loop move dirrernt direction
			{
				int g, h;
				if (location.dir == 1){
					g = location.x + 1;
					h = location.y;
				} // when location.dir == 1, go right
				else if (location.dir == 2){
					g = location.x;
					h = location.y + 1;
				} // when location.dir == 1, go down
				else if (location.dir == 3){
					g = location.x;
					h = location.y - 1;
				} // when location.dir == 1, go up
				else if (location.dir == 4){
					g = location.x - 1;
					h = location.y;
				} // when location.dir == 1, go left
				if ((g == exit_x) && (h == exit_y)) // check the next step is approved
				{
					step++;
					cout<<step<<":"<<g<<","<<h<<endl;
					cout<<"successfully escaped!!"<<endl;
					end = 1;
					break;
				}
				if ((maze[g][h] != '1') && (mark_maze[g][h] != 1)){
					step++; // increase step when coordinate changed
					mark_maze[g][h] = 1;  // mark the coordinate we have passed
					if (location.dir < 4){
						location.dir++;
					} // set the next direction in the stack
					else{
						location.dir = 1;
					}
					st_x.push(location.x); // set the coordinate and next direction in the stack
					st_y.push(location.y);
					st_dir.push(location.dir);
					location.x = g; // move
					location.y = h;
					cout<<step<<":"<<location.y<<","<<location.x<<endl; // print the step and cooodinate now
					location.dir = 1; // set the direction to right
				}
				else {
					location.dir++;
				} // if the next step is not approved change direction
			}
		}
		if (st_x.empty()){
			cout << "Fail to escape." << endl;
		} // when stack is empty mean no way to find pass maze
	}
	cout<<"end the code."<<endl; // when end variable = 1 (successfully escaped!!)¡B = -1 ( Fail to escape.) end the while loop
	return 0;
}
