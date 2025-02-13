#include "pch.h"
#include "Recognizer_BearishHarami.h"

// Sends pattern name and size to base recognizer class
Recognizer_BearishHarami::Recognizer_BearishHarami() : Recognizer("BearishHarami", 2)
{
}

bool Recognizer_BearishHarami::Recognize(BindingList<SmartCandlestick^>^ lscs, int CurrentIndex)
{
    if (CurrentIndex == 0) {
        return false; // Cannot have a pattern at the first candle
    }
    // Gets index of candlesticks used for pattern
    SmartCandlestick^ currentCandlestick = lscs[CurrentIndex];
    SmartCandlestick^ previousCandlestick = lscs[CurrentIndex - 1];

    // Ensure the current candle is entirely within the previous candle and the previous is bullish while current is bearish
    return previousCandlestick->Open > previousCandlestick->Close && // Previous candle is bullish
        currentCandlestick->Open < currentCandlestick->Close && // Current candle is bearish
        currentCandlestick->Open > previousCandlestick->Open && // Current open higher than previous open
        currentCandlestick->Close < previousCandlestick->Close; // Current close lower than previous close
}

