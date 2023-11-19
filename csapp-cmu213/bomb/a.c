4010f4:	41 56                	push   %r14
4010f6:	41 55                	push   %r13
4010f8:	41 54                	push   %r12
4010fa:	55                   	push   %rbp
4010fb:	53                   	push   %rbx
4010fc:	48 83 ec 50          	sub    $0x50,%rsp          ; 在栈上为局部变量分配空间
401100:	49 89 e5             	mov    %rsp,%r13           ; r13 用于迭代数组
401103:	48 89 e6             	mov    %rsp,%rsi           ; rsi 用于存储输入的六个数字
401106:	e8 51 03 00 00       	callq  40145c <read_six_numbers>  ; 读入六个数字
40110b:	49 89 e6             	mov    %rsp,%r14           ; r14 用于保存输入的六个数字的起始地址
*0x40110e:	41 bc 00 00 00 00    	mov    $0x0,%r12d         ; r12d 用于迭代计数，初始为 0
*0x401114:	4c 89 ed             	mov    %r13,%rbp           ; rbp 用于迭代数组
*0x401117:	41 8b 45 00          	mov    0x0(%r13),$eax      ; 取出数组的一个元素
*0x40111b:	83 e8 01             	sub    $0x1,%eax           ; 减去 1
*0x40111e:	83 f8 05             	cmp    $0x5,$eax           ; 判断是否小于等于 5
*0x401121:	76 05                	jbe    401128 <phase_6+0x34> // jump below or equal
*0x401123:	e8 12 03 00 00       	callq  40143a <explode_bomb>  ; 数字不在规定范围内，爆炸
*0x401128:	41 83 c4 01          	add    $0x1,%r12d          ; 计数加一
*0x40112c:	41 83 fc 06          	cmp    $0x6,%r12d          ; 判断是否迭代了六次
*0x401130:	74 21                	je     401153 <phase_6+0x5f>
*0x401132:	44 89 e3             	mov    %r12d,%ebx           ; 将计数存入 ebx // 1 ebx
*0x401135:	48 63 c3             	movslq %ebx,%rax           ; 将计数扩展为 64 位 // ??
*0x401138:	8b 04 84             	mov    (%rsp,%rax,4),$eax  ; 取出数组的一个元素 // $rsp+$rax*4
*0x40113b:	39 45 00             	cmp    $eax,0x0($rbp)      ; 比较数组中的元素和输入的数字
*0x40113e:	75 05                	jne    401145 <phase_6+0x51> // 不相等
*0x401140:	e8 f5 02 00 00       	callq  40143a <explode_bomb>  ; 相等，爆炸
*0x401145:	83 c3 01             	add    $0x1,$ebx           ; 计数加一
*0x401148:	83 fb 05             	cmp    $0x5,$ebx           ; 判断计数是否小于等于 5
*0x40114b:	7e e8                	jle    401135 <phase_6+0x41>  ; 继续迭代
*0x40114d:	49 83 c5 04          	add    $0x4,$r13           ; r13 指向下一个数字
*0x401151:	eb c1                	jmp    401114 <phase_6+0x20>  ; 继续迭代


401153:	48 8d 74 24 18       	lea    0x18($rsp),%rsi     ; rsi 指向数组的第四个元素 // 0  0
401158:	4c 89 f0             	mov    %r14,%rax           ; rax 指向输入的六个数字的起始地址
40115b:	b9 07 00 00 00       	mov    $0x7,%ecx           ; ecx 初始化为 7
401160:	89 ca                	mov    %ecx,%edx           ; edx 初始化为 ecx
401162:	2b 10                	sub    ($rax),$edx         ; 数组中的元素递减 edx
401164:	89 10                	mov    $edx,($rax)         ; 数组中的元素更新为递减后的值
401166:	48 83 c0 04          	add    $0x4,%rax           ; 指向下一个数字
40116a:	48 39 f0             	cmp    $rsi,$rax           ; 比较是否迭代完成
40116d:	75 f1                	jne    401160 <phase_6+0x6c>  ; 继续迭代
===========================

40116f:	be 00 00 00 00       	mov    $0x0,%esi           ; 初始化 esi 为 0
401174:	eb 21                	jmp    401197 <phase_6+0xa3>  ; 跳到下一段代码
// \250
401176:	48 8b 52 08          	mov    0x8($rdx),$rdx      ; 取出链表下一个元素的地址
40117a:	83 c0 01             	add    $0x1,$eax           ; 计数加一
40117d:	39 c8                	cmp    $ecx,$eax           ; 比较计数是否等于 ecx
40117f:	75 f5                	jne    401176 <phase_6+0x82>  ; 继续迭代
401181:	eb 05                	jmp    401188 <phase_6+0x94>  ; 跳转到下一段代码

