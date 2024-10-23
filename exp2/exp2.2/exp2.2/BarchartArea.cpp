#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>
#include <cstdlib>

// 计算柱状图中矩形的最大面积
int largestRectangleArea(std::vector<int>& heights) {
    int maxArea = 0;
    std::stack<int> s;
    heights.push_back(0); // 添加一个0高度的柱子，方便处理最后的剩余柱子
    for (int i = 0; i < heights.size(); ++i) {
        while (!s.empty() && heights[s.top()] > heights[i]) {
            int height = heights[s.top()];
            s.pop();
            int width = s.empty() ? i : i - s.top() - 1;
            maxArea = std::max(maxArea, height * width);
        }
        s.push(i);
    }
    heights.pop_back(); // 恢复原始数据
    return maxArea;
}

// 随机生成柱状图高度
std::vector<int> generateRandomHeights(int length) {
    std::vector<int> heights(length);
    for (int i = 0; i < length; ++i) {
        heights[i] = rand() % 10; // 生成范围在0到10之间的随机高度
    }
    return heights;
}

int main() {
    srand(static_cast<unsigned>(time(0))); // 初始化随机数种子

    // 进行10组测试
    for (int i = 0; i < 10; ++i) {
        int length = 1 + rand() % 10; // 随机生成数组长度，范围1到10
        std::vector<int> heights = generateRandomHeights(length);
        int maxArea = largestRectangleArea(heights);
        std::cout << "Test " << i + 1 << ": ";
        std::cout << "Heights = [";
        for (int j = 0; j < heights.size(); ++j) {
            std::cout << heights[j];
            if (j != heights.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
        std::cout << "Maximum Rectangle Area = " << maxArea << "\n\n";
    }

    return 0;
}

