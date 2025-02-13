# Stock Analysis Tool

This project is a Windows Forms application designed for stock analysis. It allows users to load stock data from Yahoo Finance, display the data in a DataGridView, and visualize candlestick patterns on a chart control. The application supports daily, weekly, and monthly stock data.

## Features

- **Stock Data Input**: Users can store stock `.csv` files in a "Stock Data" folder. Ensure the files are named `xxx-Day.csv`, `xxx-Week.csv`, and `xxx-Month.csv`.
- **Candlestick Chart**: Displays candlestick charts with various patterns detected, including:
  - **Single Candlestick Patterns**: Bullish, Bearish, Neutral, Doji, Dragonfly Doji, Gravestone Doji, Marubozu, Hammer.
  - **2-Candlestick Patterns**: Bullish and Bearish Engulfing, Bullish and Bearish Harami.
  - **3-Candlestick Patterns**: Peak and Valley.
- **Pattern Recognition**: Uses specialized `Recognizer_xxx` classes to identify patterns, which are derived from an abstract base class `Recognizer`.
- **Chart Annotations**: Patterns are identified with annotations (RectangleAnnotation, ArrowAnnotation) on the candlestick chart.
- **UI**: Allows users to select patterns via a ComboBox, and displays patterns in different forms for each stock.

## Requirements

- **Stock Data**: Download stock data from Yahoo Finance and store in the "Stock Data" folder. Ensure files are in `.csv` format and named correctly.
- **.NET Framework**: This application is built using .NET Framework and requires Visual Studio to run and modify.

## Structure

- **Recognizer Class**: An abstract class that serves as a base for all individual pattern recognizers.
- **Recognizer_xxx Classes**: Each candlestick pattern has a dedicated recognizer class (e.g., `Recognizer_BullishEngulfing`).
- **Chart Controls**: Each stock has a dedicated form displaying its candlestick chart and allows pattern selection.

## Getting Started

1. Clone the repository to your local machine.
2. Open the project in Visual Studio.
3. Load the stock data files in the "Stock Data" folder.
4. Run the application and select candlestick patterns for analysis.

## License

This project is for educational purposes and may be freely modified or used for personal projects.

