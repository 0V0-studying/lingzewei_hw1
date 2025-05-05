#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    // 检查行列数是否相同
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    
    // 创建结果矩阵
    Matrix result = create_matrix(a.rows, a.cols);
    
    // 逐元素相加
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }       
    return result;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    // 检查行列数是否相同
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    
    // 创建结果矩阵
    Matrix result = create_matrix(a.rows, a.cols);
    
    // 逐元素相减
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    
    return result;
}

Matrix mul_matrix(Matrix a, Matrix b)
{
     // 检查a的列数是否等于b的行数
     if (a.cols != b.rows) {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
    
    // 创建结果矩阵（行数为a的行数，列数为b的列数）
    Matrix result = create_matrix(a.rows, b.cols);
    
    // 矩阵乘法运算
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            result.data[i][j] = 0; // 初始化结果矩阵元素为0
            for (int k = 0; k < a.cols; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    
    return result;
}

Matrix scale_matrix(Matrix a, double k)
{
    // 创建结果矩阵（行列数与输入矩阵a相同）
    Matrix result = create_matrix(a.rows, a.cols);
    
    // 对矩阵a的每个元素乘以k
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] * k;
        }
    }
    
    return result;
}

Matrix transpose_matrix(Matrix a)
{
    // 创建转置矩阵（行列互换）
    Matrix result = create_matrix(a.cols, a.rows);
    
    // 转置操作：原矩阵的列变为行，行变为列
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[j][i] = a.data[i][j];
        }
    }
    
    return result;
}

// 辅助函数：获取子矩阵（去掉第row行和第col列）
Matrix get_submatrix(Matrix a, int row, int col) {
    Matrix sub = create_matrix(a.rows - 1, a.cols - 1);
    int sub_i = 0;
    for (int i = 0; i < a.rows; i++) {
        if (i == row) continue;
        int sub_j = 0;
        for (int j = 0; j < a.cols; j++) {
            if (j == col) continue;
            sub.data[sub_i][sub_j] = a.data[i][j];
            sub_j++;
        }
        sub_i++;
    }
    return sub;
}

double det_matrix(Matrix a)
{
    // 检查是否为方阵
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }

    // 基本情况：1x1矩阵
    if (a.rows == 1) {
        return a.data[0][0];
    }

    // 基本情况：2x2矩阵
    if (a.rows == 2) {
        return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
    }

    double det = 0;
    int sign = 1;

    // 对第一行进行Laplace展开
    for (int j = 0; j < a.cols; j++) {
        Matrix sub = get_submatrix(a, 0, j);
        det += sign * a.data[0][j] * det_matrix(sub);
        sign *= -1; // 交替符号
    }

    return det;
}

Matrix inv_matrix(Matrix a)
{
    // ToDo
    return create_matrix(0, 0);
}

int rank_matrix(Matrix a)
{
    // ToDo
    return 0;
}

double trace_matrix(Matrix a)
{
    // 检查是否为方阵
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }

    double trace = 0;
    
    // 计算主对角线元素之和
    for (int i = 0; i < a.rows; i++) {
        trace += a.data[i][i];
    }

    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}