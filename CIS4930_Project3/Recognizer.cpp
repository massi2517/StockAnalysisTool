#include "pch.h"
#include "Recognizer.h"

/// <summary>
/// Constructor for the Recognizer class.
/// </summary>
/// <param name="pn">The name of the pattern this recognizer will identify.</param>
/// <param name="pl">The length of the pattern, in terms of number of candlesticks involved.</param>
Recognizer::Recognizer(String^ pn, int pl) {
    // Assign the provided pattern name to the PatternName member variable.
    PatternName = pn;
    // Assign the provided pattern length to the PatternLength member variable.
    PatternLength = pl;
}

/// <summary>
/// Recognizes patterns for all candlesticks in the list.
/// </summary>
/// <param name="lscs">The list of SmartCandlesticks to analyze.</param>
void Recognizer::RecognizeAll(BindingList<SmartCandlestick^>^ lscs) {
    for (int index = 0; index < lscs->Count; ++index) {
        Recognize(lscs, index);
    }
}
