#pragma once 
//Open readable file for anyone wnating to use the candlestick class

// Using directives to include namespaces from the .NET Framework
using namespace System;
using namespace System::Globalization;
using namespace System::Collections::Generic;
using namespace System::IO;

/// <summary>
/// Declares structure of candlestick class
/// </summary>
public ref class Candlestick
{
public:
    property DateTime Date; // Public property to store the date of the candlestick.
    property double Open; // Public property to store the opening price of the asset.
    property double High; // Public property to store the highest price of the asset during the trading period.
    property double Low; // Public property to store the lowest price of the asset during the trading period.
    property double Close; // Public property to store the closing price of the asset.
    property double AdjClose; // Public property to store the adjusted closing price of the asset, accounting for any corporate actions.
    property Int64 Volume; // Public property to store the trading volume of the asset.

    // Constructor that initializes a new instance of the Candlestick class using a string representing data from a CSV line.
    Candlestick(String^ csvLine);
};