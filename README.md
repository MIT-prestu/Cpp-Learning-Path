# 🚀 C++ Mastery Journey | C++ 进阶与工程实践之路

欢迎来到我的 C++ 学习与技术沉淀仓库。
Welcome to my C++ repository for technical accumulation.

本项目用于系统化记录我掌握 C++ 的每一步足迹，重点在于通过独立实践，追求严谨的工程规范、极致的边界处理与良好的代码复用性。
This project is dedicated to systematically recording my footprints of mastering C++, focusing on robust engineering standards, meticulous boundary handling, and high code reusability through independent practice.

所有的代码实现均严格遵循现代 C++ 最佳实践，并包含详尽的边界测试与持续重构思考。
All implementations strictly adhere to modern C++ best practices and are equipped with rigorous boundary testing and continuous refactoring reflections.

---

## 🛠️ 当前里程碑：工业级 Date 类的设计与重构 (Current Milestone: Engineering-Grade Date Class)

### 核心亮点与工程思考 (Key Highlights & Engineering Reflections)

作为本仓库的起点，我实现并多次重构了一个高健壮性的 `Date` 日期类。在开发过程中，我深入思考并解决了以下工业级开发所看重的边界与性能问题：
As the starting point of this repository, I implemented and iteratively refactored a highly robust `Date` class, deeply exploring boundary cases and performance tradeoffs valued in enterprise-level development:

* **复用性与正交设计**：拒绝冗余。`operator+` 完美复用 `operator+=`，比较运算符（如 `<`、`<=`）基于 `operator>` 与 `operator==` 进行正交取反复用，保证了代码的高度可维护性。
* **Code Reusability & Orthogonal Design**: Eliminated redundancy. `operator+` seamlessly reuses `operator+=`, while comparison operators (e.g., `<`, `<=`) are orthogonally built upon `operator>` and `operator==` for high maintainability.

* **极致性能优化**：将高频调用的月天数查找表 `GetMonth` 声明为 `static` 静态数组，避免了函数反复调用在栈上重复创建对象的开销。
* **Performance Optimization**: Declared the high-frequency lookup table `GetMonth` as a `static` array, preventing the overhead of repeatedly recreating objects on the stack.

* **严谨的边界与负数处理**：重写了 `operator+=` 和 `operator-=` 的借位进位逻辑，全面覆盖了大小月、闰年跨月跨年的循环借位，并完美支持了传入负数天数（如 `date += -5`）的自动平滑转换。
* **Rigorous Boundary & Negative Input Handling**: Rewrote borrowing/carrying logic for `operator+=` and `operator-=`, perfectly supporting negative days (e.g., `date += -5`) with cyclic cross-month/cross-year adjustments.

* **C++ 规范与内存安全**：
* **C++ Standards & Memory Safety**:

    * 严格区分前置与后置 `++/--`。后置运算符正确返回临时局部对象的副本（而非野引用），杜绝了悬空引用导致的内存崩溃隐患。
    * Strictly distinguished between prefix and postfix `++/--`. Postfix operators correctly return a copy of the temporary object rather than a dangling reference, eliminating potential crashes caused by wild references.

    * 在赋值运算符重载中，使用 `this != &d` 进行高效的指针地址比对，防止自我赋值引发的无效开销。
    * Utilized `this != &d` in the assignment operator for highly efficient pointer address comparison, avoiding invalid overhead during self-assignment.

    * 为所有只读成员函数规范化加上 `const` 限定符。
    * Standardized read-only member functions with trailing `const` qualifiers.

---

## 🎯 下一步演进计划 (Next Steps & Upcoming Milestone)

本仓库将采取渐进式迭代的原则，持续向更深层次的底层逻辑演进：
Adhering to the principle of incremental iteration, this repository will continuously evolve towards deeper low-level logics:

- [ ] **Date 类特性扩展 (Date Class Extension)**
- [ ] **C++ 核心内存管理深入 (Deep Dive into C++ Memory Management)**
