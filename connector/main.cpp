#include <mysqlx/xdevapi.h>
#include <iostream>

int main() {
    try {
        mysqlx::Session sess("localhost", 33060, "root", "Zaq12wsx");

        mysqlx::Schema db = sess.getSchema("grzyby");
        mysqlx::Table table = db.getTable("grzyb");
        mysqlx::RowResult res = table.select("*").execute();

        for (mysqlx::Row row : res) {
            for (unsigned int i = 0; i < row.colCount(); ++i) {
                std::cout << row[i] << " ";
            }
            std::cout << std::endl;
        }
    } catch (...) {
        std::cerr << "error" << std::endl;
    }


    return 0;
}
