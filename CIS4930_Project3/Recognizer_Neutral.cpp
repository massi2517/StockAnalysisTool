#include "pch.h"
#include "Recognizer_Neutral.h"

// Sends pattern name and size to base recognizer class
Recognizer_Neutral::Recognizer_Neutral() : Recognizer("Neutral", 1)
{
}

bool Recognizer_Neutral::Recognize(BindingList<SmartCandlestick^>^ lscs, int CurrentIndex)
{
	// Gets pattern from smartCandlestick dictionary
	SmartCandlestick^ scs = lscs[CurrentIndex];
	return scs->CheckPattern(PatternName);
}