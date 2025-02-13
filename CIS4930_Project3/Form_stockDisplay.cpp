

#include "pch.h"
#include "Form_stockDisplay.h"
#include "smartCandlestick.h"

// Define the namespace for this portion of the C++/CLI project
namespace CppCLRWinFormsProject
{
    // Use the namespace for charting to simplify code and improve readability
    using namespace System::Windows::Forms::DataVisualization::Charting;

    /// <summary>
    /// Reads candlestick data from a CSV file and creates a list of SmartCandlestick objects.
    /// Each line in the CSV file represents a candlestick with its data, which is converted into a SmartCandlestick object.
    /// </summary>
    /// <param name="filePath">Path to the CSV file containing the candlestick data.</param>
    /// <returns>List of SmartCandlestick objects parsed from the CSV file.</returns>
    List<SmartCandlestick^>^ Form_stockDisplay::ReadDataFromFile(String^ filePath)
    {
        // Initialize a list of SmartCandlestick objects with an initial capacity of 1024 elements
        List<SmartCandlestick^>^ listOfSmartCandlesticks = gcnew List<SmartCandlestick^>(1024);
        // Clear the list to ensure it's empty before filling it with data
        listOfSmartCandlesticks->Clear();
        // Check if the specified file exists before attempting to read from it
        if (File::Exists(filePath))
        {
            // Open the file for reading
            StreamReader^ reader = gcnew StreamReader(filePath);
            // Read and discard the first line assuming it's a header
            String^ header = reader->ReadLine();
            String^ line;
            // Continue reading lines until the end of the file is reached
            while ((line = reader->ReadLine()) != nullptr) {
                // For each line, create a new SmartCandlestick object and add it to the list
                SmartCandlestick^ smartCandlestick = gcnew SmartCandlestick(line);
                listOfSmartCandlesticks->Add(smartCandlestick);
            }
            // Close the StreamReader to free up resources
            reader->Close();
        }
        else {
            // Output a message to the console if the file was not found
            Console::WriteLine("CSV file not found.");
        }
        // Return the populated list of SmartCandlestick objects
        return listOfSmartCandlesticks;
    }

    /// <summary>
    /// Filters the provided list of SmartCandlestick objects based on a specified date range,
    /// including only those candlesticks whose date falls within the range.
    /// </summary>
    /// <param name="allSmartCandlesticks">The complete list of SmartCandlestick objects to filter.</param>
    /// <param name="startDate">The starting date of the filtering range.</param>
    /// <param name="endDate">The ending date of the filtering range.</param>
    /// <returns>A filtered list of SmartCandlestick objects within the specified date range.</returns>
    List<SmartCandlestick^>^ Form_stockDisplay::filterCandlesticks(List<SmartCandlestick^>^ allSmartCandlesticks, DateTime startDate, DateTime endDate)
    {
        // Initialize a new list to hold the filtered SmartCandlestick objects
        List<SmartCandlestick^>^ chosenSmartCandlesticks = gcnew List<SmartCandlestick^>(allSmartCandlesticks->Count);
        // Iterate through all SmartCandlesticks to find those within the date range
        for (int i = 0; i < allSmartCandlesticks->Count; ++i) {
            SmartCandlestick^ scs = allSmartCandlesticks[i];
            // If the SmartCandlestick's date is within the range, add it to the filtered list
            if (scs->Date >= startDate && scs->Date <= endDate) {
                chosenSmartCandlesticks->Add(scs);
            }
        }
        // Return the list of SmartCandlesticks that fall within the specified date range
        return chosenSmartCandlesticks;
    }

    /// <summary>
    /// Updates the display of the candlestick data based on the selected date range from the date time pickers, filtering the candlesticks to only those within the range, and then displaying the filtered data in both the data grid view and the chart.
    /// </summary>
    void Form_stockDisplay::updateDisplay()
    {
        // Retrieve the start date from the date time picker control
        DateTime startDate = dateTimePicker_start->Value;
        // Retrieve the end date from the date time picker control
        DateTime endDate = dateTimePicker_end->Value;
        // Filter the list of candlesticks based on the selected date range
        List<SmartCandlestick^>^ filteredSmartCandlesticks = filterCandlesticks(listOfSmartCandlesticks, startDate, endDate);
        // Create a new binding list with the filtered candlesticks for data binding
        boundSmartCandlesticks = gcnew BindingList<SmartCandlestick^>(filteredSmartCandlesticks);
        // Bind the filtered candlesticks list to the chart as its data source
        chart_stockDisplay->DataSource = boundSmartCandlesticks;
        // Bind the data to the chart, refreshing the display
        chart_stockDisplay->DataBind();
        // Clear any existing annotations on the chart
        chart_stockDisplay->Annotations->Clear();
    }


