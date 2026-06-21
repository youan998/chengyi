#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

// 一维数组的最大子段和 (Kadane算法)
int maxSubArray(const vector<int>& nums) {
    int cur_max = nums[0], overall_max = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        cur_max = max(nums[i], cur_max + nums[i]);
        overall_max = max(overall_max, cur_max);
    }
    return overall_max;
}

// ========== 3. 最大子矩阵和 ==========
void solveMaxSubMatrix() {
    cout << "========== 3. 最大子矩阵和 ==========" << endl;
    vector<vector<int>> matrix = {
        { 0, -2, -7,  0},
        { 9,  2, -6,  2},
        {-4,  1, -4,  1},
        {-1,  8,  0, -2}
    };

    int rows = matrix.size();
    if (rows == 0) return;
    int cols = matrix[0].size();

    int max_sum = -1e9; // 初始为一个极小值

    // 遍历所有可能的上下行组合 (top 到 bottom)
    for (int top = 0; top < rows; ++top) {
        // 用于存放压扁成一维的列和
        vector<int> col_sum(cols, 0);

        for (int bottom = top; bottom < rows; ++bottom) {
            // 将第 bottom 行的数据累加到 col_sum 中
            for (int col = 0; col < cols; ++col) {
                col_sum[col] += matrix[bottom][col];
            }

            // 对一维数组求最大子段和
            int current_max = maxSubArray(col_sum);
            max_sum = max(max_sum, current_max);
        }
    }

    cout << "矩阵为：" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%3d ", matrix[i][j]);
        }
        cout << endl;
    }
    cout << "最大子矩阵和为: " << max_sum << endl; // 应输出 15
}

int main() {
    solveMaxSubMatrix();
    return 0;
}
