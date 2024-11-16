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
All jumps use list of marks whith every method holds, so jumps only availible in method range.

### Calls
When method calls first (K) registers [0:K-1] threated as parameters, when method returns value in accumulator threated as return value.

</details>

<details>
<summary><b>Move instructions</b></summary>

### mv.\<type\> \<reg\>, \<val\>   
reg = val

### stacc.\<type\> \<reg\>
acc = reg

### ldacc.\<type\> \<reg\>
reg = acc

</details>

<details>
<summary><b>Arithmetical instructions</b></summary>

### add.\<type\> \<regout\>, \<regin_1\>, \<regin_2\>   
regout = regin_1 + regin_2

### sub.\<type\> \<regout\>, \<regin_1\>, \<regin_2\>   
regout = regin_1 - regin_2

### mul.\<type\> \<regout\>, \<regin_1\>, \<regin_2\>   
regout = regin_1 * regin_2

### div.\<type\> \<regout\>, \<regin_1\>, \<regin_2\>   
regout = regin_1 / regin_2

</details>

<details>
<summary><b> Compare instructions </b></summary>

### cmpeq.\<type\> \<regin_1\>, \<regin_2\>  
acc = regin_1 == regin_2

### cmpgt.\<type\> \<regin_1\>, \<regin_2\>  
acc = regin_1 > regin_2

### cmpge.\<type\> \<regin_1\>, \<regin_2\>  
acc = regin_1 >= regin_2

</details>

<details>
<summary><b> Jump instructions </b></summary>

### jmp \<mark\>   
pc = address(mark)

### cjmpt \<mark\>   
if(acc)
    pc = address(mark)

### cjmpf \<mark\>   
if(!acc)
    pc = address(mark)

</details>

<details>
<summary><b> Call instructions </b></summary>

### call \<function\>   
function()

### ret
return

</details>