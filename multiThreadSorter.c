#include "multiThreadSorter.h"
#include "mergesort.c"

void *searchDirectory(void *_directory);

// GLOBAL VARIABLES
pthread_mutex_t mutex;
int g_count = 0;
char *g_column;
char *g_output;
char* g_column_headers = "color,director_name,num_critic_for_reviews,duration,director_facebook_"
"likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,"
"genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_"
"likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,"
"num_user_for_reviews,language,country,content_rating,budget,title_year,"
"actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes";

pthread_t *threads;
// pthread_t *thread_copy;

MovieNode *g_head = NULL;

long p_tid;

/*
Params: col - A constant string paramater
Returns: Integer - returns the following depending on the type of the string
           |__ 0 = String
           |__ 1 = Int
           |__ 2 = Double
*/
int getDataType(const char *col) {
  int string = 0;
  int doub = 2;
  int inte = 1;
  if (strcmp(col, "color") == 0) {
    return string;
  } else if (strcmp(col, "director_name") == 0) {
    return string;
  } else if (strcmp(col, "num_critic_for_reviews") == 0) {
    return inte;
  } else if (strcmp(col, "duration") == 0) {
    return inte;
  } else if (strcmp(col, "director_facebook_likes") == 0) {
    return inte;
  } else if (strcmp(col, "actor_3_facebook_likes") == 0) {
    return inte;
  } else if (strcmp(col, "actor_2_name") == 0) {
    return string;
  } else if (strcmp(col, "actor_1_facebook_likes") == 0) {
    return inte;
  } else if (strcmp(col, "gross") == 0) {
    return doub;
  } else if (strcmp(col, "genres") == 0) {
    return string;
  } else if (strcmp(col, "actor_1_name") == 0) {
    return string;
  } else if (strcmp(col, "movie_title") == 0) {
    return string;
  } else if (strcmp(col, "num_voted_users") == 0) {
    return inte;
  } else if (strcmp(col, "cast_total_facebook_likes") == 0) {
    return inte;
  } else if (strcmp(col, "actor_3_name") == 0) {
    return string;
  } else if (strcmp(col, "facenumber_in_poster") == 0) {
    return inte;
  } else if (strcmp(col, "plot_keywords") == 0) {
    return string;
  } else if (strcmp(col, "movie_imdb_link") == 0) {
    return string;
  } else if (strcmp(col, "num_user_for_reviews") == 0) {
    return inte;
  } else if (strcmp(col, "language") == 0) {
    return string;
  } else if (strcmp(col, "country") == 0) {
    return string;
  } else if (strcmp(col, "content_rating") == 0) {
    return string;
  } else if (strcmp(col, "budget") == 0) {
    return doub;
  } else if (strcmp(col, "title_year") == 0) {
    return inte;
  } else if (strcmp(col, "actor_2_facebook_likes") == 0) {
    return inte;
  } else if (strcmp(col, "imdb_score") == 0) {
    return doub;
  } else if (strcmp(col, "aspect_ratio") == 0) {
    return doub;
  } else if (strcmp(col, "movie_facebook_likes") == 0) {
    return inte;
  } else {
    // printf("Column name does not exist\n");
    return -1;
  }
}

char *trim(char *token) {
  char *end;

  while (isspace((unsigned char)*token)) {
    token++;
  }

  if (*token == 0) {
    return token;
  }

  end = token + strlen(token) - 1;
  while (end > token && isspace((unsigned char)*end)) {
    end--;
  }
  end[1] = '\0';

  return token;
}

void push(MovieNode **head, Movie *movie_data) {
  MovieNode *new_node = (MovieNode *)malloc(sizeof(MovieNode));
  new_node->data = *movie_data;
  new_node->next = *head;
  new_node->prev = NULL;
  if ((*head) != NULL) {
    (*head)->prev = new_node;
  }
  *head = new_node;
}

