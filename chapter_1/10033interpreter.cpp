#include<iostream>
#include<string>
#include<cstring>

//global constants
const int RAM_SIZE = 1000;
const int REG_SIZE = 10;
const int PC_IDX= RAM_SIZE + REG_SIZE;
const int MAX_VAL = 1000;

//pre-declared functions
int digit_giver(int input, int index);

int main() {
     int case_count(0);
     std::cin >> case_count;

     
     while(case_count--) {
          //make, initialize a storage array
          int ram_data[RAM_SIZE+REG_SIZE+1] = {0};
          
          //get rid of extraspaces, read incs
          std::string input_line =  std::string();
          while(input_line.empty())
               std::getline(std::cin, input_line);
          
          //take input instructions
          int inc_counter(0);
          bool cont_read(true);
          while(cont_read) {
               if (!input_line.empty()) {
                    ram_data[inc_counter++] = atoi(input_line.c_str());
                    std::getline(std::cin, input_line);
               }
               else
                    cont_read = false;
          }
          
          //execute instructions
          bool cont_exec(true);
          int inc_exec_counter = 0;
          while(cont_exec) {
               //extract current instruction, increment instruction counter, Program counter
               int local_inc(ram_data[ram_data[PC_IDX]++]);
               ++inc_exec_counter;
               
               if (digit_giver(local_inc, 1) == 2 || digit_giver(local_inc, 1) == 3 || digit_giver(local_inc, 1) == 4) {
                    int n_val(digit_giver(local_inc, 3));
                    switch(digit_giver(local_inc, 1)) {
                         case 2:
                              ram_data[RAM_SIZE + digit_giver(local_inc, 2)] = n_val;
                              break;
                         
                         case 3:
                              ram_data[RAM_SIZE + digit_giver(local_inc, 2)] = (n_val+ram_data[RAM_SIZE + digit_giver(local_inc, 2)])%MAX_VAL;
                              break;
                         
                         case 4:
                              ram_data[RAM_SIZE + digit_giver(local_inc, 2)] = (n_val*ram_data[RAM_SIZE + digit_giver(local_inc, 2)])%MAX_VAL;
                              break;
                         
                         default:
                              break;
                    }
                    //std::cout << "INC: " << local_inc << "\n";
               }
               else if (digit_giver(local_inc, 1) == 5 || digit_giver(local_inc, 1) == 6 || digit_giver(local_inc, 1) == 7) {
                    int reg_val(ram_data[RAM_SIZE + digit_giver(local_inc, 3)]);
                    switch(digit_giver(local_inc, 1)) {
                         case 5:
                              ram_data[RAM_SIZE + digit_giver(local_inc, 2)] = reg_val;
                              break;
                         
                         case 6:
                              ram_data[RAM_SIZE + digit_giver(local_inc, 2)] = (reg_val+ram_data[RAM_SIZE + digit_giver(local_inc, 2)])%MAX_VAL;
                              break;
                         
                         case 7:
                              ram_data[RAM_SIZE + digit_giver(local_inc, 2)] = (reg_val*ram_data[RAM_SIZE + digit_giver(local_inc, 2)])%MAX_VAL;
                              break;
                         
                         default:
                              break;
                    }
               }
               else if (digit_giver(local_inc, 1) == 8 || digit_giver(local_inc, 1) == 9) {
                    //getting an alias to the mentioned address
                    int& addr_val = ram_data[ram_data[RAM_SIZE + digit_giver(local_inc, 3)]];
                    switch(digit_giver(local_inc, 1)) {
                         case 8:
                              ram_data[RAM_SIZE + digit_giver(local_inc, 2)] = addr_val;
                              break;
                         
                         case 9:
                              addr_val = ram_data[RAM_SIZE + digit_giver(local_inc, 2)];
                              break;
                         
                         default:
                              break;
                         }
               }
               else if (digit_giver(local_inc, 1) == 0) {
                    if (ram_data[RAM_SIZE + digit_giver(local_inc, 3)])
                         ram_data[PC_IDX] = ram_data[RAM_SIZE + digit_giver(local_inc, 2)];
               }
               else {
                    //halt
                    cont_exec = false;
               }
          }
          
          std::cout << inc_exec_counter << "\n\n";
     }
     
     return 0;
}

//takes an int, index as input; returns a digit
int digit_giver(int input, int index) {
     if (index == 3)
          return input%10;
     if (index == 2)
          return (input%100-input%10)/10;
     return (input%1000-input%100)/100;
}