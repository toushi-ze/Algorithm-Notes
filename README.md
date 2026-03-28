# My Algorithm-Notes :bulb: 

> **Ugly action beats perfection**

## :bulb:介绍   
此仓库用于记录数据结构的学习历程、核心算法实现以及 LeetCode一些题目的题解和收获，核心目标：
- 培养算法思维以及好的代码习惯
- 总结解题模板与思路技巧
- 方便后续复盘与知识点回顾

## :mag:目录结构
```
Algorithm/
├── docs/
│   └── 25_reverse_nodes_in_k_group.md  # 示例题解
│       ...                             # 其他题解
├── inc/
│   └── list/
│       ├── list_node.h                # 链表节点定义
│       └── list_k_group_reverse.h     # 函数声明
│       ...                            # 其他头文件
├── src/
│   └── list/
│       └── list_k_group_reverse.c     # 函数实现
│       ...                            # 其他源文件
├── test/
│   └── main.c                         # 测试入口
├── .gitignore                         # 忽略无关文件
├── .clang-format                      # C 语言代码格式化配置（Google 风格）
├── cmake_build.sh                     # 一键构建脚本（编译+运行+清理）
├── CMakeLists.txt                     # CMake 构建配置
└── README.md                          # 仓库说明文档
```

## 🚀 进度 (Progress)

| 日期 | 题目 | 难度 | 核心考点 | 题解 | 源码 |
| :---: | :--- | :---: | :--- | :---: | :---: |
| 2026-03-10 | 21. 合并两个有序链表 | 🟢 | 哨兵位 | [Analysis](./docs/92_reverse_linked_list_ii.md) | [Code](./src/list/list_merge.c) |
| 2026-03-11 | 206. 反转链表 | 🟢 | 三指针 | [Analysis](./docs/92_reverse_linked_list_ii.md) | [Code](./src/list/list_reverse.c) |
| 2026-03-11 | 92. 反转链表 II | 🟡 | 区间反转 | [Analysis](./docs/92_reverse_linked_list_ii.md) | [Code](./src/list/list_range_reverse.c) |
| 2026-03-16 | 19. 删除倒数第N个节点 | 🟡 | 快慢指针 | [Analysis](./docs/19_remove_nth_node_from_end_of_list.md) | [Code](./src/list/list_nth_remove.c) |
| 2026-03-19 | 25. K个一组翻转链表 | 🔴 | K组反转 | [Analysis](./docs/25_reverse_nodes_in_k_group.md) | [Code](./src/list/list_k_group_reverse.c) |
| 2026-03-22 | 141. 环形链表 | 🟢 | 快慢指针/判圈 | [Analysis](./docs/141_linked_list_cycle.md) | [Code](./src/list/list_cycle.c) |
| 2026-03-26 | 142. 环形链表 II | 🟡 | 追击问题 | [Analysis](./docs/142_linked_list_cycle_ii.md) | [Code](./src/list/list_cycle_ii.c) |

---

## :heavy_check_mark:题解笔记规范
每道题的 `solution.md` 包含以下模块：  
1. **题目介绍**：题目内容、考点
2. **解题思路**：
   - 我的直观思路
   - 优化思路（时间/空间复杂度优化）
   - 有何收获
3. **我的错误总结**：编码过程中遇到的问题及解决方案

## :triangular_flag_on_post:阶段性里程碑 (Milestones)
- [2026-03-10] 开始链表的学习，解决LC21.
  
- [2026-03-11] 创建仓库

- [2026-03-11] 解决LC206.&LC92

- [2026-03-12] 提交 LC92 综合题解
   > **说明**：由于 LC92 涵盖了前两题的核心考点，仅保留一份题解包含全部收获。
   > 源码部分（LC206, LC21, LC92）已全部同步更新。

- [2026-03-16] 提交 LC19 综合题解 
 
- [2026-03-19] 提交 LC25 综合题解

- [2026-03-22] 提交 LC141 综合题解

- [2026-03-26] 提交 LC142 综合题解
## :wave:交流
- 欢迎一起完善题解
- 若发现代码错误或有更优解法，欢迎提交 Issue
- 可通过 GitHub 私信联系，共同进步

## :loudspeaker:声明
本仓库所有题解均为个人学习笔记，仅供参考   

:smiling_face_with_three_hearts:作者：toushi-ze  
:key:仓库地址:[https://github.com/toushi-ze/Algorithm-Notes]()