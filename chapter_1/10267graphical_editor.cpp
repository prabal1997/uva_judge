#include<iostream>
#include<sstream>
#include<string>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<utility>

#define WHITE 'O'
#define null_ptr 0

//neccesary data-types
struct file {
	public:
		//fields
		std::string name;
		char* data_array;
		int cols;
		int rows;

		//constructors, destructors
		file() {
			name = "";
			cols = rows = 0;
			data_array = null_ptr;
		}
		
		file(std::string input_name, int input_cols, int input_rows) {
			name = input_name;
			cols = input_cols;
			rows = input_rows;
			
			//initializing entire table to white
			data_array = new char[rows*cols];
			for (int count = 0; count < rows*cols; ++count)
				data_array[count] = WHITE;
		}
		
		~file() {
			delete[] data_array;
			data_array = null_ptr;
		}
		
		//operator(s)
		char& operator() (int col_num, int row_num) {
			col_num -= 1; row_num -= 1;
			return data_array[row_num*cols+col_num];
		}
};

void color_neighbors(int, int, file&, std::vector<std::pair<int, int>>&, bool*);

int main() {
	std::stringstream output_data;
	std::string command;
	std::vector<file*> file_list;
	
	while(command[0]!='X') {
		std::cin >> command;
		
		//process if command's correct, ignore otherwise
		switch(command[0]) {
			case 'I': {
				int m(0), n(0);
				std::cin >> m >> n;
				
				//create, initialize field
				file* new_file = new file("untitled", m, n);
				file_list.push_back(new_file);
				
				break;
			}
			case 'C': {
				file* current_file = file_list[file_list.size()-1];
				
				//recolor entire table to white
				int size = (current_file->rows)*(current_file->cols);
				for (int count = 0; count < size; ++count)
					current_file->data_array[count] = WHITE;
				
				break;
			}
			case 'L': {
				file* current_file = file_list[file_list.size()-1];
				int x(0), y(0);
				char c(0);
				
				std::cin >> x >> y >> c;
				(*current_file)(x, y) = c;
				
				break;
			}
			case 'V': {
				file* current_file = file_list[file_list.size()-1];
				int x(0), y_1(0), y_2(0);
				char c(0);
				
				std::cin >> x >> y_1 >> y_2 >> c;
				if (y_1 > y_2)
					std::swap(y_1, y_2);
				for (int row_index = y_1; row_index < y_2+1; ++row_index)
					(*current_file)(x, row_index) = c;
				
				break;
			}
			case 'H': {
				file* current_file = file_list[file_list.size()-1];
				int x_1(0), x_2(0), y(0);
				char c(0);
				
				std::cin >> x_1 >> x_2 >> y >> c;
				if (x_1 > x_2)
					std::swap(x_1, x_2);
				for (int col_index = x_1; col_index < x_2+1; ++col_index)
					(*current_file)(col_index, y) = c;
				
				break;
			}
			case 'K': {
				file* current_file = file_list[file_list.size()-1];
				int x_1(0), y_1(0), x_2(0), y_2(0);
				char c(0);
				
				std::cin >> x_1 >> y_1 >> x_2 >> y_2 >> c;
				if (x_1 > x_2)
					std::swap(x_1, x_2);
				if (y_1 > y_2)
					std::swap(y_1, y_2);
				for (int col_index = x_1; col_index < x_2+1; ++col_index)
					for (int row_index = y_1; row_index < y_2+1; ++row_index)
						(*current_file)(col_index, row_index) = c;
				
				break;
			}
			case 'F': {
				file& current_file = *file_list[file_list.size()-1];
				std::vector<std::pair<int, int>> point_list;
				
				bool* tracker_array = new bool[current_file.rows*current_file.cols];
				for (int counter = 0; counter < current_file.rows*current_file.cols-1; ++counter)
					tracker_array[counter] = false;

				int x(0), y(0);
				char c(0);
				
				std::cin >> x >> y >> c;
				
				//make list of all elements that require modification
				color_neighbors(x, y, current_file, point_list, tracker_array);
				
				//iterate through the entire list and change the colors
				for (int counter = 0; counter < point_list.size(); ++counter)
					current_file(point_list[counter].first, point_list[counter].second) = c;
				
				//delete the created array
				delete[] tracker_array;
				
				break;
			}
			case 'S': {
				std::string input_name;
				std::cin >> input_name;

				//change name
				file* current_file = file_list[file_list.size()-1];
				current_file->name = input_name;
				
				//print the file
				output_data << input_name << "\n";
				
				int size = (current_file->rows)*(current_file->cols);
				for (int count = 0; count < size; ++count) {
					output_data << (current_file->data_array)[count];
					if ( count%(current_file->cols) == current_file->cols-1 )
						output_data << "\n";
				}
				break;
			}
			//NOTE: Case 'X' is included in 'default'
			default: {
				continue;
			}
		}
	}
	//dumping all the data on the screen
	std::cout << output_data.str();
	
	return 0;
}

//colors a cell's neighbors recursively
void color_neighbors(int col_num, int row_num, file& file_object, std::vector<std::pair<int, int>>& list, bool* tracker_array) {
	//check if the current cell has already been examined
	int abs_row_num = row_num - 1;
	int abs_col_num = col_num - 1;
	if (tracker_array[abs_row_num*file_object.cols + abs_col_num])
		return;
	
	//mark the un-marked cell visited
	tracker_array[abs_row_num*file_object.cols + abs_col_num] = true;
	
	//continue processing if the current cell has never been examined
	const int SIZE = 3;
	int max_row(file_object.rows), max_col(file_object.cols);
	
	for (int col_idx = -SIZE/2; col_idx < SIZE/2 + 1; ++col_idx) {
		for (int row_idx = -SIZE/2; row_idx < SIZE/2 + 1; ++row_idx) {
			int calculated_col(col_num+col_idx), calculated_row(row_num+row_idx);
			
			//we only visit nodes directly above, below, front, or back - NO DIAGNOLS
			if (col_idx==row_idx || calculated_col < 1 || calculated_col > max_col || calculated_row < 1 || calculated_row > max_row) {
				//calculated_col = col_num; calculated_row = row_num;
				continue;
			}
			
			if (file_object(calculated_col, calculated_row) == file_object(col_num, row_num)){
				//store list of ALL co-ordinates around that have the same color
				std::pair<int, int> current_pair;
				current_pair.first = calculated_col;
				current_pair.second = calculated_row;
				
				list.push_back(current_pair);
				
				//recursively call the function
				color_neighbors(calculated_col, calculated_row, file_object, list, tracker_array);
			}
		}
	}
}