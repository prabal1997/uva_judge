import sys
import math

#creates all possible permutations of a list
#NOTE: repeated permutations are printed AGAIN
def backtrack(input_list, partial_solution=[], counter=[0], iter_start=[False], bit_vector=[]):
     
     if (not iter_start[0]):
          #given an ID to EACH element in the input list
          input_list = [ (element, index) for index, element in enumerate(input_list) ];
          iter_start[0] = True;
     
     if (len(partial_solution)==len(input_list)):
          #print the relevant part of the list to the output
          partial_solution = [ element[0] for element in partial_solution ];
          print(partial_solution);
          
          counter[0] += 1;
     else:
          if (counter[0] < math.factorial(len(input_list))):
               candidates = make_candidates(input_list, partial_solution);
               for candidate in candidates:
                    partial_solution.append(candidate);
                    backtrack(input_list, partial_solution, counter);
                    partial_solution.pop();
               
def make_candidates(input_list, partial_solution):
     input_list = set(input_list);
     partial_solution = set(partial_solution);
     
     return list(input_list.difference(partial_solution));
     
#print a list of all the permutations
backtrack(list("mns"));
