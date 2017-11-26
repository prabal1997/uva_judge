#read the input test cases into a list (of lists)
test_file = open("input_test_case", "r")
test_file = [element.strip() for element in test_file]

test_case_count = int(test_file[0])
test_cases = [[] for col in range(test_case_count)]; test_case_count = 0

test_file = test_file[2:]
for idx, element in enumerate(test_file):
     if (len(element)):
          test_cases[test_case_count].append(element)
     else:
          test_case_count += 1
          
#process each case individually
for case in test_cases:
     #calculate length of the file
     file_len = 0
     for fragment in case:
          file_len += len(fragment)
     file_len //= (len(case)//2)
     
     #create an array of dicts. for all possible fragments
     dict_array = [ {} for frag_size in range(file_len) ]
     for fragment in case:
          if (fragment in dict_array[len(fragment)]):
               dict_array[len(fragment)-1][fragment] += 1
          else:
               dict_array[len(fragment)-1][fragment] = 1
     dict_array = [ list(element) for element in dict_array ]

     #go through each of the sizes, and create all possible combinations of a file
     comb_array = [ set() for case_count in range(file_len//2) ]
     for idx in range(file_len//2):
          word_size = idx + 1;
          if ( word_size == file_len//2 and (not file_len%2) ):
               if (len(dict_array[word_size-1]) == 1):
                    comb_array[idx].add(2*dict_array[word_size-1][0])
               else:
                    for rep in range(0, 1+1):
                         comb_array[idx].add("".join(dict_array[word_size-1]))
                         dict_array[word_size-1].reverse()
          else:
               for idx_1, element_1 in enumerate(dict_array[word_size-1]):
                    for idx_2, element_2 in enumerate(dict_array[file_len-word_size-1]):
                         comb_array[idx].add(element_1 + element_2); comb_array[idx].add(element_2 + element_1)
     
     #we find the only combination that's common across ALL the words
     final_set = set();
     for comb_set in comb_array:
          if (comb_set):
               #check if 'final' set is empty
               if (not final_set):
                    final_set = final_set.union(comb_set)
               else:
                    final_set.intersection_update(comb_set)
                    #break out of loop if only one selection remains
                    if (len(final_set) == 1):
                         break
                    
     #we print all possibilities (in case there are multiple)
     print(list(final_set)[0])
     print("");
     
     #NOTE: there can be MULTIPLE solutions (and we need to print only ONE of them), and that might NOT neccesarily
     #match uDebug's solution(s), but this solutino IS correct
               
               