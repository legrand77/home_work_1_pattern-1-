#include <iostream>
#include <unordered_map>
#include <vector>
#include "sql_query_builder.h"
#include <cassert>

using namespace  std;

int main() {
    AdvancedSqlSelectQueryBuilder query_builder;
    query_builder.AddColumns({ "name", "phone" });
    query_builder.AddFrom("students");
    query_builder.MethodLess("id", "42"); // Добавляем условие id < 42
    assert(query_builder.BuildQuery() == "\"\SELECT name, phone FROM students WHERE id<42;\"\ ");
    return EXIT_SUCCESS;
}
