## VM course   
### Participants   
Ozerov Nikita https://github.com/nik0zer   
Klimentieva Maria https://github.com/MariaKlimenteva   
### VM instructions
<details>
<summary><b>General rules</b></summary>

### Registers   
Each method keeps informations about number of call parameters (N) and number of registers needed for local
variables(M). When calls, method allocate N + M registers in registers [0:N-1] the arguments of the function lie. Other can be used as local variables.

### Accumulator (acc)   
Special register witch state doesn't reset when method's frame ends. At the start of method must be treated as contains trash. After call any method, acc contains return value from called method. 

### Types
All instrations which operates with values contains postfix \<type\> that shows types of operands in instruction. Now type only can be i64 refers to int64_t

### Jumps 
All jumps use list of marks whith every method holds, so jumps only availible in method range. In bytecode transforms to <opcode> <offset>

### Calls
When method calls first (K) registers [0:K-1] threated as parameters, when method returns value in accumulator threated as return value.

</details>

<details>
<summary><b>Move instructions</b></summary>

### mv.\<type\> \<reg\>, \<val\>   
reg = val
opcode: 0

### stacc.\<type\> \<reg\>
acc = reg
opcode: 1

### ldacc.\<type\> \<reg\>
reg = acc
opcode: 2

</details>

<details>
<summary><b>Arithmetical instructions</b></summary>

### add.\<type\> \<regout\>, \<regin_1\>, \<regin_2\>   
regout = regin_1 + regin_2
opcode: 3

### sub.\<type\> \<regout\>, \<regin_1\>, \<regin_2\>   
regout = regin_1 - regin_2
opcode: 4

### mul.\<type\> \<regout\>, \<regin_1\>, \<regin_2\>   
regout = regin_1 * regin_2
opcode: 5

### div.\<type\> \<regout\>, \<regin_1\>, \<regin_2\>   
regout = regin_1 / regin_2
opcode: 6

</details>

<details>
<summary><b> Compare instructions </b></summary>

### cmpeq.\<type\> \<regin_1\>, \<regin_2\>  
acc = regin_1 == regin_2
opcode: 7

### cmpgt.\<type\> \<regin_1\>, \<regin_2\>  
acc = regin_1 > regin_2
opcode: 8

### cmpge.\<type\> \<regin_1\>, \<regin_2\>  
acc = regin_1 >= regin_2
opcode: 9

</details>

<details>
<summary><b> Jump instructions </b></summary>

### jmp \<mark\>   
pc = address(mark)
opcode: 10

### cjmpt \<mark\>   
if(acc)
    pc = address(mark)
opcode: 11

### cjmpf \<mark\>   
if(!acc)
    pc = address(mark)

opcode: 12

</details>

<details>
<summary><b> Call instructions </b></summary>

### call \<function\>   
function()
opcode: 13

### ret
return
opcode: 14

</details>