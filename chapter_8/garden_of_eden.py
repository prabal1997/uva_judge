import sys
import itertools

#define constants, functions
BYTE_SIZE = 8;
append_zeros = lambda bit_pattern, ideal_size: "0"*(ideal_size-len(bit_pattern))+bit_pattern; 

#backtrack to produce a list of SETS, each SET contains all the possibilities; before returning the answer, we 'intersect'...
#...all the sets
def backtrack(input_seq, new_state_map):
     
     #prepare a set of possible 'previous values' for each position in the input sequence
     solution_set = [];
     for index, digit in enumerate(input_seq):
          possible_vals = [ append_zeros(bin(index)[2:], 3) for index, element in enumerate(new_state_map) if (element == digit) ];
          solution_set.append(possible_vals);
          
     #start recursive backtracking
     def prepare_candidates(solution_set, solution_vector):
          if (solution_vector):
               return [ element for element in solution_set[len(solution_vector)] if (solution_vector[-1][1:] == element[:1+1]) ]
          else:
               return solution_set[0];
               
     def recur_backtrack(solution_set, solution_vector=[], solution=[False]):
          #check if the answer's been found
          if (len(solution_vector) == len(solution_set)):
               if (solution_vector[-1][1:] == solution_vector[0][:1+1]):
                    solution[0] = True;
          else:
               #prepare a list of candidates for the next step
               candidate_list = prepare_candidates(solution_set, solution_vector);
               for candidate in candidate_list:
                    #add the candidate to the solution vector
                    solution_vector.append(candidate);
                    #check if we have the correct solution
                    recur_backtrack(solution_set, solution_vector, solution);
                    #pop-out the candidate
                    solution_vector.pop();
                    
               
     #return the output  
     boolean_val = [False];
     recur_backtrack(solution_set, solution=boolean_val);
     
     return boolean_val[0];      
          
#read input from the file
raw_input = open("input_test_case", "r").read();
raw_input = raw_input.split('\n');
raw_input = [ line.split(' ') for line in raw_input ];

#process each test separately
for test in raw_input:
     #map input cell pattern to output cell pattern
     append_zeros = lambda bit_pattern, ideal_size: "0"*(ideal_size-len(bit_pattern))+bit_pattern; 
     
     new_state_map = bin(int(test[0]))[2:];
     new_state_map = append_zeros(new_state_map, BYTE_SIZE);
     
     #start backtracking
     if (backtrack(test[2], new_state_map)):
          print('REACHABLE');
     else:
          print('GARDEN OF EDEN');
          
#print(raw_input);