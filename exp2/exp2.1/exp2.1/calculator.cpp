#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// 栈的最大容量
const int MaxSize = 100;

// 栈类模板
template <class T>
class Stack {
private:
    T data[MaxSize];
    int top;
public:
    Stack() { top = -1; }
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == MaxSize - 1; }

    // 入栈
    bool push(T x) {
        if (isFull()) return false;
        data[++top] = x;
        return true;
    }

    // 出栈
    bool pop(T& x) {
        if (isEmpty()) return false;
        x = data[top--];
        return true;
    }

    // 获取栈顶元素
    bool getTop(T& x) {
        if (isEmpty()) return false;
        x = data[top];
        return true;
    }
};

// 优先级表实现
int priority(char op) {
    switch (op) {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    case '(': return 0;
    default: return -1;
    }
}

// 计算两个数的运算结果
double calculate(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) {
            throw "除数不能为零";
        }
        return a / b;
    default: return 0;
    }
}

// 判断是否是数字
bool isNumber(char c) {
    return c >= '0' && c <= '9';
}

// 字符串计算器主函数
double stringCalculator(string expr) {
    Stack<double> numStack;  // 数字栈
    Stack<char> opStack;     // 运算符栈

    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == ' ') continue;  // 跳过空格

        if (isNumber(expr[i])) {  // 处理数字
            double num = 0;
            while (i < expr.length() && (isNumber(expr[i]) || expr[i] == '.')) {
                if (expr[i] == '.') {
                    double decimal = 0.1;
                    i++;
                    while (i < expr.length() && isNumber(expr[i])) {
                        num += (expr[i] - '0') * decimal;
                        decimal *= 0.1;
                        i++;
                    }
                }
                else {
                    num = num * 10 + (expr[i] - '0');
                    i++;
                }
            }
            i--;
            numStack.push(num);
        }
        else if (expr[i] == '(') {  // 处理左括号
            opStack.push(expr[i]);
        }
        else if (expr[i] == ')') {  // 处理右括号
            char op;
            while (!opStack.isEmpty()) {
                opStack.getTop(op);
                if (op == '(') {
                    opStack.pop(op);
                    break;
                }
                opStack.pop(op);
                double b, a;
                numStack.pop(b);
                numStack.pop(a);
                numStack.push(calculate(a, b, op));
            }
        }
        else {  // 处理运算符
            while (!opStack.isEmpty()) {
                char top;
                opStack.getTop(top);
                if (priority(expr[i]) <= priority(top)) {
                    opStack.pop(top);
                    double b, a;
                    numStack.pop(b);
                    numStack.pop(a);
                    numStack.push(calculate(a, b, top));
                }
                else {
                    break;
                }
            }
            opStack.push(expr[i]);
        }
    }

    // 处理剩余的运算符
    while (!opStack.isEmpty()) {
        char op;
        opStack.pop(op);
        double b, a;
        numStack.pop(b);
        numStack.pop(a);
        numStack.push(calculate(a, b, op));
    }

    double result;
    numStack.pop(result);
    return result;
}

// 主函数，包含测试用例
int main() {
    try {
        // 测试用例
        string expressions[] = {
            "1 + 2",
            "2.5 * 4",
            "3 + 4 * 2",
            "(1 + 2) * 3",
            "1 + 2 * 3 + 4",
            "10 / 2 + 3",
            "1.5 + 2.5 * 3"
        };

        for (const string& expr : expressions) {
            cout << "表达式: " << expr << endl;
            cout << "结果: " << stringCalculator(expr) << endl;
            cout << "-------------------" << endl;
        }

        // 交互式测试
        string userExpr;
        cout << "请输入要计算的表达式（输入q退出）：";
        while (getline(cin, userExpr) && userExpr != "q") {
            try {
                cout << "结果: " << stringCalculator(userExpr) << endl;
            }
            catch (const char* msg) {
                cout << "错误: " << msg << endl;
            }
            cout << "请输入要计算的表达式（输入q退出）：";
        }

    }
    catch (const char* msg) {
        cout << "错误: " << msg << endl;
    }

    return 0;
}