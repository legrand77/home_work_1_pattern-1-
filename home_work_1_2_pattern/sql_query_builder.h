#pragma once
#include "iostream"
#include "map"
#include "vector"


using namespace std;

struct SqlSelectQuery {
    string SELECT_1{ "*" };
    string SELECT_2;
    string FROM;
    string WHERE_1;
    string WHERE_2;
    string AND_1;
    string AND_2;
    vector<string> Column;
    map<string, string> Where;
};

class SqlSelectQueryBuilder {
public:

    SqlSelectQueryBuilder& AddColumn(const string& column) noexcept {
        SqlSelectQuery.Column.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const string& _from) {
        SqlSelectQuery.FROM = _from;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const string& column, const string& value) {
        SqlSelectQuery.Where[column] = value;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& pair : kv) {
            SqlSelectQuery.Where[pair.first] = pair.second;
        }
      
        while (!SqlSelectQuery.Where.empty()) {
            string x{};
            for (const auto& pair : SqlSelectQuery.Where) {
                x = pair.first;
                SqlSelectQuery.WHERE_1 += x + "=" + pair.second;
                break;
            }
            SqlSelectQuery.Where.erase(x);
            if (!SqlSelectQuery.Where.empty())  SqlSelectQuery.WHERE_1 += " AND ";

        }
        SqlSelectQuery.WHERE_1 += "\"\ ";

        return *this;
    };

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        for (const auto& column : columns) {
            SqlSelectQuery.Column.push_back(column);
        }

        if (!SqlSelectQuery.Column.empty())  SqlSelectQuery.SELECT_1 = {};
        while (!SqlSelectQuery.Column.empty()) {
            string SELECT = SqlSelectQuery.Column.back();
            SqlSelectQuery.SELECT_1 += SELECT;
            SqlSelectQuery.Column.pop_back();
            if (!SqlSelectQuery.Column.empty())  SqlSelectQuery.SELECT_1 += ", ";
        }

        return *this;
    };

    const void BuildQuery() noexcept {
        cout << "\"\SELECT " << SqlSelectQuery.SELECT_1 << " FROM " << SqlSelectQuery.FROM << " WHERE " << SqlSelectQuery.WHERE_1;
    }
    private:
    SqlSelectQuery SqlSelectQuery;
};