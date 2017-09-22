/* This is the consol executable, that makes use of the BullCow class.
THis acts as the view of the MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Changing type names to be more inline with Epic coding standard 
using FText = std::string;

// Function prototypes declarations
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSumamry();

// instantiate a new game
FBullCowGame BCGame;	

/* The entry point for our application.*/
int32 main()
{	
	bool KeepPlaying = false;
	do {
		PrintIntro();
		PlayGame();
		KeepPlaying = AskToPlayAgain();
		// Reset the game if user chooses to keep playing
		if (KeepPlaying) {
			BCGame.Reset();
		}
	} while (KeepPlaying);
	// Tell user what hidden word was
	std::cout << "The hidden word was " << "\"" <<  BCGame.GetHiddenWord() << "\"." << std::endl;
	return 0;
}
/* PlayGame is a void function with no input parameters. It's main function is
to begin the game-play loop and give information to the user about their inputs
via BCGame.SunmitValidGuess(). At the end of game a summary of the game is 
then printed to the user.*/
void PlayGame()
{	
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "You have " << MaxTries << " tries to guess." << std::endl;
	// loop asking for guess while the game is NOT wone
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText CurrentGuess = GetValidGuess();

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitVaidGuess(CurrentGuess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	
	PrintGameSumamry();
	return;
}

/* PrintGameSummary is a void function with no input parameters. This functions
simply prints a summary of the game depending on if the game was won or no.*/
void PrintGameSumamry() 
{
	if (BCGame.IsGameWon()) {
		std::cout << "Great job, you won the game! The word was" << BCGame.GetHiddenWord() << std::endl;
	} else {
		std::cout << "You lose. Better luck next time.\n";
	}
}

/* GetValidGuess() returns a FText (std::string) and has no input parameters.
This function is meant to check if user input is a valid guess to the hidden word
and give useful feedback on how to input a valid word. */
FText GetValidGuess()
{
	// Initialize Status as invaid to enter the do-while loop
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		// get a guess from the player
		std::cout << "Try " << BCGame.GetCurrentTry() << " out of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::cin >> Guess;
		// Check Validity of guess
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word with all lowercase letters.\n";
			break;
		default:
			// assuming the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors

	return Guess;
}

/*AskToPlayAgain() returns a boolean and has no input parameters.
This functions asks if the player would like to continue playing with a different
word and returns the response. */
bool AskToPlayAgain()
{
	std::cout << "Do you wish to play again with a different hidden word (y/n)?\n";
	FText Response = "";
	std::cin >> Response;
	return (Response[0] == 'Y' || Response[0] == 'y');
}

/* PrintIntro() returns void and has no input parameters.
This function introduces user to the game and tells user how many
letters are in the hidden word.*/
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

