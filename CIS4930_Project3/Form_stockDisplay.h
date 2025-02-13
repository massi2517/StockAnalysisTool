#pragma once
#include "smartCandlestick.h"

// Include all the added recognizer classes
#include "Recognizer.h"
#include "Recognizer_Bearish.h"
#include "Recognizer_Bullish.h"
#include "Recognizer_Neutral.h"
#include "Recognizer_Doji.h"
#include "Recognizer_DragonFlyDoji.h"
#include "Recognizer_GravestoneDoji.h"
#include "Recognizer_Marubozu.h"
#include "Recognizer_Hammer.h"
#include "Recognizer_BearishEngulfing.h"
#include "Recognizer_BullishEngulfing.h"
#include "Recognizer_BearishHarami.h"
#include "Recognizer_BullishHarami.h"
#include "Recognizer_Peak.h"
#include "Recognizer_Valley.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	// Form that displays stock candlestick data graphically and allows for dynamic interaction.
	/// It supports loading stock data from CSV files, visualizing this data as candlestick charts,
	/// and provides tools for analyzing patterns within the data.
	/// </summary>
	public ref class Form_stockDisplay : public System::Windows::Forms::Form
	{

		// Holds the list of all Candlestick objects loaded from a file.
		List<SmartCandlestick^>^ listOfSmartCandlesticks;

	private: System::Windows::Forms::OpenFileDialog^ openFileDialog_pickStock;
		// The main chart control for displaying the candlestick data.
		// A binding list that holds the candlestick data to be bound to UI controls like DataGridView.
		// This allows for automatic UI updates when the list changes.
		BindingList<SmartCandlestick^>^ boundSmartCandlesticks;

	private:
		// Create dictionary for recognizers
		Dictionary<String^, Recognizer^>^ Dictionary_Recognizers;
		// Declare functions for initializing recognizers and combobox
		void InitializeRecognizers();
		void InitializeComboBox();

	public:
		Form_stockDisplay(void)
		{
			InitializeComponent();
			// Allocates memory for the list of Candlestick objects with an initial capacity of 1024.
			// This is a preemptive optimization for performance, assuming a large number of candlesticks.
			listOfSmartCandlesticks = gcnew List<SmartCandlestick^>(1024);

			InitializeRecognizers();  // Initializes the pattern recognizers for candlestick analysis.
			InitializeComboBox();  // Populates the combo box with the names of recognized patterns.
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form_stockDisplay()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart_stockDisplay;
	protected:
	private: System::Windows::Forms::Label^ label_patternDisplay;
	private: System::Windows::Forms::ComboBox^ comboBox_patternSelect;
	private: System::Windows::Forms::Label^ label_end;
	private: System::Windows::Forms::Label^ label_start;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_end;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_start;
	private: System::Windows::Forms::Button^ button_update;
	private: System::Windows::Forms::Button^ button_loadStock;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::Title^ title2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->chart_stockDisplay = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label_patternDisplay = (gcnew System::Windows::Forms::Label());
			this->comboBox_patternSelect = (gcnew System::Windows::Forms::ComboBox());
			this->label_end = (gcnew System::Windows::Forms::Label());
			this->label_start = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker_end = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTimePicker_start = (gcnew System::Windows::Forms::DateTimePicker());
			this->button_update = (gcnew System::Windows::Forms::Button());
			this->button_loadStock = (gcnew System::Windows::Forms::Button());
			this->openFileDialog_pickStock = (gcnew System::Windows::Forms::OpenFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_stockDisplay))->BeginInit();
			this->SuspendLayout();
			// 
			// chart_stockDisplay
			// 
			chartArea1->Name = L"ChartArea_OHLC";
			chartArea2->AlignWithChartArea = L"ChartArea_OHLC";
			chartArea2->Name = L"ChartArea_Volume";
			this->chart_stockDisplay->ChartAreas->Add(chartArea1);
			this->chart_stockDisplay->ChartAreas->Add(chartArea2);
			this->chart_stockDisplay->Location = System::Drawing::Point(31, 12);
			this->chart_stockDisplay->Name = L"chart_stockDisplay";
			series1->ChartArea = L"ChartArea_OHLC";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Candlestick;
			series1->CustomProperties = L"PriceDownColor=192\\, 0\\, 0, PriceUpColor=0\\, 192\\, 0";
			series1->IsVisibleInLegend = false;
			series1->IsXValueIndexed = true;
			series1->Name = L"Series_OHLC";
			series1->XValueMember = L"Date";
			series1->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::DateTime;
			series1->YValueMembers = L"High,Low,Open,Close";
			series1->YValuesPerPoint = 4;
			series2->ChartArea = L"ChartArea_Volume";
			series2->IsVisibleInLegend = false;
			series2->IsXValueIndexed = true;
			series2->Name = L"Series_Volume";
			series2->XValueMember = L"Date";
			series2->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::DateTime;
			series2->YValueMembers = L"Volume";
			series2->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Int64;
			this->chart_stockDisplay->Series->Add(series1);
			this->chart_stockDisplay->Series->Add(series2);
			this->chart_stockDisplay->Size = System::Drawing::Size(1894, 823);
			this->chart_stockDisplay->TabIndex = 15;
			this->chart_stockDisplay->Text = L"chart_stockDisplay";
			title1->DockedToChartArea = L"ChartArea_OHLC";
			title1->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Left;
			title1->IsDockedInsideChartArea = false;
			title1->Name = L"Title_OHLC_Left";
			title1->Text = L"Price ($)";
			title2->DockedToChartArea = L"ChartArea_Volume";
			title2->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Left;
			title2->IsDockedInsideChartArea = false;
			title2->Name = L"Title_Volume_Left";
			title2->Text = L"Volume";
			this->chart_stockDisplay->Titles->Add(title1);
			this->chart_stockDisplay->Titles->Add(title2);
			// 
			// label_patternDisplay
			// 
			this->label_patternDisplay->AutoSize = true;
			this->label_patternDisplay->Location = System::Drawing::Point(1252, 885);
			this->label_patternDisplay->Name = L"label_patternDisplay";
			this->label_patternDisplay->Size = System::Drawing::Size(180, 29);
			this->label_patternDisplay->TabIndex = 24;
			this->label_patternDisplay->Text = L"Display Pattern:";
			// 
			// comboBox_patternSelect
			// 
			this->comboBox_patternSelect->FormattingEnabled = true;
			this->comboBox_patternSelect->Location = System::Drawing::Point(1448, 882);
			this->comboBox_patternSelect->Name = L"comboBox_patternSelect";
			this->comboBox_patternSelect->Size = System::Drawing::Size(388, 37);
			this->comboBox_patternSelect->TabIndex = 23;
			this->comboBox_patternSelect->SelectedIndexChanged += gcnew System::EventHandler(this, &Form_stockDisplay::comboBox_patternSelect_SelectedIndexChanged);
			// 
			// label_end
			// 
			this->label_end->AutoSize = true;
			this->label_end->Location = System::Drawing::Point(111, 908);
			this->label_end->Name = L"label_end";
			this->label_end->Size = System::Drawing::Size(118, 29);
			this->label_end->TabIndex = 22;
			this->label_end->Text = L"End Date:";
			// 
			// label_start
			// 
			this->label_start->AutoSize = true;
			this->label_start->Location = System::Drawing::Point(105, 860);
			this->label_start->Name = L"label_start";
			this->label_start->Size = System::Drawing::Size(124, 29);
			this->label_start->TabIndex = 21;
			this->label_start->Text = L"Start Date:";
			// 
			// dateTimePicker_end
			// 
			this->dateTimePicker_end->Location = System::Drawing::Point(247, 908);
			this->dateTimePicker_end->Name = L"dateTimePicker_end";
			this->dateTimePicker_end->Size = System::Drawing::Size(482, 35);
			this->dateTimePicker_end->TabIndex = 20;
			// 
			// dateTimePicker_start
			// 
			this->dateTimePicker_start->Location = System::Drawing::Point(247, 860);
			this->dateTimePicker_start->Name = L"dateTimePicker_start";
			this->dateTimePicker_start->Size = System::Drawing::Size(482, 35);
			this->dateTimePicker_start->TabIndex = 19;
			this->dateTimePicker_start->Value = System::DateTime(2022, 1, 1, 0, 0, 0, 0);
			// 
			// button_update
			// 
			this->button_update->Location = System::Drawing::Point(1041, 871);
			this->button_update->Name = L"button_update";
			this->button_update->Size = System::Drawing::Size(136, 56);
			this->button_update->TabIndex = 18;
			this->button_update->Text = L"Update";
			this->button_update->UseVisualStyleBackColor = true;
			this->button_update->Click += gcnew System::EventHandler(this, &Form_stockDisplay::button_update_Click);
			// 
			// button_loadStock
			// 
			this->button_loadStock->Location = System::Drawing::Point(773, 856);
			this->button_loadStock->Name = L"button_loadStock";
			this->button_loadStock->Size = System::Drawing::Size(249, 87);
			this->button_loadStock->TabIndex = 17;
			this->button_loadStock->Text = L"Load Stock";
			this->button_loadStock->UseVisualStyleBackColor = true;
			this->button_loadStock->Click += gcnew System::EventHandler(this, &Form_stockDisplay::button_loadStock_Click);
			// 
			// openFileDialog_pickStock
			// 
			this->openFileDialog_pickStock->FileName = L"openFileDialog_pickStock";
			this->openFileDialog_pickStock->Multiselect = true;
			this->openFileDialog_pickStock->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form_stockDisplay::openFileDialog_pickStock_FileOk);
			// 
			// Form_stockDisplay
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1949, 964);
			this->Controls->Add(this->label_patternDisplay);
			this->Controls->Add(this->comboBox_patternSelect);
			this->Controls->Add(this->label_end);
			this->Controls->Add(this->label_start);
			this->Controls->Add(this->dateTimePicker_end);
			this->Controls->Add(this->dateTimePicker_start);
			this->Controls->Add(this->button_update);
			this->Controls->Add(this->button_loadStock);
			this->Controls->Add(this->chart_stockDisplay);
			this->Name = L"Form_stockDisplay";
			this->Text = L"Form_stockDisplay";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_stockDisplay))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}


	// Declares a private member function that reads candlestick data from a file and returns a list of Candlestick objects.
	private: List<SmartCandlestick^>^ ReadDataFromFile(String^ filepath);
	// Declares a private member function that filters a list of Candlestick objects based on a start and end date, returning the filtered list.
	private: List<SmartCandlestick^>^ filterCandlesticks(List<SmartCandlestick^>^ allCandlesticks, DateTime startDate, DateTime endDate);
	// Declares a private member function that updates the display, with no return type and no parameters.
	private: void updateDisplay();
	// Declares a private member function that adjusts the Y-axis limits of the OHLC to fit only the displayed candlesticks
	private: void normalize();
	// Declares a private member function that annotates the chart by placing an arrow annotation on candlesticks that match a given pattern name
	private: void AnnotatePatternOnChart(String^ patternName);

