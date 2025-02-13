#pragma once
using namespace System;
using namespace System::Globalization;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;
#include "Recognizer.h"

public ref class Recognizer_GravestoneDoji : Recognizer
{
public:
	Recognizer_GravestoneDoji();

	bool Recognize(BindingList<SmartCandlestick^>^ lscs, int CurrentIndex) override;
};
