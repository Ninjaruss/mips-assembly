.data
    endl:    .asciiz  "\n"   # used for cout << endl;
    sumlbl:    .asciiz  "Sum: " # label for sum
    revlbl:    .asciiz  "Reversed Number: " # label for rev
    pallbl:    .asciiz  "Is Palindrome: " # label for isPalindrome
    sumarr:    .word 1
               .word 3
               .word 44
               .word 66
               .word 88
               .word 90
               .word 9
               .word 232
               .word 4325
               .word 2321
    arr:       .word 1
               .word 2
               .word 3
               .word 4
               .word 5
               .word 4
               .word 3
               .word 2
               .word 1
    beg:	.word 1
    end:	.word 1

.text

# sum               --> $s0
# address of sumarr --> $s1
# rev               --> $s2
# num               --> $s3
# isPalindrome      --> $s4
# address of arr    --> $s5
# i                 --> $t0
# beg               --> $s6
# end               --> $s7
# d                 --> $t1
# 10                --> $t2
# 100               --> $t3
main:
	li $s0, 0	# sum = 0
	la $s1, sumarr	# sumarr ptr
	li $t0, 0	# i = 0
	li $t2, 10	# 10
	
	
	loop1:
		lw $t4, ($s1) 	# load sumarr[i]
		add $s0, $s0, $t4	# sum = sum + sumarr[i]
		addi $s1, $s1, 4 	# point to next element
		addi $t0, $t0, 1	# i++
		blt $t0, $t2, loop1 	# i < size
	
	li $s3, 45689	# num = 45689
	li $s2, 0	# rev = 0
	li $t1, -1	# d = -1
	
	loop2:
		## div $s3, $t2 ## num % 10
		rem $t1, $s3, $t2 # d = num % 10
		mul $s2, $s2, $t2 # rev*10
		add $s2, $s2, $t1 # rev+d
		div $s3, $s3, $t2 # num/10
		bgt $s3, 0, loop2 # num>0
		
	la $s5, arr	# arr ptr
	li $s6, 0	# beg = 0
	li $s7, 8	# end = 8
	li $s4, 1	# isPalindrome = 1
	
	
	loop3:
		lw $t5, ($s5) 		# load arr ptr for beg
		mul $t0, $s6, 4		# offset for arr[beg]
		add $t5, $t5, $t0	# move pointer to arr[beg]
		
		lw $t6, ($s5)		# load arr ptr for end
		mul $t0, $s7, 4		# offset for arr[end]
		add $t6, $t6, $t0	# move pointer to arr[end]
		
		beq $t5, $t6, exit1
		
		addi $s6, $s6, 1
		addi $s7, $s7, -1
		
		blt $s6, $s7, loop3 # beg < end
		exit1:
			li $s4, -1
			j exitL3
	exitL3:

exit:
  la   $a0, sumlbl    # puts sumlbl into arg0 (a0 register) for cout
  addi $v0, $0, 4     # puts 4 in v0 which denotes we are printing a string
  syscall             # make a syscall to system

  move $a0, $s0       # puts sum into arg0 (a0 register) for cout
  addi $v0, $0, 1     # puts 1 in v0 to denote we are printing an int
  syscall             # make a syscall to system

  la   $a0, endl      # puts the address of the string endl into a0
  addi $v0, $0, 4     # puts 4 into v0 saying we are printing a string
  syscall

  la   $a0, revlbl    # puts revlbl into arg0 (a0 register) for cout
  addi $v0, $0, 4     # puts 4 in v0 which denotes we are printing an string
  syscall             # make a syscall to system

  move $a0, $s2       # puts rev into arg0 (a0 register) for cout
  addi $v0, $0, 1     # puts 1 in v0 to denote we are printing an int
  syscall             # make a syscall to system

  la   $a0, endl      # puts the address of the string endl into a0
  addi $v0, $0, 4     # puts 4 into v0 saying we are printing a string
  syscall

  la   $a0, pallbl    # puts pallbl into arg0 (a0 register) for cout
  addi $v0, $0, 4     # puts 4 in v0 which denotes we are printing a string
  syscall             # make a syscall to system

  move $a0, $s4       # puts isPalindrome into arg0 (a0 register) for cout
  addi $v0, $0, 1     # puts 1 in v0 to denote we are printing an int
  syscall             # make a syscall to system

  la   $a0, endl      # puts the address of the string endl into a0
  addi $v0, $0, 4     # puts 4 into v0 saying we are printing a string
  syscall


  addi $v0,$0, 10
  syscall
