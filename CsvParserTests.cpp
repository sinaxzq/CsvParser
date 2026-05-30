#include "CsvParser.h"

#include <cassert>
#include <iostream>
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

int main()
{
    testSplitCsvLineSimple();
    testParseCsvSimple();
    testParseEmptyCsv();
    testSplitEmptyCsvLineSimple();
    testParseOnlyHeaderCsvTableSimple();
    return 0;
}