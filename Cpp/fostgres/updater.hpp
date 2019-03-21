/**
    Copyright 2016-2018, Felspar Co Ltd. <https://support.felspar.com/>

    Distributed under the Boost Software License, Version 1.0.
    See <http://www.boost.org/LICENSE_1_0.txt>
*/


#pragma once


#include <fostgres/matcher.hpp>
#include <fostgres/response.hpp>
#include <fostgres/sql.hpp>


namespace fostgres {


    /// Internal class used for PATCH and PUT
    class updater {
      public:
        const fostlib::string relation;

        updater(fostlib::json method_config,
                fostlib::pg::connection &,
                const fostgres::match &,
                fostlib::http::server::request &);

        /// Returning data
        const std::vector<fostlib::string> returning() const {
            return returning_cols;
        }

        /// ## Tracking of `UPDATE` versus `INSERT ON CONFLICT UPDATE`
        enum class action { do_default, insertable, updateable };
        /// The default action is required to support the difference in
        /// default behaviour between CSJ and object `PATCH` requests.
        /// CSJ has always defaulted to performing the `INSERT` statement,
        /// and the object requests have done the `UPDATE`. We need to
        /// keep the default for the object requests so that we don't break
        /// old `PATCH` configurations.
        ///
        /// The new behaviour for object `PATCH` will be supported if
        /// the configuration contains the new columns configuration:
        ///     "insert": "required"

        /// Break apart the data into the key and value parts
        using intermediate_data = std::pair<fostlib::json, fostlib::json>;
        intermediate_data data(const fostlib::json &data);

        /// Perform an INSERT and potentially return a response
        [[nodiscard]] std::pair<boost::shared_ptr<fostlib::mime>, int>
                insert(intermediate_data, std::optional<std::size_t> row = {});
        /// Perform an update
        std::pair<boost::shared_ptr<fostlib::mime>, int>
                update(intermediate_data, std::optional<std::size_t> row = {});

        /// The old APIs which combine the UPDATE/INSERT with the
        /// data processing.
        [[nodiscard]] std::pair<
                std::pair<boost::shared_ptr<fostlib::mime>, int>,
                std::pair<fostlib::json, fostlib::json>>
                upsert(const fostlib::json &data,
                       std::optional<std::size_t> row = {});
        std::pair<fostlib::json, fostlib::json>
                update(const fostlib::json &data);

      private:
        action deduced_action;
        fostlib::json config, col_config;
        std::vector<fostlib::string> returning_cols;

        fostlib::pg::connection &cnx;
        const fostgres::match &m;
        fostlib::http::server::request &req;
    };


    std::pair<boost::shared_ptr<fostlib::mime>, int> schema_check(
            fostlib::pg::connection &cnx,
            const fostlib::json &config,
            const fostgres::match &m,
            fostlib::http::server::request &req,
            const fostlib::json &schema_config,
            const fostlib::json &instance,
            fostlib::jcursor dpos);


}
