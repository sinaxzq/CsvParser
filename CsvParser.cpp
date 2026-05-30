#include <CsvParser.h>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>

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