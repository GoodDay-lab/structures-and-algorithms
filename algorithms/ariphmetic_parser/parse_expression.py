"""
(C) Pavel Vasilev
"""

class Token:
    tok_binop = -1
    tok_number = -2
    tok_identifier = -3
    tok_eof = -4

BinOpPrecedence = {}

"""
Здесь вы можете настроить очерёдность операций
Чем выше значение, тем раньше эта операция будет выполнена!

Попробуем альтернативную арифметику :)
"""
BinOpPrecedence['+'] = 1
BinOpPrecedence['-'] = 1
BinOpPrecedence['*'] = 2
BinOpPrecedence['/'] = 2
BinOpPrecedence['^'] = 3

SymbolTable = {}


def gettok(string):
    value = ''
    i = 0
    while i < len(string):
        char = string[i]
        if char == ' ':
            i += 1
            continue
            
        if char.isdigit():
            value = 0
            while i < len(string) and string[i].isdigit():
                value *= 10
                value += int(string[i])
                i += 1
            yield (Token.tok_number, value)
        elif char.isalpha():
            value = ''
            while i < len(string) and (string[i].isalpha() or string[i].isdigit()):
                value += string[i]
                i += 1
            SymbolTable[value] = None
            yield (Token.tok_identifier, value)
        elif char in '+-/*()^':
            i += 1
            yield (Token.tok_binop, char)
    while True: 
        yield (Token.tok_eof, None)


def parse_expression2(analyzer, prec=max(BinOpPrecedence.values())):
    """
    Uses onlu "+-*/()" operations
    """
    token, primary = next(analyzer)
    if (token == Token.tok_eof):
        return 0
    
    lhs = primary if not (primary == "(") \
                  else parse_expression2(analyzer, prec)
    last_prec = prec
    
    while True:
        op_token, binop = next(analyzer)
        if op_token == Token.tok_eof or binop == ")":
            return lhs
        op_prec = BinOpPrecedence[binop]
        
        if last_prec > op_prec:
            rhs = parse_expression2(analyzer, op_prec)
        else:
            token, rhs = next(analyzer)
            if token == Token.tok_binop and rhs == "(":
                rhs = parse_expression2(analyzer, prec)
        last_prec = op_prec
        lhs = {"op": binop, "lhs": lhs, "rhs": rhs}


def compute(root):
    if type(root) == dict:
        match (root["op"]):
            case ("+"): return compute(root["lhs"]) + compute(root["rhs"])
            case ("-"): return compute(root["lhs"]) - compute(root["rhs"])
            case ("*"): return compute(root["lhs"]) * compute(root["rhs"])
            case ("/"): return compute(root["lhs"]) / compute(root["rhs"])
            case ("^"): return compute(root["lhs"]) ** compute(root["rhs"])
    elif type(root) == str:
        return float(SymbolTable[root])
    else:
        return root
        
        
        
# Example:
#
# 23+23/23+23*23
#

string = input("Введите арифметическое выражение: ")
root = parse_expression2(gettok(string))

for key in SymbolTable:
    SymbolTable[key] = int(input("Введите число  '%s' = " % (key)))

print("Дерево выражения: %s" % str(root))
print("Результат работы алгоритма: %f" % compute(root))
print("Результат работы встроенной функции 'eval()': %f" % eval(string.replace("^", "**")))

