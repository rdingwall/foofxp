/*
 *  session_controller.h
 *  foofxp
 *
 *  Created by Richard on 17/05/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <algorithm>
#if 0

using std::for_each;

namespace foofxp {
namespace model {

class session_controller
{
public:
	
	void something()
	{
		for_each(sessions_.begin(), sessions_.end(), check_keep_alive);
	};
	
	
	
private:

	void check_keep_alive(session_ptr & session)
	{
		if (session->is_busy())
			return;
		
		if (session->requires_keep_alive())
			session->begin_keep_alive();
	};

	typedef vector<session_ptr> session_ptr_vector;

	session_ptr_vector sessions_;
};

} // namespace model
} // namespace foofxp

#endif