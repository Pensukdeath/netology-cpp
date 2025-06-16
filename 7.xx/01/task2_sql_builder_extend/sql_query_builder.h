#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>

class SqlSelectQueryBuilder {
public:
    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        columns_.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        columns_.insert(columns_.end(), columns.begin(), columns.end());
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table) {
        table_ = table;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) {
        where_.emplace_back(column, value);
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& [key, val] : kv)
            where_.emplace_back(key, val);
        return *this;
    }

    std::string BuildQuery() const {
        std::ostringstream query;
        query << "SELECT ";
        if (columns_.empty()) {
            query << "*";
        } else {
            for (size_t i = 0; i < columns_.size(); ++i) {
                query << columns_[i];
                if (i + 1 < columns_.size()) query << ", ";
            }
        }
        query << " FROM " << table_;
        if (!where_.empty()) {
            query << " WHERE ";
            for (size_t i = 0; i < where_.size(); ++i) {
                query << where_[i].first << "=" << where_[i].second;
                if (i + 1 < where_.size()) query << " AND ";
            }
        }
        query << ";";
        return query.str();
    }

private:
    std::vector<std::string> columns_;
    std::string table_;
    std::vector<std::pair<std::string, std::string>> where_;
};