// L\001
401183:	ba d0 32 60 00       	mov    $0x6032d0,%edx      ; edx 存储 0x6032d0 地址
401188:	48 89 54 74 20       	mov    $rdx,0x20(%rsp,%rsi,2)  ; 将 edx 的值存储在数组中
40118d:	48 83 c6 04          	add    $0x4,%rsi           ; 更新 esi，指向下一个位置
401191:	48 83 fe 18          	cmp    $0x18,%rsi          ; 比较是否到达数组末尾
401195:	74 14                	je     4011ab <phase_6+0xb7>  ; 迭代完成，跳到下一段代码


401197:	8b 0c 34             	mov    ($rsp+$rsi,1),$ecx   ; 取出数组中的元素
40119a:	83 f9 01             	cmp    $0x1,%ecx           ; 比较是否大于 1
40119d:	7e e4                	jle    401183 <phase_6+0x8f>  ; 如果小于等于 1，跳到下一段代码
40119f:	b8 01 00 00 00       	mov    $0x1,%eax           ; 初始化 eax 为 1
// L\001
4011a4:	ba d0 32 60 00       	mov    $0x6032d0,%edx      ; edx 存储 0x6032d0 地址
4011a9:	eb cb                	jmp    401176 <phase_6+0x82>  ; 跳到下一段代码

____________________________________________________________________________________

*0x4011ab:	48 8b 5c 24 20       	mov    0x20($rsp),$rbx     ; rbx 指向数组中的一个元素
*0x4011b0:	48 8d 44 24 28       	lea    0x28($rsp),$rax     ; rax 指向数组的下一个元素
*0x4011b5:	48 8d 74 24 50       	lea    0x50(%rsp),%rsi     ; rsi 指向数组的末尾
*0x4011ba:	48 89 d9             	mov    %rbx,%rcx           ; rcx 初始化为数组的一个元素
*0x4011bd:	48 8b 10             	mov    (%rax),%rdx         ; 取出数组的下一个元素

*0x4011c0:	48 89 51 08          	mov    %rdx,0x8(%rcx)       ; Move the value in %rdx to the address (%rcx + 8)
*0x4011c4:	48 83 c0 08          	add    $0x8,%rax            ; Increment the value in %rax by 8
*0x4011c8:	48 39 f0             	cmp    %rsi,%rax           ; Compare %rax with %rsi
*0x4011cb:	74 05                	je     4011d2 <phase_6+0xde> ; Jump to 4011d2 if equal
//
*0x4011cd:	48 89 d1             	mov    $rdx,$rcx            ; Move the value in %rdx to %rcx
*0x4011d0:	eb eb                	jmp    4011bd <phase_6+0xc9> ; Jump to 4011bd
*0x4011d2:	48 c7 42 08 00 00 00 	movq   $0x0,0x8(%rdx)       ; Move the value 0 to the address (%rdx + 8)
*0x4011d9:	00
*0x4011da:	bd 05 00 00 00       	mov    $0x5,%ebp             ; Move the value 5 to %ebp
*0x4011df:	48 8b 43 08          	mov    0x8(%rbx),%rax       ; Move the value at (%rbx + 8) to %rax
*0x4011e3:	8b 00                	mov    (%rax),%eax          ; Move the value at (%rax) to %eax
// eax rbx
4011e5:	39 03                	cmp    $eax,($rbx)         ; Compare %eax with the value at (%rbx)
4011e7:	7d 05                	jge    4011ee <phase_6+0xfa> ; Jump to 4011ee if greater or equal
4011e9:	e8 4c 02 00 00       	callq  40143a <explode_bomb> ; Call explode_bomb if the comparison fails
4011ee:	48 8b 5b 08          	mov    0x8(%rbx),%rbx       ; Move the value at (%rbx + 8) to %rbx
4011f2:	83 ed 01             	sub    $0x1,%ebp             ; Decrement %ebp by 1
4011f5:	75 e8                	jne    4011df <phase_6+0xeb> ; Jump to 4011df if not equal to zero
4011f7:	48 83 c4 50          	add    $0x50,%rsp            ; Adjust the stack pointer by 80 bytes
4011fb:	5b                   	pop    %rbx                  ; Pop the top of the stack into %rbx
4011fc:	5d                   	pop    %rbp                  ; Pop the top of the stack into %rbp
4011fd:	41 5c                	pop    %r12                  ; Pop the top of the stack into %r12
4011ff:	41 5d                	pop    %r13                  ; Pop the top of the stack into %r13
401201:	41 5e                	pop    %r14                  ; Pop the top of the stack into %r14
401203:	c3                   	retq                           ; Return from the function