void map(Movie *movie_data, char *field, char *column) {
  if (field == NULL) {
    field = "\0";
  }

  if (strcmp(column, "color") == 0) {
    // movie_data->color = malloc(strlen(field) + 2);
    strcpy(movie_data->color, field);
  } else if (strcmp(column, "director_name") == 0) {
    // movie_data->director_name = malloc(strlen(field) + 2);
    strcpy(movie_data->director_name, field);
  } else if (strcmp(column, "num_critic_for_reviews") == 0) {
    // movie_data->num_critic_for_reviews = malloc(strlen(field) + 2);
    strcpy(movie_data->num_critic_for_reviews, field);
  } else if (strcmp(column, "duration") == 0) {
    // movie_data->duration = malloc(strlen(field) + 2);
    strcpy(movie_data->duration, field);
  } else if (strcmp(column, "director_facebook_likes") == 0) {
    // movie_data->director_facebook_likes = malloc(strlen(field) + 2);
    strcpy(movie_data->director_facebook_likes, field);
  } else if (strcmp(column, "actor_3_facebook_likes") == 0) {
    // movie_data->actor_3_facebook_likes = malloc(strlen(field) + 2);
    strcpy(movie_data->actor_3_facebook_likes, field);
  } else if (strcmp(column, "actor_2_name") == 0) {
    // movie_data->actor_2_name = malloc(strlen(field) + 2);
    strcpy(movie_data->actor_2_name, field);
  } else if (strcmp(column, "actor_1_facebook_likes") == 0) {
    // movie_data->actor_1_facebook_likes = malloc(strlen(field) + 2);
    strcpy(movie_data->actor_1_facebook_likes, field);
  } else if (strcmp(column, "gross") == 0) {
    // movie_data->gross = malloc(strlen(field) + 2);
    strcpy(movie_data->gross, field);
  } else if (strcmp(column, "genres") == 0) {
    // movie_data->genres = malloc(strlen(field) + 2);
    strcpy(movie_data->genres, field);
  } else if (strcmp(column, "actor_1_name") == 0) {
    // movie_data->actor_1_name = malloc(strlen(field) + 2);
    strcpy(movie_data->actor_1_name, field);
  } else if (strcmp(column, "movie_title") == 0) {
    // movie_data->movie_title = malloc(strlen(field) + 2);
    strcpy(movie_data->movie_title, field);
  } else if (strcmp(column, "num_voted_users") == 0) {
    // movie_data->num_voted_users = malloc(strlen(field) + 2);
    strcpy(movie_data->num_voted_users, field);
  } else if (strcmp(column, "cast_total_facebook_likes") == 0) {
    // movie_data->cast_total_facebook_likes = malloc(strlen(field) + 2);
    strcpy(movie_data->cast_total_facebook_likes, field);
  } else if (strcmp(column, "actor_3_name") == 0) {
    // movie_data->actor_3_name = malloc(strlen(field) + 2);
    strcpy(movie_data->actor_3_name, field);
  } else if (strcmp(column, "facenumber_in_poster") == 0) {
    // movie_data->facenumber_in_poster = malloc(strlen(field) + 2);
    strcpy(movie_data->facenumber_in_poster, field);
  } else if (strcmp(column, "plot_keywords") == 0) {
    // movie_data->plot_keywords = malloc(strlen(field) + 2);
    strcpy(movie_data->plot_keywords, field);
  } else if (strcmp(column, "movie_imdb_link") == 0) {
    // movie_data->movie_imdb_link = malloc(strlen(field) + 2);
    strcpy(movie_data->movie_imdb_link, field);
  } else if (strcmp(column, "num_user_for_reviews") == 0) {
    // movie_data->num_user_for_reviews = malloc(strlen(field) + 2);
    strcpy(movie_data->num_user_for_reviews, field);
  } else if (strcmp(column, "language") == 0) {
    // movie_data->language = malloc(strlen(field) + 2);
    strcpy(movie_data->language, field);
  } else if (strcmp(column, "country") == 0) {
    // movie_data->country = malloc(strlen(field) + 2);
    strcpy(movie_data->country, field);
  } else if (strcmp(column, "content_rating") == 0) {
    // movie_data->content_rating = malloc(strlen(field) + 2);
    strcpy(movie_data->content_rating, field);
  } else if (strcmp(column, "budget") == 0) {
    // movie_data->budget = malloc(strlen(field) + 2);
    strcpy(movie_data->budget, field);
  } else if (strcmp(column, "title_year") == 0) {
    // movie_data->title_year = malloc(strlen(field) + 2);
    strcpy(movie_data->title_year, field);
  } else if (strcmp(column, "actor_2_facebook_likes") == 0) {
    // movie_data->actor_2_facebook_likes = malloc(strlen(field) + 2);
    strcpy(movie_data->actor_2_facebook_likes, field);
  } else if (strcmp(column, "imdb_score") == 0) {
    // movie_data->imdb_score = malloc(strlen(field) + 2);
    strcpy(movie_data->imdb_score, field);
  } else if (strcmp(column, "aspect_ratio") == 0) {
    // movie_data->aspect_ratio = malloc(strlen(field) + 2);
    strcpy(movie_data->aspect_ratio, field);
  } else if (strcmp(column, "movie_facebook_likes") == 0) {
    // movie_data->movie_facebook_likes = malloc(strlen(field) + 2);
    strcpy(movie_data->movie_facebook_likes, field);
  } else {
    return;
  }
}

