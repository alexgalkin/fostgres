/*
    Copyright 2016 Felspar Co Ltd. http://support.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include <fostgres/fg/fg.hpp>
#include <fost/postgres>


namespace {


    fg::json sql_file(
        fg::frame &stack, fg::json::const_iterator pos, fg::json::const_iterator end
    ) {
        auto sql = fostlib::coerce<fostlib::utf8_string>(
            fostlib::utf::load_file(
                fostlib::coerce<boost::filesystem::path>(
                    stack.resolve_string(stack.argument("filename", pos, end)))));
        fostlib::pg::connection cnx(stack.lookup("pg.dsn"));
        cnx.exec(sql);
        cnx.commit();
        return fostlib::json();
    }


}


fg::frame::builtin fg::lib::sql_file = ::sql_file;
