#include<iostream>
#include<cstdio>
#include<string>
#include<sstream>
#include<algorithm>

#define null_pointer 0

//create a special notation indicating positions of variables
enum lcd_part {top = 0, top_left, top_right, middle, bottom_left, bottom_right, bottom};

void give_bar(std::stringstream& output, int row_num, int s_value, std::string char_code) {
	//use character code to determine what needs to be printed
	std::string bar = " ";
	if (row_num == 0) {
		bar = ( (char_code[top]-'0') ? "-" : " " );
	}
	else if (row_num == s_value+1) {
		bar = ( (char_code[middle]-'0') ? "-" : " " );
	}
	else if (row_num == 2*s_value+2) {
		bar = ( (char_code[bottom]-'0') ? "-" : " " );
	}
	
	//make output
	output << " ";
	for (int count = 0; count < s_value; ++count)
		output << bar;
	output << "  "; 
}

void give_row(std::stringstream& output, int row_num, int s_value, std::string char_code) {
	std::string left_bar, right_bar;
	if (row_num > 0 && row_num < s_value+1) {
		left_bar = ( (char_code[top_left]-'0') ? "|" : " " );
		right_bar = ( (char_code[top_right]-'0') ? "|" : " " );
	}
	else if (row_num > s_value+1 && row_num < 2*s_value+2) {
		left_bar = ( (char_code[bottom_left]-'0') ? "|" : " " );
		right_bar = ( (char_code[bottom_right]-'0') ? "|" : " " );
	}
	
	//make output
	output << left_bar;
	for (int count = 0; count < s_value; ++count)
		output << " ";
	output << right_bar << " ";
}

int main() {
	uint32_t s(1);
	std::string n;
	std::stringstream output_data, reference_stream;
	/*
	. The following diagram shows that each 'index' of a
    . digit's 'config' array-element represents the following components of the LCD:
	.    0  
	.    - 
	. 1 |3| 2
	.    -
	. 4 |6| 5 
	.    -
	*/

	std::string list[10] = {std::string()+"1110111", std::string()+"0010010", std::string()+"1011101",
						   std::string()+"1011011", std::string()+"0111010", std::string()+"1101011",
						   std::string()+"1101111", std::string()+"1010010", std::string()+"1111111",
						   std::string()+"1111011"};
	
	bool cont(true), first_iteration(true);
	while(cont) {
		//receive the input
		std::cin >> s >> n;
		
		//terminate only when both 's', 'n' are zero
		if ( !s && !std::stoi(n, null_pointer, 10) ) {
			cont = false;
		}
		else {
			
			if (!first_iteration)
				output_data << "\n\n";
			else
				first_iteration = false;
			
			//start drawing the characters onto the 'output_array'
			for (int row_num = 0; row_num < (2*s+3); ++row_num) {
				for (int count = 0; count < n.length(); ++count) {
					//extract character-relevant code
					std::string char_code = list[n[count]-'0'];
					
					//clear reference stream0
					reference_stream.str(std::string());
					reference_stream.clear();
					
					//check if the row corresponds to top, middle, or bottom bar
					bool is_last_char = (count == n.length()-1);
					if ( (row_num == 0) || (row_num == s+1) || (row_num == 2*s+2) )
						give_bar(reference_stream, row_num, s, char_code);
					else
						give_row(reference_stream, row_num, s, char_code);
					
					output_data << reference_stream.str();
				}
				//print a new line after drawing a row
				int last_row = (2*s+2);
				if (row_num != last_row)
					output_data << "\n";
			}
		}
	}
	//dumping the bufferred output
	std::cout << output_data.str() << "\n\n";

	return 0;
}
