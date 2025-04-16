#include <iostream>
#include <unordered_map>
#include <vector>
#include "sql_query_builder.h"
#include <cassert>

using namespace  std;

int main() {
    SqlSelectQueryBuilder query_builder;
    unordered_map<string, string> whereConditions = {
        {"id", "42"},
        {"name", "John"},
        {"age", "20"}
    };
    query_builder.AddWhere(whereConditions);
    query_builder.AddFrom("students").AddFrom("students_1");
    query_builder.AddColumns({ "name", "phone", "email" });
    assert(query_builder.BuildQuery() =="\"\SELECT name, phone, email FROM students_1 WHERE id=42 AND name=John AND age=20;\"\ ");

    return EXIT_SUCCESS;
}