void *thread_function_file(void *_file) {
  fprintf(stdout, "%u, ",syscall(__NR_gettid) );
  fflush(stdout);

  pthread_mutex_lock(&mutex);
  char *filepath = (char *)_file;
  // fprintf(stdout, "[F]: %s\n", filepath);
  // FUNCTION VARIABLES
  int NUMBER_OF_COLUMNS = 0;

  FILE *fptr;
  fptr = fopen(filepath, "r");

  //============= SET HEADER ARRAY HERE =============
  if (fptr == NULL) {
    fprintf(stderr, "[22]: Can't open file\n");
  }
  char h_line[1024];
  char *file_headers = fgets(h_line, 1024, fptr);

  if (file_headers != NULL) {
    if (strstr(g_column_headers, g_column) != NULL) {
      // fprintf(stdout,"\tFILE HEADERS: %s\n",file_headers);

      // COUNT NUMBER OF HEADERS IN FILE
      char *h_token_counter;
      char *temp_counter = strdup(file_headers);

      while ((h_token_counter = strtok_r(temp_counter, ",", &temp_counter))) {
        // fprintf(stdout,"%s\n",h_token);
        NUMBER_OF_COLUMNS++;
      }

      // GO BACK TO TOP OF THE FILE
      rewind(fptr);

      // BUILD HEADER ARRAY
      file_headers = fgets(h_line, 1024, fptr);

      char *h_token;
      char *temp = strdup(file_headers);
      char *h_array[NUMBER_OF_COLUMNS];

      int h_index = 0;

      while ((h_token = strtok_r(temp, ",", &temp)) &&
             (h_index < NUMBER_OF_COLUMNS)) {
        h_array[h_index] = trim(h_token);
        h_index++;
      }

      // for (int j = 0; j < NUMBER_OF_COLUMNS; j++)
      // {
      // printf("[%d]: %s\n",j,h_array[j]);
      // }
      // fprintf(stdout,"\tFILE HEADERS: %s\n",file_headers);

      //============= START MAPPING FIELDS HERE =============
      //============= Variables =============
      int NUMBER_OF_NODES = 0;

      char f_line[1024];
      while (fgets(f_line, 1024, fptr) != NULL) {
        char *f_temp = strdup(f_line);
        f_temp = trim(f_temp);
        // fprintf(stdout,"%s\n",f_line);

        Movie *new_movie = (Movie *)malloc(sizeof(Movie));

        int CURRENT_COLUMN = 0;
        while (CURRENT_COLUMN < NUMBER_OF_COLUMNS) {
          char *quote = "\"";
          char *comma = ",";
          char *f_token;
          // char* front = &temp[0];
          if (f_temp[0] != '\"') {
            f_token = strsep(&f_temp, comma);
          } else {
            f_temp++;
            f_token = strsep(&f_temp, quote);
            f_temp++;
          }

          f_token = trim(f_token);

          map(new_movie, f_token, h_array[CURRENT_COLUMN]);

          CURRENT_COLUMN++;
        }
        // if(CURRENT_COLUMN != NUMBER_OF_COLUMNS){
        //   fprintf(stderr, "BAD CSV FILE: Number of columns does not match the numbe of headers\n");
        //   exit(0);
        //   return;
        // }else{
          push(&g_head, new_movie);
        // }

        // printNode(new_movie);
        free(new_movie);
      }
      // fprintf(stdout,"NUMBER OF COLUMNS: %d\n",NUMBER_OF_COLUMNS);
    } else {
      fprintf(stderr, "[INVALID HEADERS]: %s does not exist in the global headers for %s.\n", g_column,
              filepath);
    }
  } else {
    fprintf(stderr, "\t[BAD INPUT]: No headers in %s\n", filepath);
  }

  // printf("NUMBER OF COLUMNS: %d\n",NUMBER_OF_COLUMNS);

  fclose(fptr);
  pthread_mutex_unlock(&mutex);
  // pthread_exit(0);
  return 0;
}

