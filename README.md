# TVM

Repository which represents sparkVM(official implementation of Theia Virtual Machine)

# VM Opcodes
| num  | name        | args | arg types                      | arg limits                                                   | flags count | flags | description                                                  | example           | Stack [before]→[after]                            |
| ---- | ----------- | ---- | ------------------------------ | ------------------------------------------------------------ | ----------- | ----- | ------------------------------------------------------------ | ----------------- | ------------------------------------------------- |
| 0    | stop        | 0    | N/A                            | N/A                                                          | 0           | N/A   | stop execution of the program                                | stop              | * → [empty]                                       |
| 1    | bl          | 1    | offset                         | $0-2^{64}$                                                   | 0           | N/A   | goes to another instruction at branchoffset                  | bl @32            | [no change]                                       |
| 2    | swap_ref    | 2    | index, index                   | $2^{64}, 2^{64}$                                             | 0           | N/A   | swap two references. indexing starts from top of stack       | swap 1, 3         | value1,value2→value2,value1                       |
| 3    | swap        | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 0           | N/A   | swap two values on top of the stack                          | swap 32, 64       | value1,value2→value2,value1                       |
| 4    | add         | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 0           | N/A   | sum up two values on top of the stack                        | add 32, 32        | value1,value2→value1+value2                       |
| 5    | sub         | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 0           | N/A   | substract two values from top of the stack                   | sub 32, 32        | value1,value2→value1-value2                       |
| 6    | div         | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 0           | N/A   | devide two values from top of the stack                      | div 32, 32        | value1,value2→value1/value2                       |
| 7    | mul         | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 0           | N/A   | multiply two values from top of the stack                    | mul 32, 32        | value1,value2→value1*value2                       |
| 8    | mod         | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 0           | N/A   | find mod of two values on top of the stack                   | mod 32, 32        | value1,value2→value1%value2                       |
| 9    | or          | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 0           | N/A   | bitwise inclusive OR of two values on top of the stack       | or 32, 32         | value1, value2→value1\|value2                     |
| 10   | and         | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 0           | N/A   | bitwise AND of two values on top of the stack                | and 32, 32        | value1, value2→value1&value3                      |
| 11   | xor         | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 0           | N/A   | bitwise exclusive OR of two values on top of the stack       | xor 32, 32        | value1,value2→value1^value2                       |
| 12   | lshift      | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}\equiv 0 \pmod{2}$                      | 0           | N/A   | logical shift left value1 by value2                          | lshift 32, 16     | value1, value2→value1<<value2                     |
| 13   | rshift      | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}\equiv 0 \pmod{2}$                      | 0           | N/A   | logical shift right value1 by value2                         | rshift 32, 16     | value1, value2→value1>>value2                     |
| 14   | pop         | 1    | size                           | $2^{[0-8]}$                                                  | 0           | N/A   | pop value from top of the stack                              | pop 32            | value1, value2→value2                             |
| 15   | pop2        | 2    | size,size                      | $2^{[0-8]}$                                                  | 0           | N/A   | pop 2 values from top of the stack                           | pop 32, 64        | value1, value2→                                   |
| 16   | dup         | 1    | size                           | $2^{[0-8]}$                                                  | 0           | N/A   | duplicate value from top of the stack                        | dup 32            | value1 → value1, value1                           |
| 17   | vmcall      | 1    | libname                        | N/A                                                          | 0           | N/A   | loads library's bytecode to be included into project         | vmcall sha3       | [no change]                                       |
| 18   | cnst_0      | 1    | size                           | $2^{[0-8]}\equiv 0 \pmod{2}$                                 | 0           | N/A   | push int value 0 onto the stack.                             | cnst_0 32         | → 0                                               |
| 19   | cnst_1      | 1    | size                           | $2^{[0-8]}\equiv 0 \pmod{2}$                                 | 0           | N/A   | push int value 0 onto the stack.                             | cnst_0 64         | → 1                                               |
| 20   | cnst_2      | 1    | size                           | $2^{[0-8]}\equiv 0 \pmod{2}$                                 | 0           | N/A   | push int value 0 onto the stack.                             | cnst_0 128        | → 2                                               |
| 21   | cnst_3      | 1    | size                           | $2^{[0-8]}\equiv 0 \pmod{2}$                                 | 0           | N/A   | push int value 0 onto the stack.                             | cnst_0 256        | → 3                                               |
| 22   | cnst_4      | 1    | size                           | $2^{[0-8]}\equiv 0 \pmod{2}$                                 | 0           | N/A   | push int value 0 onto the stack.                             | cnst_0 16         | → 4                                               |
| 23   | astorea     | 1    | size                           | $2^{64}$                                                     | 0           | N/A   | store reference into array by array reference and index * size on top of the stack | astorea           | arrayref, index → value                           |
| 24   | aloada      | 1    | size                           | $2^{64}$                                                     | 0           | N/A   | load reference onto the stack by array reference and index * size on top of the stack | aloada            | arrayref, index → value                           |
| 25   | str         | 1    | value                          | $0-2^{64}$                                                   | 0           | N/A   | load value from register onto the stack                      | str 64            | → value                                           |
| 26   | ldr         | 1    | size                           | $2^[0-6]$                                                    | 0           | N/A   | load value from top of the stack into register               | ldr 64            | value →                                           |
| 27   | strp        | 2    | objectNameSize, objectName     | $0-2^8, [ A-Z, a-z, \textunderscore]$                        | 0           | N/A   | loads object address from  constant pool(ASM like) onto the stack | ldr 4, _arr       | → address                                         |
| 28   | cmp_eq      | 3    | size,size, offset              | $2^{[0-8]}\equiv 0 \pmod{2}, 2^{[0-8]}\equiv 0 \pmod{2}, 0-2^{64}$ | 0           | N/A   | compare two values on top of the stack if first == second. jumps to the offset if true | cmp_eq 32, 32, 2  | [no change]                                       |
| 29   | cmp_ne      | 3    | size,size, offset              | $2^{[0-8]}\equiv 0 \pmod{2}, 2^{[0-8]}\equiv 0 \pmod{2}, 0-2^{64}$ | 0           | N/A   | compare two values on top of the stack if first != second. jumps to the offset if true | cmp_ne 32, 32, -2 | [no change]                                       |
| 30   | cmp_ge      | 3    | size,size, offset              | $2^{[0-8]}\equiv 0 \pmod{2}, 2^{[0-8]}\equiv 0 \pmod{2}, 0-2^{64}$ | 0           | N/A   | compare two values on top of the stack if first >= second. jumps to the offset if true | cmp_ge 32, 32, -3 | [no change]                                       |
| 31   | cmp_le      | 3    | size,size, offset              | $2^{[0-8]}\equiv 0 \pmod{2}, 2^{[0-8]}\equiv 0 \pmod{2}, 0-2^{64}$ | 0           | N/A   | compare two values on top of the stack if first <= second. jumps to the offset if true | cmp_le 32, 32, -4 | [no change]                                       |
| 32   | cmp_gt      | 3    | size,size, offset              | $2^{[0-8]}\equiv 0 \pmod{2}, 2^{[0-8]}\equiv 0 \pmod{2}, 0-2^{64}$ | 0           | N/A   | compare two values on top of the stack if first > second. jumps to the offset if true | cmp_gt 32, 32, -5 | [no change]                                       |
| 33   | cmp_lt      | 3    | size,size, offset              | $2^{[0-8]}\equiv 0 \pmod{2}, 2^{[0-8]}\equiv 0 \pmod{2}, 0-2^{64}$ | 0           | N/A   | compare two values on top of the stack if first < second. jumps to the offset if true | cmp_lt 32, 32, 3  | [no change]                                       |
| 34   | nop         | 0    | N/A                            | N/A                                                          | 0           | N/A   | performs no operation                                        | nop               | [no change]                                       |
| 35   | call        | 2    | functionNameSize, functionName | $0-2^8, [ A-Z, a-z, \textunderscore]$                        | 0           | N/A   | calls the function                                           | call foo          | →  return_address/link_register_value/[no change] |
| 36   | ret         | 1    | size, operationOffset          | $2^{[0-8]}$, # + $<0-\infty>$                                     | 0           | N/A   | return from subroutine                                       | ret 32, #3        | [no change]                                       |
| 37   | virtualcall | 1    | VC_ID                          | $0-2^{16}$                                                   | 0           | N/A   | calls virtual system call                                    | virtualcall 0x0   | depends on non-virtual systemcall                 |

