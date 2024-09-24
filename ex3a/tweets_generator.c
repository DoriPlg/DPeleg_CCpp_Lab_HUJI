#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "markov_chain.h"

#define FILE_PATH_ERROR "Error: incorrect file path"
#define NUM_ARGS_ERROR "Usage: invalid number of arguments"

#define DELIMITERS " \n\t\r"
#define MAX_TWEET_LENGTH 1024
#define MAX_TWEET_WORDS 20
#define ADDING_ERROR -1
#define BASE 10

enum {NO_CAP = 4, WITH_CAP};
enum {SEED = 1, TWEETS,PATH, CAP};


//fill the database with the words from the file
// @param file file to read from
// @param words_to_read number of words to read, pass -1 if no limit
// @param markov_chain markov chain to fill
// @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
int fill_database(FILE *file, int words_to_read, MarkovChain **markov_chain)
{
    // indicator for whether there is a cap or not
    const int cap_exists = (words_to_read == -1) ? 0 : 1;
    char tweet[MAX_TWEET_LENGTH];
    // Read the file line by line, until the end of the file ot the amount
    // of words to read, if there is a cap.
    while(fgets(tweet, MAX_TWEET_LENGTH, file) &&\
                        cap_exists * words_to_read >= 0)
    { 
        char *word = strtok(tweet, DELIMITERS);
        Node * prev= NULL;
        // Read the words from the line, until the end of the line or the
        // amount of words to read, if there is a cap.
        while(word && cap_exists * (--words_to_read)>=0)
            {
            Node * new = add_to_database((*markov_chain), word);
            if(prev != NULL)
            {
                if(new == NULL || \
                add_node_to_frequency_list(prev->data, new->data)\
                                                    ==EXIT_FAILURE)
                {
                    return EXIT_FAILURE;
                }
            }
            prev = new;
            word = strtok(NULL, DELIMITERS);
        }
    }
    return EXIT_SUCCESS;
}

// Generate a tweet, the main function of the program
int main(int argc, char * argv[]){
    // Check if the number of arguments is correct
    if (argc != NO_CAP && argc != WITH_CAP){
        printf(NUM_ARGS_ERROR);
        return EXIT_FAILURE;
    }
    // Parse the arguments, set the seed, tweets, and cap
    unsigned int seed = strtol(argv[SEED],NULL,BASE), \
        tweets = strtol(argv[TWEETS],NULL,BASE);
    int cap = (argc == NO_CAP) ? -1 : strtol(argv[CAP],NULL,BASE);
    char *path = argv[PATH];
    srand(seed);

    // Create the markov chain, and check if the allocation was successful
    MarkovChain *markov_chain = malloc(sizeof(MarkovChain));
    if (markov_chain == NULL){
        printf(ALLOCATION_ERROR_MASSAGE);
        return EXIT_FAILURE;
    }
    markov_chain->database = NULL;

    // Open the file, and check if the file was opened successfully.
    // Free the database if the file was not opened successfully.
    FILE *file = fopen(path, "r");
    if (file == NULL){
        printf(FILE_PATH_ERROR);
        free_database(&markov_chain);
        return EXIT_FAILURE;
    }

    // Fill the database, either with a cap or wih negtive for no cap
    if(fill_database(file, cap, &markov_chain)==EXIT_FAILURE)
    {
        free_database(&markov_chain);
        return EXIT_FAILURE;
    }
    fclose(file);

    // Generate tweets
    for (unsigned int i = 0; i < tweets; i++){
        printf("Tweet %d:", i+1);
        generate_tweet(get_first_random_node(markov_chain), MAX_TWEET_WORDS);
    }        

    free_database(&markov_chain);
    return EXIT_SUCCESS;
}
