import sys

#read input file
input_file = open("input_test_case", "r");
input_file = [ line.strip() for line in input_file if (line.strip() != "") ];
case_count = int(input_file[0]);
input_file = input_file[1:];

#access data
def access_data(input_matrix, start_range, end_range):
     #receives address, returns '#' if invalid
     def get_data(input_matrix, addr):
          row, col = addr;
          if ( ( row >= len(input_matrix) or col >= len(input_matrix[0]) ) or ( row < 0 or col < 0 ) ):
               return '#';
          return input_matrix[row][col];
     
     #handle special case
     if (start_range == end_range):
          return get_data(input_matrix, start_range);
     
     #define start, end, and increment variables
     start_row_idx, start_col_idx = start_range[0], start_range[1];
     end_row_idx, end_col_idx = end_range[0], end_range[1];
     
     sign = lambda x: 0 if (not x) else (x/abs(x));
     row_inc, col_inc = [ sign(end_range[idx] - start_range[idx]) for idx in range(0, 1+1)];
     
     #itearte to make word
     output_list = ['#'] * max(abs(end_row_idx - start_row_idx)+1, abs(end_col_idx - start_col_idx)+1);
     counter = 0;
     while(start_row_idx != end_row_idx + row_inc + (row_inc==0) and start_col_idx != end_col_idx + col_inc + (col_inc == 0)  ):
          output_list[counter] = str(get_data(input_matrix, (start_row_idx, start_col_idx)));

          counter += 1;
          start_col_idx += col_inc;
          start_row_idx += row_inc;
     
     return "".join(output_list);
     
#gives the preferred index out of two
def give_preferred_index(first, second):
     if (first[0] < second[0]):
          return first;
     elif (first[0] == second[0]):
          if (first[1] < second[1]):
               return first;
          else:
               return second;
     else:
          return second;
     
#store all the cases in ram as [(grid, word_dict)]
input_cases = [[] for idx in range(case_count)];

case_counter, file_read_counter = 0, 0;
row_size, col_size, dict_size = 0, 0, 0;
row_read, word_read = 0, 0;
grid, input_dict = [], [];

while(case_counter < case_count):
     #read grid dimensions
     grid_size = input_file[file_read_counter];                  file_read_counter += 1;
     grid_size = grid_size.split(' ');
     row_size, col_size = int(grid_size[0]), int(grid_size[1]);
     
     #read in the grid
     grid = [0]*row_size;
     for row_idx in range(row_size):
          grid[row_idx] = input_file[file_read_counter];         file_read_counter += 1;
          
     #read in the dict_size
     dict_size = int(input_file[file_read_counter]);             file_read_counter += 1;
     
     #read in the dictionary
     input_dict = [0]*dict_size;
     for dict_idx in range(dict_size):
          input_dict[dict_idx] = input_file[file_read_counter];  file_read_counter += 1;
     
     #store case data, reset everything
     input_cases[case_counter] = (tuple(grid), tuple(input_dict));
     
     row_size, col_size, dict_size, row_read, word_read = 0, 0, 0, 0, 0;
     grid, input_dict = [], [];

     #increment case count
     case_counter +=1;
    
#make an array, intialize
for case in input_cases:
     output_list = [(float("inf"), float("inf"))] * len(case[1]);
     row_size, col_size = len(case[0]), len(case[0][0]);
     
     #iterate through each position in grid, and look for word in EVERY orientation
     for word_idx, word in enumerate(case[1]):
          current_word_loc = (float("inf"), float("inf"));
          for row_sgn in [-1, 0, 1]:
               for col_sgn in [-1, 0, 1]:
                    for col_idx in range(col_size):
                         for row_idx in range(row_size):
                                   
                              start_addr = (row_idx, col_idx);
                              end_addr = (row_idx+row_sgn*(len(word)-1), col_idx+col_sgn*(len(word)-1));
                              
                              found_word = access_data(case[0], start_addr, end_addr);
                              if (word.lower() == found_word.lower()):
                                   current_word_loc = give_preferred_index(current_word_loc, start_addr);
                                   output_list[word_idx] = current_word_loc;                  
                              
     for start_addr in output_list:
          print( str(start_addr[0]+1) + " " + str(start_addr[1]+1) );
     print("");
     
     