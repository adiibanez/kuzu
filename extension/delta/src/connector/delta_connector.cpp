#include "connector/delta_connector.h"

namespace kuzu {
namespace delta_extension {

void DeltaConnector::connect(const std::string& /*dbPath*/, const std::string& /*catalogName*/,
    const std::string& /*schemaName*/, main::ClientContext* context) {
    // Creates an in-memory duckdb instance, then install httpfs and attach postgres.
    instance = std::make_unique<duckdb::DuckDB>(nullptr);
    connection = std::make_unique<duckdb::Connection>(*instance);
    // Install the Desired Extension on DuckDB
    executeQuery("install delta;");
    executeQuery("load delta;");
    executeQuery("install httpfs;");
    executeQuery("load httpfs;");
    initRemoteFSSecrets(context);
}

} // namespace delta_extension
} // namespace kuzu
