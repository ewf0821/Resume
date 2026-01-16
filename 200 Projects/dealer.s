##############################################################################
# Dealer                                                              dealer.s
#
# This project is all about manipulating arrays and using subroutines.  I've
# preloaded a set of strings naming the cards in a deck and set up an array
# of pointers to the card names.  I suggest you don't alter these, but you
# can copy the array and manipulate it in various ways.
#
# Specifically, you should have a deck array and a discard array. Initially,
# both arrays should be filled with null pointers.  For I/O, the main program
# accepts (S)huffle and only accepts (D)raw if the deck array is not empty.
# When these commands are selected, a subroutine is called to handle them. In
# the case of the (D)raw command, when the subroutine returns, the main
# program should display the returned card name.
#
# For the (S)huffle command, a subroutine is called with the addresses of the
# deck and discard arrays. It should clear the discard array if it is not
# already empty and copy the array of pointers to card to the deck array. It
# should then shuffle the deck array.
#
# For the (D)raw command, a subroutine is called with the addresses of the
# deck and discard arrays, as well as the index of the last card in the deck.
# it will then move that card pointer to the discard array, clear it from the
# deck array, and return the pointer to the caller.
#
# For your shuffle subroutine, you will need to modify and use the random
# code you built for the first project.  You don't need it to loop and you
# always need a number between 0 and 51 foe indexing into the card array. For
# this project, I allow the use of system service #30, so you can use the time
# value returned in $a0 as your seed.
#
# Author: Patrick Kelley (skeleton file)			11.5.2023
# Author:
##############################################################################
	.data
# constants
Multiplier:	.word	1073807359	# a sufficiently large prime
Seed:		.word	0
Newline:	.asciiz "\n"
#----- Your data definitions go here -----#
Intro: 	.asciiz "In put S to shuffle, D to draw, or Q to quit: "
Draw: 	.asciiz "You draw the card: "
DeckArray:  .space 208
Current:    .word   0
Buffer: .space 5
Error:    .asciiz "Invalid input. Please enter S, D, or Q.\n"
Q_byte: .byte 81  # ASCII value for 'Q'
S_byte: .byte 83  # ASCII value for 'S'
D_byte: .byte 68  # ASCII value for 'D'

	.text
	.globl main
main:
	jal 	initCards		# initialize the Cards array

	# just some code to test print the unshuffled Cards array
	# delete it when you like
PrintLoop:
	blez	$t0, Endit
	addiu	$t0, $t0, -1
	lw	$a0, 0($t1)	# get address of next string
	syscall			# and print it
	la	$a0, Newline	# and then print a new line
	syscall
	addiu	$t1, $t1, 4	# get next string pointer address
	j	PrintLoop

Endit:	
	# This is how you get the seed from the system time		
	li	$v0, 30
	syscall
	sw	$a0, Seed
	
	#----- Your main code can go here -----#
Mymain: 
	li $v0, 4 #setting value for syscall
	la $a0, Intro #the statement thats getting printed
	syscall #calling syscall 4 which will print
	
	li $v0, 8 #setting syscall value
    	la $a0, Buffer #setting buffer address aka how big the input can be
    	li $a1, 5 #setting syscall to 5 which grabs input
   	syscall	#calling syscall

	la $a0, Buffer #loading buffer again
	lb $t0, 0($a0) # Load the ASCII value from user input
	
	la $t1, Q_byte #loading Q into a register
	lb $t1, 0($t1) #load the ASCII value for 'Q'

	la $t2, S_byte #loading S input into a register
	lb $t2, 0($t2) #load the ASCII value for 'S'

	la $t3, D_byte #loading D input into a register
	lb $t3, 0($t3)  #load the ASCII value for 'D'


	beq $t1, $t0, End #branch to exit if input is Q
	beq $t2, $t0, Shuffle #branch to shuffle if input is S
	beq $t3, $t0, DrawCard #branch to input to Draw if input is D
	j ErrMsg #jump to error message if none of that is true
ErrMsg:

	li $v0, 4
	la $a0, Error
	syscall
	
	j Mymain

	
End:	
	li	$v0, 10
	syscall

