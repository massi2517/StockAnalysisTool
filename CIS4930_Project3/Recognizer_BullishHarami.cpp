#include "pch.h"
#include "Recognizer_BullishHarami.h"

// Sends pattern name and size to base recognizer class
Recognizer_BullishHarami::Recognizer_BullishHarami() : Recognizer("BullishHarami", 2)
{
}

bool Recognizer_BullishHarami::Recognize(BindingList<SmartCandlestick^>^ lscs, int CurrentIndex)
{
    if (CurrentIndex == 0) {
        return false; // Cannot have a pattern at the first candle
    }
    // Gets index of candlesticks used for pattern
    SmartCandlestick^ currentCandlestick = lscs[CurrentIndex];
    SmartCandlestick^ previousCandlestick = lscs[CurrentIndex - 1];

    // Ensure the current candle is entirely within the previous candle and the previous is bearish while current is bullish
    return previousCandlestick->Open < previousCandlestick->Close && // Previous candle is bearish
        currentCandlestick->Open > currentCandlestick->Close && // Current candle is bullish
        currentCandlestick->Open < previousCandlestick->Close && // Current open lower than previous close
        currentCandlestick->Close > previousCandlestick->Open; // Current close higher than previous open
}
