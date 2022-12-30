import pdb
import lib601.sm as sm
import string
import operator

class Tokenizer(sm.SM):
    def __init__(self):
        self.inputs = ''
        self.inp = ''
        self.out = ''
        self.out_temp = ''
        self.Out_List = []
        self.state = ''
        self.last_state = 'Start'
        self.cnt = 0

    def transduce(self, strs=''):
        self.inputs = strs
        while self.cnt < len(self.inputs):
            if self.cnt == 0:
                self.inp = self.inputs[self.cnt]
            else:
                self.out = self.inp
                self.inp = self.inputs[self.cnt]
            self.get_next_value()
            if self.last_state == 'Start':
                self.Out_List.append('')
            elif self.last_state == 'Go':
                if self.out != ' ':
                    self.Out_List.append(self.out)
                else:
                    self.Out_List.append('')
            elif self.last_state == 'Wait':
                self.out_temp += self.out
                if self.state == 'Wait':
                    self.Out_List.append('')
                else:
                    self.Out_List.append(self.out_temp)
                    self.out_temp = ''
            elif self.last_state == 'Stop_Wait':
                if self.out != ' ':
                    self.Out_List.append(self.out)
                else:
                    self.Out_List.append('')
            self.last_state = self.state
            self.cnt += 1
        print self.Out_List

    def get_next_value(self):
       if self.inp in ['(',')','+','-','*','/','=',' ']:
           if self.last_state == 'Wait':
               self.state = 'Stop_Wait'
           else:
               self.state = 'Go'
       else:
           self.state = 'Wait'

class stack(object):
    def __init__(self):
        self.items = []
    def is_empty(self):
        return len(self.items) == 0
    def push(self,item):
        self.items.append(item)
    def pop(self):
        return self.items.pop()
    def peek(self):
        return self.items[len(self.items) - 1]
    def size(self):
        return len(self.items)
    
class BinaryTree(object):
    def __init__(self, root_obj):
        self.key = root_obj
        self.left_child = None
        self.right_child = None

    def insert_left(self, new_node):
        self.left_child = BinaryTree(new_node)

    def insert_right(self, new_node):
        self.right_child = BinaryTree(new_node)

    def get_left_child(self):
        return self.left_child

    def get_right_child(self):
        return self.right_child

    def get_root_val(self):
        return self.key

    def set_root_val(self, obj):
        self.key = obj

class BinaryOp:
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __str__(self):
        return self.opStr + '(' + \
               str(self.left) + ', ' +\
               str(self.right) + ')'
    __repr__ = __str__

class Sum(BinaryOp):
    opStr = 'Sum'
    def evals(self,env = {}):
        return (self.left + self.right) * 1.0
    def eval(self,env = {}):
        return (self.left.eval(env) + self.right.eval(env)) * 1.0
class Prod(BinaryOp):
    opStr = 'Prod'
    def evals(self,env = {}):
        return (self.left * self.right) * 1.0
    def eval(self,env = {}):
        return (self.left.eval(env) * self.right.eval(env)) * 1.0
class Quot(BinaryOp):
    opStr = 'Quot'
    def evals(self,env = {}):
        return (self.left / self.right) * 1.0
    def eval(self,env = {}):
        return (self.left.eval(env) / self.right.eval(env)) * 1.0
class Diff(BinaryOp):
    opStr = 'Diff'
    def evals(self,env = {}):
        return (self.left - self.right) * 1.0
    def eval(self,env = {}):
        return (self.left.eval(env) - self.right.eval(env)) * 1.0
class Assign(BinaryOp):
    opStr = 'Assign'
    def evals(self,env = {}):
        env[self.left] = self.right * 1.0     
    def eval(self,env = {}):
        env[(self.left).name] = self.right.eval(env) * 1.0        
class Number:
    def __init__(self, val):
        self.value = val
    def __str__(self):
        return 'Num('+str(self.value)+')'
    __repr__ = __str__
    def eval(self,env = {}):
        return self.value