##############################################################################
# Your shuffling subroutine needs to get a random number between 0 and 51.
# Call this random subroutine anytime you need a new random number
##############################################################################
GetRandom52:

	li $t2, 52 #load 52 into $t2
	la $t3, Multiplier #load Multiplier value into $t3
	la $t4, Seed #load Seed value into $t4
	
	mul $t5, $t3, $t4 #multiply seed and multiplier and store new value into $t5
	# lo replaces the old seed
	mflo $t4
	#put the hi of the random number in to $t5
	mfhi $t5
	
	divu $t6, $t5, $t2 #divide the new random number by 52
	
	mfhi $t6 #set the new value to t6
	
	move $s1, $t6 #move the new random value to $s1 making it usable everywhere
	jr $ra #return values
	
##############################################################################
# The shuffle routine should copy the Cards array to your deck array and clear
# the discard array.  You can then shuffle the deck array by looping through
# every item in the deck array and swapping it with another random item. You
# only need to do that once to sufficiently shuffle the deck.  Doing it more
# than three times is a waste of time as you will spend most of your time
# reshuffling what has already been shuffled.
##############################################################################
Shuffle:

    li $t0, 52 #put 52 into $t0

    la $t1, DeckArray #put Deck array into $t1
    la $t2, Cards #put cards into #$t2
    li $t3, 4 #put 4 into $t3

    addi $sp, $sp, 8 #adding space to the stack
    sw $ra, 0($sp) #store $ra

Shuffleloop:
   	# if at the end of the array, end the loop
    	beqz $t0, EndShuffle

   	# decrement the length by 1 each time
   	addi $t0, $t0, -1

   	 # load the DeckArray by using la into the register used for the DeckArray constant
   	la $t4, DeckArray

   	 # call GetRandom52 subroutine
   	jal GetRandom52

	# calculate the random index for swapping
	mul $t5, $s1, $t3
	# move to the next position
	add $t4, $t4, $t3

    j Shuffleloop

EndShuffle:
    la $t1, DeckArray

    sw $t1, Current

    lw $ra, 0($sp)

    addi $sp, $sp, 8

    jr $ra

##############################################################################
# Let the main program keep track of the index of the current draw card.  When
# you reshuffle, the index is 51. Once you draw index 0, the deck is empty and
# you can't draw again until it is re-shuffled.
# 
# When this routine is given the index, it gets the pointer value from the
# deck array and puts it in the discard array at (51 - index).  This takes the
# cards from the bottom of the deck array and fills the discard array from the
# top.  It then returns the pointer value to the caller so the caller can
# print the card string.  Don't forget that the main program, not the sub-
# routine, must update the index when a card is drawn.
##############################################################################
DrawCard:
    	# Load the address of the current card into $t1 (assuming it's a pointer to the card string)
    	la $t1, Current

    	# Check if Current is beyond the end of the array
    	la $t2, DeckArray
    	addi $t3, $t2, 204  # Calculate the end of the array
    	bge $t1, $t3, Return  # If Current is greater than or equal to the end, return

    	# Print the "You drew the card: " message
    	li $v0, 4
    	la $a0, Draw
    	syscall

    	# Load the address of the card string into $a0
    	lw $a0, ($t1)

    	# Print the card string
    	li $v0, 4
    	syscall

    	# Print a new line
    	li $v0, 4
    	la $a0, Newline
    	syscall

    	# Move to the next card in the array
    	addi $t1, $t1, 4

    	# Store the updated Current value
    	sw $t1, Current

Return:
    # Store registerA back into the Current variable
    sw $t1, Current

    # Add four back to $sp
    addi $sp, $sp, 4

    # Return $ra using jr
    jr $ra
##############################################################################
# THIS IS THE CODE TO INITIALIZE THE CARDS AND THE CARD ARRAY.
# IT WORKS, DON'T TOUCH IT.
##############################################################################
	.data 
