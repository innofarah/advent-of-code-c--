#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int alpha_to_num(string alpha) {
  if (alpha == "one")
    return 1;
  else if (alpha == "two")
    return 2;
  else if (alpha == "three")
    return 3;
  else if (alpha == "four")
    return 4;
  else if (alpha == "five")
    return 5;
  else if (alpha == "six")
    return 6;
  else if (alpha == "seven")
    return 7;
  else if (alpha == "eight")
    return 8;
  else if (alpha == "nine")
    return 9;
  else
    return -1;
}

bool isdigitC(char c) {
  // char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
  return (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' ||
          c == '5' || c == '6' || c == '7' || c == '8' || c == '9');
}

int main() {

  // --- Part One ---
  string input;
  int final_sum = 0;
  int first_digit = -1, last_digit = -1;

  fstream inputFile("day1-input.txt");

  while (getline(inputFile, input)) {
    first_digit = input.at(input.find_first_of("0123456789")) - '0';
    last_digit = input.at(input.find_last_of("0123456789")) - '0';
    final_sum += first_digit * 10 + last_digit;
  }

  inputFile.close();

  cout << "result: " << final_sum << endl;

  // --- Part Two ---

  final_sum = 0;
  fstream inputFile1("day1-input.txt");
  string digits_alpha[] = {"zero", "one", "two",   "three", "four",
                           "five", "six", "seven", "eight", "nine"};
  string firsts, lasts;

  while (getline(inputFile1, input)) {
    first_digit = input.find_first_of("0123456789"); // index
    last_digit = input.find_last_of("0123456789");
    string sub_last = string(&input[last_digit], &input[input.size()]);
    last_digit = 0; // for later test
    string sub_first = string(&input[0], &input[first_digit]);

    for (const string &digit : digits_alpha) {
      int index = sub_first.find(digit);
      if (index != input.npos && index < first_digit) {
        first_digit = index;
        firsts = digit;
      }

      int index_last0 = sub_last.find(digit, 0);

      int index_last = -1;
      while (index_last0 != input.npos) {
        index_last = index_last0;
        index_last0 = sub_last.find(digit, index_last0 + 1);
      }

      if (index_last != input.npos && index_last > last_digit) {
        last_digit = index_last;
        lasts = digit;
      }
    }

    if (last_digit == 0)
      last_digit = input.find_last_of("0123456789");
    else
      last_digit = last_digit + input.find_last_of("0123456789");

    int first, last;
    if (isdigitC(input.at(first_digit))) {
      first = input.at(first_digit) - '0';
    } else {
      first = alpha_to_num(firsts);
    }
    if (isdigitC(input.at(last_digit))) {
      last = input.at(last_digit) - '0';
    } else {
      last = alpha_to_num(lasts);
    }

    final_sum += first * 10 + last;
    cout << "first digit: " << first << endl << "last digit: " << last << endl;
  }

  inputFile.close();

  cout << "result: " << final_sum << endl;
}
