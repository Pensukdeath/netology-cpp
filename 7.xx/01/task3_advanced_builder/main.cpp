#include <iostream>
#include "advanced_sql_query_builder.h"

int main() {
    AdvancedSqlSelectQueryBuilder query;
    query.AddColumns({"name", "phone"})
         .AddFrom("students")
         .AddGreater("id", "100");

    std::cout << query.BuildQuery() << std::endl;
}
