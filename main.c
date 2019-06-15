#include "common.h"
#include "sysutil.h"
#include "session.h"

int main(int argc, char **argv)
{
	if (getuid() != 0) {
		fprintf(stderr, "miniftpd: must be started as root\n");
		exit(EXIT_FAILURE);
	}

	int listenfd = tcp_server(NULL, 5188);
	int conn;
	pid_t pid;

	while (1) 
	{
		conn = accept_timeout(listenfd, NULL, 0);
		if (conn == -1)
			ERR_EXIT("accept_timeout");

		session_t sess = 
		{
			/* control connect */
			-1, "", "", "",
			/* child_parent channel */
			-1, -1
		};
		
		pid = fork();
		if (pid == -1)
			ERR_EXIT("fork");

		if (pid == 0)
		{
			close(listenfd);
			sess.ctrl_fd = conn;
			begin_session(&sess);
		}
		else 
		{
			close(conn);
		}
	}

	return 0;
}
