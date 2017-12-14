import sys

#reverses a number, adds it to itself - returns a string
def give_palindrome(number):
     number = list(number);
     number = [int(digit) for digit in number];
     
     rev_num = number[::-1];
     
     number, rev_num = [0] + number, [0] + rev_num;
     carry_arr, sum_arr = [0] * (len(number)+1), ['0'] * len(number);
     
     number, rev_num = number[::-1], rev_num[::-1]
     for digit in range(len(number)):
          sum_val = number[digit] + rev_num[digit] + carry_arr[digit];
          sum_arr[digit] = str(sum_val%10);
          carry_arr[digit+1] = sum_val//10;
     
     sum_arr = str(int("".join(sum_arr[::-1])));
     
     return sum_arr

     
#reading raw data
raw_input = open("input_test_case", "r");

raw_input = raw_input.read();
raw_input = raw_input.split('\n');
raw_input = raw_input[1:];

#process each number individually
for number in raw_input:
     palin_num = number;
     iter_count = 0;
     
     #reverse and add an integer, check if it's a palindrome
     while (palin_num != palin_num[::-1]):
          palin_num = give_palindrome(palin_num);
          iter_count += 1;
     
     print(iter_count, palin_num);
     