    /// <summary>
    /// Normalizes the displayed stock data by adjusting the Y-axis limits of the OHLC (Open, High, Low, Close) ChartArea.
    /// This is achieved by calculating the maximum high and minimum low values across all candlesticks, 
    /// adding a padding to these values, and then setting the padded values as the new Y-axis limits.
    /// </summary>
    void Form_stockDisplay::normalize() {
        // Check if the collection of candlesticks is empty. If so, exit the function.
        if (boundSmartCandlesticks->Count == 0) return; // Ensure there are candlesticks to process

        // Initialize variables to store the maximum high and minimum low values found in the candlesticks.
        double maxHigh = Double::MinValue; // Initialize with the smallest possible value
        double minLow = Double::MaxValue; // Initialize with the largest possible value

        // Iterate over each candlestick in the collection to find the maximum high and minimum low values.
        for each (SmartCandlestick ^ candlestick in boundSmartCandlesticks) {
            // If the current candlestick's high is greater than the current maxHigh, update maxHigh.
            if (candlestick->High > maxHigh) maxHigh = candlestick->High;
            // If the current candlestick's low is less than the current minLow, update minLow.
            if (candlestick->Low < minLow) minLow = candlestick->Low;
        }

        // Calculate the range between the maximum high and minimum low.
        double range = maxHigh - minLow;
        // Calculate a padding value as 2% of the range.
        double padding = range * 0.02; // 2% padding

        // Add the padding to the maximum high value and subtract it from the minimum low value.
        maxHigh += padding;
        minLow -= padding;

        // Set the adjusted maxHigh and minLow as the new Y-axis limits for the OHLC ChartArea.
        chart_stockDisplay->ChartAreas["ChartArea_OHLC"]->AxisY->Maximum = maxHigh;
        chart_stockDisplay->ChartAreas["ChartArea_OHLC"]->AxisY->Minimum = minLow;
    }


    /// <summary>
    /// Annotates the chart by placing a rectangular annotation around candlesticks that match a given pattern name.
    /// </summary>
    /// <param name="patternName">The name of the candlestick pattern to annotate on the chart.</param>
    // Modified method to annotate the chart based on the selected pattern
    void Form_stockDisplay::AnnotatePatternOnChart(String^ patternName) {
        // Remove all previous annotations from the chart to start fresh
        chart_stockDisplay->Annotations->Clear();

        // If no candlestick data is available, log to console and exit the function
        if (boundSmartCandlesticks == nullptr || boundSmartCandlesticks->Count == 0) {
            Console::WriteLine("No candlesticks are available to annotate.");
            return;
        }

        // If recognizers for patterns have not been initialized, initialize them
        if (Dictionary_Recognizers == nullptr || Dictionary_Recognizers->Count == 0) {
            InitializeRecognizers();
        }

        // Declare a pointer for the recognizer related to the requested pattern
        Recognizer^ selectedRecognizer = nullptr;
        // Check if the pattern name exists in the dictionary and retrieve the corresponding recognizer
        if (Dictionary_Recognizers->TryGetValue(patternName, selectedRecognizer)) {
            // Iterate through all the candlesticks to apply the recognizer
            for (int i = 0; i < boundSmartCandlesticks->Count; i++) {
                // If the pattern is recognized at the current index
                if (selectedRecognizer->Recognize(boundSmartCandlesticks, i)) {
                    int startIndex = i;
                    int count = 1;

                    // Adjust the start index and count based on the specific pattern to annotate
                    if (patternName == "BearishEngulfing" || patternName == "BullishEngulfing" ||
                        patternName == "BearishHarami" || patternName == "BullishHarami") {
                        startIndex = i - 1;  // Start from the previous candlestick
                        count = 2;           // Include the current and previous candlesticks
                    }
                    else if (patternName == "Peak" || patternName == "Valley") {
                        startIndex = i - 1;  // Start from one candlestick before the current
                        count = 3;           // Include the current, previous, and the next candlestick
                    }

                    // Ensure the selected range does not exceed the bounds of the candlestick data
                    if (startIndex < 0 || startIndex + count > boundSmartCandlesticks->Count) continue;

                    double top = Double::MinValue;
                    double bottom = Double::MaxValue;

                    // Determine the highest and lowest points within the selected range
                    for (int j = startIndex; j < startIndex + count; j++) {
                        SmartCandlestick^ candle = boundSmartCandlesticks[j];
                        top = Math::Max(top, candle->High);     // Find the maximum high value
                        bottom = Math::Min(bottom, candle->Low); // Find the minimum low value
                    }

                    // Create a new rectangle annotation to visually represent the pattern on the chart
                    RectangleAnnotation^ rect = gcnew RectangleAnnotation();
                    rect->AnchorDataPoint = chart_stockDisplay->Series["Series_OHLC"]->Points[startIndex];
                    rect->AxisX = chart_stockDisplay->ChartAreas[0]->AxisX;
                    rect->AxisY = chart_stockDisplay->ChartAreas[0]->AxisY;
                    rect->X = startIndex + 0.5;               // Position the rectangle centrally over the candlestick
                    rect->Y = top;                            // Set the top boundary of the rectangle
                    rect->Height = bottom - top;              // Set the height of the rectangle
                    rect->Width = count;                      // Set the width of the rectangle covering the required candlesticks
                    rect->LineColor = Color::Black;           // Set the border color of the rectangle
                    rect->LineWidth = 2;                      // Set the border thickness
                    rect->BackColor = Color::Transparent;     // Set the background color of the rectangle
                    rect->IsSizeAlwaysRelative = false;       // Ensure the size is fixed and not relative to the chart

                    // Add the newly created rectangle to the chart's annotations collection
                    chart_stockDisplay->Annotations->Add(rect);
                }
            }
        }
    }


