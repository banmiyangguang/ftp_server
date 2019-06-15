#include "session.h"
#include "ftpproto.h"
#include "privparent.h"


void begin_session(session_t *sess)
{
	pid_t pid;
	int sockfds[2];

	if(socketpair(PF_UNIX, SOCK_STREAM, 0, sockfds) < 0)
		ERR_EXIT("socketpair");

	pid = fork();
	if (pid < 0)
		ERR_EXIT("fork");

	if (pid == 0) 
	{
		// ftp server process
		close(sockfds[0]);
		sess->child_fd = sockfds[1];
		handle_child(sess);
		
	}
	else 
	{
		//nobody process
		close(sockfds[1]);
		sess->parent_fd = sockfds[0];
		handle_parent(sess);
	}
}