class Variable:
    def __init__(self, name):
        self.name = name
    def __str__(self):
        return 'Var('+self.name+')'
    __repr__ = __str__
    def eval(self,env = {}):
        if env.get(self.name):
             return env[self.name]
        else:
            env[self.name] = 0
# characters that are single-character tokens
seps = ['(', ')', '+', '-', '*', '/', '=']

# Convert strings into a list of tokens (strings)
def tokenize(strings):
    strings_list = []
    temp_string = ''
    i = 0
    while i < len(strings):
        strings_list = []
        temp_string = ''
        i = 0
        while i < len(strings):
            if strings[i] in ['+','-','*','=','(',')','/']:
                strings_list.append(strings[i])
                i += 1
            elif strings[i] == ' ':
                i += 1
            else:
                temp_string = ''
                while True:
                    if strings[i] in [' ',')','=','+','-','*','/']:
                        break
                    else:
                        temp_string += strings[i]
                        i += 1
                strings_list.append(temp_string)
    return strings_list
# tokens is a list of tokens
# returns a syntax tree:  an instance of {\tt Number}, {\tt Variable},
# or one of the subclasses of {\tt BinaryOp} 
def parse(tokens):
    myOp = {
        '+':Sum,
        '-':Diff,
        '*':Prod,
        '/':Quot,
        '=':Assign
    }
    def parseExp(index):
        if '0' <= tokens[index] <= '9':
            return (Number(float(tokens[index])),index+1)
        elif 'a' <= tokens[index] <= 'z' or 'A' <= tokens[index] <= 'Z':
            return (Variable(tokens[index]), index + 1)
        elif tokens[index] == '(':
            flag = 0
            for i in range(index,len(tokens)):
                if tokens[i] == '(':
                    flag +=1
                elif tokens[i] == ')':
                    flag -=1
                elif tokens[i] in ['+','-','*','/','='] and flag == 1:
                    fn = myOp[tokens[i]]
                    return (fn(parse(tokens[1:i]), parse(tokens[i + 1:len(tokens) - 1])), len(tokens))
    (parseExp, nextIndex) = parseExp(0)
    return parseExp

env = {}
variable_alpha_None_flag = 0
def build_parse_tree(fpexp):
    global env
    global variable_alpha_None_flag
    flag = 0
    p_stack = stack()
    e_tree = BinaryTree('')
    p_stack.push(e_tree)
    current_tree = e_tree
    for i in fpexp:
        if i == '(':
            current_tree.insert_left(i)
            p_stack.push(current_tree)
            current_tree = current_tree.get_left_child()
        elif '0' <= i <= '9':
            current_tree.set_root_val((int(i)))
            parent = p_stack.pop()
            current_tree = parent
        elif i in ['+', '-', '*', '/', '=']:
            if i == '=':
                flag = 1
            current_tree.set_root_val(i)
            current_tree.insert_right('')
            p_stack.push(current_tree)
            current_tree = current_tree.get_right_child()
        elif i == ')':
            current_tree = p_stack.pop()
        elif i == ' ':
            pass
        else:
            if env.get(i) and flag == 1:
                current_tree.set_root_val(env[i])
            elif env.get(i) and flag == 0:
                current_tree.set_root_val(i)
            else:
                variable_alpha_None_flag = 1
                env.update({i: 0})
                current_tree.set_root_val(i)
            parent = p_stack.pop()
            current_tree = parent
    return e_tree

def Calc_Tree(parse_tree):
    global env
    opers = {
                '+': Sum,
                '-': Diff,
                '*': Prod,
                '/': Quot,
                '=': Assign
            }
    left_child = parse_tree.get_left_child()
    right_child = parse_tree.get_right_child()
    if left_child and right_child:
        fn = opers[parse_tree.get_root_val()]
        return fn(Calc_Tree(left_child), Calc_Tree(right_child)).evals(env)
    else:
        return parse_tree.get_root_val()

