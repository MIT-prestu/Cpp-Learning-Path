# 🚀 C++ High-Performance Standard Library Reconstruction (Production-Ready)
# 🚀 工业级 C++ 高性能标准容器库深度还原与极端鲁棒性实践

本项目是一个专注于**极致性能、内存安全与现代 C++ 最佳实践**的底层基础库重建项目。项目完全脱离第三方依赖，由本人高强度独立手写完成。
This project is a low-level foundation library reconstruction project focusing on **extreme performance, memory safety, and modern C++ best practices**. The project is completely independent of third-party dependencies and was hand-coded by myself.

我们拒绝玩具级的代码堆砌，而是深入标准库底层布局（Memory Layout），重点攻克了**强异常安全（Strong Exception Safety）、无符号数边界溢出（Unsigned Overflow）、迭代器失效（Iterator Invalidations）以及频繁堆分配开销**等大厂生产环境中的高频痛点。
We reject toy-level code stacking. Instead, we dive deep into the low-level memory layout of the standard library, focusing on conquering high-frequency pain points in production environments, such as **strong exception safety, unsigned integer boundary overflow, iterator invalidation, and frequent heap allocation overhead**.

---
---

## 🛠️ 当前主打里程碑（Featured Milestones）

### 1. 三参数拓扑管道与双重迭代器完美复用
### 1. Three-Parameter Topological Pipeline and Dual-Iterator Reuse

我拒绝为 `iterator` 和 `const_iterator` 冗余手写两套完全相同的类代码。
I refused to write two redundant, identical sets of class code for `iterator` and `const_iterator`.

通过对底层迭代器注入 `<T, Ref, Ptr>` 三参数拓扑管道，在上层容器仅凭一行 `typedef` 瞬间动态导出完全隔离的**只读与读写双重迭代器**。
By injecting a `<T, Ref, Ptr>` three-parameter topological pipeline into the underlying iterator, completely isolated **read-write and read-only dual iterators** are dynamically derived with a single line of `typedef` in the upper-level container.

配合常量正确性（Const Correctness），在编译期直接拦截任何试图通过只读迭代器修改数据的越权行为，最大化减少代码冗余并精简编译器符号表。
Combined with Const Correctness, any unauthorized attempts to modify data through a read-only iterator are intercepted directly at compile time, maximizing code reduction and streamlining the compiler's symbol table.

### 2. 现代 Copy-and-Swap 拓扑范式与极致异常安全
### 2. Modern Copy-and-Swap Paradigm and Strong Exception Safety

全面落地现代 Copy-and-Swap 资源流转策略，彻底摒弃浅拷贝引发的物理双重释放（Double Free）隐患。
Fully implemented the modern Copy-and-Swap resource transfer strategy, completely eliminating the physical hazards of double free caused by shallow copies.

在 `operator=` 中利用**值传递（Pass-by-value）**天然触发拷贝构造生成临时对象，随后通过指针级所有权原子交换，让编译器在作用域结束时自动托管旧资源的无痛释放。
By utilizing **pass-by-value** in `operator=`, a temporary object is naturally constructed via the copy constructor. Then, through an atomic pointer-level swap of ownership, the compiler automatically manages the painless release of old resources at the end of the scope.

即便中途内存不足抛出异常，也绝不破坏原对象的状态（提供**强异常安全保证**）。
Even if an out-of-memory exception occurs midway, the state of the original object is never compromised, providing a **strong exception safety guarantee**.

### 3. 正交化解耦架构与边界安全防御
### 3. Orthogonal Decoupling Architecture and Boundary Safety Defense

在容器流转控制中，我将上层组合操作与底层核心原语进行了深度的正交化解耦。
In container flow control, I deeply decoupled upper-level composite operations from underlying core primitives orthogonally.

`push_back`、`push_front`、`pop_back`、`pop_front` 等全部无缝复用了底层高阶组件 `insert` 和 `erase`，将复杂的指针缝合逻辑收拢于单点维护。
Methods like `push_back`, `push_front`, `pop_back`, and `pop_front` all seamlessly reuse the underlying high-grade components `insert` and `erase`, consolidating complex pointer-splicing logic into a single point of maintenance.

