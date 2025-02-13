#include "pch.h"
#include "candlestick.h"

/// <summary>
/// Initializes a new instance of the Candlestick class using a CSV-formatted string.
/// </summary>
/// <param name="csvLine">A string containing CSV-formatted candlestick data.</param>
Candlestick::Candlestick(String^ csvLine)
{
    array<wchar_t>^ separators = { L',', L' ' }; // Defines an array of characters to be used as delimiters in the CSV data (comma and space).

    // Splits the input string into an array of substrings based on the specified separators. Empty entries are removed.
    array<String^>^ fields = csvLine->Split(separators, StringSplitOptions::RemoveEmptyEntries);

    // Parses the date from the first field (at index 0) using a specified format and the invariant culture to avoid locale-specific interpretations.
    Date = DateTime::ParseExact(fields[0], "M/d/yyyy", CultureInfo::InvariantCulture);
    // Parses the open price from the second field (at index 1) as a double, using the invariant culture.
    Open = Double::Parse(fields[1], CultureInfo::InvariantCulture);
    // Parses the high price from the third field (at index 2) as a double, using the invariant culture.
    High = Double::Parse(fields[2], CultureInfo::InvariantCulture);
    // Parses the low price from the fourth field (at index 3) as a double, using the invariant culture.
    Low = Double::Parse(fields[3], CultureInfo::InvariantCulture);
    // Parses the close price from the fifth field (at index 4) as a double, using the invariant culture.
    Close = Double::Parse(fields[4], CultureInfo::InvariantCulture);
    // Parses the adjusted close price from the sixth field (at index 5) as a double, using the invariant culture.
    AdjClose = Double::Parse(fields[5], CultureInfo::InvariantCulture);
    // Parses the volume from the seventh field (at index 6) as a 64-bit integer.
    Volume = Int64::Parse(fields[6]);
}