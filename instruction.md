## 1. 项目简介

本项目是一个基于 C11 标准的**跨平台、类型无关的通用链表库**，采用 `void*` 类型擦除技术支持任意数据类型。同时项目还包含一组对应 LeetCode 经典题目的**链表算法实现**。

- **版本:** 1.0.0
- **语言:** C (C11)
- **构建系统:** CMake (>= 3.10)
- **外部依赖:** 无（纯标准库实现）

---

## 2. 项目结构

```
D:\demo\
├── CMakeLists.txt                  # CMake 构建配置
├── cmake_build.sh                  # Bash 构建/测试脚本
├── .clang-format                   # 代码格式化配置（Google）
├── README.md                       # 项目主文档
├── instruction.md                  # 使用说明
├── inc/
│   ├── list/                       # 链表头文件目录
│   │   ├── list.h                  # 通用链表公共 API
│   │   └── list_node.h            # 整数链表节点
│   ├── stack/
│   │   └── stack.h                # 通用栈公共 API
│   └── queue/
│       └── queue.h                # 通用队列公共 API
├── src/
│   ├── list/                       # 链表源码目录
│   │   ├── list.c                  # 通用链表核心实现
│   │   └── list_node.c            # 整数节点工具函数
│   ├── stack/
│   │   └── stack.c                # 通用栈实现
│   └── queue/
│       └── queue.c                # 通用队列实现
├── test/                           # 测试目录
│   ├── list_test.c                 # 通用链表单元测试
│   ├── algorithms_test.c           # 算法演示测试
│   └── stack_queue_test.c         # 栈与队列单元测试
└── docs/                           # 算法题解文档
```
---

## 3. 功能概览

### 3.1 通用链表库

基于 `void*` 的泛型单链表，内部维护头尾指针和长度计数，支持：

| 功能分类   | 函数 / 宏                      | 说明                                    |
| ---------- | ------------------------------ | --------------------------------------- |
| 创建/销毁  | `list_create()`                | 创建空链表                              |
|            | `list_destroy()`               | 销毁链表并释放所有节点（置空指针）      |
|            | `list_clear()`                 | 清空链表但保留链表对象                  |
| 插入       | `list_insert_head()`           | 头部插入 O(1)                           |
|            | `list_insert_tail()`           | 尾部插入 O(1)                           |
|            | `list_insert()`                | 按索引插入（支持负索引）                |
| 删除       | `list_remove_index()`          | 按索引删除                              |
|            | `list_remove_value()`          | 删除第一个匹配值                        |
|            | `list_remove_all_value()`      | 删除所有匹配值                          |
| 查找       | `list_get()`                   | 按索引取值（支持负索引）                |
|            | `list_find()`                  | 按值查找，返回索引                      |
| 遍历       | `list_foreach()`               | 回调函数遍历                            |
|            | `LIST_FOR_EACH()`              | 迭代器宏遍历                            |
| 信息       | `list_get_length()`            | O(1) 获取链表长度                       |

**错误码** (`list_error_t`)：

| 错误码             | 含义           |
| ------------------ | -------------- |
| `LIST_OK`          | 操作成功       |
| `LIST_NULL_POINTER`| 空指针         |
| `LIST_INDEX_OUT_OF_BOUNDS` | 索引越界 |
| `LIST_MEMORY_ALLOC`| 内存分配失败   |
| `LIST_NOT_FOUND`   | 未找到         |
| `LIST_EMPTY_LIST`  | 链表为空       |
| `LIST_INVALID_PARAM`| 无效参数       |

### 3.2 链表算法实现

| 算法             | 对应 LeetCode | 难度 | 说明                       |
| ---------------- | ------------- | ---- | -------------------------- |
| `list_reverse`   | #206          | Easy | 迭代法反转整个链表         |
| `list_merge`     | #21           | Easy | 合并两个有序链表           |
| `list_nth_remove`| #19           | Medium | 快慢指针删除倒数第 N 节点 |
| `list_range_reverse` | #92       | Medium | 反转区间 [left, right] 内的节点 |
| `list_k_group_reverse` | #25    | Hard | K 个一组反转链表           |
| `list_cycle_check` | #141        | Easy | Floyd 判圈算法             |
| `list_cycle_entry_find` | #142  | Medium | Floyd 算法找环入口        |

### 3.3 通用栈 (Stack)

基于链表封装的 LIFO（后进先出）栈，支持任意数据类型：

| 功能分类   | 函数                   | 说明                                    |
| ---------- | ---------------------- | --------------------------------------- |
| 创建/销毁  | `stack_create()`       | 创建空栈                                |
|            | `stack_destroy()`      | 销毁栈并释放所有元素（置空指针）        |
|            | `stack_clear()`        | 清空栈但保留栈对象                      |
| 操作       | `stack_push()`         | 压栈 O(1)                               |
|            | `stack_pop()`          | 弹栈 O(1)                               |
|            | `stack_top()`          | 获取栈顶元素 O(1)                       |
| 信息       | `stack_get_length()`   | O(1) 获取栈长度                         |
|            | `stack_is_empty()`     | O(1) 判断栈是否为空                     |

### 3.4 通用队列 (Queue)

基于链表封装的 FIFO（先进先出）队列，支持任意数据类型：

| 功能分类   | 函数                   | 说明                                    |
| ---------- | ---------------------- | --------------------------------------- |
| 创建/销毁  | `queue_create()`       | 创建空队列                              |
|            | `queue_destroy()`      | 销毁队列并释放所有元素（置空指针）      |
|            | `queue_clear()`        | 清空队列但保留队列对象                  |
| 操作       | `queue_enqueue()`      | 入队 O(1)                               |
|            | `queue_dequeue()`      | 出队 O(1)                               |
|            | `queue_front()`        | 获取队首元素 O(1)                       |
|            | `queue_back()`         | 获取队尾元素 O(1)                       |
| 信息       | `queue_get_length()`   | O(1) 获取队列长度                       |
|            | `queue_is_empty()`     | O(1) 判断队列是否为空                   |

