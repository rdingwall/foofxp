#ifndef FOOFXP_FILE_HPP_INCLUDED
#define FOOFXP_FILE_HPP_INCLUDED

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace foofxp {
namespace model {

class file
{
public:
	
	typedef unsigned long size_type;
	typedef boost::posix_time::ptime time_type;
	typedef enum { plain_old_file, directory, link, other } file_type;
	
	file() : name_(), type_(plain_old_file), size_(0), time_() {};
	
	file(const std::string & name) : 
		name_(name), type_(plain_old_file), size_(0), time_() {};
	
	file(const file & other) :
		name_(other.name_),
		type_(other.type_),
		size_(other.size_),
		time_(other.time_)
	{};
	
	virtual ~file() {};
	
	file & operator=(const file & other)
	{
		name_ = other.name_;
		type_ = other.type_;
		size_ = other.size_;
		time_ = other.time_;
		return *this;
	};
	
	bool operator==(const file & other) const
	{
		return name_ == other.name_ && 
		       type_ == other.type_ &&
		       size_ == other.size_ &&
		       time_ == other.time_;
	};
	
	bool operator!=(const file & other) const
	{
		return name_ != other.name_ ||
		       type_ != other.type_ ||
		       size_ != other.size_ ||
		       time_ != other.time_;
	};
	
	void name(const std::string & name) { name_ = name; };
	void type(file_type type) { type_ = type; };
	void size(size_type size) { size_ = size; };
	void time(time_type time) { time_ = time; };
	
	const std::string name() const { return name_; };
	file_type type() const { return type_; };
	size_type size() const { return size_; };
	time_type time() const { return time_; };
	
	std::string extension() const
	{
		// Find delimiter.
		std::string::size_type offset = name_.rfind('.');
		
		if (offset != std::string::npos && offset != 0)
			return name_.substr(offset + 1);
		else
			return std::string();
	};
	
	bool is_file() const { return type_ == plain_old_file; };
	bool is_link() const { return type_ == link; };
	bool is_directory() const
	{
		return type_ == directory || type_ == link;
	};
	
protected:
	
	std::string name_;
	file_type type_;
	size_type size_;
	time_type time_;
};

} // namespace model
} // namespace foofxp

#endif // FOOFXP_FILE_HPP_INCLUDED