void *searchDirectory(void *_directory) {

  if(p_tid != syscall(__NR_gettid)){
    fprintf(stdout, "%u\n",syscall(__NR_gettid) );
    fflush(stdout);
  }

  char *directory = (char *)_directory;
  struct dirent *sd;
  DIR *dir;
  dir = opendir(directory);

  if (dir == NULL) {
    printf("Unable to open directory\n");
    exit(1);
  }
  while ((sd = readdir(dir)) != NULL) {

    // fprintf(stdout, "%u\n",syscall(__NR_gettid) );

    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", directory, sd->d_name);
    // fprintf(stdout,"%s\n",path);

    if (strcmp(sd->d_name, ".git") == 0|| strcmp(sd->d_name, ".") == 0 || strcmp(sd->d_name, "..") == 0) {
      continue;
    }
    if (sd->d_type == DT_DIR) {
      // Directory
      // g_count++;
      // pthread_t thread_directory_id;
      // fprintf(stdout, "%lu, ", thread_directory_id);
      // fflush(stdout);
      // fprintf(stdout,"%s\n",path);
      // thread_copy[g_count] = threads[g_count];
      pthread_create(&threads[g_count], NULL, searchDirectory, path);
      pthread_join(threads[g_count], NULL);

      g_count++;
      // pthread_exit(0);
      // searchDirectory(path);
    } else if (sd->d_type == DT_REG) {
      // Regular File

      // g_count++;
      // pthread_t thread_file_id;
      // // printf("%lu\n",thread_file_id);
      // fprintf(stdout, "%lu, ", thread_file_id);
      // fflush(stdout);

      char *csv_extension = &(sd->d_name)[strlen(sd->d_name) - 4];
      // int filelength = strlen(sd->d_name);

      // fprintf(stdout,"%s\n",path);
      if ((strcmp(csv_extension, ".csv") == 0) &&
          !(strstr(sd->d_name, "-sorted-"))) {
            // thread_copy[g_count] = threads[g_count];

        pthread_create(&threads[g_count], NULL, thread_function_file, path);
        pthread_join(threads[g_count], NULL);

        g_count++;
        // pthread_exit(0);
      }
    } else {
      continue;
    }
  }
  closedir(dir);
  return NULL;
}

void printNode(Movie *movie_data, FILE *fp) {
  fprintf(fp,
          "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\"%s\",%s,%s,%s,%s,%s,%s,%s,%s,%s,%"
          "s,%s,%s,%s,%s,%s,%s\n",
          movie_data->color, movie_data->director_name,
          movie_data->num_critic_for_reviews, movie_data->duration,
          movie_data->director_facebook_likes,
          movie_data->actor_3_facebook_likes, movie_data->actor_2_name,
          movie_data->actor_1_facebook_likes, movie_data->gross,
          movie_data->genres, movie_data->actor_1_name, movie_data->movie_title,
          movie_data->num_voted_users, movie_data->cast_total_facebook_likes,
          movie_data->actor_3_name, movie_data->facenumber_in_poster,
          movie_data->plot_keywords, movie_data->movie_imdb_link,
          movie_data->num_user_for_reviews, movie_data->language,
          movie_data->country, movie_data->content_rating, movie_data->budget,
          movie_data->title_year, movie_data->actor_2_facebook_likes,
          movie_data->imdb_score, movie_data->aspect_ratio,
          movie_data->movie_facebook_likes);
}

