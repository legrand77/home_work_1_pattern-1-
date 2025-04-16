#include <iostream>
#include <map>
#include <vector>
#include "sql_query_builder.h"

using namespace  std;

int main(){
    SqlSelectQueryBuilder query_builder;
    query_builder.AddWhere("id", "42").AddWhere("name", "John");
    query_builder.AddFrom("students").AddFrom("students");
    query_builder.AddColumn("name").AddColumn("phone");
    
    //static_assert(
    query_builder.BuildQuery();

    //"SELECT name, phone FROM students WHERE id=42 AND name=John;");

    return EXIT_SUCCESS;
}