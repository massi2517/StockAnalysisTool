#include "pch.h"
#include "Recognizer_BearishEngulfing.h"

// Sends pattern name and size to base recognizer class
Recognizer_BearishEngulfing::Recognizer_BearishEngulfing() : Recognizer("BearishEngulfing", 2)
{
}

bool Recognizer_BearishEngulfing::Recognize(BindingList<SmartCandlestick^>^ lscs, int CurrentIndex)
{
    if (CurrentIndex == 0) {
        return false; // Cannot have a pattern at the first candle
    }

    // Gets index of candlesticks used for pattern
    SmartCandlestick^ currentCandlestick = lscs[CurrentIndex];
    SmartCandlestick^ previousCandlestick = lscs[CurrentIndex - 1];

    // Ensure the current candle engulfs the previous candle completely and the current is bearish while previous is bullish
    return previousCandlestick->Open < previousCandlestick->Close && // Previous candle is bullish
        currentCandlestick->Open > currentCandlestick->Close && // Current candle is bearish
        currentCandlestick->Open > previousCandlestick->Close && // Current open higher than previous close
        currentCandlestick->Close < previousCandlestick->Open; // Current close lower than previous open
}
