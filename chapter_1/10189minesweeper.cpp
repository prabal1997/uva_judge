#include<iostream>
#include<cstdint>
#include<sstream>
#include<string>

int give_count(char* multi_array, int index, int rows, int cols) {
	//converting index to row, col index
	int row_index(index/cols);
	int col_index(index%cols);

	//making an array of paramters that need to be tested
	const int SIZE = 3;
	
	//counting the number of stars in neigbourhood
	int star_counter(0);
	for (int row_counter = -SIZE/2; row_counter < SIZE/2 + 1; ++row_counter) {
		for (int col_counter = -SIZE/2; col_counter < SIZE/2 + 1; ++col_counter) {
			int calc_row = row_index + row_counter;
			int calc_col = col_index + col_counter;
			
			//if the calculated row, col number is out of bounds, we simply reset the row, col number to that of the input index
			if (calc_row < 0 || calc_row > rows - 1 || calc_col < 0 || calc_col > cols-1) {
				calc_row = row_index;
				calc_col = col_index;
			}
			
			if (multi_array[cols*calc_row+calc_col] == '*')
				++star_counter;
		}
	}
	
	return star_counter;
}

int main() {
	//declaring variables for storing rows, cols, and test-case number
	int n(0), m(0), counter(0);	
	
	//create a 'stringstream' to output all the string data
	std::stringstream output_data;
	
	//check if we are on the first iteration
	bool first_iter = true;
	
	while(true){
		//receive input
		std::cin >> n >> m;
		if (!n && !m)
			break;
		
		//printing white-space appropriately
		if (first_iter)
			first_iter = false;
		else
			output_data << "\n";

		//create an array to store input
		char* matrix = new char[n*m];
		for (int counter_i = 0; counter_i < n*m; ++counter_i) {
			matrix[counter_i] = 0;
		}
		for (int counter_i = 0; counter_i < m*n; ++counter_i) {
			std::cin >> matrix[counter_i];
		}

		//create an output
		int out_matrix[n*m];
		for (int counter_i = 0; counter_i < m*n; ++counter_i) {
			//initializing...just to be extra-extra-extra safe?????
			out_matrix[counter_i] = 0;
			
			if ( matrix[counter_i] != '*' )
				out_matrix[counter_i] = give_count(matrix, counter_i, n, m);
			else
				out_matrix[counter_i] = (int)'*';
		}

		//print data
		++counter;
		output_data << "Field #" << counter << ":\n";
		for (int counter_i = 0; counter_i < m*n; ++counter_i) {
			if (out_matrix[counter_i]!='*')
				output_data << out_matrix[counter_i];
			else
				output_data << '*';
			
			if ( (counter_i+1)%m == 0 )
				output_data << "\n";
		}
	}

	//print all the output at once (except the last newline character)
	std::string output = output_data.str();
	std::cout << output;
	
	return 0;
}
