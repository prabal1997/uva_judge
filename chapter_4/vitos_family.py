import sys
import numpy as npy

#open file, read testcases
raw_test = open("input_test_case", "r");

split_test = (raw_test.read()).split("\n");
split_test=split_test[1:];


#process data line-by-line
for element in split_test:
     
     #make array
     addr_array = (element.split(" "))[1:];
     addr_array = [int(val) for val in addr_array if val != ""];
     
     #find median in O(n*log(n))
     addr_array.sort();
     optimal_addr = addr_array[len(addr_array)//2];
     
     #print distance
     dist_sum = sum([abs(optimal_addr-addr) for addr in addr_array]);
     print(dist_sum);
