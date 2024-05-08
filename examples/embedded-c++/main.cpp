#include "duckdb.hpp"

using namespace duckdb;

int main() {
	DuckDB db(nullptr);

	Connection con(db);

	con.Query("CREATE TABLE t1(i INTEGER)");
	con.Query("INSERT INTO t1 VALUES (3)");
	con.Query("INSERT INTO t1 VALUES (2)");

	con.Query("CREATE TABLE t2(i INTEGER)");
	con.Query("INSERT INTO t2 VALUES (3)");
	con.Query("INSERT INTO t2 VALUES (4)");

	auto result = con.SendQuery("SELECT * FROM t1,t2 WHERE t1.i = t2.i;");

	auto chunk = result->FetchRaw();
	while (chunk != nullptr) {
		chunk->Print();
		chunk = result->FetchRaw();
	}

	auto res = con.Query("EXPLAIN SELECT * FROM t1,t2 WHERE t1.i = t2.i;");
	res->Print();
}
								