#include "pch.h"
#include "Recognizer_Marubozu.h"

// Sends pattern name and size to base recognizer class
Recognizer_Marubozu::Recognizer_Marubozu() : Recognizer("Marubozu", 1)
{
}

bool Recognizer_Marubozu::Recognize(BindingList<SmartCandlestick^>^ lscs, int CurrentIndex)
{
	// Gets pattern from smartCandlestick dictionary
	SmartCandlestick^ scs = lscs[CurrentIndex];
	return scs->CheckPattern(PatternName);
}