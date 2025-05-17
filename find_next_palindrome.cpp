/*
* Problem: Palindrome Check and Next Palindrome Finder
 *
 * You are given a **positive integer** as input. Your task is to return a pair:
 *
 *   - The first element of the pair is a boolean (`true` or `false`):
 *       * `true` if the input number is a palindrome
 *       * `false` if it is not a palindrome
 *
 *   - The second element of the pair is the **next smallest palindrome number
 *     strictly greater than the input**. If the input itself is a palindrome,
 *     this next palindrome must still be strictly greater.
 *
 * Definitions:
 * - A palindrome is a number that reads the same forwards and backwards (e.g., 121, 777, 9889).
 *
 * You may assume:
 * - The input is a positive integer in the range [1, 2^31 - 1].
 * - You must return a result of type `std::pair<bool, int>` or equivalent.
 * - Leading zeroes are not considered valid in any number.
 *
 * Examples (palindromic inputs):
 *   Input: 121   → Output: {true, 131}
 *   Input: 999   → Output: {true, 1001}
 *   Input: 1     → Output: {true, 2}
 *   Input: 12321 → Output: {true, 12421}
 *   Input: 44    → Output: {true, 55}
 *
 * Examples (non-palindromic inputs):
 *   Input: 42    → Output: {false, 44}
 *   Input: 123   → Output: {false, 131}
 *   Input: 88    → Output: {false, 99}
 *   Input: 789   → Output: {false, 797}
 *   Input: 1201  → Output: {false, 1221}
 *   Input: 100   → Output: {false, 101}
 *
 * Constraints:
 * - Your algorithm must correctly detect whether the number is a palindrome.
 * - It must find the next palindrome efficiently, not by brute-force checking each number.
 */


#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace  std;

pair<bool, int> find_next_palindrome(int input) {
    int num_digits = static_cast<int>(std::log10(input)) + 1;
    // deal with 99999... corner case (solution leads to higher order magnitude)
    if (input == static_cast<int>(pow(10,num_digits)) - 1) {
        return {true, input + 2};
    }
    else if (num_digits == 1) {
        return {true, input + 1};
    }
    string s = to_string(input);

    const int original = input;
    bool is_input_pal = true;
    int next_pal = -1;

    // is_input_pal
    string in_int = to_string(input);
    if (input == 1) {
        cout << " hi";
    }
    for (int i = 0; i < in_int.size() / 2; ++i) {
        if (in_int[i] != in_int[in_int.size() - 1 - i]) {
            is_input_pal = false;
            break;
        }
    }

    // next_pal
   // input = 0;
    // first find # of digits

    if (is_input_pal) {

        if (num_digits % 2 == 0) { /// 123321
            next_pal = input / static_cast<int>(pow(10, num_digits/2));
            ++next_pal;
            string temp = to_string(next_pal);
            string to_append = temp;
            ranges::reverse(to_append);
            next_pal = stoi(temp + to_append);
        }
        else { // 12321
            next_pal = input / static_cast<int>(pow(10, num_digits/2));
            ++next_pal;
            int tempint = next_pal % 10;
            next_pal /= 10;
            string temp = to_string(next_pal);
            string to_append = temp;
            ranges::reverse(to_append);
            next_pal = stoi(temp + to_string(tempint) + to_append);
        }
    }
    else {
        bool found_next = false;
        if (num_digits % 2 == 0) { /// 123456
            next_pal = input / static_cast<int>(pow(10, num_digits/2));
            //++next_pal;
            string temp = to_string(next_pal);
            string to_append = temp;
            ranges::reverse(to_append);
            next_pal = stoi(temp + to_append);
        }
        else { // 12321
            next_pal = input / static_cast<int>(pow(10, num_digits/2));
            //++next_pal;
            int tempint = next_pal % 10;
            next_pal /= 10;
            string temp = to_string(next_pal);
            string to_append = temp;
            ranges::reverse(to_append);
            next_pal = stoi(temp + to_string(tempint) + to_append);
        }
        if (next_pal > original) found_next = true;

        while (!found_next) {
            if (num_digits % 2 == 0) { /// 123456
                next_pal = input / static_cast<int>(pow(10, num_digits/2));
                ++next_pal;
                string temp = to_string(next_pal);
                string to_append = temp;
                ranges::reverse(to_append);
                next_pal = stoi(temp + to_append);
            }
            else { // 12321
                next_pal = input / static_cast<int>(pow(10, num_digits/2));
                ++next_pal;
                int tempint = next_pal % 10;
                next_pal /= 10;
                string temp = to_string(next_pal);
                string to_append = temp;
                ranges::reverse(to_append);
                next_pal = stoi(temp + to_string(tempint) + to_append);
            }






            if (next_pal > original) found_next = true;
        }
    }
    return {is_input_pal, next_pal};
}


int main() {
    pair<bool, int> ret = find_next_palindrome(989);
    cout << ret.first << "   " << ret.second << endl << endl;


    // Example input values
    std::vector<int> inputs = {
        121, 999, 1, 12321, 44,   // Palindromic inputs
        42, 123, 88, 789, 1201, 100  // Non-palindromic inputs
    };

    // Corresponding expected outputs as pairs of (is_palindrome, next_palindrome)
    std::vector<std::pair<bool, int>> expected_outputs = {
        {true, 131},
        {true, 1001},
        {true, 2},
        {true, 12421},
        {true, 55},
        {false, 44},
        {false, 131},
        {true, 99},
        {false, 797},
        {false, 1221},
        {false, 101}
    };

    for (unsigned i = 0; i < inputs.size(); ++i) {
        cout << "Input " << inputs[i] << endl;
        if (find_next_palindrome(inputs[i]) == expected_outputs[i]) {
            cout << "Success!" << endl;
        }
        else {
            cout << "Fail! Expected: " <<expected_outputs[i].first << " " << expected_outputs[i].second << " . Returned: " << find_next_palindrome(inputs[i]).first << " " << find_next_palindrome(inputs[i]).second << endl;
        }
        cout << endl;
    }

    return 0;
}
