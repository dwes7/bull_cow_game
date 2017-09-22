#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"

/* BullCowGame() is the constuctor. This function calls Reset which does the
most of the initialization*/
FBullCowGame::FBullCowGame() { 
	Difficulty = "easy";
	Reset();
}

/*Desctuctor*/
FBullCowGame::~FBullCowGame()
{
}

/*SubmitValidGuess() returns the FBullCowCont struct and asks for an FString as input.
This function contains the alogorithm that calculates the number of cows and bulls in 
the users guess and checks if the game is won.*/
FBullCowCount FBullCowGame::SubmitVaidGuess(FString Guess)
{
	MyCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount;

	// loop through all leters in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	for (int32 i = 0; i < WordLength; i++) {
		// compare letters against the guess word
		for (int32 j = 0; j < WordLength; j++) {
			// if they match then
			if (MyHiddenWord[i] == Guess[j]) {
				// if they're in the same place
				if (i == j) {
					// increment bulls
					BullCowCount.Bulls++;
				} else {
					// increment cows if not
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	} else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

/*ChoosDifficulty() is a void function and has no input parameters.
This function asks for user input on what difficulty they would
like to play and then updates the Difficulty member variable.*/
void FBullCowGame::ChooseDifficulty()
{
	std::cout << "Choose your difficulty (easy/medium/hard).\n";
	FString Choice = "";
	std::cin >> Choice;
	if (Choice == "easy") {
		Difficulty = "easy";
	}
	else if (Choice == "medium") {
		Difficulty = "medium";
	}
	else if (Choice == "hard") {
		Difficulty = "hard";
	}
	else {
		Difficulty = "easy";
	}
}

/*Reset() is a void function with no input parameters. This function
Initializes the game, and is recalled if the user would like to play again*/
void FBullCowGame::Reset()
{
	ChooseDifficulty();
	MyHiddenWord = GenerateHiddenWord();
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

/*IsIsogram() asks for an FString and returns a boolean. This function checks
to see if a word is actually an isogram and returns. If the word is indeed and isogram
the function returns true, otherwise, it returns false.*/
bool FBullCowGame::IsIsogram(FString Word) const
{
	// treate 0 or 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	// set up our map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false; // we do NOT have an isogram 
		} else {
			LetterSeen[Letter] = true;
		}
	}
	return true; // for example in cas where "/0" is entered
}

/* IsLowerCase() requires an FString as an input parameter and returns a boolean.
This function checks to see if a string is all lowercase and returns true if it is
and false if it is not.*/
bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

/*GenrateHiddenWord() Returns an FString and requires to input parameters.
Depending on the difficulty selected by the user, This function will randomly select
a word from one of three txt files. It will the return that word*/
FString FBullCowGame::GenerateHiddenWord()
{
// open file and get the total line numbers for random number generator later
	std::ifstream Isograms;
	int32 LinesCount = 0; // This is how many lines are in easy_isogram.txt
							 // TODO. Make this so it can read in any size text file.
	if (Difficulty == "hard") {
		Isograms.open("hard_isogram.txt");
		LinesCount = 82;
	} else if (Difficulty == "medium") {
		Isograms.open("medium_isogram.txt");
		LinesCount = 70;
	} else {
		Isograms.open("easy_isogram.txt");
		LinesCount = 3119;
	}
	if (Isograms.fail()) {
		std::cout << "Error opening file.\n";
	}
	if (Isograms.good()) {
		FString Word = "";
		int32 SecretNumber = 0;
		
		FString Line;
		// assign the line count to the random number max
		int32 RandNumberMax = LinesCount;
		// Generate random seed
		srand(time(NULL));
		// Generate a random bumber from 1 - RandNmberMax
		SecretNumber = rand() % RandNumberMax + 1;
		// Use secret number to get isogram on that line number
		for (int32 i = 0; i < SecretNumber; i++) {
			Isograms >> Word;
		}

		Isograms.close();
		return Word;
	}
}

/*GetMaxTries() returns an int32 */
int32 FBullCowGame::GetMaxTries() const {

	TMap<int32, int32> WordLengthToMaxTries{ { 4, 10 },{ 5,12 },{ 6, 15 },{ 7,19 },
												{ 8, 24 },{ 9, 30 },{ 10, 30 },{ 11, 30 },
												{ 12, 30 },{ 13, 30 },{ 14, 30 },{ 15, 30 } };

	return WordLengthToMaxTries[MyHiddenWord.length()];

}

int32 FBullCowGame::GetBulls() const { return 0; }

int32 FBullCowGame::GetCows() const { return 0; }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetRemainingTries() const { return 0; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) 
{ 
	// if the guess isn't an isogram
	if (!IsIsogram(Guess)) { // TODO write function
		// return an error
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowerCase(Guess)) { // TODO write function if the guess isn't all lowercase
		//return an error
		return EGuessStatus::Not_Lowercase;
	} else if (Guess.length() != GetHiddenWordLength()) { // if guess is wrong length
		// return an error
		return EGuessStatus::Wrong_Length;
	} else {
		return EGuessStatus::OK; // TODO make actual error 
	}
}

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }
