#

1. 记录 clang++ 的profile 写到makefile里面
2. 记录咱们优化的过程，也就是一些trick，一个是把重复的初始化给提取出去，一个是减少循环的遍历串的次数

## clang llvm profile

Profiling with Clang can be done using several methods, depending on your goals (e.g., performance analysis, code coverage, or Profile-Guided Optimization). Here's a guide to common approaches:

---

### **1. Code Coverage Profiling**

Use Clang's built-in instrumentation to track code coverage (useful for testing).

#### Steps

1. **Compile with instrumentation flags**:

   ```bash
   clang -fprofile-instr-generate -fcoverage-mapping your_program.c -o your_program
   ```

2. **Run the program** to generate raw profiling data (`default.profraw`):

   ```bash
   LLVM_PROFILE_FILE="coverage.profraw" ./your_program
   ```

3. **Convert raw data to a usable format** (`.profdata`):

   ```bash
   llvm-profdata merge -sparse coverage.profraw -o coverage.profdata
   ```

4. **Generate a coverage report**:

   ```bash
   llvm-cov show ./your_program -instr-profile=coverage.profdata
   ```

---

### **2. Performance Profiling with `perf` (Linux)**

Use the `perf` tool to analyze runtime performance.

#### Steps

1. **Compile with debug symbols**:

   ```bash
   clang -g -O2 your_program.c -o your_program
   ```

2. **Profile with `perf`**:

   ```bash
   perf record ./your_program
   ```

3. **View results**:

   ```bash
   perf report
   ```

---

### **3. Clang XRay (Function Call Tracing)**

Trace function calls for detailed performance insights.

#### Steps

1. **Compile with XRay instrumentation**:

   ```bash
   clang -fxray-instrument -o your_program your_program.c
   ```

2. **Run the program** and generate XRay logs:

   ```bash
   XRAY_OPTIONS="patch_premain=true" ./your_program
   ```

3. **Analyze logs**:

   ```bash
   llvm-xray account xray-log.your_program.* -sort=count -sortorder=dsc
   ```

---

### **4. Profile-Guided Optimization (PGO)**

Optimize your code using runtime profiling data.

#### Steps

1. **Generate profiling data**:

   ```bash
   clang -fprofile-instr-generate your_program.c -o your_program
   LLVM_PROFILE_FILE="pgo.profraw" ./your_program
   llvm-profdata merge -output=pgo.profdata pgo.profraw
   ```

2. **Recompile with PGO**:

   ```bash
   clang -fprofile-instr-use=pgo.profdata -O2 your_program.c -o your_program_optimized
   ```

---

### **5. Valgrind + Callgrind (Advanced Profiling)**

Use Valgrind's `callgrind` for detailed call-graph analysis.

1. **Compile with debug symbols**:

   ```bash
   clang -g -O0 your_program.c -o your_program
   ```

2. **Profile with `callgrind`**:

   ```bash
   valgrind --tool=callgrind ./your_program
   ```

3. **Visualize results** (with `kcachegrind`):

   ```bash
   kcachegrind callgrind.out.*
   ```

---

### Notes

- **Install Dependencies**: Ensure tools like `llvm`, `perf`, `valgrind`, or `kcachegrind` are installed.
- **Workload**: Run your program with realistic input to capture meaningful profiling data.
- **macOS Users**: Use `Instruments.app` (part of Xcode) for similar functionality.

Let me know if you need help with a specific tool!
