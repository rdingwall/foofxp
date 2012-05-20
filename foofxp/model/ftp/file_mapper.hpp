#ifndef FOOFXP_FILE_MAPPER_HPP_INCLUDED
#define FOOFXP_FILE_MAPPER_HPP_INCLUDED

#include <string>
#include <vector>
#include "../file.hpp"

namespace foofxp {
namespace model {
namespace ftp {

std::vector<file> get_files(const std::vector<std::string> & lines);

} // namespace ftp
} // namespace model
} // namespace foofxp

#endif // FOOFXP_FILE_MAPPER_HPP_INCLUDED