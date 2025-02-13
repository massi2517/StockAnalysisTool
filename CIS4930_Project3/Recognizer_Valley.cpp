#include "pch.h"
#include "Recognizer_Valley.h"

// Sends pattern name and size to base recognizer class
Recognizer_Valley::Recognizer_Valley() : Recognizer("Valley", 3)
{
}

bool Recognizer_Valley::Recognize(BindingList<SmartCandlestick^>^ lscs, int CurrentIndex)
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
	// Checks if current candlestick has the smallest low value compared to previous and next candlestick
	return currentCandlestick->Low < previousCandlestick->Low && currentCandlestick->Low < nextCandlestick->Low;

}