# First define all the card name strings:
# (byte data should be done last but we'll only lose 3 bytes at worst, so...)
AceOfDiamonds:		.asciiz	"Ace of Diamonds"
TwoOfDiamonds:		.asciiz	"Two of Diamonds"
ThreeOfDiamonds:	.asciiz	"Three of Diamonds"
FourOfDiamonds:		.asciiz	"Four of Diamonds"
FiveOfDiamonds:		.asciiz	"Five of Diamonds"
SixOfDiamonds:		.asciiz	"Six of Diamonds"
SevenOfDiamonds:	.asciiz	"Seven of Diamonds"
EightOfDiamonds:	.asciiz	"Eight of Diamonds"
NineOfDiamonds:		.asciiz	"Nine of Diamonds"
TenOfDiamonds:		.asciiz	"Ten of Diamonds"
JackOfDiamonds:		.asciiz	"Jack of Diamonds"
QueenOfDiamonds:	.asciiz	"Queen of Diamonds"
KingOfDiamonds:		.asciiz	"King of Diamonds"
AceOfClubs:		.asciiz	"Ace of Clubs"
TwoOfClubs:		.asciiz	"Two of Clubs"
ThreeOfClubs:		.asciiz	"Three of Clubs"
FourOfClubs:		.asciiz	"Four of Clubs"
FiveOfClubs:		.asciiz	"Five of Clubs"
SixOfClubs:		.asciiz	"Six of Clubs"
SevenOfClubs:		.asciiz	"Seven of Clubs"
EightOfClubs:		.asciiz	"Eight of Clubs"
NineOfClubs:		.asciiz	"Nine of Clubs"
TenOfClubs:		.asciiz	"Ten of Clubs"
JackOfClubs:		.asciiz	"Jack of Clubs"
QueenOfClubs:		.asciiz	"Queen of Clubs"
KingOfClubs:		.asciiz	"King of Clubs"
AceOfHearts:		.asciiz	"Ace of Hearts"
TwoOfHearts:		.asciiz	"Two of Hearts"
ThreeOfHearts:		.asciiz	"Three of Hearts"
FourOfHearts:		.asciiz	"Four of Hearts"
FiveOfHearts:		.asciiz	"Five of Hearts"
SixOfHearts:		.asciiz	"Six of Hearts"
SevenOfHearts:		.asciiz	"Seven of Hearts"
EightOfHearts:		.asciiz	"Eight of Hearts"
NineOfHearts:		.asciiz	"Nine of Hearts"
TenOfHearts:		.asciiz	"Ten of Hearts"
JackOfHearts:		.asciiz	"Jack of Hearts"
QueenOfHearts:		.asciiz	"Queen of Hearts"
KingOfHearts:		.asciiz	"King of Hearts"
AceOfSpades:		.asciiz	"Ace of Spades"
TwoOfSpades:		.asciiz	"Two of Spades"
ThreeOfSpades:		.asciiz	"Three of Spades"
FourOfSpades:		.asciiz	"Four of Spades"
FiveOfSpades:		.asciiz	"Five of Spades"
SixOfSpades:		.asciiz	"Six of Spades"
SevenOfSpades:		.asciiz	"Seven of Spades"
EightOfSpades:		.asciiz	"Eight of Spades"
NineOfSpades:		.asciiz	"Nine of Spades"
TenOfSpades:		.asciiz	"Ten of Spades"
JackOfSpades:		.asciiz	"Jack of Spades"
QueenOfSpades:		.asciiz	"Queen of Spades"
KingOfSpades:		.asciiz	"King of Spades"
Cards:			.word	0:52			# space for 52 pointers

	.text
