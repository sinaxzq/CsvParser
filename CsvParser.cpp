#include <CsvParser.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> splitCsvLineSimple(const std::string &line)
{
    std::vector<std::string> cells;

    std::istringstream stream(line);

    std::string cell;

    while (std::getline(stream, cell, ','))
    {
        cells.push_back(cell);
    }

    return cells;
}

CsvTable parseCsvSimple(const std::vector<std::string> &lines)
{
    CsvTable table;

    if (lines.empty())
        return table;

    table.headers = splitCsvLineSimple(lines[0]);

    for (std::size_t i = 1; i < lines.size(); ++i)
    {
        table.rows.push_back(CsvRow{splitCsvLineSimple(lines[i])});
    }

    return table;
}

std::optional<CsvTable> loadCsvFromFile(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file)
        return std::nullopt;

    std::vector<std::string> lines;

    std::string line;

    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    return parseCsvSimple(lines);
}

std::optional<double> sumColumn(const CsvTable &table, const std::string &columnName)
{
    const auto it = std::find(table.headers.begin(), table.headers.end(), columnName);

    if (it == table.headers.end())
    {
        return std::nullopt;
    }

    const std::size_t columnIndex =
        static_cast<std::size_t>(std::distance(table.headers.begin(), it));

    double sum = 0.0;

    for (const CsvRow &row : table.rows)
    {
        if (columnIndex >= row.cells.size())
        {
            return std::nullopt;
        }

        try
        {
            sum += std::stod(row.cells[columnIndex]);
        }
        catch (...)
        {
            return std::nullopt;
        }
    }

    return sum;
}