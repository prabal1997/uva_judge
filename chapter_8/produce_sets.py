import sys

#NOTE: this creates ALL possible subsets given a list of objects

list_of_objects = list("1234");

#calculate the number upto which we need to count
obj_count = len(list_of_objects);
counter_count = 2**obj_count;

for set_choice in range(counter_count):
     #creating a list of objects based on bit-pattern
     binary_val = bin(set_choice); binary_val = binary_val[1+1:];
     binary_val = "0"*(obj_count-len(binary_val)) + binary_val;
     
     obj_set = [list_of_objects[index] for index in range(len(list_of_objects)) if int(binary_val[index])];
     
     #print the produced set
     print(obj_set);
