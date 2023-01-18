# TVM

Repository which represents sparkVM(official implementation of Theia Virtual Machine)

# Dependencies:

- OpenSSL
- Boost
- jemalloc
- RocksDB

# VM Opcodes

| hex num | name        | args                   | note                                                         | examples     | Stack [before]→[after]           | exception                           | Implemented(true/false) |
| ------- | ----------- | ---------------------- | ------------------------------------------------------------ | ------------ | -------------------------------- | ----------------------------------- | ----------------------- |
| 000     | stop        | -                      | stop execution of the program                                | stop         | * → [empty]                      | -                                   | true                    |
| 001     | go_to       | int                    | goes to another instruction at *branchoffset*                | go_to 2      | [no change]                      | -                                   | true                    |
| 002     | swap        | int,int                | swaps two references. indexing starts from top of stack      | swap 1 3     | value1,value2→value2,value1      | -                                   | true                    |
| 003     | iadd        | num, num               | adding value                                                 |              | value1,value2→result             | -                                   | true                    |
| 004     | isub        | num, num               | subtract value                                               |              | value1,value2→result             | -                                   | true                    |
| 005     | idivide     | num, num               | devide value                                                 |              | value1,value2→result             | -                                   | true                    |
| 006     | imul        | num, num               | multiply value                                               |              | value1,value2→result             | -                                   | true                    |
| 007     | imod        | int, int               | a % b                                                        |              | value1,value2→result             | -                                   | true                    |
| 008     | ixor        | int, int               | a ^ b                                                        |              | value1,value2→result             | -                                   | true                    |
| ~~009~~ | -           | -                      | -                                                            | -            | -                                | -                                   | pop                     |
| 010     | ilshift     | int, int               | a << val                                                     |              | value1,value2→result             | second parameter  < int32 max value | true                    |
| 011     | irshift     | int                    | a >> val                                                     |              | value1,value2→result             | -                                   | true                    |
| 012     | pop         | object                 | pop value                                                    |              | value→                           | -                                   | true                    |
| 013     | pop2        | object, object         | pop 2 values on top of the stack                             | -            | value1,value2→                   | -                                   | true                    |
| 014     | dup         | object                 | duplicate from top of the stack                              |              | value→value1,value1              | -                                   | true                    |
| 015     | ior         | num                    | a \|\| b                                                     |              | value1,value2→result             | -                                   | true                    |
| 016     | iand        | int                    | a & b                                                        |              | value1,value2→result             | -                                   | true                    |
| 017     | pshnull     | -                      | push null reference on top of the stack                      | -            | →null                            | -                                   | true                    |
| 018     | sha3        | object                 | apply sha3_256 value on top of the stack.                    |              | value→sha3(value)                | -                                   | true                    |
| 019     | balance     | string                 | get balance of address                                       |              | →value                           | -                                   | true                    |
| 020     | timestamp   | -                      | get timestamps                                               |              | →value                           | -                                   | true                    |
| 021     | blockhash   | -                      | get blockhash                                                |              | →value                           | -                                   | true                    |
| 022     | chainid     | -                      | returns chain_id                                             |              | →value                           | -                                   | true                    |
| 023     | create      | -                      | create contract                                              |              | [no change]                      | -                                   | true                    |
| 024     | destruct    | string                 | destruct contract and returns all holdings to their holders  |              | [no change]                      | -                                   | true                    |
| 025     | address     | -                      | address of current contract                                  |              | →value                           | -                                   | true                    |
| 026     | invalid     | -                      | invalid                                                      | -            | -                                | -                                   | true                    |
| 027     | icnst_0     | int                    | push int value 0 onto the stack.                             | -            | → 0                              | -                                   | true                    |
| 028     | icnst_1     | int                    | push int value 1 onto the stack                              | -            | → 1                              | -                                   | true                    |
| 029     | icnst_2     | int                    | push int value 2 onto the stack                              | -            | → 2                              | -                                   | true                    |
| 030     | icnst_3     | int                    | push int value 3 onto the stack                              | -            | → 3                              | -                                   | true                    |
| 031     | icnst_4     | int                    | push int value 4 onto the stack                              | -            | → 4                              | -                                   | true                    |
| 032     | u64cnst_0   | -                      | push uint64_t value 0 onto the stack                         | -            | → 0                              | -                                   | true                    |
| 033     | u64cnst_1   | -                      | push uint64_t value 1 onto the stack                         | -            | → 1                              | -                                   | true                    |
| 034     | checktype   | int                    | check if objectref's type equals type in the classes virtual pool by index of class in pool | checktype    | value→value                      | -                                   | true                    |
| 035     | u32cnst_0   | -                      | push uint32_t value 0 onto the stack                         | -            | → 0                              | -                                   | true                    |
| 036     | u32cnst_1   | -                      | push uint32_t value 1 onto the stack                         | -            | → 1                              | -                                   | true                    |
| 037     | u32str_0    | -                      | push uint32_t into register 0                                | -            | value→                           | -                                   | true                    |
| 038     | u32str_1    | -                      | push uint32_t into register 1                                | -            | value→                           | -                                   | true                    |
| 039     | u32str_2    | -                      | push uint32_t into register 2                                | -            | value→                           | -                                   | true                    |
| 040     | u32str_3    | -                      | push uint32_t into register 3                                | -            | value→                           | -                                   | true                    |
| 041     | u64str_0    | -                      | push uint64_t into register 0                                | -            | value→                           | -                                   | true                    |
| 042     | u64str_1    | -                      | push uint64_t into register 1                                | -            | value→                           | -                                   | true                    |
| 043     | u64str_2    | -                      | push uint64_t into register 2                                | -            | value→                           | -                                   | true                    |
| 044     | u64str_3    | -                      | push uint64_t into register 3                                | -            | value→                           | -                                   | true                    |
| 045     | astorec     | -                      | store char into array                                        | -            | arrayref, index, value →         | -                                   | true                    |
| 046     | aloadc      | -                      | load char from array                                         | -            | -                                | -                                   | true                    |
| 047     | u128str_0   | int                    | push uint128_t value into local 0                            |              | value→                           | -                                   | true                    |
| 048     | u128str_1   | int                    | push uint128_t value into local 1                            |              | value→                           | -                                   | true                    |
| 049     | u128str_2   | int                    | push uint128_t value into local 2                            |              | value→                           | -                                   | true                    |
| 050     | u128str_3   | int                    | push uint128_t value into local 3                            |              | value→                           | -                                   | true                    |
| 051     | ldc         | int index              | load #index from blockhain data.                                                                                                                              If program looks like: [60, 1], it'll load first value from blockchain data[^1] onto the stack.                                                                                                                 If program looks like: [60, 2], it'll load second value from blockchain data[^1]onto the stack. |              | → value                          | -                                   | true                    |
| 052     | ild_0       | -                      | load integer from local_0 on top of stack                    | iload 1      | → value                          | -                                   | true                    |
| 053     | ild_1       | -                      | load integer from local_0 on top of stack                    | iload 1      | → value                          | -                                   | true                    |
| 054     | ild_2       | -                      | load integer from local_0 on top of stack                    | iload 1      | → value                          | -                                   | true                    |
| 055     | ild_3       | -                      | load integer from local_0 on top of stack                    | iload 1      | → value                          | -                                   | true                    |
| 056     | swap        | -                      | swaps two top elements                                       | swap         | value1,value2→value2,value1      | -                                   | true                    |
| 057     | if_acmpeq   | object, object         | checks if two values (Object or string) on top of the stack are equal. next index - index of next instruction. (a == b) | if_acmpeq 23 | [no change]                      | -                                   | true                    |
| 058     | if_acmpne   | object , object        | checks if two values (Object or string) on top of the stack are not equal. next index - index of next instruction. (a != b) | if_acmpne 23 | [no change]                      | -                                   | true                    |
| 059     | if_icmpeq   | object, object         | checks if two integers (int32, uint64, uint128, uint256) on top of the stack are equal. next index - index of next instruction. (a == b) | if_icmpeq 23 | [no change]                      | -                                   | true                    |
| 060     | if_icmpge   | num,num                | checks if two integers (int32, uint64, uint128, uint256) on top of the stack are greater than or equal. next index - index of next instruction. (a >= b) | if_icmpge 23 | [no change]                      | -                                   | true                    |
| 061     | if_icmpgt   | num,num                | checks if two integers (int32, uint64, uint128, uint256) on top of the stack are greater than. next index - index of next instruction. (a > b) | if_icmpgt 23 | [no change]                      | -                                   | true                    |
| 062     | if_icmple   | num,num                | checks if two integers (int32, uint64, uint128, uint256) on top of the stack are less than or equal. next index - index of next instruction. (a <= b) | if_icmple 23 | [no change]                      | -                                   | true                    |
| 063     | if_icmplt   | num,num                | checks if two integers (int32, uint64, uint128, uint256) on top of the stack are less. next index - index of next instruction. (a < b) | if_icmplt 23 | [no change]                      | -                                   | true                    |
| 064     | if_icmpne   | num,num                | checks if two integers (int32, uint64, uint128, uint256) on top of the stack are not equal. next index - index of next instruction. (a != b) | if_icmpne 23 | [no change]                      | -                                   | true                    |
| 065     | ifeq        | num                    | checks if integer (int32, uint64, uint128, uint256) on top of the stack are 0. next index - index of next instruction. (a == 0) | ifeq 23      | [no change]                      | -                                   | true                    |
| 066     | ifge        | num                    | checks if integer (int32, uint64, uint128, uint256) on top of the stack greater than or equal to 0. next index - index of next instruction. (a >= 0) | ifge 23      | [no change]                      | -                                   | true                    |
| 067     | ifgt        | num                    | checks if integer (int32, uint64, uint128, uint256) on top of the stack greater than 0. next index - index of next instruction. (a > 0) | ifgt 23      | [no change]                      | -                                   | true                    |
| 068     | ifle        | num                    | checks if integer (int32, uint64, uint128, uint256) on top of the stack less than or equal to 0. next index - index of next instruction. (a <= 0) | ifle 23      | [no change]                      | -                                   | true                    |
| 069     | iflt        | num                    | checks if integer (int32, uint64, uint128, uint256) on top of the stack less than 0. next index - index of next instruction. (a < 0) | iflt 23      | [no change]                      | -                                   | true                    |
| 070     | ifne        | num                    | checks if integer (int32, uint64, uint128, uint256) on top of the stack not equals 0. next index - index of next instruction. (a != 0) | ifne 23      | [no change]                      | -                                   | true                    |
| 071     | ifnonnull   | Object                 | checks if value (Object or string) on top of the stack are not null. next index - index of next instruction. (a != null) | ifnonnull 23 | [no change]                      | -                                   | true                    |
| 072     | ifnull      | Object                 | checks if value (Object or string) on top of the stack are not null. next index - index of next instruction. (a == null) | ifnull 23    | [no change]                      | -                                   | true                    |
| 073     | nop         | -                      | perform no operation                                         | nop          | [no change]                      | -                                   | true                    |
| ~~074~~ | -           | -                      | -                                                            | -            | -                                | -                                   | false                   |
| 075     | dcnst_0     | -                      | push double value 0.0 onto the stack.                        | dcnst_0      | → 0.0                            | -                                   | true                    |
| 076     | dcnst_1     | -                      | push double value 1.0 onto the stack.                        | dcnst_1      | → 1.0                            | -                                   | true                    |
| 077     | lcnst_0     | -                      | push long value 0 onto the stack.                            | lcnst_0      | → 0                              | -                                   | true                    |
| 078     | lcnst_1     | -                      | push long value 1 onto the stack.                            | lcnst_0      | → 1                              | -                                   | true                    |
| ~~079~~ | -           | -                      | -                                                            | -            | -                                | -                                   | false                   |
| 080     | dadd        | num, num               | adding value                                                 |              | value1,value2→value1+value2      | -                                   | true                    |
| 081     | u128cnst_0  | -                      | push uint128_t value 0 onto the stack.                       | -            | → 0                              | -                                   | true                    |
| 082     | u128cnst_1  | -                      | push uint128_t value 1 onto the stack.                       | -            | → 1                              | -                                   | true                    |
| 083     | u256cnst_0  | -                      | push uint256_t value 0 onto the stack.                       | -            | → 0                              | -                                   | true                    |
| 084     | u256cnst_1  | -                      | push uint256_t value 1 onto the stack.                       | -            | → 1                              | -                                   | true                    |
| 083     | dsub        | num, num               | subtract value                                               |              | value1,value2→value1-value2      | -                                   | true                    |
| 084     | lsub        | long,long              | subtract long                                                | -            | value1,value2→value1-value2      | -                                   | true                    |
| 085     | lmul        | long,long              | multiply long                                                | -            | value1,value2→value1*value2      | -                                   | true                    |
| 086     | ldiv        | long,long              | divide long                                                  | -            | value1,value2→value1/value2      | -                                   | true                    |
| 087     | u256str_0   | int                    | push uint256_t value into local 0                            |              | value→                           | -                                   | true                    |
| 088     | u256str_1   | int                    | push uint256_t value into local 1                            |              | value→                           | -                                   | true                    |
| 089     | u256str_2   | int                    | push uint256_t value into local 2                            |              | value→                           | -                                   | true                    |
| 090     | u256str_3   | int                    | push uint256_t value into local 3                            |              | value→                           | -                                   | true                    |
| 091     | rtcall      | objectref              | calling method at runtime by objectref                       | -            | objectref,[arg1,arg2,...]→result | -                                   | true                    |
| 092     | stcall      | objectref              | calling static method at runtime by objectref                | -            | objectref,[arg1,arg2,...]→result | -                                   | true                    |
| 093     | itfcall     | objectref              | calling interface method at runtime by objectref             | -            | objectref,[arg1,arg2,...]→result | -                                   | true                    |
| 094     | spcall      | objectref              | calling methods from classes(parent classes, private methods and other current class methods of certain object) runtime by objectref | -            | objectref,[arg1,arg2,...]→result | -                                   | true                    |
| 095     | lld_0       | -                      | load long from local_0 on top of stack                       | -            | → value                          | -                                   | true                    |
| 096     | lld_1       | -                      | load long from local_1 on top of stack                       | -            | → value                          | -                                   | true                    |
| 097     | lld_2       | -                      | load long from local_2 on top of stack                       | -            | → value                          | -                                   | true                    |
| 098     | lld_3       | -                      | load long from local_3 on top of stack                       | -            | → value                          | -                                   | true                    |
| 099     | aloadi      | -                      | load integer from array                                      | -            | -                                | -                                   | true                    |
| 100     | astorei     | -                      | store integer into array                                     | -            | -                                | -                                   | true                    |
| ~~101~~ | -           | -                      | -                                                            | -            | -                                | -                                   | false                   |
| 102     | dinv        | num                    | !a                                                           |              | value→!value                     | -                                   | true                    |
| 103     | ddiv        | num, num               | devide value                                                 |              | value1,value2→value1/value2      | -                                   | true                    |
| 104     | dmul        | num, num               | multiply value                                               |              | value1,value2→value1*value2      | -                                   | true                    |
| 105     | aloadl      | -                      | load long from array                                         | -            | -                                | -                                   | true                    |
| 106     | astorel     | -                      | store long into array                                        | -            | -                                | -                                   | true                    |
| 107     | aloadd      | -                      | load double from array                                       | -            | -                                | -                                   | true                    |
| 108     | astored     | -                      | store long into array                                        | -            | -                                | -                                   | true                    |
| 109     | aloadb      | -                      | load bool from array                                         | -            | -                                | -                                   | true                    |
| 110     | astoreb     | -                      | store bool into array                                        | -            | -                                | -                                   | true                    |
| 111     | -           | -                      | -                                                            | -            | -                                | -                                   | false                   |
| 112     | iinc        | int, num               | a + increasing_value(e.g 1,2,3,4,5,6,7,8,9 etc). First parameter - is index of local(e.g 1,2,3,4), second - increasing value. In example we're increasing value in local#1 by 4, so if we have in local#1, for example value 6, it'll become 10 after instruction | iinc 1 4     | [No change]                      | -                                   | true                    |
| 113     | i2d         | num,num                | convert int to double (two top values from stack)            | i2d          | (int)value→(double)result        | -                                   | true                    |
| 114     | i2u64       | num,num                | convert int to uint64 (two top values from stack)            | i2u64        | (int)value→(uint64)result        | -                                   | true                    |
| 115     | i2u128      | num,num                | convert int to uint128 (two top values from stack)           | i2u128       | (int)value→(uint128)result       | -                                   | true                    |
| 116     | i2u256      | num,num                | convert int to uint256 (two top values from stack)           | i2u256       | (int)value→(uint256)result       | -                                   | true                    |
| 117     | i2b         | int                    | convert int to byte                                          | i2b          | (int)value→(byte)result          | -                                   | true                    |
| 118     | i2c         | int                    | convert int to char                                          | i2c          | (int)value→(char)result          | -                                   | true                    |
| 119     | i2l         | int                    | convert int to long                                          | i2l          | (int)value→(long)result          | -                                   | true                    |
| 120     | i2s         | int                    | convert int to char                                          | i2s          | (int)value→(short)result         | -                                   | true                    |
| 121     | d2i         | double                 | convert double to int                                        | d2i          | (double)value→(int)result        | -                                   | true                    |
| 122     | d2l         | double                 | convert double to long                                       | d2l          | (double)value→(long)result       | -                                   | true                    |
| 123     | ireturn     | int                    | return an integer from a method                              | ireturn      | value→[empty]                    | -                                   | true                    |
| 124     | lreturn     | long                   | return an long from a method                                 | lreturn      | value→[empty]                    | -                                   | true                    |
| 125     | return      | -                      | return from void method                                      | return       | -                                | -                                   | true                    |
| 126     | areturn     | objectref              | return reference from a method                               | refreturn    | objectRef → [empty]              | -                                   | true                    |
| 127     | new         | int                    | loading object with type by index in constant pool           | new 115      | → objectRef                      | -                                   |                         |
| 128     | newarray    | uint64_t               | create a new array with size at the top of the stack         | newarray     | (array_size)value→arrayref       | -                                   | true                    |
| 129     | new_mdarray | byte1,byte2,dimensions | create a new multidimensional array of type by classref in pool by index (indexbyte1 << 8 \|\| indexbyte2) | -            | count1, [count2,...] → arrayref  | -                                   | false                   |
| 130     | dreturn     | -                      | return a double from method                                  | -            | value→[empty]                    | -                                   | true                    |
| 131     | u32return   | -                      | return a uint32 from method                                  | -            | value→[empty]                    | -                                   | true                    |
| 132     | u64return   | -                      | return a uint64 from method                                  | -            | value→[empty]                    | -                                   | true                    |
| 133     | u128return  | -                      | return a uint128 from method                                 | -            | value→[empty]                    | -                                   | true                    |
| 134     | u256return  | -                      | return a uint256 from method                                 | -            | value→[empty]                    | -                                   | true                    |
| 135     | aloadu32    | -                      | load uint32 from array                                       | -            | -                                | -                                   | true                    |
| 136     | astoreu32   | -                      | store uint32 into array                                      | -            | -                                | -                                   | true                    |
| 137     | aloadu64    | -                      | load uint64 from array                                       | -            | -                                | -                                   | true                    |
| 138     | astoreu64   | -                      | store uint64 into array                                      | -            | -                                | -                                   | true                    |
| 139     | aloadu128   | -                      | load uint128 from array                                      | -            | -                                | -                                   | true                    |
| 140     | astoreu128  | -                      | store uint128 into array                                     | -            | -                                | -                                   | true                    |
| 141     | aloadu256   | -                      | load uint256 from array                                      | -            | -                                | -                                   | true                    |
| 142     | astoreu256  | -                      | store uint256 into array                                     | -            | -                                | -                                   | true                    |
| 143     | aloada      | -                      | load reference from array                                    | -            | -                                | -                                   | true                    |
| 144     | astorea     | -                      | store reference into array                                   | -            | -                                | -                                   | true                    |
