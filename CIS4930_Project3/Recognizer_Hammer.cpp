#include "pch.h"
#include "Recognizer_Hammer.h"

// Sends pattern name and size to base recognizer class
Recognizer_Hammer::Recognizer_Hammer() : Recognizer("Hammer", 1)
{
}

bool Recognizer_Hammer::Recognize(BindingList<SmartCandlestick^>^ lscs, int CurrentIndex)
{
	// Gets pattern from smartCandlestick dictionary
	SmartCandlestick^ scs = lscs[CurrentIndex];
	return scs->CheckPattern(PatternName);
}