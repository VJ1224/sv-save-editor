#include <stdio.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>

PGconn *conn = PQconnectdb("user=doadmin dbname=saves host=db-postgres-sveditor-do-user-7743111-0.b.db.ondigitalocean.com password=dnr98u98ixayr7gz port=25060 sslmode = require");

namespace database {
void insertFile(const char* username, const char* filename, const char* xml) {
    const char *paramValues[3];
    paramValues[0] = username;
    paramValues[1] = filename;
    paramValues[2] = xml;

    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
    }

    const char *stm = "INSERT INTO saves VALUES($1,$2,XML($3),NOW())";
    PGresult *res = PQexecParams(conn, stm, 3, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Error: %s\n",
            PQerrorMessage(conn));
    }
}

char* getFile(const char* name) {
    const char *paramValues[1];
    paramValues[0] = name;

    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
    }

    const char *stm = "SELECT * FROM saves WHERE name=$1 LIMIT 1";
    PGresult *res = PQexecParams(conn, stm, 1, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
    }

    return PQgetvalue(res, 0, 1);
}
}