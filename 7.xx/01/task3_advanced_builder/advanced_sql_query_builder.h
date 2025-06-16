#pragma once
#include "sql_query_builder.h"

class AdvancedSqlSelectQueryBuilder : public SqlSelectQueryBuilder {
public:
    AdvancedSqlSelectQueryBuilder& AddGreater(const std::string& column, const std::string& value) {
        extra_.emplace_back(column + ">" + value);
        return *this;
    }

    AdvancedSqlSelectQueryBuilder& AddLess(const std::string& column, const std::string& value) {
        extra_.emplace_back(column + "<" + value);
        return *this;
    }

    std::string BuildQuery() const {
        std::string base = SqlSelectQueryBuilder::BuildQuery();
        std::string result = base;

        if (!extra_.empty()) {
            size_t where_pos = result.find("WHERE ");
            result.pop_back();
            if (where_pos != std::string::npos) {
                for (const auto& cond : extra_) {
                    result += " AND " + cond;
                }
            } else {
                result += " WHERE ";
                for (size_t i = 0; i < extra_.size(); ++i) {
                    result += extra_[i];
                    if (i + 1 < extra_.size()) result += " AND ";
                }
            }
            result += ";";
        }

        return result;
    }

private:
    std::vector<std::string> extra_;
};
