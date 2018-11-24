#ifndef test
#define test
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
/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

typedef struct _movie
{
	char *color;
	char *director_name;
	char *num_critic_for_reviews;
	char *duration;
	char *director_facebook_likes;
	char *actor_3_facebook_likes;
	char *actor_2_name;
	char *actor_1_facebook_likes;
	char *gross;
	char *genres;
	char *actor_1_name;
	char *movie_title;
	char *num_voted_users;
	char *cast_total_facebook_likes;
	char *actor_3_name;
	char *facenumber_in_poster;
	char *plot_keywords;
	char *movie_imdb_link;
	char *num_user_for_reviews;
	char *language;
	char *country;
	char *content_rating;
	char *budget;
	char *title_year;
	char *actor_2_facebook_likes;
	char *imdb_score;
	char *aspect_ratio;
	char *movie_facebook_likes;
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
