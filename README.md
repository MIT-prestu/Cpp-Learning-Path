# 🚀 C++ 极致进阶与工业级实践
# 🚀 C++ Ultimate Progress and Industrial Practice

本项目系统记录了我独立手敲的高性能 C++ 自定义类库，专注于深度还原标准库的底层行为与内存布局。
This project systematically records my self-implemented high-performance custom C++ classes, focusing on deeply recreating the low-level behavior and memory layout of the standard library.

本项目中所展示的自定义 String 类的所有核心底层逻辑与工业级优化，均在一天内高强度独立手敲实现。
All core low-level logics and industrial-grade optimizations of the custom String class demonstrated in this project were hand-coded and achieved within a single high-intensity day.

---
---

## 🛠️ 当前主打里程碑：一日封顶全功能 String
## 🛠️ Current Key Milestone: One-Day Completion of Full-Featured String

### 1. 现代资源管理与写安全
### 1. Modern Resource Management and Safe Copying

我彻底摒弃了浅拷贝的物理隐患，全盘采用现代 Copy-and-Swap 拓扑范式。
I abandoned physical hazards of shallow copies, fully adopting the modern Copy-and-Swap paradigm.

通过临时对象与堆内存指针交换，让编译器自动托管旧资源释放，确保了强异常安全性。
By swapping pointers with temporary objects, the compiler automatically manages resource release to ensure strong exception safety.

### 2. 区间修改与无符号数防御
### 2. Range Modification and Unsigned Integer Defense

我攻克了任意位置区间插入与防无符号溢出截断擦除的硬核底层机制。
I conquered the underlying mechanisms of range insertion and anti-unsigned-overflow erasure.

在 `erase` 中将有风险的加法逻辑重构为安全的减法判定（如 `len >= _size - pos`），彻底封锁了内存越界隐患。
Refactored risky addition checks in `erase` into safe subtraction evaluations (e.g., `len >= _size - pos`), completely blocking out-of-bounds memory risks.

### 3. 指针算术高效查找
### 3. High-Performance Search via Pointer Arithmetic

在子串检索中，直接利用命中指针与字符串首地址做差（`ptr - _str`）的拓扑运算快速导出绝对数组下标。
The absolute array index is derived directly through a topological operation of subtracting the base address from the hit pointer (`ptr - _str`).

这成功避免了低效的二次遍历，并确立了严格的常量正确性。
This successfully avoids inefficient nested scans and strictly enforces read-only semantics.

### 4. 高性能栈缓冲流控
### 4. High-Performance Stack-Buffered Stream Control

为改变单字符追加导致频繁触发 `new/delete` 重新分配堆内存的现状，引入了 128 字节的局部栈缓冲区。
To prevent high-frequency heap reallocations (`new/delete`) triggered by character-by-character appending, a 128-byte local stack buffer was introduced.

采用“以百代一”的批量追加策略（Batch-Flushing），将堆空间分配频次降低了数个数量级。
A batch-flushing strategy reduces the frequency of dynamic heap allocations by orders of magnitude.

---
---

## 📦 已归档并调通的模块
## 📦 Archived and Verified Modules

* **工业级日期类 (Date Class)**：完整重载了日期全套算术与关系比较运算符，并在构造函数中设计了严格的闰年和合法性多重拦截机制。
* **Industrial Date Class**: Fully overloaded complete arithmetic and relational operators of Date, with strict leap year and validation interception mechanisms designed within the constructor.

* **双重迭代器 (Dual Iterators)**：纯手工包装原生指针实现了 `iterator` 与 `const_iterator`，使容器天然支持基于范围的 `for` 循环。
* **Dual Iterators**: Manually wrapped raw pointers to implement `iterator` and `const_iterator`, enabling native support for range-based `for` loops.

---
---
