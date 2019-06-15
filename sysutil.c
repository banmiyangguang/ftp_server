#include "sysutil.h"

/*
 * tcp_server - start server
 * @host: IP or hostname
 * @port: port
 * success: return listen socket
 */
int tcp_server(const char *host, unsigned short port)
{
	int listenfd;
	if ((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		ERR_EXIT("tcp_server");
	}
	
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	if (host != NULL) {
		if (inet_aton(host, &servaddr.sin_addr) == 0) {
			struct hostent *hp;
			hp = gethostbyname(host);
			if (hp == NULL) {
				ERR_EXIT("gethostbyname");
			}
			servaddr.sin_addr = *(struct in_addr*)hp->h_addr;
		}
	} else {
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}

	servaddr.sin_port = htons(port);

	int on = 1;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
		ERR_EXIT("setsockopt");
	}

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		ERR_EXIT("bind");
	}

	if (listen(listenfd, SOMAXCONN) < 0) {
		ERR_EXIT("listen");
	}
	
	return listenfd;
}

int getlocalip(char *ip)
{
	char host[100] = {0};
	if (gethostname(host, sizeof(host)) < 0) {
		return -1;
	}
	struct hostent *hp;
	if ((hp = gethostbyname(host)) == NULL) {
		return -1;
	}

	strcpy(ip, inet_ntoa(*(struct in_addr*)hp->h_addr));
	return 0;
}

/*
	set fd nonblock
*/
void activate_nonblock(int fd)
{
	int ret;
	int flags = fcntl(fd, F_GETFL);
	if (flags == -1) {
		ERR_EXIT("fcntl");
	}

	flags |= O_NONBLOCK;
	ret = fcntl(fd, F_SETFL, flags);
	if (ret == -1) {
		ERR_EXIT("fcntl");
	}
}

/*
 * cancel fd nonblock
 */
void deactivate_nonblock(int fd)
{
	int ret;
	int flags = fcntl(fd, F_GETFL);
	if (flags == -1)
		ERR_EXIT("fcntl");
	
	flags &= ~O_NONBLOCK;
	ret = fcntl(fd, F_SETFL, flags);
	if (ret == -1)
		ERR_EXIT("fcntl");
}

int read_timeout(int fd, unsigned int wait_seconds)
{
	int ret = 0;
	if (wait_seconds > 0)
	{
		fd_set read_fdset;
		struct timeval timeout;

		FD_ZERO(&read_fdset);
		FD_SET(fd, &read_fdset);

		timeout.tv_sec = wait_seconds;
		timeout.tv_usec = 0;
		do {
			ret = select(fd + 1, &read_fdset, NULL, NULL, &timeout);
		} while (ret < 0 && errno == EINTR);

		if (ret == 0)
		{
			ret = -1;
			errno = ETIMEDOUT;
		}
		else if (ret == -1)
			ret = 0;
	}

	return ret;
}

int write_timeout(int fd, unsigned int wait_seconds)
{
	
	int ret = 0;
	if (wait_seconds > 0)
	{
		fd_set write_fdset;
		struct timeval timeout;

		FD_ZERO(&write_fdset);
		FD_SET(fd, &write_fdset);

		timeout.tv_sec = wait_seconds;
		timeout.tv_usec = 0;
		do {
			ret = select(fd + 1, &write_fdset, NULL, NULL, &timeout);
		} while (ret < 0 && errno == EINTR);

		if (ret == 0)
		{
			ret = -1;
			errno = ETIMEDOUT;
		}
		else if (ret == -1)
			ret = 0;
	}

	return ret;
}
int accept_timeout(int fd, struct sockaddr_in *addr, unsigned int wait_seconds)
{
	int ret;
	socklen_t addrlen = sizeof(struct sockaddr_in);

	if (wait_seconds > 0) {
		fd_set accept_fdset;
		struct timeval timeout;
		
		FD_ZERO(&accept_fdset);
		FD_SET(fd, &accept_fdset);
		timeout.tv_sec = wait_seconds;
		timeout.tv_usec = 0;
		do {
			ret = select(fd + 1, &accept_fdset, NULL, NULL, &timeout);
		} while (ret < 0 && errno == EINTR);

		if (ret == -1) {
			return -1;
		} else if (ret == 0) {
			errno = ETIMEDOUT;
			return -1;
		}
	}

	if (addr != NULL) {
		ret = accept(fd, (struct sockaddr*)addr, &addrlen);
	} else {
		ret = accept(fd, NULL, NULL);
	}

	return ret;
}
int connect_timeout(int fd, struct sockaddr_in *addr, unsigned int wait_secondd)
{
	return 0;
}

ssize_t readn(int fd, void *buf, size_t count)
{
	return 0;
}
ssize_t writen(int fd, const void *buf, size_t count)
{
	return 0;
}
ssize_t recv_peek(int sockfd, void *buf, size_t len)
{
	return 0;
}
ssize_t readline(int sockfd, void *buf, size_t maxline)
{
	return 0;
}

void send_fd(int sock_fd, int fd)
{

}
int recv_fd(const int sock_fd)
{
	return 0;
}
