#pragma once

#include <cpp/string.hpp>
#include <cpp/vector.hpp>

typedef int32_t INTEGER;
typedef bool LOGICAL;
typedef double REAL;

static const size_t PROGRAM_COUNTER_EXIT = ~((size_t)0);

enum DataType
{
    Integer,
    Logical,
    Real,
};

class Variable
{
public:
    string Name; // symbol name representing the variable
    DataType Type; // data type of the variable
    size_t Scope; // scope depth at which this variable was declared
    void* Pointer; // pointer to the value of the variable

    void declare(const string& name, const DataType type, const size_t scope);
    void dispose(void);

    INTEGER getInteger(void) const;
    LOGICAL getLogical(void) const;
    REAL getReal(void) const;

    void set(const INTEGER value);
    void set(const LOGICAL value);
    void set(const REAL value);
};

class Program
{
public:
    // progRun
    void run(const char* const codePtr);

private:
    vector<vector<string>> m_program; // lines of code
    vector<Variable> m_variables; // vector of all currently declared variables

    size_t m_counter; // program counter
    size_t m_scope; // current scope depth
    vector<size_t> m_scopeStack; // contains indexes at which the program pushed the scope (used by while loop)

    // progCmdExe
    void executeCommand(void); // executes the command at the current line

    // progVar
    bool varDeclare(const string& name, const DataType type); // declares a new variable with a specified name and data type
    Variable* varFind(const string& name); // finds a variable by name and returns a pointer to it, returns nullptr on failure
    INTEGER* varGetIntegerPtr(const string& varName); // returns an integer value pointer
    LOGICAL* varGetLogicalPtr(const string& varName); // returns a logical value pointer
    REAL* varGetRealPtr(const string& varName); // returns a real value pointer
    bool nameValid(const string& name); // check if the variable name is valid (contains only valid characters and isn't a keyword)

    // progError
    void error(const char* const str); // prints an error message and exits the program
    void error(const string& str); // overload of error() to make it easier to use string objects
    void errorVarUndeclared(const string& name); // "variable hasn't been declared" error
    void errorSymbolUnresolved(const string& name); // "unable to resolve symbol" error
    void errorTypesIncompatible(void); // "variables don't have matching data types" error
    void errorOperatorInvalid(const string& strOperator); // "symbol is not a valid operator" error
    void errorDivisionByZero(void); // "cannot divide by zero" error

    // progExpression
    bool symbolToInteger(const string& strSymbol, INTEGER* const output, const bool throwError = true);
    bool symbolToLogical(const string& strSymbol, LOGICAL* const output, const bool throwError = true);
    bool symbolToReal(const string& strSymbol, REAL* const output, const bool throwError = true);

    bool evaluateInteger(const string& strSymbol1, const string& strOperator, const string& strSymbol2, INTEGER* const output);
    bool evaluateLogical(const string& strSymbol1, const string& strOperator, const string& strSymbol2, LOGICAL* const output);
    bool evaluateReal(const string& strSymbol1, const string& strOperator, const string& strSymbol2, REAL* const output);

    bool realSqrt(const string& strSourceSymbol, Variable* const outputVariable);
    bool convertToInteger(const string& strSourceSymbol, Variable* const outputVariable);
    bool convertToLogical(const string& strSourceSymbol, Variable* const outputVariable);
    bool convertToReal(const string& strSourceSymbol, Variable* const outputVariable);

    // progScope
    void scopePush(void); // pushes current program counter onto the scope stack and incremenets the scope level
    void scopePop(void); // decrements the scope level and disposes all variables that were declared in that scope

    size_t findEnd(void);
    size_t findElse(void);

    void elseLoop(void);
    bool breakScope(const size_t levelsToBreak, const bool breakLast);
};
