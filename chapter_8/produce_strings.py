import sys

#NOTE: this program produces ALL possible words in a language given a list of all the symbols, and length of the word to be formed

#set up a list of symbols to use for building all possible strings using them
symbol_list = "abc";
word_len = 3;

#set up a dynamic, nested loop depending upon the number of symbols
loop_count = word_len;
loop_state = [0] * loop_count;

#create a routine to increment the nested loop
def increment_loop():
     
     #increment the loop from inside-out
     update_loop = True;
     for loop_depth in range(loop_count-1, -1, -1):
          if (update_loop):
               loop_state[loop_depth] = (loop_state[loop_depth]+1)%len(symbol_list);
               update_loop = (loop_state[loop_depth] == 0);
          
     #check if the entire loop has terminated (happens when the outer-most loop restarts)
     return (not update_loop);
     
     
#creates a string based on the loop state
for idx in range(len(symbol_list)**word_len):
     #make a word based on the loop state
     new_word = [symbol_list[symbol_index] for symbol_index in loop_state];
     new_word = "".join(new_word);
     print(new_word);
     
     #increment the loop
     increment_loop();