/*
    Copyright 2016, Felspar Co Ltd. http://support.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include <fost/log>
#include <fostgres/fostgres.hpp>
#include <fostgres/sql.hpp>


std::pair<std::vector<fostlib::string>, fostlib::pg::recordset> fostgres::sql(
    const fostlib::string &host, const fostlib::string &database, const fostlib::string &cmd
) {
    auto logger = fostlib::log::debug(c_fostgres);
    logger("", "Executing SQL command")
        ("host", host)
        ("database", database)
        ("command", cmd);

    /// Execute the SQL we've been given
    fostlib::pg::connection cnx(host, database);
    auto rs = cnx.exec(fostlib::coerce<fostlib::utf8_string>(cmd));

    /// Calculate the column headings
    std::vector<fostlib::string> columns;
    std::size_t number{0};
    for ( const auto &c : rs.columns() ) {
        columns.push_back(c.value("un-named." + std::to_string(++number)));
    }

    /// Return data suitable for sending to the browser
    return std::make_pair(std::move(columns), std::move(rs));
}

