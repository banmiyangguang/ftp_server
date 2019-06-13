#ifndef _COMMON_H_
#define _COMMON_H_

#include <unistd.h>
#include <error.h>


#include <stdlib.h>
#include <stdio.h>

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} \
	while(0)

#endif /* _COMMON_H_ */
