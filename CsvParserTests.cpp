#include "CsvParser.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
void testSplitCsvLineSimple()
{
    const std::vector<std::string> cells = splitCsvLineSimple("name,age,city");

    assert(cells.size() == 3);
    assert(cells[0] == "name");
    assert(cells[1] == "age");
    assert(cells[2] == "city");
}

void testSplitEmptyCsvLineSimple()
{
    const std::vector<std::string> cells = splitCsvLineSimple("");

    assert(cells.size() == 0);
}

void testParseOnlyHeaderCsvTableSimple()
{
    const std::vector<std::string> lines = {
        "name",
    };

    const CsvTable table = parseCsvSimple(lines);

    assert(table.headers.size() == 1);
    assert(table.headers[0] == "name");
    assert(table.rows.empty());
}

void testParseCsvSimple()
{
    const std::vector<std::string> lines = {
        "name,age,city",
        "Alice,20,Poznan",
        "Bob,22,Warsaw",
    };

    const CsvTable table = parseCsvSimple(lines);

    assert(table.headers.size() == 3);
    assert(table.headers[0] == "name");
    assert(table.headers[1] == "age");
    assert(table.headers[2] == "city");

    assert(table.rows.size() == 2);
    assert(table.rows[0].cells[0] == "Alice");
    assert(table.rows[0].cells[1] == "20");
    assert(table.rows[0].cells[2] == "Poznan");

    assert(table.rows[1].cells[0] == "Bob");
    assert(table.rows[1].cells[1] == "22");
    assert(table.rows[1].cells[2] == "Warsaw");
}

void testParseEmptyCsv()
{
    const CsvTable table = parseCsvSimple({});

    assert(table.headers.empty());
    assert(table.rows.empty());
}

void testLoadCsvFromFile()
{
    const std::string filename = "test_load_csv.csv";

    {
        std::ofstream file(filename);
        file << "name,age\n";
        file << "Alice,20\n";
        file << "Bob,22\n";
    }

    const std::optional<CsvTable> table = loadCsvFromFile(filename);

    assert(table.has_value());
    assert(table->headers.size() == 2);
    assert(table->headers[0] == "name");
    assert(table->headers[1] == "age");

    assert(table->rows.size() == 2);
    assert(table->rows[0].cells[0] == "Alice");
    assert(table->rows[0].cells[1] == "20");

    std::filesystem::remove(filename);
}

void testLoadMissingCsvFileReturnsNullopt()
{
    const std::optional<CsvTable> table = loadCsvFromFile("missing_file_hopefully.csv");

    assert(!table.has_value());
}

void testSumColumn()
{
    const CsvTable table = parseCsvSimple({
        "name,amount",
        "food,12.5",
        "rent,1000",
        "coffee,8.25",
    });

    const std::optional<double> total = sumColumn(table, "amount");

    assert(total.has_value());
    assert(*total == 1020.75);
}

void testSumColumnReturnsNulloptForMissingColumn()
{
    const CsvTable table = parseCsvSimple({
        "name,amount",
        "food,12.5",
    });

    const std::optional<double> total = sumColumn(table, "missing");

    assert(!total.has_value());
}

void testSumColumnReturnsNulloptForInvalidNumber()
{
    const CsvTable table = parseCsvSimple({
        "name,amount",
        "food,abc",
    });

    const std::optional<double> total = sumColumn(table, "amount");

    assert(!total.has_value());
}

void testSumColumnReturnsNulloptForShortRow()
{
    const CsvTable table = parseCsvSimple({
        "name,amount",
        "food",
    });
    const std::optional<double> total = sumColumn(table, "amount");
    assert(!total.has_value());
}

void testSumColumnCanReturnZero()
{
    const CsvTable table = parseCsvSimple({
        "name,amount",
        "a,0",
        "b,0",
    });

    const std::optional<double> total = sumColumn(table, "amount");

    assert(total.has_value());
    assert(*total == 0.0);
}
void testGroupSumColumn()
{
    const CsvTable table = parseCsvSimple({
        "category,amount",
        "food,12.5",
        "rent,1000",
        "food,8",
    });

    const std::optional<std::vector<GroupSum>> results =
        groupSumColumn(table, "category", "amount");

    assert(results.has_value());
    assert(results->size() == 2);

    assert((*results)[0].group == "rent");
    assert((*results)[0].sum == 1000.0);

    assert((*results)[1].group == "food");
    assert((*results)[1].sum == 20.5);
}

void testGroupSumColumnReturnsNulloptForMissingGroupColumn()
{
    const CsvTable table = parseCsvSimple({
        "category,amount",
        "food,12.5",
    });

    const std::optional<std::vector<GroupSum>> results = groupSumColumn(table, "missing", "amount");

    assert(!results.has_value());
}

void testGroupSumColumnReturnsNulloptForInvalidNumber()
{
    const CsvTable table = parseCsvSimple({
        "category,amount",
        "food,abc",
    });

    const std::optional<std::vector<GroupSum>> results =
        groupSumColumn(table, "category", "amount");

    assert(!results.has_value());
}

void testGroupSumColumnReturnsNulloptForShortRow()
{
    const CsvTable table = parseCsvSimple({
        "category,amount",
        "food",
    });

    const std::optional<std::vector<GroupSum>> results =
        groupSumColumn(table, "category", "amount");

    assert(!results.has_value());
}

int main()
{
    testSplitCsvLineSimple();
    testParseCsvSimple();
    testParseEmptyCsv();
    testSplitEmptyCsvLineSimple();
    testParseOnlyHeaderCsvTableSimple();
    testLoadCsvFromFile();
    testLoadMissingCsvFileReturnsNullopt();
    testSumColumn();
    testSumColumnReturnsNulloptForMissingColumn();
    testSumColumnReturnsNulloptForInvalidNumber();
    testSumColumnReturnsNulloptForShortRow();
    testSumColumnCanReturnZero();
    testGroupSumColumn();
    testGroupSumColumnReturnsNulloptForMissingGroupColumn();
    testGroupSumColumnReturnsNulloptForInvalidNumber();
    testGroupSumColumnReturnsNulloptForShortRow();
    return 0;
}