#ifndef __MYMATRIX__
#define __MYMATRIX__

# include<iostream>

class Matrix {
public:
    Matrix(int rows, int cols);
    ~Matrix();
    Matrix operator*(Matrix &other);
    //不能设置为类函数
    friend std::istream& operator>>(std::istream& in, Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
private:
    int rows;
    int cols;
    int **matrix;
};

Matrix::Matrix(int rows, int cols): rows(rows), cols(cols) 
{
    //matrix指向一个指针数组
    matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        //给指针数组里的指针指向的空间分配内存
        matrix[i] = new int[cols];
    }
    // 初始化每个元素为0
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
}

Matrix::~Matrix()
{   
    //先释放指针数组中的每个指针
    for (int i = 0; i < this->rows; i++) {
        delete[] matrix[i];
    }
    //再释放整个指针数组
    delete[]matrix;
}

std::istream& operator>>(std::istream& in, Matrix& matrix)
{
    int rows = matrix.rows;
    int cols = matrix.cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            in >> (matrix.matrix)[i][j];
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    int rows = matrix.rows;
    int cols = matrix.cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            os << (matrix.matrix)[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}

Matrix Matrix::operator*(Matrix &other)
{
    Matrix Mt(rows,rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < cols; k++)
                Mt.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
        }
    }
    return Mt;
}

#endif   