#-------------------------------------------------------------------------------
# lcrand.s
#
# This program prompts the user for a min and max integer value and then for an
# integer number of results to produce.  Finally, it asks for a number to use as
# a random number seed. With those four values properly entered, it loops
# generating a series of random numbers that fit between the min and max values
# previously entered, using the Linear Congruence algorithm.
#
# This is intended to be the first project in Assembly Language written by
# students in CS200 at NAU as an introduction to the language.  It does not
# require the use of subroutines or other advanced techniques.
#
# Author: 
# Date:   
#
# Revision Log 
#-------------------------------------------------------------------------------
# 10/02/2023 - Created Skeleton for student use
#-------------------------------------------------------------------------------

        .data
# constants
Multiplier:	.word	1073807359	# a sufficiently large prime

# You probably have enough registers that you won't need variables.
# However, if you do wish to have named variables, do it here.
# Word Variables First

# HalfWord Variables Next

# Byte Variables Last (Strings and characters are Byte data)

# common strings
minPrompt:	.asciiz	"Enter the smallest number acceptable (0<=n<=998): "
maxPrompt:	.asciiz "Enter the biggest number acceptable ( n <= 1000): "
qtyPrompt:	.asciiz "How many randoms do you want (5 - 100)? "
rsdPrompt:	.asciiz "Enter a seed number (1073741824 - 2147483646): "
smErr1:		.asciiz "That number is too small, try again: "
smErr2:		.asciiz "The max cannot be less than the min, try again: "
bgErr:		.asciiz "That number is too large, try again: "
outStr:		.asciiz "Here is the series of randoms:\n"
newLine:	.asciiz "\n"

	.text
	.globl	main
#-------------------------------------------------------------------------------
# The start: entry point from the MIPS file is encompassed in the kernel code 
# of the QTSPIM simulator.  This version starts with main: which does everything
# in this simple program.
#-------------------------------------------------------------------------------

