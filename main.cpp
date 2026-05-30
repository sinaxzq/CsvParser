#include "CsvParser.h"

#include <iostream>
#include <optional>
#include <string>

namespace
{
void printUsage()
{
    std::cout << "Usage:\n";
    std::cout << "  CsvAnalyzerApp summary <csv_file>\n";
    std::cout << "  CsvAnalyzerApp sum <csv_file> <column_name>\n";
}

void printSummary(const CsvTable &table)
{
    std::cout << "Headers: " << table.headers.size() << "\n";
    std::cout << "Rows: " << table.rows.size() << "\n";

    std::cout << "Columns:\n";

    for (const std::string &header : table.headers)
    {
        std::cout << "  " << header << "\n";
    }
}
} // namespace

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printUsage();
        return 1;
    }

    const std::string command = argv[1];
    const std::string filename = argv[2];

    if (command == "summary")
    {
        const std::optional<CsvTable> table = loadCsvFromFile(filename);

        if (!table)
        {
            std::cout << "Could not open file\n";
            return 1;
        }

        printSummary(*table);
        return 0;
    }
    if (command == "sum")
    {
        const std::optional<CsvTable> table = loadCsvFromFile(filename);

        if (!table)
        {
            std::cout << "Could not open file\n";
            return 1;
        }
        std::optional<double> sum = sumColumn(*table, argv[3]);
        if (!sum)
        {
            std::cout << "Could not sum column\n";
            return 1;
        }

        std::cout << "Sum of column " << argv[2] << " = " << *sum << "\n";

        return 0;
    }

    std::cout << "Unknown command\n";
    printUsage();
    return 1;
}