import sys

#this uses backtracking to create all possible sets
def backtrack(input_list, partial_vector=[], global_count=[0]):
     if (len(partial_vector) == len(input_list)):
          global_count[0] += 1;
          print(vector_to_set(input_list, partial_vector));
     else:
          candidate_list = construct_candidate_list();
          #only make a new solution if we need to
          if (global_count[0] < 2**len(input_list)):
               #use the candidate list to make every new vector that's one element longer than the received partial solution
               for candidate in candidate_list:
                    #add an additional candidate to the end of the list
                    partial_vector = partial_vector + [candidate];
                    
                    #backtrack with this new vector of inputs                    
                    backtrack(input_list, partial_vector, global_count);

                    #REMOVE the additional entry for replacement by another entry
                    partial_vector.pop();

#make a list of all possible candidate
def construct_candidate_list():
     candidate_list = [True, False];
     return candidate_list;

#converts an input list, and a bool vector to a complete solution
def vector_to_set(input_list, partial_vector):
     return [element for element, boolean in zip(input_list, partial_vector) if (boolean)];
     
#start backtracking using the input ['a', 'b', 'c']
backtrack(['a', 'b', 'c']);