main:		# start of the main procedure

		# prompt for the minimum result and get the value
		# this is where you ask the user to tell you the beginning of the
		# range of output numbers ("randoms from 15 to 25", for example).
		# check that the input number is in the valid range for minimum,
		# 0 to 998, and if it isn't, display an error and keep looping
		# back until the user enters a good number.
		
			# 1) prompt for the number
			li $v0, 4	#making syscall 4 which is the print string syscall
			la $a0, minPrompt #telling syscall what to print
			syscall		#calling syscall
			# 2) read the integer
			step2forlower:	#designating the start of a function called step2forlower
			li $v0, 5	#making the syscall value 5
			syscall		#calling syscall 5 which is get input
			move $t0, $v0	#move the input to an acutaly register
			
			# 3) if the integer is >= 0 go to step 4
			#	else print error and return to step 2
			bge $t0, $zero , step4forlower	##branch if input is greater than 0
			
			li $v0, 4	#setting syscall value
			la $a0, smErr1	#telling syscall what to print
			syscall		#calling syscall
			j step2forlower	#jump back to grab input
			
			# 4) if the number is <= 998 go to next input
			#	else print error and return to step 2
			step4forlower:		#designation of new function called step4forlower
			ble $t0, 998, next_input_to_maximum 	#branch if input is  less than or equal to 998
			
			li $v0,4 	#value for syscall
			la $a0,bgErr	#error code for number too big
			syscall		#calling syscall
			j step2forlower		#jump back to step 2 for input
			
		# prompt for the maximum result and get the value
		# just like the minimum result, you keep asking for the input
		# until you get a good value.  In addition to making sure it
		# is in a valid range, you also have to make sure it is 
		# greater than the minimum entered before.
		
		next_input_to_maximum:
			# 1) prompt for the number
			li $v0, 4	#value for syscall
			la $a0, maxPrompt	#what is getting printed by syscall
			syscall		#calling syscall
			
			# 2) read the integer
			step2formaximum:	#new function for getting max
			li $v0, 5	#value for syscall to grab input
			syscall		#calling syscall
			move $t1, $v0		#moving the input to an actual usable register
			
			
			# 3) if the integer is >= minimum go to step 4
			#	else print error and return to step 2
			bgt $t1, $t0, step4formaximum		#branch if greater or equal to $t0
			
			li $v0, 4		#value for syscall
			la $a0, smErr2		#error for to small of a number
			syscall		#calling syscall
			j step2formaximum	#jump back to step 2 for input
			# 4) if the number is <= 1000 go to next input
			#	else print error and return to step 2
			step4formaximum:	#initializing function
			bge $t1, 1001, maxtoolarge	#branch on greater than or equal to 1001 and jump to error
			j aftermax	#jump to aftermax
			
			maxtoolarge:	#function for max larger than 1000
			li $v0, 4	#value of syscall
			la $a0, bgErr	#error string for input is too big
			syscall		#call syscall
			j step2formaximum	#jump back to step 2 to get input
	
		# now you ask for how many randoms the user wants
		# I arbitrarily chose 5 to 100 as enough to show you are getting
		# random numbers without overdoing it.  Very similar to the last:
		aftermax:	#initializing aftermax
			# 1) prompt for the number
			li $v0, 4	#value of syscall
			la $a0, qtyPrompt	#printing string called qtyprompt
			syscall		#calling syscall
			# 2) read the integer
			step2forhowmany:	#initializing new function
			li $v0, 5	#value for syscall
			syscall		#calling syscall
			move $t2, $v0	#moving input to an actual usablee register
			# 3) if the integer is >= 5 go to step 4
			#	else print error and return to step 2
			bge $t2, 5, step4forhowmany	#branch on greater than or equal to 5 
			
			li $v0, 4	#value of syscall
			la $a0, smErr1	#print error for numer too small
			syscall		#calling syscall
			j step2forhowmany	#jump back to step 2 and grab input again
			
			# 4) if the number is <= 100 go to next input
			#	else print error and return to step 2
			step4forhowmany:	#initializing a new function
			bge $t2, 101, toolargehowmany		#branch on greater than or equal to 101
			j seednumber	#jump to next function seednumber
			
			toolargehowmany:	#initializing function
			li $v0, 4	#value of syscall
			la $a0, bgErr	#print error for number to large
			syscall		#calling syscall
			j step2forhowmany	#jump to step 2 to grab input again


		# This one is just as easy, though the boundary values are large. The reason
		# is buried in how the generation algorithm works but you can just trust me
		# that the numbers in this range SHOULD give good random values.
		seednumber:	#initializing function
			# 1) prompt for the number
			li $v0, 4	#value of syscall
			la $a0, rsdPrompt	#print message for seed prompt
			syscall		#call syscall
			# 2) read the integer
			seedint:	#initialize function for grabbing input
			li $v0, 5	#value of syscall
			syscall		#calling syscall
			move $t3, $v0	#move the input to an actual usable register
			
			# 3) if the integer is >= 1073741823 go to step 4
			#	else print error and return to step 2
			bge $t3, 1073741823, step4forseed	#branch on input greater than or equal to given number
			
			li $v0, 4	#value of syscall
			la $a0, smErr1		#error for number being too small
			syscall		#calling syscall
			j seedint
			
			# 4) if the number is <= 2147483646 go to next input
			#	else print error and return to step 2
			step4forseed:		#initialize new function
			bge $t3, 2147483647, seedtoolarge	#branch on greater than or equal too number
			j randprompt	#jump to next function
			
			seedtoolarge:	#initialize function
			li $v0, 4	#value of syscall
			la $a0, bgErr	#error message saying number is too large
			syscall		#calling syscall
			j seedint	#jump back to step 2 for new input
		# Now would be a good time to compute the output range so you don't have to
		# do it each time you generate a new random.
		# precalculate the range by subtracting the minimum from the maximum
		# then add 1 to the result
		

		# tell the user "here come the randoms" or something similar
		randprompt:	#initialize function
		li $v0, 4	#value for syscall
		la $a0, outStr	#print message for the user
		syscall		#calling syscall
		j loop		#jumping to next function
		# initialize the loop counter with the number of desired randoms

		# top of random generator loop
			# first generate a random
		
		loop:	#initialize function called loop
		
		
		
				# 1) multiply the seed by the multiplier
			li $t4, 1073807359	#putting the value 1073807359 into the register $t4
			mul $t5, $t3, $t4	#multiplying $t3 (seed input) by $t4 (multiplier value)
				# 2) lo replaces the old seed
			mflo $t3	#assigning the lo to the register $t3
				# 3) hi is the raw random number
			mfhi $t5	#assigning hi to the register $t5
			# next range fit the raw random for output
				# 1) divide the raw random by the precalculated range
			divu $t5, $t5, $t1	#dividing $t5 (raw random output) by $t1 (range value)
				# 2) hi hold the ranged random after division
			mfhi $t5	#assighing hi to $t5 again
				# 3) add minimum to the ranged random 
			add $t5, $t5, $t0	#adding $t0 (minimum bound) to $t5
				# 4) print out the result
			li $v0, 1	#value for syscall 1 meaning print int
			move $a0, $t5	#moving $t5 value to a printable register
			syscall		#calling syscall
				# 5) print out a newline or " " to separate the next
			li $v0, 4	#value for syscall
			la $a0, newLine		#print statement just for new line (\n)
			syscall		#calling syscall
			# decrement the loop counter
			sub $t2, $t2, 1		#subratcting 1 from $t2 (how many numbers we want to print) 
						#to decrement the loop
					
			# if loop counter > 0, jump back to start of loop
			bgtz $t2, loop	#branch on greater than zero back to the start of the loop
		# exit program
		li	$v0, 10	#value for syscall
		syscall		#calling syscall which ends the program
