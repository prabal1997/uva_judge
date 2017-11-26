import sys

def make_string(row_col_start_addr, row_col_inc, word_len, list_input):
     #build the word letter-by-letter by iterating through the grid
     my_word = [0]*word_len;
     for word_idx in range(word_len):
          row_idx, col_idx = row_col_start_addr;
          row_inc, col_inc = row_col_inc;
          
          row_idx, col_idx = row_idx+row_inc*word_idx, col_idx+col_inc*word_idx;
          my_word[word_idx] = list_input[row_idx][col_idx];
          
     return "".join(my_word);
     
file = open("input_test_case2", "r");
file = file.read();
file = file.split('\n');

print(make_string([5, 0], [-1, -1], 5, file));