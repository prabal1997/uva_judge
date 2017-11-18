import sys

#ranking, unranking functions
rank_sym = lambda sym_input: ord(sym_input)-ord('a');
unrank_sym = lambda rank_input: chr(rank_input+ord('a'));

#we create functionality for a directed, weighted graph
symbol_count = ord('z')-ord('a')+1;
ideal_to_real_map, real_to_ideal_map = [0] * symbol_count, [0] * symbol_count;

#convert a string into a generic format based on the frequency of letters, and word sizes
def give_format(input_string):
     starting_char = ord('A');
     for idx in range(len(input_string)):
          if ( not ( ord('A') <= ord(input_string[idx]) <= ord('Z') ) ):
               input_string = input_string.replace(input_string[idx], chr(starting_char));
               starting_char += 1;
     return input_string;

#dynamic looper that returns 'True' when all iterations are complete
counter_vals, upper_limits = [], [];
def increment_count():
     
     #iterate through all possibilites of a set
     update_parent = True;
     for idx in range(0, len(counter_vals)):
          rev_idx = (len(counter_vals)-1)-idx;
          
          if (not update_parent):
               break;
          
          counter_vals[rev_idx] = (1+counter_vals[rev_idx])%upper_limits[rev_idx];
          if (not counter_vals[rev_idx]):
               update_parent = True;
          else:
               update_parent = False;
               
     #inform user if all iterations are complete
     if (update_parent):
          return True;
     else:
          return False;


"""
PROGRAM CREATION
"""
#read all the input dictionary, strip surrounding whitespace
file = open("input_test_case", "r");
file = ([line.strip() for line in file]);

dict_len = int(file[0]);
dict_vals = file[1:1+dict_len];
test_cases = file[(1+dict_len):];

for test_case in test_cases:
     #clear the data from previous iteration
     ideal_to_real_map, real_to_ideal_map = [0] * symbol_count, [0] * symbol_count;
     counter_vals, upper_limits = [], [];
     
     #form unique dictionary of encrypted data
     test_case = test_case.split(' ');

     #see which dictionary words match the format of each word
     test_case_buckets = [ [ dict_val for dict_val in dict_vals if ( give_format(dict_val) == give_format(test_word) ) ] for test_word in test_case ];

     #now go through a dynamic number of loops (first element is the current index, the second element is the range)
     counter_vals = [0] * len(test_case_buckets);
     upper_limits = [ len(test_case_buckets[idx]) for idx in range(len(test_case_buckets)) ]

     #keep running the loop
     stop_dynamic_loop = False;
     match_found = False;
     while(not stop_dynamic_loop):
          #checking all values
          invalid_size_bucket_lists = any([ ( len(test_case_buckets[idx]) == 0 ) for idx in range(len(test_case_buckets)) ]);
          if (invalid_size_bucket_lists):
               match_found = False;
               stop_dynamic_loop = True;
               continue;
          
          #prepare a selection of words based on the counter value
          selected_words = [ test_case_buckets[idx][counter_vals[idx]] for idx in range(len(test_case_buckets)) ];
          
          #checking consistency of all words
          wrong_word_comparison = False;
          for bucket_word, real_word in zip(selected_words, test_case):
               for bucket_letter, real_letter in zip(bucket_word, real_word):
                    if ( (not ideal_to_real_map[rank_sym(bucket_letter)]) and (not real_to_ideal_map[rank_sym(real_letter)]) ):
                         ideal_to_real_map[rank_sym(bucket_letter)] = real_letter;
                         real_to_ideal_map[rank_sym(real_letter)] = bucket_letter;
                    else:
                         if (ideal_to_real_map[rank_sym(bucket_letter)] == real_letter and real_to_ideal_map[rank_sym(real_letter)] == bucket_letter):
                              continue;
                         else:
                              wrong_word_comparison = True;
                              break;
                    
               if (wrong_word_comparison):
                    break;
          
          if (wrong_word_comparison):
               #increment counter(s)
               ideal_to_real_map, real_to_ideal_map = [0] * symbol_count, [0] * symbol_count;
               stop_dynamic_loop = increment_count();
          else:
               stop_dynamic_loop = True;
               match_found = True;
     
     #print the decoded message
     if (match_found):
          #decrypt the sequence using the calculated decryption scheme
          for idx in range(len(test_case)):
               for letter in test_case[idx]:
                    #replace all lowercase letter with equivalent decryption
                    if (letter.lower() == letter):
                         test_case[idx] = test_case[idx].replace(letter, str(real_to_ideal_map[rank_sym(letter)]).upper());
                         
               test_case[idx] = test_case[idx].lower();
     
     else:
          #replace every character with a star to indicate unsuccessful decryption
          test_case = [  ("*" * len(test_word)) for test_word in test_case ];
     
     #convert the list to a sentence
     test_case = [ (word + " ") for word in test_case];
     test_case = ("".join(test_case)).strip();
     print(test_case);     