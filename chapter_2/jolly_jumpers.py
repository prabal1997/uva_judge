#RECEIVE INPUT IN PYTHON FOR UVA: http://rizkywardana.github.io/2013/01/23/read-from-stdin-in-python-for-common-algorithm-challenges.html

#NOTE: this algorithm runs in O(n) time, with O(log m) ADDITIONAL space required
import sys
import math

split_digits = lambda int_input, dig_count: [ int( (str(int_input).zfill(dig_count))[idx] ) for idx in range(0, dig_count) ];

test_file = open("input_test_case", "r");
for each_line in test_file:
     input_data = each_line.split(' ');
     if (input_data[-1]==''):
          input_data = input_data[:len(input_data)-1];
     input_data = [int(num_str) for num_str in input_data];
     
     diff_count = 0;
     tracker_array = [0] * (input_data[0]-1);
     
     #count number of digits required to represent each number
     digit_count = int(math.ceil(math.log(sys.maxint)/math.log(10)));
     
     #we count occurence of EACH digit at each position
     immediate_break = False;
     
     digit_counter = [ [0]*digit_count for idx in range(0, 10) ];
     ideal_digit_counter = [ [0]*digit_count for idx in range(0, 10) ];
     for idx in range(1, input_data[0]):
          #finding the abs difference
          diff = abs(input_data[idx+1]-input_data[idx]);
          
          #updating digit counter(s)
          ideal_split, non_ideal_split = split_digits(idx, digit_count), split_digits(diff, digit_count);
          for idx_2 in range(0, digit_count):
               ideal_digit_counter[ideal_split[idx_2]][idx_2] += 1;
               digit_counter[non_ideal_split[idx_2]][idx_2] += 1;
          
          #analysing if the value can be rendered invalid definitely
          if ( ( diff == 0 ) or ( diff > input_data[0]-1 ) ):
               immediate_break = True;
               print('Not jolly');
               break;
               
     #see if we skip completing this iteration
     if (immediate_break):
          continue;
          
     #check if the digit count matches, print results
     if (digit_counter == ideal_digit_counter):
          print('Jolly');
     else:
          print('Not jolly');