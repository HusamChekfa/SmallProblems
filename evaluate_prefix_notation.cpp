/*
* Problem: Nested Arithmetic Expression Parser
 *
 * You are given a string that represents a nested arithmetic expression
 * involving integer constants and the following operations: add, sub, mult, and div.
 * Each operation takes exactly two arguments and is written in the form:
 *
 *     operation(arg1,arg2)
 *
 * Here, `operation` is one of the four keywords: `add`, `sub`, `mult`, or `div`.
 * The arguments `arg1` and `arg2` may either be integer literals (e.g., 5, -2, 0)
 * or other valid nested expressions of the same format.
 *
 * There are no spaces in the input string. You must evaluate the expression
 * and return the result as a double. Integer division should be performed
 * as floating-point division (e.g., div(5,2) = 2.5).
 *
 * You can assume:
 * - All input strings are valid and properly formatted.
 * - Parentheses are always properly balanced.
 * - Division by zero will never occur.
 *
 * Examples:
 *   Input: "add(1,3)"                         → Output: 4.0
 *   Input: "sub(add(5,2),3)"                  → Output: 4.0
 *   Input: "mult(2,sub(7,1))"                 → Output: 12.0
 *   Input: "div(add(4,2),3)"                  → Output: 2.0
 *   Input: "add(mult(2,sub(10,4)),div(20,5))" → Output: 16.0
 *
 * Constraints:
 * - All numeric values are integers and fit within 32-bit signed integers.
 * - Nesting can be arbitrarily deep.
 * - The implementation must parse and evaluate the expression recursively
 *   or using a stack-based approach.
 * - Do not use external parsing libraries—manual parsing only.
 */

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace  std;

double calculate(string str) {
    stack<string> s;

    while (!str.empty()) {
        // find the first ',' or  '(' or ')'
        size_t o_p = str.find('(');
        size_t c_p = str.find(')');
        size_t c = str.find(',');

        size_t found = std::min({o_p, c_p,c});

        string curr = str.substr(0,found);
        if (isdigit(curr[0]) && isdigit(s.top()[0])) {
            string temp = curr;;
            while (!s.empty() && isdigit(temp[0]) && isdigit(s.top()[0])) {
                string popped = s.top();
                s.pop();
                string operation = s.top();
                s.pop();
                if (operation == "add") temp = (to_string(stod(temp) + stod(popped)));
                else if (operation == "sub") temp = (to_string(stod(popped) - stod(temp)));
                else if (operation == "mult") temp = (to_string(stod(temp) * stod(popped)));
                else temp = (to_string(stod(popped) / stod(temp))); // div
            }
            s.push(temp);
        }
        else if (!curr.empty()) s.push(curr);

        str = str.substr(found+1);
    }
    return stod(s.top());
}

int main() {
    string input = "add(1,3)";
    cout << calculate(input);
    cout << endl;

    std::vector<std::string> expressions = {
        "add(mult(2,sub(10,4)),div(20,5))",
        "sub(add(15,mult(2,3)),div(18,3))",
        "mult(add(4,5),sub(12,div(16,4)))",
        "div(mult(add(2,2),sub(9,3)),add(1,1))",
        "add(sub(mult(3,7),div(20,4)),add(1,1))",
        "sub(div(add(9,3),mult(2,2)),sub(10,6))",
        "mult(div(sub(18,6),2),add(3,4))",
        "div(mult(sub(30,15),2),add(2,2))",
        "add(mult(add(1,1),sub(8,3)),div(24,6))",
        "sub(add(mult(2,add(3,2)),div(16,4)),mult(2,2))"
    };

    // Manually computed results as doubles:
    std::vector<double> results = {
        // 1) add(mult(2,sub(10,4)),div(20,5))
        //    sub(10,4) = 6, mult(2,6)=12, div(20,5)=4, add(12,4)=16
        16.0,

        // 2) sub(add(15,mult(2,3)),div(18,3))
        //    mult(2,3)=6, add(15,6)=21, div(18,3)=6, sub(21,6)=15
        15.0,

        // 3) mult(add(4,5),sub(12,div(16,4)))
        //    add(4,5)=9, div(16,4)=4, sub(12,4)=8, mult(9,8)=72
        72.0,

        // 4) div(mult(add(2,2),sub(9,3)),add(1,1))
        //    add(2,2)=4, sub(9,3)=6, mult(4,6)=24, add(1,1)=2, div(24,2)=12
        12.0,

        // 5) add(sub(mult(3,7),div(20,4)),add(1,1))
        //    mult(3,7)=21, div(20,4)=5, sub(21,5)=16, add(1,1)=2, add(16,2)=18
        18.0,

        // 6) sub(div(add(9,3),mult(2,2)),sub(10,6))
        //    add(9,3)=12, mult(2,2)=4, div(12,4)=3, sub(10,6)=4, sub(3,4)=-1
        -1.0,

        // 7) mult(div(sub(18,6),2),add(3,4))
        //    sub(18,6)=12, div(12,2)=6, add(3,4)=7, mult(6,7)=42
        42.0,

        // 8) div(mult(sub(30,15),2),add(2,2))
        //    sub(30,15)=15, mult(15,2)=30, add(2,2)=4, div(30,4)=7.5
        7.5,

        // 9) add(mult(add(1,1),sub(8,3)),div(24,6))
        //    add(1,1)=2, sub(8,3)=5, mult(2,5)=10, div(24,6)=4, add(10,4)=14
        14.0,

        // 10) sub(add(mult(2,add(3,2)),div(16,4)),mult(2,2))
        //     add(3,2)=5, mult(2,5)=10, div(16,4)=4, add(10,4)=14, mult(2,2)=4, sub(14,4)=10
        10.0
    };

    for (unsigned i = 0; i < expressions.size(); ++i) {
        if (calculate(expressions[i]) == results[i]) {
            cout << "Success!" << endl;
        }
        else cout << "Fail!" << " Expected: " << results[i] << " but calculated " << calculate(expressions[i]) << endl;
    }

    return 0;
}
