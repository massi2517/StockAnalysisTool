#include "pch.h"
#include "Recognizer_Peak.h"

// Sends pattern name and size to base recognizer class
Recognizer_Peak::Recognizer_Peak() : Recognizer("Peak", 3)
{
}

bool Recognizer_Peak::Recognize(BindingList<SmartCandlestick^>^ lscs, int CurrentIndex)
{

	SmartCandlestick^ currentCandlestick = lscs[CurrentIndex];
	// Makes sure it starts on the second candlestick since it is a 3 candlestick pattern
	if (CurrentIndex == 0)
	{
		return false;
	}
	// Get the prvious candlestick from the current index
	SmartCandlestick^ previousCandlestick = lscs[CurrentIndex - 1];
	// Checks if on the last candlestick
	if (CurrentIndex == lscs->Count - 1)
	{
		return false;
	}
	// Get the next candlestick from the current index
	SmartCandlestick^ nextCandlestick = lscs[CurrentIndex + 1];

	// Checks if current candlestick has the largets high value compared to previous and next candlesticks
	return currentCandlestick->High > previousCandlestick->High && currentCandlestick->High > nextCandlestick->High;

}