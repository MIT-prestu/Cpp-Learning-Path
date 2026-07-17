# 🚀 C++ High-Performance Standard Library Reconstruction (Production-Ready)
# 🚀 工业级 C++ 高性能标准容器库深度还原与极端鲁棒性实践

本项目是一个专注于**极致性能、内存安全与现代 C++ 最佳实践**的底层基础库重建项目。项目完全脱离第三方依赖，由本人高强度独立手写完成。
This project is a low-level foundation library reconstruction project focusing on **extreme performance, memory safety, and modern C++ best practices**. The project is completely independent of third-party dependencies and was hand-coded by myself.

我们拒绝玩具级的代码堆砌，而是深入标准库底层布局（Memory Layout），重点攻克了**强异常安全（Strong Exception Safety）、无符号数边界溢出（Unsigned Overflow）、迭代器失效（Iterator Invalidations）以及频繁堆分配开销**等大厂生产环境中的高频痛点。
We reject toy-level code stacking. Instead, we dive deep into the low-level memory layout of the standard library, focusing on conquering high-frequency pain points in production environments, such as **strong exception safety, unsigned integer boundary overflow, iterator invalidation, and frequent heap allocation overhead**.

---
---

## 🛠️ 当前主打里程碑（Featured Milestones）

### 1. 现代资源管理与极致异常安全
### 1. Modern Resource Management and Strong Exception Safety

我彻底摒弃了浅拷贝的物理隐患，全盘采用现代 Copy-and-Swap 拓扑范式。
I abandoned the physical hazards of shallow copies, fully adopting the modern Copy-and-Swap paradigm.

在 `operator=` 中利用**值传递（Pass-by-value）**天然触发拷贝构造生成临时对象，随后通过 `noexcept` 的 `Swap` 成员函数实现极速的指针级所有权原子交换（Atomic Ownership Transfer）。
By utilizing **pass-by-value** in `operator=`, a temporary object is naturally constructed via the copy constructor. Then, a highly-optimized, atomic pointer-level swap of ownership is executed using the `noexcept` `Swap` member function.

让编译器在作用域结束时自动托管旧资源的无痛释放。即便中途内存不足抛出异常，也绝不破坏原对象的状态（提供**强异常安全保证**）。
This allows the compiler to automatically manage the painless release of old resources at the end of the scope. Even if an out-of-memory exception occurs midway, the state of the original object is never compromised, providing a **strong exception safety guarantee**.

### 2. 迭代器失效与内存漂移防御
### 2. Iterator Invalidation and Memory Drift Defense

在容器触发扩容（Reallocation）时，原内存被 `delete[]` 释放，导致传入的迭代器（如 `insert` 中的 `pos`）瞬间沦为野指针。
When a container triggers reallocation, the original memory is released via `delete[]`, causing the passed iterator (such as `pos` in `insert`) to instantly become a dangling pointer.

我在 `CYX::vector` 内部设计了精准的**相对偏移量重定位（Relative Offset Relocation）**机制。在扩容前精确锁定逻辑偏移，内存漂移后让指针动态纠偏重生，彻底封锁指针解引用崩溃。
I designed a precise **Relative Offset Relocation** mechanism inside `CYX::vector`. It locks the logical offset before reallocation, and dynamically recalibrates the pointer after memory drift, completely blocking pointer dereference crashes.

在 `resize` 扩容分支中，通过提前建立动态终点快照（`T* dest = _start + n`），阻断了循环中 `_finish++` 带来的动态指针边界判断失控，保证了极端的控制流鲁棒性。
In the `resize` allocation branch, by establishing a dynamic destination snapshot (`T* dest = _start + n`) beforehand, we block the out-of-control boundary evaluations caused by progressive `_finish++` increments in the loop, ensuring extreme control-flow robustness.

### 3. 区间修改与无符号数防御
### 3. Range Modification and Unsigned Integer Defense

我攻克了任意位置区间插入与防无符号溢出截断擦除的硬核底层机制。
I conquered the underlying mechanisms of range insertion and anti-unsigned-overflow erasure.

