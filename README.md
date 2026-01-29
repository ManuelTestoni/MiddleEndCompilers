# Middle-End Compiler Optimizations

This repository contains a comprehensive collection of **LLVM-based compiler optimizations** and **dataflow analysis implementations** developed as part of the Compilers course at the University of Modena and Reggio Emilia.

## 📋 Project Overview

The project demonstrates advanced compiler techniques through four main assignments and supporting laboratory activities, all implemented using LLVM 18+ infrastructure. Each component includes detailed documentation, test cases, and course materials.

## 🎯 Assignments

### Assignment 1: Algebraic Optimizations
Implementation of algebraic simplification passes for LLVM IR.

**Key Features:**
- **Algebraic Identity**: Simplification of operations with identity elements (e.g., `x + 0 → x`, `x * 1 → x`)
- **Strength Reduction**: Replacement of expensive operations with cheaper equivalents (e.g., `x * 2 → x << 1`)

**Location:** [`Assignment/Compilatori-24-25/assignement-1/`](Assignment/Compilatori-24-25/assignement-1/)

**Test Cases:** Multiple LLVM IR examples including Fibonacci, loop structures, and optimization benchmarks

---

### Assignment 2: Dataflow Analysis Frameworks
Theoretical analysis and documentation of three fundamental dataflow analysis frameworks.

**Frameworks Covered:**
1. **Very Busy Expression Analysis**: Forward analysis to identify expressions that will be used on all paths
2. **Dominator Analysis**: Computing dominator relationships in the Control Flow Graph (CFG)
3. **Constant Propagation**: Tracking variables with constant values throughout program execution

**Documentation Includes:**
- Analysis domain and direction
- Transfer functions
- Meet operators
- Boundary and initial conditions

**Location:** [`Assignment/Compilatori-24-25/assignement-2/`](Assignment/Compilatori-24-25/assignement-2/)

---

### Assignment 3: Loop Invariant Code Motion (LICM)
Advanced loop optimization pass that identifies and hoists loop-invariant computations.

**Implementation Phases:**
1. **Invariant Detection**: Identifies instructions whose results don't change across iterations
2. **Safety Analysis**: Verifies dominance conditions for safe code motion
3. **Code Motion**: Moves invariant instructions to the loop preheader

**Optimization Benefits:**
- Reduced instruction execution count
- Improved runtime performance
- Enhanced code readability

**Location:** [`Assignment/Compilatori-24-25/assignement-3/`](Assignment/Compilatori-24-25/assignement-3/)

**Test Cases:** Multiple loop examples demonstrating various invariant patterns

---

### Assignment 4: Loop Fusion
Sophisticated optimization that merges adjacent loops to improve cache locality and reduce loop overhead.

**Implementation Features:**
- **Adjacency Analysis**: Verifies physical adjacency in the CFG
- **Control Flow Equivalence**: Ensures loops have identical structure
- **Dependence Analysis**: Checks for negative dependencies using LLVM's DependenceAnalysis
- **Safe Fusion**: Merges loops while preserving program semantics

**Key Analyses:**
- Loop adjacency verification
- CFG structure comparison
- Memory dependence checking
- Scalar Evolution integration

**Location:** [`Assignment/Compilatori-24-25/assignement-4/`](Assignment/Compilatori-24-25/assignement-4/)

**Test Cases:** Various loop patterns including guarded loops, iteration-dependent computations, and fusion candidates

---

## 🔬 Laboratory Activities

### Lab 2: Local Optimizations
Exploration of LLVM IR structure and basic pass development.

**Topics:**
- LLVM IR navigation
- Instruction and operand manipulation
- Basic block analysis
- Module-level passes

**Location:** [`Lab2/`](Lab2/)

---

### Lab 3: Loop Analysis
Deep dive into LLVM's loop analysis infrastructure.

**Topics:**
- LoopInfo analysis
- Loop detection and hierarchy
- Preheader and exit block identification
- Loop optimization foundations

**Location:** [`Lab3/`](Lab3/)

---

## 🛠️ Prerequisites

- **LLVM**: Version 18 or higher
- **Clang**: Compatible with LLVM version
- **CMake**: Version 3.13 or higher
- **C++ Compiler**: Supporting C++17 standard
- **Operating System**: Linux, macOS, or Windows with appropriate LLVM setup

## 🚀 Building and Running

### General Build Process

```bash
# Navigate to assignment directory
cd Assignment/Compilatori-24-25/assignement-X/

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake -DLT_LLVM_INSTALL_DIR=$LLVM_DIR ..

# Build the pass
make
```

### Running Optimizations

```bash
# Generate LLVM IR from source
clang -S -emit-llvm program.c -o program.ll

# Apply optimization pass
opt -load-pass-plugin=../build/libPass.so -passes="pass-name" program.ll -o optimized.ll

# On macOS (Apple Silicon)
opt -load-pass-plugin=../build/libPass.dylib -passes="pass-name" program.ll -o optimized.ll
```

### Viewing Results

```bash
# Compare original and optimized code
diff program.ll optimized.ll

# Visualize CFG
opt -dot-cfg program.ll
```

## 📁 Repository Structure

```
MiddleEndCompilers/
├── Assignment/
│   └── Compilatori-24-25/
│       ├── assignement-1/          # Algebraic Optimizations
│       ├── assignement-2/          # Dataflow Analysis
│       ├── assignement-3/          # Loop Invariant Code Motion
│       └── assignement-4/          # Loop Fusion
├── Lab2/                           # Local Optimizations Lab
├── Lab3/                           # Loop Analysis Lab
└── Laboratori_Compilatori/         # Additional Lab Materials
```

## 📚 Learning Outcomes

Through these assignments and labs, the following compiler concepts are explored:

- **Code Optimization**: Algebraic simplifications, strength reduction, loop optimizations
- **Program Analysis**: Dataflow analysis, dominance analysis, dependence analysis
- **LLVM Infrastructure**: Pass development, IR manipulation, analysis framework usage
- **Performance Engineering**: Understanding optimization trade-offs and effectiveness

## 🎓 Academic Context

**Course**: Linguaggi e Compilatori (Languages and Compilers)  
**University**: Università degli Studi di Modena e Reggio Emilia  
**Academic Year**: 2024-2025  
**Focus**: Back-end and Middle-end Compiler Optimizations

## 📖 Documentation

Each assignment directory contains:
- **README.md**: Detailed implementation guide
- **Examples/**: Test cases and sample programs
- **Slides**: Course materials describing the optimization techniques
- **Source Code**: Fully commented C++ implementations

## 🔍 Key Technologies

- **LLVM**: Industry-standard compiler infrastructure
- **Static Single Assignment (SSA)**: Intermediate representation form
- **Control Flow Graph (CFG)**: Program structure representation
- **Scalar Evolution**: Mathematical expression analysis
- **Dependence Analysis**: Memory access pattern analysis

## 🤝 Team

This project was developed collaboratively as part of the Compilers course curriculum.

## 📄 License

This project is developed for educational purposes as part of university coursework.

## 📞 Support

For questions or issues:
- Review individual assignment READMEs for specific guidance
- Consult LLVM documentation: https://llvm.org/docs/
- Reference course materials included in assignment directories

---

**Note**: This repository demonstrates practical applications of compiler optimization theory, providing hands-on experience with industry-standard tools and techniques used in modern compiler development.
