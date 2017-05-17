#### 基本的c语言编译器
---

#### 怎样运行
``` shell
linux:
git clone https://github.com/dongchangzhang/zcc
cd zcc
make
./run.sh
<-- input the c test file. like 'test/main.c' -->
```

``` shell
windows
需要下载make和g++（64bit）并配置环境变量
git clone https://github.com/dongchangzhang/zcc
cd zcc
make
双击run.bat
<-- input the c test file. like 'test/main.c' -->
```
#### 实现功能
1. 有穷自动机实现c语言词法分析
2. 采用LR1实现c语言的语法分析。具体过程包括求first集合，对文法元素求闭包、构造dfa并生成goto表和action表。可以识别绝大多数的语法结构。文法可参考res/myc_grammar.txt
3. 通过语法制导翻译，在语法分析进行的同时进行语义分析：增设语法元素属性栈记录符号属性，并在多数必要的产生式后添加语义动作，在产生式进行规约过程中对其综合属性进行计算以及采取其他相应动作。在产生式中添加标记性非终结符实现if, while等语句的回填动作，可以分析for、while、分支语句、算术表达式、数组、布尔表达式等
4. 翻译汇编代码（功能有限，待后续扩展）
#### 项目结构
```
├── bin　// 生成的可执行代码位置
├── build　//　obj文件
├── include // 所有的头文件
├── lib // windows上需要的dll
├── LICENCE
├── Makefile
├── README.md
├── res // 我的c语言文法，goto表和action表
├── run.bat // windows上的运行脚本
├── run.sh // linux上的运行脚本
├── src // 源代码
└── test //测试用的简单c代码

```
include和src目录对应放相应的头文件和源文件
```
.include
├── asm // 汇编代码生成器
├── lex // 词法分析
├── parser //文法分析
├── symboltable //符号表
├── tools // action表和goto表的生成工具
├── translate // 语义分析
├── unstd.h // 某些常量
└── utils // 小工具

```
```
.res
├── create_table_on_linux.sh // 该脚本根据文法生成goto表和action表
├── myc_grammar.txt // c语言文法
└── parsing_table.txt // goto表和action表

```
