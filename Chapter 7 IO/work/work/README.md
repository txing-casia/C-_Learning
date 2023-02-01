## 第七章作业 - 文件加密和解密

### 文件结构

工程文件在VSCode的C++环境下开发完成，包括以下文件：

- `decrypt.cpp`：解密主程序文件；
- `encrypt.cpp`：加密主程序文件；
- `launch.json`：VSCode的C++环境配置文件；
- `tasks.json`：VSCode的C++环境配置文件；
- `result.png`：输出结果截图；
- `README.pdf`：作业说明
- `CipherText.txt`，`CipherText2.txt`，`cleartext.txt`，`codebook1.txt`，`codebook2.txt`：

编译`main.cpp`后，命令行输入

```
./encrypt  codebook.txt  cleartext.txt  output.txt
./decrypt  codebook.txt  CipherText.txt  cleartext.txt
```

即可执行。



### 代码功能

实现以下功能：

- 实现加密功能；
- 实现解密功能；
- 实现大小写对应；
- 实现换行对应；
- 扩展1：
  - 无
- 扩展2：
  -  无