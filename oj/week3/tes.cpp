#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

namespace LargeInteger {
    std::string subtract( std::string& num1,  std::string& num2) {
        std::string result;
        int borrow = 0;
        int count =0;
        int i = num1.length() - 1;
        int j = num2.length() - 1;

        // Ensure num1 is always greater or equal to num2 in length
        if (j > i) {
            swap(num1, num2);
            swap(i,j);
            count++;
        }else if(i == j){
            for(int k=0;k<i+1;k++){
                if(num2[k]>num1[k]){
                    swap(num1, num2);
                    swap(i,j);
                    count++;
                }
            }
        }

        // Perform subtraction digit by digit
        while (i >= 0) {
            int digit1 = (i >= 0) ? (num1[i] - '0') : 0;
            int digit2 = (j >= 0) ? (num2[j] - '0') : 0;

            // Calculate the difference with borrow
            int diff = digit1 - digit2 - borrow;

            // Update borrow if necessary
            if (diff < 0) {
                diff += 10;  // Borrow from higher digit
                borrow = 1;
            } else {
                borrow = 0;
            }

            // Append the result digit to the result string
            result.push_back(diff + '0');

            // Move to the next digits
            i--;
            j--;
        }

        // Remove leading zeros
        while (!result.empty() && (result.back() == '0')) {
            result.pop_back();
        }

        // If result is zero, return "0"
        if (result.empty()) {
            return "0";
        }

        // Reverse the result since we filled it from right to left
        std::reverse(result.begin(), result.end());

        if(count==0){
            return result;
        }else if(count == 1){
            string w = "-";
            return w+result;
        }

    }
}

int main() {
    using namespace std;
    using namespace LargeInteger;

    string num1, num2;
    cout << "Enter the first number: ";
    cin >> num1;
    cout << "Enter the second number: ";
    cin >> num2;

    string difference = subtract(num1, num2);
    cout << "Difference: " << difference << endl;

    return 0;
}