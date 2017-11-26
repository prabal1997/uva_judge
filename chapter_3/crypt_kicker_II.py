import sys

#generalizes the string structure
def gen_string(input_string):
    ord_count = 0;
    for idx, letter in enumerate(input_string):
        if ( (not letter.isspace()) and letter.islower() ):
            input_string = input_string.replace(letter, chr(ord_count+ord('A')));
            ord_count += 1;
            
    return ("".join(input_string)).lower();
            
#import the test case to the program
test_file = open("input_test_case", "r");
test_file = [line.strip() for line in test_file];

test_count = int(test_file[0]); test_file = test_file[2:];
test_array = [ [] for idx in range(test_count) ];

group_counter = 0;
for line in test_file:
    if (not len(line)):
        group_counter += 1;
        continue;
    test_array[group_counter].append(line);
test_array = test_array[:-1];

#process each input individually
match_sentence = "the quick brown fox jumps over the lazy dog";
code_to_real_array, temp_array = [], [];

for case in test_array:
    
    code_to_real_array = [''] * (ord('z') - ord('a') + 1);
    temp_array = [''] * (ord('z') - ord('a') + 1);
    code_found = 0;
    
    #check if a decryption is possible
    for line in case:
        #reset array for every line
        temp_array = [''] * (ord('z') - ord('a') + 1);
        
        #check if decryption of line exists, and store it permanently
        if (gen_string(match_sentence) == gen_string(line)):
            code_found += 1;
            for idx in range(len(match_sentence)):
                if (not match_sentence[idx].isspace()):
                    temp_array[ord(line[idx])-ord('a')] = match_sentence[idx];
            code_to_real_array = temp_array[:];
            
    #check if unique solution exists, and print it if possible
    if (code_found == 1):
        #replacing letters with their original self
        for line in case:
            for letter in line:
                if ( (not letter.isspace()) and letter.islower() ):
                    line = line.replace(letter, code_to_real_array[ord(letter)-ord('a')].upper());
                    
            line = line.lower();
            #print the decoded line
            print(line);
    else:
        print("No Solution");
    print("");
    
            
    