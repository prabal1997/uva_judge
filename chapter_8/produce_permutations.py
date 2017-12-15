import sys
import math

#NOTE: this program individually generates permutations iteratively

#string to be permuted
input_string = "pineapple";
not_unique = (len(input_string) > len(set(input_string)));

#number of nested loops we need, their starting and ending ranges, and their state
loop_count = len(input_string);
loop_ranges = [ (0, len(input_string)-1-idx) for idx in range(len(input_string)) ];
loop_states = [ 0 for idx in range(len(input_string)) ];

#increment the loop
def increment_loop():
     #constants for notational convenience
     LAST_INDEX = -1;
     START_VALUE, END_VALUE = 0, 1;
     
     #incrementing the loop, starting from the deepest loop
     update_loop = True;
     for loop_depth in range(len(input_string)-1, -1, -1):
          #increment counter, check if other loops need to be updated
          if (update_loop):
               loop_states[loop_depth] = (loop_states[loop_depth]+1)%(loop_ranges[loop_depth][END_VALUE]+1);
               update_loop = (loop_states[loop_depth] == 0);
               
     #return 'False' if the entire loop has ended
     return (not update_loop);

#reads the loop state, prints a permutations accordingly
def give_string_perm():
     #convert string to list for easier processing
     str_list = list(input_string);
     
     #create a word using the list of all chars from the original word
     used_letters = 0;
     word_permute = "";
     for loop_depth in range(len(input_string)):
          #swap letters
          a, b = str_list[loop_states[loop_depth]], str_list[len(input_string)-1-used_letters];
          str_list[loop_states[loop_depth]], str_list[len(input_string)-1-used_letters] = b, a;
          
          #increment counter, update word
          used_letters += 1;
          word_permute = word_permute + a;
     
     #return the word
     return word_permute;
          
#print each permutation
full_list = [];
for idx in range(math.factorial(len(input_string))):
     full_list.append(give_string_perm());
     increment_loop();
     
#we find the unique permutations, print them
if (not_unique):
     full_list.sort();
     full_list = [permutation for index, permutation in enumerate(full_list) if permutation!=full_list[index-1]];
for element in full_list:
     print(element);