# Constant pool
| num | key-word | description                             | example             |
|-----|----------|-----------------------------------------|---------------------|
| 0   | .ascii   | a string contained in double quotes     | .ascii "Hello"      |
| 1   | .asciz   | a 0-byte terminated ascii string        | .asciz "Hello\0"    |
| 2   | .double  | Double-precision floating-point values  | .double 0.0001      |
| 3   | .float   | floating-point values                   | .float 0.0001       |
| 4   | .i1      | 1-byte integers                         | .i1 1               |
| 5   | .i2      | 2-byte integers                         | .i2 2               |
| 6   | .i4      | 4-byte integers                         | .i4 3               |
| 7   | .i8      | 8-byte integers                         | .i8 4               |
| 8   | .i16     | 16-byte integers                        | .i16 5              |
| 9   | .arr     | key-word for arrays                     | .arr: .i16 1 .i16 2 |

# Other Key-words

| num | key-word | args | arg types | description       | example    |
|-----|----------|------|-----------|-------------------|------------|
| 0   | fn       | N/A  | N/A       | function key-word | fn main(): |

# IR(intermediate representation) Examples

## № 1

```assembly
fn _main():
#1 	align 4
#3 	cnst_2 32
#4 	cnst_2 32
#5 	add 32, 32
#6 	cnst_2 32
@7: ; offset
#8 	cmp_ge 32, 32, @12
#9 	cnst_2 32
#10	add 32, 32
#11	bl @7
@12:
#5 	ret 0, 0 ; 0, 0 means nothing to be returned, second argument not important in this case
```

> C analogue of code above is:

```c
int main() {
  int c = 2 + 2;
  int d = 2;
  while(d < c) {
   	d += 2;
  }
  return 0;
}
```

## № 2

```assembly
fn _test():
#1 	align 4
#2	cnst_1 32
#3	cnst_2 32
#4	add 32, 32
#5	ret 32, #4

fn _main():
#1 	align 4
#2 	call 4, _test
#3 	ret 0, 0
	
```

>  C analogue of code above is:

```c
int test() {
	return 1 + 2;
}
int main() {
	int a = test();
	return 0;
}
```

