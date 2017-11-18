#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<sstream>

int digit_giver(int input, int index) {
     if (index == 3)
          return input%10;
     if (index == 2)
          return (input%100-input%10)/10;
     return (input%1000-input%100)/100;
}

int main() {
	std::string word = "APPLE";
	std::pair<int, int> stuff;
	std::cout << stuff.first;
	return 0;
}
