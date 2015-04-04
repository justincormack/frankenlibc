#include <signal.h>
#include <lwp.h>

int raise(int) __attribute__ ((weak));

int
raise(int s)
{

	return _lwp_kill(_lwp_self(), s);
}