# Run calculator interactively
def calc(record_input):
    global env
    global variable_alpha_None_flag
    if '=' in record_input:
        record_input = tokenize(record_input)
        tree = build_parse_tree(record_input)
        variable_alpha_value = Calc_Tree(tree)
        if variable_alpha_None_flag:
            variable_alpha_None_flag = 0
            print 'None\n\tenv = ', env
        else:
            print variable_alpha_value, '\n\tenv = ', env
    else:
        if '(' in record_input:
            record_input = tokenize(record_input)
            tree = build_parse_tree(record_input)
            variable_alpha_value = Calc_Tree(tree)
            print variable_alpha_value, '\n\tenv = ', env 
        else:
            variable_alpha = record_input
            print env[variable_alpha],'\n\tenv = ',env

# exprs is a list of strings
# runs calculator on those strings, in sequence, using the same environment
def calcTest(exprs):
    env = {}
    for e in exprs:
        print '%', e                    # e is the experession 
        calc(e)

# Simple tokenizer tests
'''Answers are:
['fred']
['777']
['777', 'hi', '33']
['*', '*', '-', ')', '(']
['(', 'hi', '*', 'ho', ')']
['(', 'fred', '+', 'george', ')']
['(', 'hi', '*', 'ho', ')']
['(', 'fred', '+', 'george', ')']
'''
def testTokenize():
    env = {}
    print tokenize('fred ')
    print tokenize('777 ')
    print tokenize('777 hi 33 ')
    print tokenize('**-)(')
    print tokenize('( hi * ho )')
    print tokenize('(fred + george)')
    print tokenize('(hi*ho)')
    print tokenize('( fred+george )')


# Simple parsing tests from the handout
'''Answers are:
Var(a)
Num(888.0)
Sum(Var(fred), Var(george))
Quot(Prod(Var(a), Var(b)), Diff(Var(cee), Var(doh)))
Quot(Prod(Var(a), Var(b)), Diff(Var(cee), Var(doh)))
Assign(Var(a), Prod(Num(3.0), Num(5.0)))
'''
def testParse():
    env = {}
    print parse(['a'])
    print parse(['888'])
    print parse(['(', 'fred', '+', 'george', ')'])
    print parse(['(', '(', 'a', '*', 'b', ')', '/', '(', 'cee', '-', 'doh', ')' ,')'])
    print parse(tokenize('((a * b) / (cee - doh))'))
    print parse(tokenize('(a = (3 * 5))'))

####################################################################
# Test cases for EAGER evaluator
####################################################################

def testEval():
    env = {}
    Assign(Variable('a'), Number(5.0)).eval(env)
    print Variable('a').eval(env)
    env['b'] = 2.0
    print Variable('b').eval(env)
    env['c'] = 4.0
    print Variable('c').eval(env)
    print Sum(Variable('a'), Variable('b')).eval(env)
    print Sum(Diff(Variable('a'), Variable('c')), Variable('b')).eval(env)
    Assign(Variable('a'), Sum(Variable('a'), Variable('b'))).eval(env)
    print Variable('a').eval(env)
    print env

# Basic calculator test cases (see handout)
testExprs = ['(2 + 5)',
             '(z = 6)',
             'z',
             '(w = (z + 1))',
             'w'
             ]
test = ['fred ','777 ','777 hi 33 ','**-)( ','(hi*ho) ','(fred + george) ']
def testState(test=[]):
    for e in test:
        print 'Tokenizer().transduce(' + str('')  + e + str('')+' )'
        Tokenizer().transduce(e)


print "*******************************"
print '¼ÆËãÆ÷²âÊÔ\n'
print "*******************************"
calcTest(testExprs)
print "*******************************"
print 'Tokenize²âÊÔ\n'
print "*******************************"
testTokenize()
print "*******************************"
print 'Parse²âÊÔ\n'
print "*******************************"
testParse()
print "*******************************"
print 'Eval²âÊÔ\n'
print "*******************************"
testEval()
print "*******************************"
print 'State²âÊÔ\n'
print "*******************************"
testState(test)
print "*******************************"
