// Matrix应该支持无参构造，此时它是一个1*1的矩阵，内部元素值为模板类型的默认值
Matrix<int> mat1;
// 通过矩阵尺寸构造，内部元素值为模板类型的默认值
Matrix<int> mat2(2, 2);
mat2[1][0] = 42; // 可以通过[][]访问内部元素
//mat1[0][1];
// 访问越界时程序行为是未定义的
assert(mat2.at(2) == 42); // 可以使用at访问矩阵按行展开后对应的元素
//mat2.at(5); // 使用at访问越界时应该抛出异常
mat2.at(1) = 1;
// 可以使用push_back()向Matrix添加元素，新添加的元素仅能通过at访问
mat2.push_back(13);
mat2.push_back(14);
assert(mat2.at(4) == 13); // pass
assert(mat2.at(5) == 14); // pass
// 可以使用reshape()修改矩阵尺寸，多余的元素会被删除，缺少的元素会使用默认值填充
mat2.reshape(3, 3);
/* 此时mat2表示的矩阵为
0 1 42
0 13 14
0 0 0
*/
// 使用initializer_list构造Matrix，此时Matrix为一个行向量
Matrix<int> mat3{1, 2, 3, 4};
Matrix<int> mat4{5, 6, 7, 8};
mat3.reshape(2, 3);
mat4.reshape(2, 3);
mat3 + mat4; // 矩阵加法，如果矩阵尺寸不同需抛出异常
mat3 - mat4; // 矩阵减法，如果矩阵尺寸不同需抛出异常
mat3 * mat4; // 矩阵乘法，此处为两个2*3的矩阵相乘，不满足矩阵乘法定义，需要抛出异常