void printList(MovieNode *node, char *output_dir) {

  if (opendir(output_dir) == NULL) {
    mkdir(output_dir, S_IRWXU);
  }

  char newPath[2048];
  snprintf(newPath, sizeof(newPath), "%s/AllFiles-sorted-%s.csv", output_dir,
           g_column);

  FILE *fptr;
  fptr = fopen(newPath, "w");
  fprintf(
      fptr,
      "color,director_name,num_critic_for_reviews,duration,director_facebook_"
      "likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,"
      "genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_"
      "likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,"
      "num_user_for_reviews,language,country,content_rating,budget,title_year,"
      "actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes\n");
  MovieNode *last;
  while (node != NULL) {
    printNode(&(node->data), fptr);
    last = node;
    node = node->next;
  }
}

int main(int argc, char **argv) {
  // printf("%s\n", NULL);]

  // if(argc == 3){
  //   fprintf(stdout, "%d,%s,%s\n",argc,argv[1],argv[2]);
  //
  // }else if(argc==5){
  //   fprintf(stdout, "%d,%s,%s,%s,%s\n",argc,argv[1],argv[2],argv[3],argv[4]);
  //
  // }else{
  //   fprintf(stdout, "%d,%s,%s,%s,%s,%s,%s\n",argc,argv[1],argv[2],argv[3],argv[4],argv[5],argv[6] );
  //
  // }
  // fprintf(stdout, "%d,%s,%s,%s,%s,%s,%s\n",argc,argv[1],argv[2],argv[3],argv[4],argv[5],argv[6] );
  g_column = (char*)malloc(strlen(argv[2])+2);
  g_output = (char*)malloc(1024);
  // int arg_counter;
  // for(arg_counter=0;arg_counter<argc;arg_counter++){
  //   if(strcmp("-c",argv[arg_counter])==0){
  //
  //   }
  // }

  char *searchDir;
  if (argc < 3) {
    fprintf(stderr, "Not enough parameters\n");
    exit(0);
    return -1;
  }

  if (argc > 7) {
    fprintf(stderr, "Too many parameters\n");
    exit(0);
    return -1;
  }
  /*
  NEED TO FIX:
      FIRST CREATE HEADER ARRAY THEN CHECK IF VALID
      NEED TO MAKE SURE IF ONLY -o IS VALID WITHOUT -d
  UPDATED:
      ORGANIZED DUSTIN'S CHANGES
  */
  // if (validColumn(argv[2]) == -1)
  // {
  //     fprintf(stderr, "%s is not a valid column type. Please try again.\n",
  //     argv[2]); exit(0); return -1;
  // }

  if (argc == 3) {
    // printf("#Args \t Name\n");
    // printf("%d \t %s\n",argc, argv[2]);
    // printf("Argument Namet: %s\n", argv[4]);

    if (strcmp(argv[1], "-c") == 0) {
      g_column = argv[2];
      searchDir = ".";
      g_output = ".";
    } else {
      fprintf(stderr, "%s is not a valid column type. Please use \"-c\".\n",
              argv[1]);
      exit(0);
      return -1;
    }
  }

  if (argc == 5) {
    // printf("#Args \t Name\n");
    // printf("%d \t %s\n",argc, argv[4]);
    if(strcmp(argv[1],"-c")==0 || strcmp(argv[3],"-c")==0){
      // DO nothing
      // int dt = getDataType(argv[2])
    }else{
      fprintf(stderr, "-c does not exist in the arguments. Please include -c.\n");
      exit(0);
      return -1;
    }
    if(strcmp(argv[1],"-c")==0 ){
      if (strcmp(argv[3], "-o") == 0) {
        if ((strcmp(argv[3], "-o") == 0) && argv[4] != NULL) {
          searchDir = ".";
          g_output = argv[4];
          g_column=argv[2];
        } else {
          fprintf(stderr, "%s is not a valid argument. Please use \"-o\".\n",
                  argv[3]);
          exit(0);
          return -1;
        }
      } else {
        if ((strcmp(argv[3], "-d") == 0) && (argv[4] != NULL)) {
          // g_column = argv[2];
          searchDir = argv[4];
          g_output = ".";
          g_column=argv[2];
        } else {
          fprintf(stderr, "%s is not a argument. Please use \"-d\".\n",
                  argv[3]);
          exit(0);
          return -1;
        }
      }

    }else if(strcmp(argv[3],"-c")==0){
      if (strcmp(argv[1], "-o") == 0) {
        if ((strcmp(argv[1], "-o") == 0) && argv[2] != NULL) {
          searchDir = ".";
          g_output = argv[2];
          g_column=argv[4];
        } else {
          fprintf(stderr, "%s is not a valid argument. Please use \"-o\".\n",
                  argv[3]);
          exit(0);
          return -1;
        }
      } else {
        if ((strcmp(argv[1], "-d") == 0) && (argv[1] != NULL)) {
          // g_column = argv[2];
          searchDir = argv[2];
          g_output = ".";
          g_column=argv[4];
        } else {
          fprintf(stderr, "%s is not a argument. Please use \"-d\".\n",
                  argv[3]);
          exit(0);
          return -1;
        }
      }
    }
    else{

    }

  }

  if (argc == 7) {
     //-c  movie_title -d thisdir -o thatdir
    if((strcmp(argv[1], "-c") == 0) && argv[2] != NULL){
      if ((strcmp(argv[5], "-o") == 0) && argv[6] != NULL) {
        g_column = argv[2];
        searchDir = argv[4];
        g_output = argv[6];
      }else if((strcmp(argv[5], "-d") == 0) && argv[6] != NULL){
        g_column = argv[2];
        searchDir = argv[6];
        g_output = argv[4];
      }
      else {
        fprintf(stderr, "%s is not a valid column type. Please use \"-o\".\n",
                argv[5]);
        exit(0);
        return -1;
      }
    }
    else if((strcmp(argv[1], "-d") == 0) && argv[2] != NULL){
      //-d thisdir -o thatdir -c  movie_title
      if ((strcmp(argv[5], "-c") == 0) && argv[6] != NULL) {
        g_column = argv[6];
        searchDir = argv[2];
        g_output = argv[4];
      }else if((strcmp(argv[5], "-o") == 0) && argv[6] != NULL){
        //-d thisdir -c movie_title -o thatdir
        g_column = argv[4];
        searchDir = argv[2];
        g_output = argv[6];
      }
      else {
        fprintf(stderr, "%s is not a valid column type. Please use \"-o\".\n",
                argv[5]);
        exit(0);
        return -1;
      }

    }
    else{
      return -1;
    }



  }

  // fprintf(stdout, "Column: %s, Output Dir: %s, Search Dir:%s\n",g_column,g_output,searchDir );

  if (pthread_mutex_init(&mutex, NULL) != 0) {
    fprintf(stderr, "\n mutex init has failed\n");
    return 1;
  }

  int dataType;
  if ((dataType = getDataType(g_column)) < 0) {
    fprintf(stderr, "%s is not a valid column in this project.\n", g_column);
    exit(EXIT_FAILURE);
    // return -1;
  } else {
    // printf("%d\n", dataType);
  }
  p_tid = syscall(__NR_gettid);

  fprintf(stdout, "Initial PID: %u\n", p_tid);
  fprintf(stdout, "TIDS's of all spawned threads: \n");
  fflush(stdout);
  threads = (pthread_t *)malloc(sizeof(pthread_t) * 2048);
  // thread_copy = (pthread_t *)malloc(sizeof(pthread_t) * 1024);

  searchDirectory(searchDir);
  // int q;
  // for (q = 0; q < g_count; q++) {
  //   fprintf(stdout, "%d, ", thread_copy[q]);
  //   // pthread_join(threads[q], NULL);
  // }
  fprintf(stdout, "\n");
  pthread_mutex_destroy(&mutex);
  // fprintf(stdout, "Total Threads: %d\n", g_count);

  g_head = mergeSort(g_head, g_column);

  printList(g_head, g_output);
  fprintf(stdout, "Total Threads: %d\n", g_count);


  return 0;
}
