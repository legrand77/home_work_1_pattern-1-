#include <iostream>
#include <map>
#include <vector>
#include "sql_query_builder.h"

using namespace  std;

int main() {
    SqlSelectQueryBuilder query_builder;
    map<string, string> whereConditions = {
        {"id", "42"},
        {"name", "John"},
        {"age", "20"}
    };
    query_builder.AddWhere(whereConditions);
    query_builder.AddFrom("students").AddFrom("students_1");
    query_builder.AddColumns({ "name", "phone", "email" });
    //static_assert(
    query_builder.BuildQuery();

    //"SELECT name, phone FROM students WHERE id=42 AND name=John;");

    return EXIT_SUCCESS;
}