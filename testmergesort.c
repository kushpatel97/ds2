#include "test.h"

MovieNode *split(MovieNode *head)
{
    MovieNode *fast = head, *slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    MovieNode *temp = slow->next;
    slow->next = NULL;
    return temp;
}
//
MovieNode *merge(MovieNode *first, MovieNode *second, char *column_to_sort)
{
    // If first linked list is empty
    if (!first)
    {
        return second;
    }

    // If second linked list is empty
    if (!second)
    {
        return first;
    }

    char *data1 = (char *)malloc(256);
    char *data2 = (char *)malloc(256);

    if (strcmp(column_to_sort, "color") == 0)
    {
        data1 = first->data.color;
        data2 = second->data.color;
    }
    else if (strcmp(column_to_sort, "director_name") == 0)
    {
        data1 = first->data.director_name;
        data2 = second->data.director_name;
    }
    else if (strcmp(column_to_sort, "num_critic_for_reviews") == 0)
    {
        data1 = first->data.num_critic_for_reviews;
        data2 = second->data.num_critic_for_reviews;
    }
    else if (strcmp(column_to_sort, "duration") == 0)
    {
        data1 = first->data.duration;
        data2 = second->data.duration;
    }
    else if (strcmp(column_to_sort, "director_facebook_likes") == 0)
    {
        data1 = first->data.director_facebook_likes;
        data2 = second->data.director_facebook_likes;
    }
    else if (strcmp(column_to_sort, "actor_3_facebook_likes") == 0)
    {
        data1 = first->data.actor_3_facebook_likes;
        data2 = second->data.actor_3_facebook_likes;
    }
    else if (strcmp(column_to_sort, "actor_2_name") == 0)
    {
        data1 = first->data.actor_2_name;
        data2 = second->data.actor_2_name;
    }
    else if (strcmp(column_to_sort, "actor_1_facebook_likes") == 0)
    {
        data1 = first->data.actor_1_facebook_likes;
        data2 = second->data.actor_1_facebook_likes;
    }
    else if (strcmp(column_to_sort, "gross") == 0)
    {
        data1 = first->data.gross;
        data2 = second->data.gross;
    }
    else if (strcmp(column_to_sort, "genres") == 0)
    {
        data1 = first->data.genres;
        data2 = second->data.genres;
    }
    else if (strcmp(column_to_sort, "actor_1_name") == 0)
    {
        data1 = first->data.actor_1_name;
        data2 = second->data.actor_1_name;
    }
    else if (strcmp(column_to_sort, "movie_title") == 0)
    {
        data1 = first->data.movie_title;
        data2 = second->data.movie_title;
    }
    else if (strcmp(column_to_sort, "num_voted_users") == 0)
    {
        data1 = first->data.num_voted_users;
        data2 = second->data.num_voted_users;
    }
    else if (strcmp(column_to_sort, "cast_total_facebook_likes") == 0)
    {
        data1 = first->data.cast_total_facebook_likes;
        data2 = second->data.cast_total_facebook_likes;
    }
    else if (strcmp(column_to_sort, "actor_3_name") == 0)
    {
        data1 = first->data.actor_3_name;
        data2 = second->data.actor_3_name;
    }
    else if (strcmp(column_to_sort, "facenumber_in_poster") == 0)
    {
        data1 = first->data.facenumber_in_poster;
        data2 = second->data.facenumber_in_poster;
    }
    else if (strcmp(column_to_sort, "plot_keywords") == 0)
    {
        data1 = first->data.plot_keywords;
        data2 = second->data.plot_keywords;
    }
    else if (strcmp(column_to_sort, "movie_imdb_link") == 0)
    {
        data1 = first->data.movie_imdb_link;
        data2 = second->data.movie_imdb_link;
    }
    else if (strcmp(column_to_sort, "num_user_for_reviews") == 0)
    {
        data1 = first->data.num_user_for_reviews;
        data2 = second->data.num_user_for_reviews;
    }
    else if (strcmp(column_to_sort, "language") == 0)
    {
        data1 = first->data.language;
        data2 = second->data.language;
    }
    else if (strcmp(column_to_sort, "country") == 0)
    {
        data1 = first->data.country;
        data2 = second->data.country;
    }
    else if (strcmp(column_to_sort, "content_rating") == 0)
    {
        data1 = first->data.content_rating;
        data2 = second->data.content_rating;
    }
    else if (strcmp(column_to_sort, "budget") == 0)
    {
        data1 = first->data.budget;
        data2 = second->data.budget;
    }
    else if (strcmp(column_to_sort, "title_year") == 0)
    {
        data1 = first->data.title_year;
        data2 = second->data.title_year;
    }
    else if (strcmp(column_to_sort, "actor_2_facebook_likes") == 0)
    {
        data1 = first->data.actor_2_facebook_likes;
        data2 = second->data.actor_2_facebook_likes;
    }
    else if (strcmp(column_to_sort, "imdb_score") == 0)
    {
        data1 = first->data.imdb_score;
        data2 = second->data.imdb_score;
    }
    else if (strcmp(column_to_sort, "aspect_ratio") == 0)
    {
        data1 = first->data.aspect_ratio;
        data2 = second->data.aspect_ratio;
    }
    else if (strcmp(column_to_sort, "movie_facebook_likes") == 0)
    {
        data1 = first->data.movie_facebook_likes;
        data2 = second->data.movie_facebook_likes;
    }
    else
    {
        // printf("Column name does not exist\n");
    }

    // Determine types
    int d_type = getDataType(column_to_sort);
    if (d_type == 0)
    {
        if ((strcmp(data1, data2) < 0))
        {
            first->next = merge(first->next, second, column_to_sort);
            first->next->prev = first;
            first->prev = NULL;
            return first;
        }
        else
        {
            second->next = merge(first, second->next, column_to_sort);
            second->next->prev = second;
            second->prev = NULL;
            return second;
        }
    }
    else if (d_type == 1)
    {
        if (atoi(data1) < atoi(data2))
        {
            first->next = merge(first->next, second, column_to_sort);
            first->next->prev = first;
            first->prev = NULL;
            return first;
        }
        else
        {
            second->next = merge(first, second->next, column_to_sort);
            second->next->prev = second;
            second->prev = NULL;
            return second;
        }
    }
    else if (d_type == 2)
    {
        if (atof(data1) < atof(data2))
        {
            first->next = merge(first->next, second, column_to_sort);
            first->next->prev = first;
            first->prev = NULL;
            return first;
        }
        else
        {
            second->next = merge(first, second->next, column_to_sort);
            second->next->prev = second;
            second->prev = NULL;
            return second;
        }
    }
    else
    {
        fprintf(stderr, "SHOULD NEVER REACH HERE");
    }
    return;
}

// Function to do merge sort
MovieNode *mergeSort(MovieNode *head, char *column_to_sort)
{
    if (!head || !head->next)
        return head;
    MovieNode *second = split(head);

    // Recur for left and right halves
    head = mergeSort(head, column_to_sort);
    second = mergeSort(second, column_to_sort);

    // Merge the two sorted halves
    return merge(head, second, column_to_sort);
}