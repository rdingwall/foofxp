#ifndef FOOFXP_BOOKMARK_HPP_INCLUDED
#define FOOFXP_BOOKMARK_HPP_INCLUDED

#include <string>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread_safe_signal.hpp>
#include "port_type.hpp"

namespace foofxp {
namespace model {
namespace ftp {

class bookmark : public boost::enable_shared_from_this<bookmark>
{
public:
	
	typedef boost::signal<void(bookmark & sender)> bookmark_event;
	
	bookmark() : 
		name_(),
		auth_tls_(true),
		tls_data_(false),
		host_(),
		port_(21),
		ipv6_(false),
		username_(),
		password_(),
		path_()
	{};
	
	bookmark(const bookmark & other) : 
		name_(other.name_),
		auth_tls_(other.auth_tls_),
		tls_data_(other.tls_data_),
		host_(other.host_),
		port_(other.port_),
		ipv6_(other.ipv6_),
		username_(other.username_),
		password_(other.password_),
		path_(other.path_)
	{};
	
	virtual ~bookmark() {};
	
	virtual bookmark & operator=(const bookmark & other)
	{
		name_     = other.name_;
		auth_tls_ = other.auth_tls_;
		tls_data_ = other.tls_data_;
		host_     = other.host_;
		port_     = other.port_;
		ipv6_     = other.ipv6_;
		username_ = other.username_;
		password_ = other.password_;
		path_     = other.path_;
		
		modified(*this);
		
		return *this;
	};
	
	virtual bool operator==(const bookmark & other) const
	{
		return name_     == other.name_ &&
		       auth_tls_ == other.auth_tls_ &&
		       tls_data_ == other.tls_data_ &&
		       host_     == other.host_ &&
		       port_     == other.port_ &&
		       ipv6_     == other.ipv6_ &&
		       username_ == other.username_ &&
		       password_ == other.password_ &&
		       path_     == other.path_;
	};
	
	virtual bool operator!=(const bookmark & other) const
	{
		return name_     != other.name_ ||
		       auth_tls_ != other.auth_tls_ ||
		       tls_data_ != other.tls_data_ ||
		       host_     != other.host_ ||
		       port_     != other.port_ ||
		       ipv6_     != other.ipv6_ ||
		       username_ != other.username_ ||
		       password_ != other.password_ ||
		       path_     != other.path_;
	};
	
	bookmark_event modified;
	
	void name(const std::string & name)
	{
		name_ = name;
		modified(*this);
	};
	
	void auth_tls(bool auth_tls)
	{
		auth_tls_ = auth_tls;
		modified(*this);
	};
	
	void tls_data(bool tls_data)
	{
		tls_data_ = tls_data;
		modified(*this);
	};
	
	void host(const std::string & host)
	{
		host_ = host;
		modified(*this);
	};
	
	void port(const port_type port)
	{
		port_ = port;
		modified(*this);
	};
	
	void ipv6(const bool ipv6)
	{
		ipv6_ = ipv6;
		modified(*this);
	};
	
	void username(const std::string & username)
	{
		username_ = username;
		modified(*this);
	};
	
	void password(const std::string & password)
	{
		password_ = password;
		modified(*this);
	};
	
	void path(const std::string & path)
	{
		path_ = path;
		modified(*this);
	};
	
	const std::string name() const { return name_; };
	bool auth_tls() const { return auth_tls_; };
	bool tls_data() const { return tls_data_; };
	const std::string host() const { return host_; };
	port_type port() const { return port_; };
	bool ipv6() const { return ipv6_; };
	const std::string username() const { return username_; };
	const std::string password() const { return password_; };
	const std::string path() const { return path_; };
		
protected:
	
	std::string name_;
	bool auth_tls_;
	bool tls_data_;
	std::string host_;
	port_type port_;
	bool ipv6_;
	std::string username_;
	std::string password_;
	std::string path_;
	
}; // class bookmark

} // namespace ftp
} // namespace model
} // namespace foofxp

#endif // FOOFXP_BOOKMARK_HPP_INCLUDED
