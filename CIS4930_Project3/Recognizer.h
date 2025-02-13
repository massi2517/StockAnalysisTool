#pragma once

#include "SmartCandlestick.h"
#include <list>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::ComponentModel; // Include for BindingList

/// <summary>
/// Abstract base class for pattern recognizers.
/// </summary>
public ref class Recognizer abstract
{
public:
    // This property represents the name of pattern recognized by the recognizer
    property String^ PatternName;

    // This property represents the length of the pattern recognized by the recognizer 
    property int PatternLength;

    /// <summary>
    /// Constructor for the Recognizer class which takes pattern name and pattern length as parameters
    /// </summary>
    /// <param name="pn">The name of the pattern this recognizer will identify.</param>
    /// <param name="pl">The length of the pattern, in terms of number of candlesticks involved.</param>
    Recognizer(String^ pn, int pl);

    /// <summary>
    /// Attempts to recognize a pattern within a list of SmartCandlesticks at a specified index.
    /// </summary>
    /// <param name="lscs">The list of SmartCandlesticks to analyze.</param>
    /// <param name="index">The index of the target SmartCandlestick within the list.</param>
    /// <returns>true if the pattern is recognized; otherwise, false.</returns>
    virtual bool Recognize(BindingList<SmartCandlestick^>^ lscs, int index) = 0;

    /// <summary>
    /// Recognizes patterns for all candlesticks in the list.
    /// </summary>
    /// <param name="lscs">The list of SmartCandlesticks to analyze.</param>
    void RecognizeAll(BindingList<SmartCandlestick^>^ lscs);
};
