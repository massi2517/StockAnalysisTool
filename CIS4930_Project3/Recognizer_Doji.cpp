#include "pch.h"
#include "Recognizer_Doji.h"

// Sends pattern name and size to base recognizer class
Recognizer_Doji::Recognizer_Doji() : Recognizer("Doji", 1)
{
}

bool Recognizer_Doji::Recognize(BindingList<SmartCandlestick^>^ lscs, int CurrentIndex)
{
	// Gets pattern from smartCandlestick dictionary
	SmartCandlestick^ scs = lscs[CurrentIndex];
	return scs->CheckPattern(PatternName);
}