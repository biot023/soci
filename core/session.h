//
// Copyright (C) 2004-2007 Maciej Sobczak, Stephen Hutton
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef SOCI_SESSION_H_INCLUDED
#define SOCI_SESSION_H_INCLUDED

#include "once-temp-type.h"

#include <ostream>
#include <string>

namespace soci
{
class values;
struct backend_factory;

namespace details
{

class session_backend;
class statement_backend;
class rowid_backend;
class blob_backend;

} // namespace details

class SOCI_DECL session
{
public:
    session();
    session(backend_factory const &factory, std::string const & connectString);

    ~session();

    void open(backend_factory const &factory, std::string const & connectString);
    void close();
    void reconnect();

    // once and prepare are for syntax sugar only
    details::once_type once;
    details::prepare_type prepare;

    // even more sugar
    template <typename T>
    details::once_temp_type operator<<(T const &t) { return once << t; }

    // support for basic logging
    void set_log_stream(std::ostream *s);
    std::ostream * get_log_stream() const;

    void log_query(std::string const &query);
    std::string get_last_query() const;

    // for diagnostics and advanced users
    // (downcast it to expected back-end session class)
    details::session_backend * get_backend() { return backEnd_; }

    details::statement_backend * make_statement_backend();
    details::rowid_backend * make_rowid_backend();
    details::blob_backend * make_blob_backend();

private:
    session(session const &);
    session& operator=(session const &);

    std::ostream *logStream_;
    std::string lastQuery_;

    backend_factory const *lastFactory_;
    std::string lastConnectString_;

    details::session_backend *backEnd_;
};

} // namespace SOCI
#endif