同时，在 `erase` 等区间边界判定中，严格将有风险的加法逻辑重构为安全的减法判定（如 `len >= _size - pos`），或者设计精密的物理断言拦截，彻底封锁了悬空断裂与无符号数下溢（Underflow）导致的内存越界隐患。
Meanwhile, in boundary evaluations like `erase`, risky addition logic is strictly refactored into safe subtraction checks (e.g., `len >= _size - pos`) or precise physical assertions, completely blocking memory out-of-bounds risks caused by dangling ruptures and unsigned integer underflow.

### 4. 迭代器失效与内存漂移防御
### 4. Iterator Invalidation and Memory Drift Defense

在 `CYX::vector` 触发扩容（Reallocation）时，针对原内存被释放导致传入迭代器瞬间沦为野指针的痛点，内部设计了精准的**相对偏移量重定位（Relative Offset Relocation）**机制。
In `CYX::vector`, addressing the pain point where the original memory is released during reallocation causing the passed iterator to instantly become a dangling pointer, a precise **Relative Offset Relocation** mechanism was designed inside.

在扩容前精确锁定逻辑偏移，内存漂移后让指针动态纠偏重生，彻底封锁指针解引用崩溃；在 `resize` 扩容分支中，通过提前建立动态终点快照，阻断了循环中动态指针边界判断失控，保证了极端的控制流鲁棒性。
It locks the logical offset before reallocation and dynamically recalibrates the pointer after memory drift, completely blocking pointer dereference crashes. In the `resize` branch, by establishing a dynamic destination snapshot beforehand, we block out-of-control boundary evaluations in loops, ensuring extreme control-flow robustness.

### 5. 高性能栈缓冲流控与指针算术高效查找
### 5. High-Performance Stack-Buffered Stream Control and Pointer Arithmetic Search

为改变单字符追加导致频繁触发 `new/delete` 重新分配堆内存的现状，引入了 128 字节的局部栈缓冲区，采用“以百代一”的批量追加策略（Batch-Flushing），将堆空间分配和系统调用频次降低了数个数量级。
To prevent high-frequency heap reallocations triggered by character-by-character appending, a 128-byte local stack buffer was introduced, adopting a batch-flushing strategy to reduce dynamic heap allocations and system calls by orders of magnitude.

在子串检索中，直接利用命中指针与字符串首地址做差（`ptr - _str`）的拓扑运算快速导出绝对数组下标，成功避免了低效的二次嵌套遍历（$O(N^2)$）。
In substring retrieval, the absolute array index is derived directly through a topological operation of subtracting the base address from the hit pointer (`ptr - _str`), successfully avoiding inefficient nested scans ($O(N^2)$).

---
---

## 📦 已归档并调通的模块
## 📦 Archived and Verified Modules

### * **List (双向循环链表双子星)**
环形双指针对称拓扑 / 三参数管道无缝双重迭代器 / 现代 Copy-and-Swap 强异常安全深拷贝 / 极致正交化插入与安全擦除。
### * **List (Doubly Circular Linked List)**
Circular dual-pointer symmetrical topology / Three-parameter pipeline seamless dual-iterators / Modern Copy-and-Swap strong exception-safe deep copy / Extremely orthogonal insertion and safe erasure.

### * **Vector (高性能动态数组)**
现代 `Copy-and-Swap` 赋值 / 相对偏移迭代器防失效 / 严苛的 `resize` 三指针安全收缩与边界扩张。彻底隔离深浅拷贝，且代码布局有利于编译器做 SIMD 向量化指令展开。
### * **Vector (Dynamic Array)**
Modern `Copy-and-Swap` assignment / Relative offset-based iterator anti-invalidation / Rigorous `resize` triple-pointer safe contraction and boundary expansion. Completely isolates deep/shallow copy issues and maintains a memory layout friendly to compiler SIMD vectorization.

### * **String (高性能字符串)**
128字节局部栈缓冲区流控 / 无符号数下溢安全拦截 / 常量级指针拓扑检索 / 基于 RAII 的资源自动托管。完美应对高频字符流追加并有效解决内存碎片化痛点。
### * **String (High-Performance String)**
128-byte local stack buffer stream control / Unsigned underflow safety interception / O(1) pointer-arithmetic retrieval / RAII-based automatic resource management. Perfectly handles high-frequency character stream appending and eliminates memory fragmentation pain points.
