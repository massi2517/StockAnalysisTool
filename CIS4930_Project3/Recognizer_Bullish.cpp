#include "pch.h"
#include "Recognizer_Bullish.h"

// Sends pattern name and size to base recognizer class
Recognizer_Bullish::Recognizer_Bullish() : Recognizer("Bullish", 1)
{
}

bool Recognizer_Bullish::Recognize(BindingList<SmartCandlestick^>^ lscs, int CurrentIndex)
{
	// Gets pattern from smartCandlestick dictionary
	SmartCandlestick^ scs = lscs[CurrentIndex];
	return scs->CheckPattern(PatternName);
}
