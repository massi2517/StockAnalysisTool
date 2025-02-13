#include "pch.h"
#include "smartCandlestick.h"

/// <summary>
/// Extends the Candlestick class by adding functionality to compute various
/// attributes such as the candlestick's body range, top and bottom prices, and tail lengths.
/// It also evaluates various candlestick patterns to support technical analysis of stock data.
/// </summary>

/// Initializes a new instance of the SmartCandlestick class using a CSV-formatted string.
SmartCandlestick::SmartCandlestick(String^ csvLine) : Candlestick(csvLine) {}


// Getter for the Range property; calculates the difference between the high and low price.
double SmartCandlestick::Range::get() {
    return High - Low;
}
// Getter for the BodyRange property; calculates the absolute difference between open and close price.
double SmartCandlestick::BodyRange::get() {
    return Math::Abs(Open - Close);
}
// Getter for the TopPrice property; determines the maximum of the open and close prices.
double SmartCandlestick::TopPrice::get() {
    return Math::Max(Open, Close);
}
// Getter for the BottomPrice property; determines the minimum of the open and close prices.
double SmartCandlestick::BottomPrice::get() {
    return Math::Min(Open, Close);
}
// Getter for the UpperTail property; calculates the length of the upper tail.
double SmartCandlestick::UpperTail::get() {
    return High - TopPrice;
}
// Getter for the LowerTail property; calculates the length of the lower tail.
double SmartCandlestick::LowerTail::get() {
    return BottomPrice - Low;
}

// Returns a dictionary of boolean values indicating the presence of specific candlestick patterns.
Dictionary<String^, bool>^ SmartCandlestick::GetCandlestickPatterns() {
    Dictionary<String^, bool>^ patterns = gcnew Dictionary<String^, bool>();  // Initialize a new dictionary to store pattern flags.

    // Add pattern "Bullish" to the dictionary; true if close price is higher than open.
    patterns->Add("Bullish", Close > Open);
    // Add pattern "Bearish" to the dictionary; true if open price is higher than close.
    patterns->Add("Bearish", Open > Close);
    // Add pattern "Neutral" to the dictionary; true if open price equals close price.
    patterns->Add("Neutral", Open == Close);
    // Add pattern "Marubozu" to the dictionary; true if there are no tails and the body is significant.
    patterns->Add("Marubozu", UpperTail == 0 && LowerTail == 0 && BodyRange > 0);
    // Add pattern "Hammer" to the dictionary; criteria are specific ratios of body to range and tail lengths.
    patterns->Add("Hammer", BodyRange / Range < 0.3 && LowerTail / BodyRange > 2 && UpperTail / Range < 0.1);
    // Add pattern "Doji" to the dictionary; true if the body is very small relative to the total range.
    patterns->Add("Doji", IsDoji());
    // Add pattern "Dragonfly Doji" to the dictionary; a Doji where the lower tail is significantly longer.
    patterns->Add("DragonflyDoji", IsDoji() && LowerTail > UpperTail && TopPrice == High);
    // Add pattern "Gravestone Doji" to the dictionary; a Doji where the upper tail is significantly longer.
    patterns->Add("GravestoneDoji", IsDoji() && UpperTail > LowerTail && BottomPrice == Low);

    return patterns;  // Return the populated dictionary of patterns.
}

// Checks if the candlestick qualifies as a Doji, which indicates market indecision.
bool SmartCandlestick::IsDoji() {
    return BodyRange / Range < 0.05;  // Returns true if the body range is less than 5% of the total range.
}

bool SmartCandlestick::CheckPattern(String^ patternName) {
    // Access the dictionary to check for the presence of the pattern
    Dictionary<String^, bool>^ patterns = GetCandlestickPatterns();
    bool hasPattern = false;

    // Try to get the value associated with the pattern name
    if (patterns->TryGetValue(patternName, hasPattern)) {
        return hasPattern;
    }
    return false; // Return false if the pattern name is not found
}