在 `erase` 等区间边界判定中，严格将有风险的加法逻辑重构为安全的减法判定（如 `len >= _size - pos`），彻底封锁了无符号数下溢（Underflow）导致的内存越界与逻辑截断隐患。
Refactored risky addition checks in boundary evaluations like `erase` into safe subtraction evaluations (e.g., `len >= _size - pos`), completely blocking out-of-bounds memory risks and logical truncation caused by unsigned integer underflow.

### 4. 指针算术高效查找
### 4. High-Performance Search via Pointer Arithmetic

在子串检索中，直接利用命中指针与字符串首地址做差（`ptr - _str`）的拓扑运算快速导出绝对数组下标。
In substring retrieval, the absolute array index is derived directly through a topological operation of subtracting the base address from the hit pointer (`ptr - _str`).

这成功避免了低效的二次嵌套遍历（$O(N^2)$），并确立了严格的常量正确性（Const Correctness），区分只读与读写迭代器，为编译器优化（如循环展开和指令加速）提供最大化的先验信息。
This successfully avoids inefficient nested scans ($O(N^2)$) and strictly enforces **Const Correctness** to distinguish read-only and read-write iterators, providing maximum prior information for compiler optimizations like loop unrolling and register reuse.

### 5. 高性能栈缓冲流控
### 5. High-Performance Stack-Buffered Stream Control

为改变单字符追加导致频繁触发 `new/delete` 重新分配堆内存的现状，引入了 128 字节的局部栈缓冲区。
To prevent high-frequency heap reallocations (`new/delete`) triggered by character-by-character appending, a 128-byte local stack buffer was introduced.

采用“以百代一”的批量追加策略（Batch-Flushing），将堆空间分配和系统调用频次降低了数个数量级，极大提升了 I/O 密集型场景下的吞吐量。
A batch-flushing strategy reduces the frequency of dynamic heap allocations and system calls by orders of magnitude, dramatically increasing throughput under I/O-intensive scenarios.

---
---

## 📦 已归档并调通的模块
## 📦 Archived and Verified Modules

### * **Vector (动态数组)**
现代 `Copy-and-Swap` 赋值 / 相对偏移迭代器防失效 / 严苛的 `resize` 三指针安全收缩与边界扩张。彻底隔离深浅拷贝，且代码布局有利于编译器做 SIMD 向量化指令展开。
### * **Vector (Dynamic Array)**
Modern `Copy-and-Swap` assignment / Relative offset-based iterator anti-invalidation / Rigorous `resize` triple-pointer safe contraction and boundary expansion. Completely isolates deep/shallow copy issues and maintains a memory layout friendly to compiler SIMD vectorization.

### * **String (高性能字符串)**
128字节局部栈缓冲区流控 / 无符号数下溢安全拦截 / 常量级指针拓扑检索 / 基于 RAII 的资源自动托管。完美应对高频字符流追加并有效解决内存碎片化痛点。
### * **String (High-Performance String)**
128-byte local stack buffer stream control / Unsigned underflow safety interception / O(1) pointer-arithmetic retrieval / RAII-based automatic resource management. Perfectly handles high-frequency character stream appending and eliminates memory fragmentation pain points.

### * **双重迭代器 (Dual Iterators)**
纯手工包装原生指针实现了 `iterator` 与 `const_iterator`，使容器天然支持基于范围的 `for` 循环（Range-based for loop）。
### * **Dual Iterators**
Manually wrapped raw pointers to implement `iterator` and `const_iterator`, enabling native support for range-based `for` loops.

### * **工业级日期类 (Date Class)**
完整重载了日期全套算术与关系比较运算符。在构造函数入口端设计了严格的闰年和合法性多重拦截机制，实现“非法数据零容忍”。
### * **Industrial Date Class**
Fully overloaded complete arithmetic and relational operators of Date, with strict leap year and validation multiple interception mechanisms designed within the constructor to enforce "zero tolerance for invalid data".
