# CsvAnalyzer

A small C++20 command-line tool for reading simple CSV files and performing basic table analysis.

## Features

* Parse simple comma-separated CSV files
* Show CSV summary
* Sum a numeric column
* Group rows by one column and sum another numeric column
* Basic tests with CTest

## Limitations

This project intentionally supports only simple CSV:

* comma delimiter
* no quoted fields
* no escaped commas
* first row is treated as headers

## Commands

```powershell
CsvAnalyzerApp.exe summary <csv_file>
CsvAnalyzerApp.exe sum <csv_file> <column_name>
CsvAnalyzerApp.exe group-sum <csv_file> <group_column> <value_column>
```

## Example

CSV:

```csv
category,amount
food,12.5
rent,1000
food,8
```

Command:

```powershell
CsvAnalyzerApp.exe group-sum expenses.csv category amount
```

Output:

```text
rent | 1000
food | 20.5
```

## Build

```powershell
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```
