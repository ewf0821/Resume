function guessingGame(){
    const randomNum = Math.floor(Math.random() * 100) + 1;
    let max = 100;
    let min = 1;
    let attempts = 0;
    let guess = prompt("Guess a number between " + min + " and " + max + ":");

    while(guess != randomNum){
        attempts++;
        if(isNaN(guess) || guess < min || guess > max)
        {
            guess = prompt("WRONG, PICK A VALID NUMBER Attempts: " + attempts );
        } 
        else if (guess < randomNum)
        {
            guess = prompt("WRONG, NUMBER IS HIGHER Attempts: " + attempts );
        }
        else if(guess > randomNum)
        {
            guess = prompt("WRONG, NUMBER IS LOWER Attempts: " + attempts );
        }      
    }   
    let choice = prompt("yippee you won PLAY AGAIN? Y N");

    if(choice == "Y"){
        guessingGame();
    }
    else if(choice == "N"){
        prompt("Bye");
    }
}
guessingGame();  