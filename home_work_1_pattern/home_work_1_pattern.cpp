#include <iostream>
#include <map>
#include <vector>
#include "sql_query_builder.h"
#include <cassert>

using namespace  std;

int main(){
    SqlSelectQueryBuilder query_builder;
    query_builder.AddWhere("id", "42").AddWhere("name", "John");
    query_builder.AddFrom("students").AddFrom("students_1");
    query_builder.AddColumn("name").AddColumn("phone");
    
    assert(query_builder.BuildQuery()=="\"\SELECT name, phone FROM students_1 WHERE id=42 AND name=John;\"\ ");

    return EXIT_SUCCESS;
}