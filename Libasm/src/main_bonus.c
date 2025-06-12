#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


typedef struct	s_list
{
	void			*data;
	struct s_list	*next;
}               t_lits_;