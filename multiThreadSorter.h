#ifndef multiThreadSorter
#define multiThreadSorter
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/syscall.h>
/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

typedef struct _movie
{
	char color[500];
	char director_name[500];
	char num_critic_for_reviews[500];
	char duration[500];
	char director_facebook_likes[500];
	char actor_3_facebook_likes[500];
	char actor_2_name[500];
	char actor_1_facebook_likes[500];
	char gross[500];
	char genres[500];
	char actor_1_name[500];
	char movie_title[500];
	char num_voted_users[500];
	char cast_total_facebook_likes[500];
	char actor_3_name[500];
	char facenumber_in_poster[500];
	char plot_keywords[500];
	char movie_imdb_link[500];
	char num_user_for_reviews[500];
	char language[500];
	char country[500];
	char content_rating[500];
	char budget[500];
	char title_year[500];
	char actor_2_facebook_likes[500];
	char imdb_score[500];
	char aspect_ratio[500];
	char movie_facebook_likes[500];
} Movie;

typedef struct _MovieNode
{
	Movie data;
	// char* string;
	struct _MovieNode *next;
	struct _MovieNode *prev;
} MovieNode;

//Suggestion: define a struct that mirrors a record (row) of the data set
int getDataType(const char *col);
//Suggestion: prototype a mergesort function
#endif
