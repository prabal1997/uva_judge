import sys
import heapq

#NOTE: this program only works given that ALL SPEEDS ARE UNIQUE (as given in the problem description)...
#...while the uva_debug website gives duplicates in test-cases too, which is an incorrect test-case

#negates, re-heapifies a list
def pretend_max_heap(input_heap):
     for idx in range(len(input_heap)):
          input_heap[idx] = -input_heap[idx];
     heapq.heapify(input_heap);
     
#read, separate test-cases
raw_test = open("input_test_case", "r").read();
raw_test = (raw_test.split("\n\n"))[1:];
raw_test = [ [ int(num) for num in arr_list.split('\n') ] for arr_list in raw_test ];

#process each test-case individually
for test in raw_test:
     #sort list of 'ints' in non-increasing order
     test = test[1:];
     test.sort();

     #start the simulation, record steps, and keep track of...
     #...people on the left & right side of the bridge
     step_list = [];
     left_heap = test[:]; heapq.heapify(left_heap);
     right_heap = [];
     
     #we handle the special case with a single player
     if (len(left_heap) <= 2):
          step_list.append(tuple(left_heap));
          left_heap, right_heap = right_heap, left_heap;
     else:
     #we handle the general case here
          give_fast_pair = lambda heap_list: tuple(sorted(heapq.nsmallest(2, heap_list)));
          give_slow_pair = lambda heap_list: tuple(sorted(heapq.nlargest(2, heap_list))); 
          
          fastest_pair = give_fast_pair(left_heap);
          while(left_heap):
               fast_pair = give_fast_pair(left_heap);
               
               #when fastest players are on the left side, move them both to right
               if (fast_pair == fastest_pair):
                    step_list.append(fast_pair);
                    for repeat in range(2):
                         heapq.heappush(right_heap, heapq.heappop(left_heap));
                         
               #when the fastest player is alone on the left side (the second fastest player will never be there alone)...
               #..., we move the slowest pair to the right, and the second-fastest player to left
               elif (fast_pair[0] == fastest_pair[0]):
                    slow_pair = give_slow_pair(left_heap);
                    step_list.append(slow_pair);
                    
                    #negate, re-heapify list to pretend it's a 'max heap'
                    pretend_max_heap(left_heap);
                    for repeat in range(2):
                         heapq.heappush(right_heap, abs(heapq.heappop(left_heap)));
                    if (not left_heap):
                         continue;
                    
                    #negate, re-heapify list to make it a min-heap again
                    pretend_max_heap(left_heap);
                         
                    #move the second-fastest player to the left
                    second_fastest_player = heapq.heappop(right_heap);
                    step_list.append(tuple([second_fastest_player]));
                    heapq.heappush(left_heap, second_fastest_player);
                    
               #when both the fast players are on the right side, we send the fastest one back to the left
               else:
                    fastest_player = heapq.heappop(right_heap);
                    step_list.append(tuple([fastest_player]));
                    heapq.heappush(left_heap, fastest_player);
               
     #print all the steps
     total_time = sum([max(element) for element in step_list]);
     print(total_time);
     for step in step_list:
          print(*step)
          
     print("");
