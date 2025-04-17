#pragma once
#include "iostream"
#include "unordered_map"
#include "vector"
#include <functional>

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
    unordered_map<string, string> Where;
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

   virtual SqlSelectQueryBuilder& AddWhere(const unordered_map<string, string>& kv) noexcept {
        int count{};
        int count_1{};
        for (const auto& pair : kv) {
            SqlSelectQuery.Where[pair.first] = pair.second;
            count++;
        }
        if (!SqlSelectQuery.Where.empty())  SqlSelectQuery.WHERE_1 = {};
        for (auto& [s, d] : SqlSelectQuery.Where) {
            SqlSelectQuery.WHERE_1 += s + "=" + d;
            count_1++;
            if (count_1 != count) SqlSelectQuery.WHERE_1 += " AND ";
        }
        SqlSelectQuery.WHERE_1+= ";\"\ ";
        return *this;
    };

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        for (const auto& column : columns) {
            SqlSelectQuery.Column.push_back(column);
        }
        if (!SqlSelectQuery.Column.empty())  SqlSelectQuery.SELECT_1 = {};
        for (auto& s : SqlSelectQuery.Column) {
            SqlSelectQuery.SELECT_1 += s;
            if (s != SqlSelectQuery.Column.back()) SqlSelectQuery.SELECT_1 += ", ";
        }
        return *this;
    };

    string BuildQuery() noexcept {
        string s;
        s = "\"\SELECT " + SqlSelectQuery.SELECT_1 + " FROM " + SqlSelectQuery.FROM + " WHERE " + SqlSelectQuery.WHERE_1;
        cout << s << endl;
        return s;
    }
protected:
    SqlSelectQuery SqlSelectQuery;
};



class AdvancedSqlSelectQueryBuilder : public SqlSelectQueryBuilder {
    public:

        AdvancedSqlSelectQueryBuilder& AddWhere(const unordered_map<string, string>& kv) noexcept override {
            int count{};
            int count_1{};
            for (const auto& pair : kv) {
                SqlSelectQuery.Where[pair.first] = pair.second;
                count++;
            }
            if (!SqlSelectQuery.Where.empty())  SqlSelectQuery.WHERE_1 = {};
            for (auto& [s, d] : SqlSelectQuery.Where) {
                SqlSelectQuery.WHERE_1 += s + get_x() + d;
                count_1++;
                if (count_1 != count) SqlSelectQuery.WHERE_1 += " AND ";
            }
            SqlSelectQuery.WHERE_1 += ";\"\ ";
            return *this;
        };

        string get_x() {
            return x;
        }
        void set_x(string _x) {
            x=_x;
        }

       AdvancedSqlSelectQueryBuilder& MethodMore(const string& column, const string& value) {
          unordered_map<string, string> Where_1;
          Where_1[column] = value;
          set_x(">");
          AddWhere(Where_1);
          return *this;
       }

       AdvancedSqlSelectQueryBuilder& MethodLess(const string& column, const string& value) {
           unordered_map<string, string> Where_1;
           Where_1[column] = value;
           set_x("<");
           AddWhere(Where_1);
           return *this;
       }

private:
       string x;


};
