/* The game logic (no view or user interface) game logic*/
#pragma once
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <time.h>
#include <limits>
#define TMap std::map

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame();
	~FBullCowGame();
	
	int32 GetMaxTries() const;
	int32 GetBulls() const;
	int32 GetCows() const;
	int32 GetCurrentTry() const;
	int32 GetRemainingTries() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString);
	FBullCowCount SubmitVaidGuess(FString);


	void Reset(); 


// Please try and ignore this and focus
private:

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
	void ChooseDifficulty();
	int32 MyCurrentTry;
	FString MyHiddenWord;
	FString Difficulty;
	FString GenerateHiddenWord();
	bool bGameIsWon;
	


};

