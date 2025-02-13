#include "pch.h"
#include "Recognizer_GravestoneDoji.h"

// Sends pattern name and size to base recognizer class
Recognizer_GravestoneDoji::Recognizer_GravestoneDoji() : Recognizer("GravestoneDoji", 1)
{
}

bool Recognizer_GravestoneDoji::Recognize(BindingList<SmartCandlestick^>^ lscs, int CurrentIndex)
{
	// Gets pattern from smartCandlestick dictionary
	SmartCandlestick^ scs = lscs[CurrentIndex];
	return scs->CheckPattern(PatternName);
}