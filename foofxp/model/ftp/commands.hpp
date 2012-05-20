#ifndef FOOFXP_COMMANDS_HPP_INCLUDED
#define FOOFXP_COMMANDS_HPP_INCLUDED

#include <stdexcept>
#include <string>

namespace foofxp {
namespace model {
namespace ftp {
namespace commands {

std::string auth_tls();
std::string cwd(const std::string & path);
std::string dele(const std::string & path) throw (std::invalid_argument);
std::string feat();
std::string mkdir(const std::string & path) throw (std::invalid_argument);
std::string pass(const std::string & password) throw (std::invalid_argument);
std::string pasv();
std::string pbsz();
std::string pwd();
std::string site(const std::string & command) throw (std::invalid_argument);
std::string stat_l();
std::string user(const std::string & username) throw (std::invalid_argument);

} // namespace commands
} // namespace ftp
} // namespace model
} // namespace foofxp

#endif // FOOFXP_COMMANDS_HPP_INCLUDED
