#pragma once

#include <optional>
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

struct GroupSum
{
    std::string group;
    double sum{};
};

std::vector<std::string> splitCsvLineSimple(const std::string &line);
CsvTable parseCsvSimple(const std::vector<std::string> &lines);
std::optional<CsvTable> loadCsvFromFile(const std::string &filename);
std::optional<double> sumColumn(const CsvTable &table, const std::string &columnName);
std::optional<std::vector<GroupSum>> groupSumColumn(const CsvTable &table,
                                                    const std::string &groupColumnName,
                                                    const std::string &valueColumnName);