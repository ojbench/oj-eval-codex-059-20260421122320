# Problem 059 - OJ 的继承与派生

**ACMOJ Problem ID**: 1440

## Table of Contents

- [Problem 059 - OJ 的继承与派生](#problem-059-oj-的继承与派生)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Background](#background)
  - [Assignment Description](#assignment-description)
    - [Grade Composition](#grade-composition)
  - [Assignment Requirements](#assignment-requirements)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
    - [Samples](#samples)
    - [Data Constraints](#data-constraints)
  - [Per-Testcase Resource Limits](#per-testcase-resource-limits)
  - [Test Data](#test-data)
  - [Submission Requirements](#submission-requirements)
    - [Submission Format](#submission-format)
    - [Submission Guidelines](#submission-guidelines)
    - [Evaluation Notes](#evaluation-notes)
    - [Academic Integrity](#academic-integrity)

## Introduction

### Background

Implement OJ judger class hierarchy: ICPCJudger, OIJudger, SpacialJudger derived from BaseJudger. OOP design with inheritance.

## Assignment Description

### Grade Composition

| Grading Component | Percentage |
| :--: | :--: |
| Pass **1440. OJ 的继承与派生** | 80% |
| Code Review | 20% |

Here are several points that need clarification:

- In the Code Review, we will **strictly examine your code style and repository organization structure, etc.**

- This assignment provides some sample data for testing, stored in the `/workspace/data/059/data_test/` directory. Note that these are not the test cases on the Online Judge. Passing all local test cases does not guarantee that you will pass the OJ tests.

- Besides the provided sample data, we also encourage you to design your own test data based on your program logic to assist debugging.

## Assignment Requirements

### Problem Description

### 题目背景

经过一个学期小作业和机考的洗礼，相信大家对 `onlinejudge` 有了一定的了解。终于到了期末机考，这次是没机会拿 `onlinejudge` 当调试器了（误），但摆在你面前的是一个实现简单 `onlinejudge` 派生类的题目。

给你的是一个 `BaseJudger` 基类，现在需要你完成的是 `ICPCJudger` 派生类、 `OIJudger` 派生类和 `SpacialJudger` 派生类。实现的目的很简单，就是能够用它们对提交的 `time`， `memory`，`output` 在不同 `judge` 机制下进行评分。 


### 题目描述

给了你一个基类 `BaseJudger`，其中你只需要在 `// todo` 的地方补全构造函数和析构函数即可，其他地方不允许进行任何修改，不允许添加任何成员和成员函数。（下发代码中的 `size_t` 是一种数据类型，你可以把它当作非负的 `int`）

题目的重点是需要你在此基础上派生出 `class ICPCJudger`， `class OIJudger` 和 `class SpacialJudger`。

派生类中请根据需要添加你需要的成员以及成员函数。


#### ICPCJudger

`ICPCJudger` 的构造方式， `judger = new ICPCJudger(time_limit, memory_limit, answer);`

`ICPCJudger` 的 `Submit` 评测标准是：

当 `time <= time_limit && memory <= memory_limit` 并且答案正确时给 100 分，其余都给零分；

可以多次 `Submit` 并且取最高的分数；

答案正确的要求是 `output` 与 `answer` 完全相同； 


#### OIJudger

`OIJudger` 的构造方式， `judger = new OIJudger(time_limit, memory_limit, answer);`

`OIJudger` 的 `Submit` 评测标准是：

当 `time <= time_limit && memory <= memory_limit` 并且答案正确时给 100 分，其余都给零分；

只能 `Submit` 一次取唯一分数，一旦多次提交直接爆零。

注意：不同于 `ICPCJudger` 的是， `OIJudger` 对答案正确的要求是忽略 `output` 和 `answer`行尾的空格的（如果 `answer` 是多行的，则忽略每一行行尾空格）；


#### SpacialJudger

`SpacialJudger` 的构造方式，`judger = new SpacialJudger(time_limit, memory_limit, full_score_time, full_score_memory, answer);`

`SpacialJudger` 的 `Submit` 评测标准：

当用 `SpacialJudger` 评测的时候，会额外给出两个指标 `full_score_time` 和 `full_score_memory`；

除了要求答案正确以外，对于 `time` 指标，当 `time <= full_score_time` 时 `time_score`给 100 分，当 `time >= time_limit` 时 `time_score` 指标给 0 分，对于 `full_score_time < time < time_limit` 的情况， `time_score` 与 `time` 是线性关系，对于 `memory` 指标是同理的（`time_score` 和 `memory_score` 的计算均向下取整），并且最后的分数是由 `floor(time_score * memory_score / 100)` 得到的。（也就是说，如果 `time` 和 `memory` 都是 50 分，最后的得分是 25 分）

可以多次 `Submit` 并且取最高的分数。

对答案正确的要求同 `ICPCJudger` 一样；

你的代码可以以如下框架为基础：
```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
class BaseJudger {
public:
    BaseJudger (size_t time_limit , size_t memory_limit ,
                const char *answer){
    // todo
    }

    virtual void Submit (size_t time , size_t memory , const char *output) = 0;

    size_t GetScore () const { return score_; }

    virtual ~BaseJudger () {
        // todo
    };

protected:
    char *answer_;
    const size_t time_limit_;
    const size_t memory_limit_;
    size_t score_;

    virtual bool CheckAnswer (const char *output) const {
        // the output must equal to the answer
        return strcmp(answer_ , output) == 0;
    }
};


class OIJudger {
    // todo
};

class ICPCJudger {
    // todo
};

class SpacialJudger {
    // todo
};
```

如下 test.cpp 可供调试参考：
```c++
#include <iostream>
#include "code3.hpp"
using namespace std;


string get_data () {
    // ignore empty lines
    string ret = "" , line;
    while (getline(cin , line)) {
        if (line.length() == 0) {
            continue;
        }
        if (line == "#####") {
            break;
        }
        ret += line + "\n";
    }
    return std::move(ret);
}

int main () {
    char judger_name[100];
    cin >> judger_name;
    size_t time_limit , mem_limit;
    cin >> time_limit >> mem_limit;
    BaseJudger *judger = nullptr;
    string tmp;
    if (strcmp(judger_name , "OIJudger") == 0) {
        tmp = get_data();
        judger = new OIJudger(time_limit , mem_limit , tmp.c_str());
    } else if (strcmp(judger_name , "ICPCJudger") == 0) {
        tmp = get_data();
        judger = new ICPCJudger(time_limit , mem_limit , tmp.c_str());
    } else if (strcmp(judger_name ,"SpacialJudger") == 0) {
        size_t full_score_time , full_score_memory;
        cin >> full_score_time >> full_score_memory;
        tmp = get_data();
        judger = new SpacialJudger(time_limit , mem_limit , full_score_time ,
                                   full_score_memory , tmp.c_str());
    } else {
        cout << "Unknown Judger type" << endl;
        return 0;
    }
    
    size_t submit_time , submit_mem;
    while (cin >> submit_time >> submit_mem) {
        tmp = get_data();
        const char *output = tmp.c_str();
        judger->Submit(submit_time , submit_mem , output);
    }
    cout << judger->GetScore() << endl;
    delete judger;
    return 0;
}
```

### Input Format

输入的第一行是 `judger_name`

输入的第二行给出了在当前 `judger` 下需要给出的若干项指标

输入的接下去若干行是正确的 `answer`（保证多行 `answer` 之间没有空行）

输入一行 `#####` 分割符，以判断 `answer` 读取完毕

接下去的输入都是提交，可能会重复多次。

每次提交的第一行是 `time` 和 `memory`

每次提交的接下去若干行是 `output`(保证多行 `output` 之间没有空行）

每次提交的最后一行是 `#####` 分割符，以判断一次提交结束

### Output Format

一行一个数，即最终的 `score`

### Samples

#### Sample 1

**Input:**
```
ICPCJudger
1000 1000
abcd
dcba
#####
500 1001
abcd
dcba
#####
500 500
abcd
dcba
#####
```

**Output:**
```
100
```

### Data Constraints

$1-4$ 测试点， `judger_name = ICPCJudger`

$5-7$ 测试点， `judger_name = SpacialJudger`

$8-10$ 测试点， `judger_name = OIJudger`

测试数据中保证分数始终为整数，且能被整除。

## Per-Testcase Resource Limits

- **Time Limit (per test case)**: 3000 ms
- **Memory Limit (per test case)**: 256 MiB
- **Disk Usage**: No disk usage is permitted.

## Test Data

The test data for this problem is located at `/workspace/data/059/data_test/`.

## Submission Requirements

### Submission Format

Submit a single C++ source file to the Online Judge. The OJ provides its own `main.cpp` which `#include "src.hpp"`. Your submission will be written to `src.hpp` and compiled together with the OJ's driver code.

### Submission Guidelines

- The submitted code must be able to compile successfully through the above compilation process
- The program needs to be able to read data from standard input and write results to standard output
- Please ensure the code runs correctly within the given time and space limits
- **You must use C++ or C language** to implement this assignment

### Evaluation Notes

- The evaluation system will test your program using the provided test data
- The program output must exactly match the expected output (including format)
- Exceeding time or memory limits will be judged as the corresponding error type
- Please pay attention to the overall time performance of your code and the time complexity of each part of your algorithm.

### Academic Integrity

If any violations are found during evaluation or code review (including but not limited to using unconventional methods to pass test cases), your final score may be significantly reduced or become **0 points**.
