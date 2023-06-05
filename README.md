# TVM

Repository which represents sparkVM(official implementation of Theia Virtual Machine)

# VM Opcodes
| num  | name          | args | arg types                      | arg limits                                                   | args{.cond} | arg types{.cond}                       | arg limits{.cond}                                | flags available | flags | description                                                  | description for usage with flags                             | example           | example with flags   | Stack [before]→[after]                           |
| ---- | ------------- | ---- | ------------------------------ | ------------------------------------------------------------ | ----------- | -------------------------------------- | ------------------------------------------------ | --------------- | ----- | ------------------------------------------------------------ | ------------------------------------------------------------ | ----------------- | -------------------- | ------------------------------------------------ |
| 0    | stop          | 0    | N/A                            | N/A                                                          | N/A         | N/A                                    | N/A                                              | 0               | N/A   | stop execution of the program                                | N/A                                                          | stop              | N/A                  | * → [empty]                                      |
| 1    | bl            | 1    | offset                         | @ + $0-2^{64}$                                               | N/A         | N/A                                    | N/A                                              | 0               | N/A   | goes to another instruction at branchoffset                  | N/A                                                          | bl @32            | N/A                  | [no change]                                      |
| 2    | swap_ref      | 2    | index, index                   | $0-2^{64}$                                                   | N/A         | N/A                                    | N/A                                              | 0               | N/A   | swap two references. indexing starts from top of stack       | N/A                                                          | swap 1, 3         | N/A                  | value1,value2→value2,value1                      |
| 3    | swap          | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | N/A         | N/A                                    | N/A                                              | 0               | N/A   | swap two values on top of the stack                          | N/A                                                          | swap 32, 64       | N/A                  | value1,value2→value2,value1                      |
| 4    | add{.cond}    | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 2           | operationOffset,operationOffset        | # + $<0-\infty>$,# + $<0-\infty>$                | 1               | v     | sum up two values on top of the stack                        | sum up two values by operationOffset                         | add 32, 32        | add.v #2, #3         | value1,value2→value1+value2                      |
| 5    | sub{.cond}    | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 2           | operationOffset,operationOffset        | # + $<0-\infty>$,# + $<0-\infty>$                | 1               | v     | substract two values from top of the stack                   | substract two values by operationOffset                      | sub 32, 32        | sub.v #2, #4         | value1,value2→value1-value2                      |
| 6    | div{.cond}    | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 2           | operationOffset,operationOffset        | # + $<0-\infty>$,# + $<0-\infty>$                | 1               | v     | devide two values from top of the stack                      | devide two values by operationOffset                         | div 32, 32        | div.v #2, #5         | value1,value2→value1/value2                      |
| 7    | mul{.cond}    | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 2           | operationOffset,operationOffset        | # + $<0-\infty>$,# + $<0-\infty>$                | 1               | v     | multiply two values from top of the stack                    | multiply two values by operationOffset                       | mul 32, 32        | mul.v #2, #6         | value1,value2→value1*value2                      |
| 8    | mod{.cond}    | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 2           | operationOffset,operationOffset        | # + $<0-\infty>$,# + $<0-\infty>$                | 1               | v     | find mod of two values on top of the stack                   | find mod of two values by operationOffset                    | mod 32, 32        | mod.v #2, #7         | value1,value2→value1%value2                      |
| 9    | or{.cond}     | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 2           | operationOffset,operationOffset        | # + $<0-\infty>$,# + $<0-\infty>$                | 1               | v     | bitwise inclusive OR of two values on top of the stack       | bitwise inclusive OR of two values by operationOffset        | or 32, 32         | or.v #2, #8          | value1, value2→value1\|value2                    |
| 10   | and{.cond}    | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 2           | operationOffset,operationOffset        | # + $<0-\infty>$,# + $<0-\infty>$                | 1               | v     | bitwise AND of two values on top of the stack                | bitwise AND of two values by operationOffset                 | and 32, 32        | and.v #2, #9         | value1, value2→value1&value3                     |
| 11   | xor{.cond}    | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}$                                       | 2           | operationOffset,operationOffset        | # + $<0-\infty>$,# + $<0-\infty>$                | 1               | v     | bitwise exclusive OR of two values on top of the stack       | bitwise exclusive OR of two values by operationOffset        | xor 32, 32        | xor.v #2, #10        | value1,value2→value1^value2                      |
| 12   | lshift{.cond} | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}\equiv 0 \pmod{2}$                      | 2           | operationOffset,operationOffset        | # + $<0-\infty>$,# + $<0-\infty>$                | 1               | v     | logical shift left value1 by value2                          | logical shift left value1 by value2 by operationOffset       | lshift 32, 16     | lshift.v #2, #11     | value1, value2→value1<<value2                    |
| 13   | rshift{.cond} | 2    | size, size                     | $2^{[0-8]}, 2^{[0-8]}\equiv 0 \pmod{2}$                      | 2           | operationOffset,operationOffset        | # + $<0-\infty>$,# + $<0-\infty>$                | 1               | v     | logical shift right value1 by value2                         | logical shift right value1 by value2 by operationOffset      | rshift 32, 16     | rshift.v #2, #12     | value1, value2→value1>>value2                    |
| 14   | pop           | 1    | size                           | $2^{[0-8]}$                                                  | N/A         | N/A                                    | N/A                                              | 0               | N/A   | pop value from top of the stack                              | N/A                                                          | pop 32            | N/A                  | value1, value2→value2                            |
| 15   | pop2          | 2    | size,size                      | $2^{[0-8]}$                                                  | N/A         | N/A                                    | N/A                                              | 0               | N/A   | pop 2 values from top of the stack                           | N/A                                                          | pop 32, 64        | N/A                  | value1, value2→                                  |
| 16   | dup           | 1    | size                           | $2^{[0-8]}$                                                  | N/A         | N/A                                    | N/A                                              | 0               | N/A   | duplicate value from top of the stack                        | N/A                                                          | dup 32            | N/A                  | value1 → value1, value1                          |
| 17   | libcall       | 1    | libname                        | N/A                                                          | N/A         | N/A                                    | N/A                                              | 0               | N/A   | loads library's bytecode to be included into project         | N/A                                                          | vmcall sha3       | N/A                  | [no change]                                      |
| 18   | cnst_0        | 1    | size                           | $2^{[0-8]}\equiv 0 \pmod{2}$                                 | N/A         | N/A                                    | N/A                                              | 0               | N/A   | push int value 0 onto the stack.                             | N/A                                                          | cnst_0 32         | N/A                  | → 0                                              |
| 19   | cnst_1        | 1    | size                           | $2^{[0-8]}\equiv 0 \pmod{2}$                                 | N/A         | N/A                                    | N/A                                              | 0               | N/A   | push int value 0 onto the stack.                             | N/A                                                          | cnst_0 64         | N/A                  | → 1                                              |
| 20   | cnst_2        | 1    | size                           | $2^{[0-8]}\equiv 0 \pmod{2}$                                 | N/A         | N/A                                    | N/A                                              | 0               | N/A   | push int value 0 onto the stack.                             | N/A                                                          | cnst_0 128        | N/A                  | → 2                                              |
| 21   | cnst_3        | 1    | size                           | $2^{[0-8]}\equiv 0 \pmod{2}$                                 | N/A         | N/A                                    | N/A                                              | 0               | N/A   | push int value 0 onto the stack.                             | N/A                                                          | cnst_0 256        | N/A                  | → 3                                              |
| 22   | cnst_4        | 1    | size                           | $2^{[0-8]}\equiv 0 \pmod{2}$                                 | N/A         | N/A                                    | N/A                                              | 0               | N/A   | push int value 0 onto the stack.                             | N/A                                                          | cnst_0 16         | N/A                  | → 4                                              |
| 23   | astorea       | 1    | size                           | $2^{64}$                                                     | N/A         | N/A                                    | N/A                                              | 0               | N/A   | store reference into array by array reference and index * size on top of the stack | N/A                                                          | astorea           | N/A                  | arrayref, index → value                          |
| 24   | aloada        | 1    | size                           | $2^{64}$                                                     | N/A         | N/A                                    | N/A                                              | 0               | N/A   | load reference onto the stack by array reference and index * size on top of the stack | N/A                                                          | aloada            | N/A                  | arrayref, index → value                          |
| 25   | str           | 1    | value                          | $0-2^{64}$                                                   | N/A         | N/A                                    | N/A                                              | 0               | N/A   | load value from register onto the stack                      | N/A                                                          | str 64            | N/A                  | → value                                          |
| 26   | ldr           | 1    | size                           | $2^[0-6]$                                                    | N/A         | N/A                                    | N/A                                              | 0               | N/A   | load value from top of the stack into register               | N/A                                                          | ldr 64            | N/A                  | value →                                          |
| 27   | strp          | 2    | objectNameSize, objectName     | $0-2^8, [ A-Z, ., a-z, \textunderscore]$                     | 3           | operationOffset,operationOffset,offset | # + $<0-\infty>$,# + $<0-\infty>$,@ + $0-2^{64}$ | 0               | N/A   | loads object address from constant pool(ASM like) on top of the stack | N/A                                                          | ldr 4, _arr       | N/A                  | → address                                        |
| 28   | cmp_eq{.cond} | 3    | size,size, offset              | $2^{[0-8]}\equiv 0 \pmod{2}, 2^{[0-8]}\equiv 0 \pmod{2}, 0-2^{64}$ | 3           | operationOffset,operationOffset,offset | # + $<0-\infty>$,# + $<0-\infty>$,@ + $0-2^{64}$ | 1               | v     | compare two values on top of the stack if first == second. jumps to the offset if true | compare two values by operationOffset if first == second. jumps to the offset if true | cmp_eq 32, 32, 2  | cmp_eq.v #2, #3, @7  | [no change]                                      |
| 29   | cmp_ne{.cond} | 3    | size,size, offset              | $2^{[0-8]}\equiv 0 \pmod{2}, 2^{[0-8]}\equiv 0 \pmod{2}, 0-2^{64}$ | 3           | operationOffset,operationOffset,offset | # + $<0-\infty>$,# + $<0-\infty>$,@ + $0-2^{64}$ | 1               | v     | compare two values on top of the stack if first != second. jumps to the offset if true | compare two values by operationOffset if first != second. jumps to the offset if true | cmp_ne 32, 32, -2 | cmp_eq.v #2, #3, @8  | [no change]                                      |
| 30   | cmp_ge{.cond} | 3    | size,size, offset              | $2^{[0-8]}\equiv 0 \pmod{2}, 2^{[0-8]}\equiv 0 \pmod{2}, 0-2^{64}$ | 3           | operationOffset,operationOffset,offset | # + $<0-\infty>$,# + $<0-\infty>$,@ + $0-2^{64}$ | 1               | v     | compare two values on top of the stack if first >= second. jumps to the offset if true | compare two values by operationOffset if first >= second. jumps to the offset if true | cmp_ge 32, 32, -3 | cmp_eq.v #2, #3, @9  | [no change]                                      |
| 31   | cmp_le{.cond} | 3    | size,size, offset              | $2^{[0-8]}\equiv 0 \pmod{2}, 2^{[0-8]}\equiv 0 \pmod{2}, 0-2^{64}$ | 3           | operationOffset,operationOffset,offset | # + $<0-\infty>$,# + $<0-\infty>$,@ + $0-2^{64}$ | 1               | v     | compare two values on top of the stack if first <= second. jumps to the offset if true | compare two values by operationOffset if first <= second. jumps to the offset if true | cmp_le 32, 32, -4 | cmp_eq.v #2, #3, @10 | [no change]                                      |
| 32   | cmp_gt{.cond} | 3    | size,size, offset              | $2^{[0-8]}\equiv 0 \pmod{2}, 2^{[0-8]}\equiv 0 \pmod{2}, 0-2^{64}$ | 3           | operationOffset,operationOffset,offset | # + $<0-\infty>$,# + $<0-\infty>$,@ + $0-2^{64}$ | 1               | v     | compare two values on top of the stack if first > second. jumps to the offset if true | compare two values by operationOffset if first > second. jumps to the offset if true | cmp_gt 32, 32, -5 | cmp_eq.v #2, #3, @11 | [no change]                                      |
| 33   | cmp_lt{.cond} | 3    | size,size, offset              | $2^{[0-8]}\equiv 0 \pmod{2}, 2^{[0-8]}\equiv 0 \pmod{2}, 0-2^{64}$ | 3           | operationOffset,operationOffset,offset | # + $<0-\infty>$,# + $<0-\infty>$,@ + $0-2^{64}$ | 1               | v     | compare two values on top of the stack if first < second. jumps to the offset if true | compare two values by operationOffset if first < second. jumps to the offset if true | cmp_lt 32, 32, 3  | cmp_eq.v #2, #3, @12 | [no change]                                      |
| 34   | nop           | 0    | N/A                            | N/A                                                          | N/A         | N/A                                    | N/A                                              | 0               | N/A   | performs no operation                                        | N/A                                                          | nop               | N/A                  | [no change]                                      |
| 35   | call          | 2    | functionNameSize, functionName | $0-2^8, [ A-Z, ., a-z, \textunderscore]$                     | N/A         | N/A                                    | N/A                                              | 0               | N/A   | calls the function                                           | N/A                                                          | call foo          | N/A                  | → return_address/link_register_value/[no change] |
| 36   | ret           | 1    | size, operationOffset          | $2^{[0-8]}$, # + $<0-\infty>$                                | N/A         | N/A                                    | N/A                                              | 0               | N/A   | return from subroutine                                       | N/A                                                          | ret 32, #3        | N/A                  | [no change]                                      |
| 37   | virtualcall   | 1    | VC_ID                          | $0-2^{16}$                                                   | N/A         | N/A                                    | N/A                                              | 0               | N/A   | calls virtual system call                                    | N/A                                                          | virtualcall 0x0   | N/A                  | depends on non-virtual systemcall                |
| 38   | align         | 1    | int                            | $1-2^{[0-8]}\equiv 0 \pmod{2}$                               | N/A         | N/A                                    | N/A                                              | 0               | N/A   | set alignment for next segment till next align instruction   | N/A                                                          | align 4           | N/A                  | [no change]                                      |


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

