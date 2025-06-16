#include <iostream>
#include "sql_query_builder.h"

int main() {
    SqlSelectQueryBuilder query;
    query.AddColumns({"name", "phone", "email"});
    query.AddFrom("students");
    query.AddWhere({
        {"id", "1"},
        {"name", "Alice"}
    });

    std::cout << query.BuildQuery() << std::endl;
}
