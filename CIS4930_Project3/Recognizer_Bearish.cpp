#include "pch.h"
#include "Recognizer_Bearish.h"

// Sends pattern name and size to base recognizer class
Recognizer_Bearish::Recognizer_Bearish() : Recognizer("Bearish", 1)
{
}

bool Recognizer_Bearish::Recognize(BindingList<SmartCandlestick^>^ lscs, int CurrentIndex)
{
	// Gets pattern from smartCandlestick dictionary
	SmartCandlestick^ scs = lscs[CurrentIndex];
	return scs->CheckPattern(PatternName);
}