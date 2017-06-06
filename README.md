# Sudoku
任意阶数独求解程序，详细说明见：

[数独求解程序](http://gaomf.cn/2017/06/07/Sudoku/)

`FIXEDORDER`、`FIXEDDIAGONAL` 、`FIXEDPARTITION`三个宏用于预定义阶数、对角线约束、分块约束，这是为了快速输入使用的。

`CheckValid()`函数用于检测某个位置填入的数字的合法性。

程序中还有一些检验输入合法性的代码。

预编译好的`exe`文件使用VS 2015编译。