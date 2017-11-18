import sys

"""
GRAPH API CREATION
"""

#ranking, unranking functions
rank_sym = lambda sym_input: ord(sym_input)-ord('a');
unrank_sym = lambda rank_input: chr(rank_input+ord('a'));

#we create functionality for a directed, weighted graph
symbol_count = ord('z')-ord('a')+1;
ideal_edge_connec_matrix = [[0 for idx in range(symbol_count)] for idx_2 in range(symbol_count)];
real_edge_connec_matrix = [[0 for idx in range(symbol_count)] for idx_2 in range(symbol_count)];

#resets the test case matrix
def reset_test():
     for idx in range(symbol_count):
          real_edge_connec_matrix[idx] = [0 for idx in range(symbol_count)];

#adding print capability
def print_graph(input_graph):
     for line in input_graph:
          print(line); 
     print("");

#making a list completely unique in O(n*log n) time
def make_unique(list_input):
     dict_input = dict(zip(list_input, [idx for idx in range(len(list_input))]));
     return [element for element in dict_input];
          
#adding functions for our graph
def add_pair(vertex_pair, input_graph):
     """
     Receives an edge tuple (a, b) between symbols a, b and adds it to the matrix
     """
     sym_a, sym_b = vertex_pair;
     sym_a, sym_b = rank_sym(sym_a), rank_sym(sym_b); 
     (input_graph[sym_a])[sym_b] += 1;
          
#adding rotation capability for 90 degrees
def rotate_graph(input_graph):
     symbol_count = len(input_graph);
     
     full_graph = [0]*symbol_count;
     for col_idx in range(symbol_count):
          reversed_list = [0]*symbol_count;
          for idx in range(symbol_count):
               reversed_list[idx] = input_graph[(symbol_count-1)-idx][col_idx];
          full_graph[col_idx] = reversed_list;
     return full_graph;     

#rotate matrix by one element
def shift_graph(input_graph):
     #swapping rows
     input_graph[0], input_graph[-1] = input_graph[-1], input_graph[0];
     
     #swapping cols
     for idx in range(len(input_graph)):
          input_graph[idx][0], input_graph[idx][-1] = input_graph[idx][-1], input_graph[idx][0];

#check if one directed graph is a subgraph of another
def check_subgraph(input_graph, superset_graph):
     for idx_1 in range(len(input_graph)):
          for idx_2 in range(len(input_graph)):
               if (input_graph[idx_1][idx_2] > superset_graph[idx_1][idx_2]):
                    return False;

     return True;

"""
PROGRAM CREATION
"""

#read all the input dictionary, strip surrounding whitespace
file = open("input_test_case", "r");
file = ([line.strip() for line in file]);

dict_len = int(file[0]);
dict_vals = file[1:1+dict_len];
test_cases = file[(1+dict_len):];

#form your ideal dictionary after removing copies, make a graph out of it
dict_vals = make_unique(dict_vals);
dict_len = len(dict_vals);
for word in dict_vals:
     for idx in range(len(word)-1):
          add_pair((word[idx], word[idx+1]), ideal_edge_connec_matrix);

for test_case in test_cases:
     #reset test case graph
     reset_test();
     
     #form unique dictionary of encrypted data
     test_case = test_case.split(' ');
     test_case = make_unique(test_case);
          
     #make a graph based on this unique dictionary
     for word in test_case:
          for idx in range(len(word)-1):
               add_pair((word[idx], word[idx+1]), real_edge_connec_matrix);
     
     #check if this empirical graph is a SUBSET of the original dictionary
     is_subgraph = [True, 0];
     for idx in range(0, symbol_count-1):
          shift_graph(real_edge_connec_matrix);
          
          is_subgraph[0] = check_subgraph(real_edge_connec_matrix, ideal_edge_connec_matrix);
          is_subgraph[1] += is_subgraph[0];
               
          if ( (not is_subgraph[0]) or (is_subgraph[1] > 1) ):
               break;
          
     #PRINT the decrypted data if subgraph detected, otherwise print stars, and continue :)
     if (is_subgraph[0] == True):
          print("Solution Exists!");
     else:
          print("No Solution!");

#create a graph based off of the inputs; In a word 'abc', a->b, b->c are the two edges added to graph
#for word in dict_args:
     
     