# This subroutine should be called by your main routine to initialize the Cards
# array.  It's not pretty but after it runs, it should let you simply do a copy
# of the pointers into your Deck array whenever you need to reinitialize it.
# Call it with jal initCards.  No parameters and no returns
initCards:
	addiu	$sp, $sp, -8	# room to save $t0 and $t1
	sw	$t0, 0($sp)
	sw	$t1, 4($sp)
	la 	$t0, Cards
	la 	$t1, AceOfDiamonds
	sw 	$t1, 0($t0)
	la 	$t1, TwoOfDiamonds
	sw 	$t1, 4($t0)
	la 	$t1, ThreeOfDiamonds
	sw 	$t1, 8($t0)
	la 	$t1, FourOfDiamonds
	sw 	$t1, 12($t0)
	la 	$t1, FiveOfDiamonds
	sw 	$t1, 16($t0)
	la 	$t1, SixOfDiamonds
	sw 	$t1, 20($t0)
	la 	$t1, SevenOfDiamonds
	sw 	$t1, 24($t0)
	la 	$t1, EightOfDiamonds
	sw 	$t1, 28($t0)
	la 	$t1, NineOfDiamonds
	sw 	$t1, 32($t0)
	la 	$t1, TenOfDiamonds
	sw 	$t1, 36($t0)
	la 	$t1, JackOfDiamonds
	sw 	$t1, 40($t0)
	la 	$t1, QueenOfDiamonds
	sw 	$t1, 44($t0)
	la 	$t1, KingOfDiamonds
	sw 	$t1, 48($t0)
	la 	$t1, AceOfClubs
	sw 	$t1, 52($t0)
	la 	$t1, TwoOfClubs
	sw 	$t1, 56($t0)
	la 	$t1, ThreeOfClubs
	sw 	$t1, 60($t0)
	la 	$t1, FourOfClubs
	sw 	$t1, 64($t0)
	la 	$t1, FiveOfClubs
	sw 	$t1, 68($t0)
	la 	$t1, SixOfClubs
	sw 	$t1, 72($t0)
	la 	$t1, SevenOfClubs
	sw 	$t1, 76($t0)
	la 	$t1, EightOfClubs
	sw 	$t1, 80($t0)
	la 	$t1, NineOfClubs
	sw 	$t1, 84($t0)
	la 	$t1, TenOfClubs
	sw 	$t1, 88($t0)
	la 	$t1, JackOfClubs
	sw 	$t1, 92($t0)
	la 	$t1, QueenOfClubs
	sw 	$t1, 96($t0)
	la 	$t1, KingOfClubs
	sw 	$t1, 100($t0)
	la 	$t1, AceOfHearts
	sw 	$t1, 104($t0)
	la 	$t1, TwoOfHearts
	sw 	$t1, 108($t0)
	la 	$t1, ThreeOfHearts
	sw 	$t1, 112($t0)
	la 	$t1, FourOfHearts
	sw 	$t1, 116($t0)
	la 	$t1, FiveOfHearts
	sw 	$t1, 120($t0)
	la 	$t1, SixOfHearts
	sw 	$t1, 124($t0)
	la 	$t1, SevenOfHearts
	sw 	$t1, 128($t0)
	la 	$t1, EightOfHearts
	sw 	$t1, 132($t0)
	la 	$t1, NineOfHearts
	sw 	$t1, 136($t0)
	la 	$t1, TenOfHearts
	sw 	$t1, 140($t0)
	la 	$t1, JackOfHearts
	sw 	$t1, 144($t0)
	la 	$t1, QueenOfHearts
	sw 	$t1, 148($t0)
	la 	$t1, KingOfHearts
	sw 	$t1, 152($t0)
	la 	$t1, AceOfSpades
	sw 	$t1, 156($t0)
	la 	$t1, TwoOfSpades
	sw 	$t1, 160($t0)
	la 	$t1, ThreeOfSpades
	sw 	$t1, 164($t0)
	la 	$t1, FourOfSpades
	sw 	$t1, 168($t0)
	la 	$t1, FiveOfSpades
	sw 	$t1, 172($t0)
	la 	$t1, SixOfSpades
	sw 	$t1, 176($t0)
	la 	$t1, SevenOfSpades
	sw 	$t1, 180($t0)
	la 	$t1, EightOfSpades
	sw 	$t1, 184($t0)
	la 	$t1, NineOfSpades
	sw 	$t1, 188($t0)
	la 	$t1, TenOfSpades
	sw 	$t1, 192($t0)
	la 	$t1, JackOfSpades
	sw 	$t1, 196($t0)
	la 	$t1, QueenOfSpades
	sw 	$t1, 200($t0)
	la 	$t1, KingOfSpades
	sw	$t1, 204($t0)
	lw	$t0, 0($sp)		# get the originals back
	lw	$t1, 4($sp)
	addiu	$sp, $sp, 8
	jr	$ra