---

## 4. 构建与运行

### 4.1 环境要求

- CMake >= 3.10
- 支持 C11 的编译器（GCC / Clang / MSVC）

### 4.2 使用 CMake 直接构建

**Linux / macOS:**

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

**Windows (MSVC):**

```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### 4.3 使用构建脚本 (Linux / macOS)

项目提供 `cmake_build.sh` 脚本简化操作：

```bash
chmod +x cmake_build.sh

./cmake_build.sh build             # 仅构建
./cmake_build.sh test              # 运行算法测试
./cmake_build.sh list-test         # 运行通用链表单元测试
./cmake_build.sh stack-queue-test  # 运行栈与队列单元测试
./cmake_build.sh clean             # 清理构建产物
./cmake_build.sh all               # 构建并运行全部测试（默认）
./cmake_build.sh help              # 显示帮助
```

### 4.4 使用 CTest 运行测试

```bash
cd build
ctest --output-on-failure
```

### 4.5 安装

```bash
cd build
cmake --install . --prefix /usr/local
```

安装后：头文件位于 `include/`，静态库位于 `lib/`。

---

## 5. 使用示例

### 5.1 基本用法

```c
#include "list/list.h"
#include <stdio.h>

int main(void)
{
    list_t *list = list_create();
    if (!list) return -1;

    /* 插入数据 */
    int a = 10, b = 20, c = 30;
    list_insert_tail(list, &a);
    list_insert_tail(list, &b);
    list_insert_tail(list, &c);

    /* 遍历打印 */
    size_t len = list_get_length(list);
    for (size_t i = 0; i < len; i++) {
        int *val = NULL;
        list_get(list, i, (void **)&val);
        printf("%d ", *val);
    }
    printf("\n"); /* 输出: 10 20 30 */

    /* 销毁 */
    list_destroy(&list);
    return 0;
}
```

### 5.2 存储字符串

```c
#include "list/list.h"
#include <stdio.h>

int main(void)
{
    list_t *list = list_create();

    list_insert_tail(list, "hello");
    list_insert_tail(list, "world");

    size_t len = list_get_length(list);
    for (size_t i = 0; i < len; i++) {
        char *s = NULL;
        list_get(list, i, (void **)&s);
        printf("%s\n", s);
    }

    list_destroy(&list);
    return 0;
}
```

### 5.3 使用回调遍历

```c
void print_int(void *data)
{
    printf("%d ", *(int *)data);
}

/* 调用 */
list_foreach(list, print_int);
```

### 5.4 使用算法模块（链表反转示例）

```c
#include "list/list_node.h"
#include "list/list_reverse.h"
#include <stdio.h>

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    ListNode *head = create_list(arr, 5);

    printf("原始: ");
    print_list(head);

    head = list_reverse(head);

    printf("反转: ");
    print_list(head);

    free_list(head);
    return 0;
}
```

### 5.5 使用栈 (Stack)

```c
#include "stack/stack.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* 创建栈（使用 free 自动释放内存） */
    stack_t *stack = stack_create(free);
    if (!stack) return -1;

    /* 压栈 */
    for (int i = 1; i <= 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        stack_push(stack, val);
    }

    /* 弹栈（LIFO: 5, 4, 3, 2, 1） */
    while (!stack_is_empty(stack)) {
        int *top = (int *)stack_top(stack);
        printf("%d ", *top);
        stack_pop(stack);
    }
    printf("\n"); /* 输出: 5 4 3 2 1 */

    stack_destroy(&stack);
    return 0;
}
```

### 5.6 使用队列 (Queue)

```c
#include "queue/queue.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* 创建队列（使用 free 自动释放内存） */
    queue_t *queue = queue_create(free);
    if (!queue) return -1;

    /* 入队 */
    for (int i = 1; i <= 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        queue_enqueue(queue, val);
    }

    /* 出队（FIFO: 1, 2, 3, 4, 5） */
    while (!queue_is_empty(queue)) {
        int *front = (int *)queue_front(queue);
        printf("%d ", *front);
        queue_dequeue(queue);
    }
    printf("\n"); /* 输出: 1 2 3 4 5 */

    queue_destroy(&queue);
    return 0;
}
```

---

## 6. 代码规范

- **命名规则:** 链表函数使用 `list_` 前缀、栈使用 `stack_` 前缀、队列使用 `queue_` 前缀 + 小写下划线；类型使用 `_t` 后缀（如 `list_t`, `stack_t`, `queue_t`）
- **内存安全:** 所有 `malloc` 返回值均做 NULL 检查；`list_destroy` 使用二级指针将调用者指针置空
- **负索引支持:** 类似 Python 的负索引，`-1` 表示尾部，`-2` 表示倒数第二个
- **格式化:** 遵循 `.clang-format` 中定义的 Google C++ 风格（4 空格缩进，80 列宽限制）

---

## 7. 编译器警告

项目开启了严格的编译警告：

| 编译器   | 标志                                              |
| -------- | ------------------------------------------------- |
| GCC/Clang| `-Wall -Wextra -Wpedantic -Werror`                |
| MSVC     | `/W4`                                             |

所有警告均被视为错误，确保代码质量。

---

## 8. 快速验证

构建并运行全部测试以验证环境是否正常：

```bash
# Linux / macOS
./cmake_build.sh all

# 或手动
mkdir build && cd build
cmake .. && cmake --build . && ctest --output-on-failure
```

预期结果：全部测试通过，无失败用例