#pragma endregion

	/// <summary>
	/// Initiates the display of a dialog for the user to select a stock data file.
	/// </summary>
	/// <param name="sender">The object that initiated the event.</param>
	/// <param name="e">Event data that provides more information about the event.</param>
	private: System::Void button_loadStock_Click(System::Object^ sender, System::EventArgs^ e) {
		// Opens a dialog for the user to select a file
		openFileDialog_pickStock->ShowDialog();
	}

	/// <summary>
	/// Handles the click event on the 'Update' button to refresh the stock display based on the current selections or data.
	/// This method calls the updateDisplay function to refresh the candlestick chart and data grid view based on the selected date range or any other filters applied.
	/// </summary>
	/// <param name="sender">The source of the event, typically the 'Update' button itself.</param>
	/// <param name="e">Contains the event data, not used in this method but necessary for event handler signature.</param>
	/// <returns></returns>
	private: System::Void button_update_Click(System::Object^ sender, System::EventArgs^ e) {
		// Call the updateDisplay function to refresh the stock display
		updateDisplay();
	}

	/// <summary>
	/// Loads the selected stock data file, reads its contents into a list of Candlesticks,
	/// binds this list to the UI, and updates the display to reflect the loaded data.
	/// Additional selected files are loaded into new forms.
	/// </summary>
	/// <param name="sender">The object that initiated the event.</param>
	/// <param name="e">Event data containing information about whether the file dialog was canceled.</param>
	private: System::Void openFileDialog_pickStock_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
		// Check if the file selection dialog resulted in one or more selected files
		if (openFileDialog_pickStock->FileNames->Length > 0) {
			// Sets the text property of the current form to the path of the first selected file
			Text = openFileDialog_pickStock->FileNames[0];

			// Reads data from the first selected file and stores it in a list of SmartCandlesticks
			listOfSmartCandlesticks = ReadDataFromFile(openFileDialog_pickStock->FileNames[0]);
			// Binds the list of SmartCandlesticks to the UI to be displayed
			boundSmartCandlesticks = gcnew BindingList<SmartCandlestick^>(listOfSmartCandlesticks);

			// Recognize patterns after loading
			for each (KeyValuePair<String^, Recognizer^> recognizerPair in Dictionary_Recognizers) {
				recognizerPair.Value->RecognizeAll(boundSmartCandlesticks);
			}

			// Updates the UI to reflect the newly loaded data
			updateDisplay();
			// Normalizes the data for better visualization or processing
			normalize();
			// Populates a ComboBox with patterns identified in the loaded data
			InitializeComboBox();

			// Iterates over any additional selected files starting from the second file
			for (int i = 1; i < openFileDialog_pickStock->FileNames->Length; i++) {
				// Creates a new instance of Form_stockDisplay for each additional selected file
				Form_stockDisplay^ newForm = gcnew Form_stockDisplay();
				// Sets the text property of the new form to the path of the current file
				newForm->Text = openFileDialog_pickStock->FileNames[i];
				// Reads data from the current file and stores it in the new form's list of SmartCandlesticks
				newForm->listOfSmartCandlesticks = ReadDataFromFile(openFileDialog_pickStock->FileNames[i]);
				// Binds the list of SmartCandlesticks to the new form's UI
				newForm->boundSmartCandlesticks = gcnew BindingList<SmartCandlestick^>(newForm->listOfSmartCandlesticks);
				// Updates the new form's display to reflect the loaded data
				newForm->updateDisplay();
				// Normalizes the data in the new form
				newForm->normalize();
				// Populates the ComboBox in the new form with patterns identified in the loaded data
				newForm->InitializeComboBox();
				// Displays the new form
				newForm->Show();
			}
		}
	}

	/// <summary>
	/// Handles the event when the selected item in the comboBox_patternSelect changes.
	/// If a new pattern is selected (and is not null), it annotates the selected pattern
	/// on a chart by calling the AnnotatePatternOnChart method.
	/// </summary>
	/// <param name="sender">The source of the event, typically the combo box itself.</param>
	/// <param name="e">Contains the event data, but not used directly in this method.</param>
	/// <returns></returns>
	private: System::Void comboBox_patternSelect_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		// Check if the selected item in the combo box is not null to ensure there's a selection to work with.
		if (comboBox_patternSelect->SelectedItem != nullptr)
		{
			// Cast the selected item to a String^ (managed string in C++/CLI) safely.
			String^ selectedPattern = safe_cast<String^>(comboBox_patternSelect->SelectedItem);
			// Call a method to annotate the selected pattern on a chart, passing in the selected pattern string.
			AnnotatePatternOnChart(selectedPattern);
		}
	}

};
}