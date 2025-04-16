#pragma once
#include "iostream"
#include "map"
#include "vector"


using namespace std;

struct SqlSelectQuery {
    string SELECT_1{"*"};
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
        SqlSelectQuery.Where[column]= value;
        return *this;
    }

   const void BuildQueryForm() noexcept {
        if (!SqlSelectQuery.Column.empty()) {
            SqlSelectQuery.SELECT_1 = SqlSelectQuery.Column.front();
        }
        if (SqlSelectQuery.SELECT_2.empty() && !SqlSelectQuery.Column.empty()) {
            SqlSelectQuery.SELECT_2 = SqlSelectQuery.Column.back();
            SqlSelectQuery.SELECT_1+= ", " + SqlSelectQuery.SELECT_2;

        }

        if (SqlSelectQuery.AND_1.empty() && SqlSelectQuery.AND_2.empty() && !SqlSelectQuery.Where.empty()) {
            for (const auto& elem : SqlSelectQuery.Where) {
                SqlSelectQuery.AND_1 = elem.first;
                SqlSelectQuery.AND_2 = elem.second;
                break;
            }
        }

         SqlSelectQuery.Where.erase(SqlSelectQuery.AND_1);

        if (SqlSelectQuery.WHERE_1.empty() && SqlSelectQuery.WHERE_2.empty() && !SqlSelectQuery.Where.empty()) {
            for (const auto& elem : SqlSelectQuery.Where){
                   SqlSelectQuery.WHERE_1 = elem.first;
                   SqlSelectQuery.WHERE_2 = elem.second;    
            }
        }       
    }

    string BuildQuery() noexcept {
        BuildQueryForm();  
        string s;
        s = "\"\SELECT "+SqlSelectQuery.SELECT_1 + " FROM " + SqlSelectQuery.FROM + " WHERE " + SqlSelectQuery.AND_1
        + "=" + SqlSelectQuery.AND_2 + " AND " + SqlSelectQuery.WHERE_1 + "=" + SqlSelectQuery.WHERE_2 + ";\"\ ";  
        return s;
    }
    private:
    SqlSelectQuery SqlSelectQuery;
};