#include <iostream>
#include <rai/lib/utility.hpp>

namespace rai
{
namespace thread_role
{
	/*
	 * rai::thread_role namespace
	 *
	 * Manage thread role
	 */
	static thread_local rai::thread_role::name current_thread_role = rai::thread_role::name::unknown;
	rai::thread_role::name get (void)
	{
		return current_thread_role;
	}

	void set (rai::thread_role::name role)
	{
		std::string thread_role_name_string;

		switch (role)
		{
			case rai::thread_role::name::unknown:
				thread_role_name_string = "<unknown>";
				break;
			case rai::thread_role::name::io:
				thread_role_name_string = "I/O";
				break;
			case rai::thread_role::name::work:
				thread_role_name_string = "Work pool";
				break;
			case rai::thread_role::name::packet_processing:
				thread_role_name_string = "Pkt processing";
				break;
			case rai::thread_role::name::alarm:
				thread_role_name_string = "Alarm";
				break;
			case rai::thread_role::name::vote_processing:
				thread_role_name_string = "Vote processing";
				break;
			case rai::thread_role::name::block_processing:
				thread_role_name_string = "Blck processing";
				break;
			case rai::thread_role::name::announce_loop:
				thread_role_name_string = "Announce loop";
				break;
			case rai::thread_role::name::wallet_actions:
				thread_role_name_string = "Wallet actions";
				break;
			case rai::thread_role::name::bootstrap_initiator:
				thread_role_name_string = "Bootstrap init";
				break;
			case rai::thread_role::name::voting:
				thread_role_name_string = "Voting";
				break;
			case rai::thread_role::name::signature_checking:
				thread_role_name_string = "Signature check";
				break;
		}

		/*
		 * We want to constrain the thread names to 15
		 * characters, since this is the smallest maximum
		 * length supported by the platforms we support
		 * (specifically, Linux)
		 */
		assert (thread_role_name_string.size () < 16);

		rai::thread_role::set_name (thread_role_name_string);

		rai::thread_role::current_thread_role = role;
	}
}
}

void rai::thread_attributes::set (boost::thread::attributes & attrs)
{
	auto attrs_l (&attrs);
	attrs_l->set_stack_size (8000000); //8MB
}

/*
 * Backing code for "release_assert", which is itself a macro
 */
void release_assert_internal (bool check, const char * check_expr, const char * file, unsigned int line)
{
	if (check)
	{
		return;
	}

	std::cerr << "Assertion (" << check_expr << ") failed " << file << ":" << line << std::endl;
	abort ();
}
