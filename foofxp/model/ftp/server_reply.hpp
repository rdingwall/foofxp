#ifndef FOOFXP_SERVER_REPLY_HPP_INCLUDED
#define FOOFXP_SERVER_REPLY_HPP_INCLUDED

#include <stdexcept>
#include <string>

namespace foofxp {
namespace model {
namespace ftp {

class server_reply
{
public:
	typedef unsigned short reply_code_type;

	server_reply(const std::string & line);
	
	bool is_end_of_reply() const;
	bool is_valid_format() const {  return is_valid_format_; };
	bool is_transient_negative_reply() const throw(std::invalid_argument);
	bool is_permanent_negative_reply() const throw(std::invalid_argument);
	bool is_negative_reply() const throw(std::invalid_argument);
	std::string get_message() const throw(std::invalid_argument);
	const std::string & original_line() const { return line_; };
	
	reply_code_type get_reply_code() const 
		throw (std::invalid_argument, std::out_of_range);
	std::string get_pwd_path() const throw (std::invalid_argument);
	
private:
	
	static bool is_valid_format(const std::string & line);
	
	std::string line_;
	bool is_valid_format_;
};

} // namespace ftp
} // namespace model
} // namespace foofxp

#endif // FOOFXP_SERVER_REPLY_HPP_INCLUDED