    /// <summary>
    /// Initializes the stock pattern recognizers and adds them to a dictionary for future use.
    /// Each type of stock pattern recognizer is instantiated and added to the Dictionary_Recognizers dictionary,
    /// which is indexed by the pattern name. This setup allows for quick retrieval and usage of different stock patterns
    /// during analysis.    
    /// </summary>
    void Form_stockDisplay::InitializeRecognizers() {
        // Initialize the dictionary to store pattern recognizers
        Dictionary_Recognizers = gcnew Dictionary<String^, Recognizer^>();
        // Instantiate and add each recognizer to the dictionary
        Recognizer^ recognizer;
        // Bullish Pattern

        recognizer = gcnew Recognizer_Bullish();
        Dictionary_Recognizers->Add(recognizer->PatternName, recognizer);
        // Bearish Pattern
        recognizer = gcnew Recognizer_Bearish();
        Dictionary_Recognizers->Add(recognizer->PatternName, recognizer);
        // Neutral Pattern
        recognizer = gcnew Recognizer_Neutral();
        Dictionary_Recognizers->Add(recognizer->PatternName, recognizer);
        // Doji Pattern
        recognizer = gcnew Recognizer_Doji();
        Dictionary_Recognizers->Add(recognizer->PatternName, recognizer);
        // DragonFly Doji Pattern
        recognizer = gcnew Recognizer_DragonflyDoji();
        Dictionary_Recognizers->Add(recognizer->PatternName, recognizer);
        // Gravestone Doji Pattern
        recognizer = gcnew Recognizer_GravestoneDoji();
        Dictionary_Recognizers->Add(recognizer->PatternName, recognizer);
        // Marubozu Pattern
        recognizer = gcnew Recognizer_Marubozu();
        Dictionary_Recognizers->Add(recognizer->PatternName, recognizer);
        // Hammer Pattern
        recognizer = gcnew Recognizer_Hammer();
        Dictionary_Recognizers->Add(recognizer->PatternName, recognizer);
        // Bearish Engulfing Pattern
        recognizer = gcnew Recognizer_BearishEngulfing();
        Dictionary_Recognizers->Add(recognizer->PatternName, recognizer);
        // Bullish Engulfing Pattern
        recognizer = gcnew Recognizer_BullishEngulfing();
        Dictionary_Recognizers->Add(recognizer->PatternName, recognizer);
        // Bearish Harami Pattern
        recognizer = gcnew Recognizer_BearishHarami();
        Dictionary_Recognizers->Add(recognizer->PatternName, recognizer);
        // Bullish Harami Pattern
        recognizer = gcnew Recognizer_BullishHarami();
        Dictionary_Recognizers->Add(recognizer->PatternName, recognizer);
        // Peak Pattern
        recognizer = gcnew Recognizer_Peak();
        Dictionary_Recognizers->Add(recognizer->PatternName, recognizer);
        // Valley Pattern
        recognizer = gcnew Recognizer_Valley();
        Dictionary_Recognizers->Add(recognizer->PatternName, recognizer);
    }

    /// <summary>
    /// Populates the comboBox_patternSelect with the names of all available stock pattern recognizers.
    /// This allows the user to select from various patterns for analysis directly from a dropdown menu,
    /// improving user interaction and efficiency.
    /// </summary>
    void Form_stockDisplay::InitializeComboBox() {
        // Clear existing items in the combo box to prevent duplication
        comboBox_patternSelect->Items->Clear();
        // Iterate over each recognizer in the dictionary and add its key (pattern name) to the combo box
        for each (auto recognizer in Dictionary_Recognizers) {
            comboBox_patternSelect->Items->Add(recognizer.Key);
        }
    }


}


