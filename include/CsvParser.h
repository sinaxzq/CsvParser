#pragma once

#include <string>
#include <vector>

struct CsvRow
{
    std::vector<std::string> cells;
};

struct CsvTable
{
    std::vector<std ::string> headers;

    std::vector<CsvRow> rows;
};

std::vector<std::string> splitCsvLineSimple(const std::string &line);
CsvTable parseCsvSimple(const std::vector<std::string> &lines);