#pragma once

#include "candlestick.h"
#include <map>

/// <summary>
/// Extends the Candlestick class by adding functionality to compute various
/// attributes such as the candlestick's body range, top and bottom prices, and tail lengths.
/// It also evaluates various candlestick patterns to support technical analysis of stock data.
/// </summary>
public ref class SmartCandlestick : public Candlestick
{
public:
    // Constructor that takes a CSV line and initializes the base Candlestick class with it
    SmartCandlestick(String^ csvLine);

    // Property to get the range of the candlestick (difference between high and low price)
    property double Range { double get(); }
    // Property to get the body range of the candlestick (absolute difference between open and close price)
    property double BodyRange { double get(); }
    // Property to get the top price of the candlestick body (maximum of open and close price)
    property double TopPrice { double get(); }
    // Property to get the bottom price of the candlestick body (minimum of open and close price)
    property double BottomPrice { double get(); }
    // Property to get the upper tail length (difference between high and the top price of the body)
    property double UpperTail { double get(); }
    // Property to get the lower tail length (difference between the bottom price of the body and low)
    property double LowerTail { double get(); }

    // Method to get a dictionary of candlestick patterns and whether they are present
    Dictionary<String^, bool>^ GetCandlestickPatterns();

    // Method to check if a specific pattern is present
    bool CheckPattern(String^ patternName);

private:
    // Helper method to determine if a candlestick qualifies as a Doji
    bool IsDoji();
};