#include "markov_chain.h"

/**
 * Get random number between 0 and max_number [0, max_number).
 * @param max_number
 * @return Random number
 */
int get_random_number(int max_number)
{
    return rand() % max_number;
}

// Free a markov node and all of it's content from memory
// @param mar_node markov node to free
void free_markov_node( MarkovChain** chain, MarkovNode** mar_node)
{
    if(*mar_node)
    {
        if ((*mar_node)->data)
        {
            (*chain)->free_data((*mar_node)->data);
        }
        if ((*mar_node)->frequency_list)
        {
            free((*mar_node)->frequency_list);
        }
        free((*mar_node));
    }
}

// Free a node and all of it's content from memory
// @param node node to free
void free_node( MarkovChain** chain, Node **node)
{
    if (*node == NULL)
    {
        return;
    }
    if ((*node)->data != NULL)
    {
        free_markov_node(chain,&(*node)->data);
    }
    free((*node));
    *node = NULL;
}

// Free markov_chain and all of it's content from memory
// @param chain_ptr markov_chain to free
void free_markov_chain(MarkovChain **chain_ptr)
{
    if (chain_ptr == NULL)
    {
        return;
    }
    if (*chain_ptr)
    {
        if ((*chain_ptr)->database)
        {
            Node *cur_node = (*chain_ptr)->database->first;
            Node *next_node = NULL;
            while (cur_node != NULL)
            {
                next_node = cur_node->next;
                free_node(chain_ptr,&cur_node);
                cur_node = next_node;
            }
            free((*chain_ptr)->database);
        }
        free((*chain_ptr)); 
    }
    *chain_ptr = NULL;
}

Node* get_node_from_database( MarkovChain *markov_chain, void *data_ptr)  
{
    if (markov_chain->database==NULL || markov_chain->database->size == 0)
    { // if the database is empty, return NULL
        return NULL;
    }
    // iterate over the linked list
    for(Node *cur_node = markov_chain->database->first;\
                        cur_node;cur_node = cur_node->next)
    {
        if(markov_chain->comp_func(cur_node->data->data, data_ptr)==0)
        {
            return cur_node;
        }
    }
    return NULL;
}

MarkovNode* get_first_random_node( MarkovChain *markov_chain)
{
    // Check if the markov chain is empty, or any other condition
    // that would prevent the function from working
    if(markov_chain == NULL || markov_chain->database == NULL ||\
        markov_chain->database->size == 0\
        || markov_chain->database->first == NULL)
    {
        return NULL;
    }
    int random_number;
    Node *cur_node;
    do {
        cur_node=markov_chain->database->first;
        random_number = get_random_number(markov_chain->database->size);
        // Advance the pointer to the random node
        for(int i = 0; i < random_number; i++){
            cur_node = cur_node->next;
        }
    } // Check if the word is the last word in a sentence, if so, get another
    while(markov_chain->is_last(cur_node->data->data));
    return cur_node->data; 
}

MarkovNode* get_next_random_node( MarkovNode *cur_markov_node)
{
    // Check if the current markov node is empty, or any other condition
    // that would prevent the function from working
    if (cur_markov_node == NULL||\
        cur_markov_node->frequency_list == NULL||\
        cur_markov_node->frequency_list==0)
    {
        return NULL;
    }
    int total_frequency = 0;
    // Sum up the frequencies top get the total frequency, for probability
    for(int i = 0; i<cur_markov_node->frequency_list_size; i++)
    {
        total_frequency += (cur_markov_node->frequency_list+i)->frequency;
    }
    int random_number = get_random_number(total_frequency);
    int random_frequency = 0;
    int j;
    // Iterate over the frequency list to get the next random node,
    // based on the probability of the frequency
    for(j =0; j<total_frequency;j++)
    {
        random_frequency += cur_markov_node->frequency_list[j].frequency;
        if(random_frequency>random_number)
        {
            break;
        }
    }
    return cur_markov_node->frequency_list[j].markov_node;
}

void generate_random_sequence( MarkovChain *markov_chain,\
                    MarkovNode *first_node, int max_length)
{
    // Check if the input is valid
    if (first_node == NULL|| max_length <= 0||\
            markov_chain->is_last(first_node->data))
    {
        return;
    }
    MarkovNode *cur_node = first_node;
    int length = 0;
    // Advance randomly through the markov chain, until the tweet is finished
    while(length<max_length-1 && markov_chain->is_last(cur_node->data)==false)
    {
        length++;
        printf(" ");
        markov_chain->print_func(cur_node->data);
        if (cur_node->frequency_list_size == 0)
        {
            printf("\n");
            return;
        }
        cur_node = get_next_random_node(cur_node);
    }
    printf(" ");
    markov_chain->print_func(cur_node->data);
    printf("\n");
}

int add_node_to_frequency_list(MarkovNode *uber_node
                               , MarkovNode *added_node,\
                               MarkovChain *markov_chain)
{
    // Check if the node is already in the frequency list
    for(int i = 0; i < uber_node->frequency_list_size; i++) 
    {
        if(markov_chain->comp_func(\
                    uber_node->frequency_list[i].markov_node->data,\
                                                added_node->data)==0)
        {
            uber_node->frequency_list[i].frequency++;
            return EXIT_SUCCESS;
        }
    }
    // If the node is not in the frequency list, add it
    uber_node->frequency_list = realloc(uber_node->frequency_list,\
                                    sizeof(MarkovNodeFrequency) *\
                                    (uber_node->frequency_list_size+1));
    if(uber_node->frequency_list == NULL)
    {
        printf(ALLOCATION_ERROR_MASSAGE);
        return EXIT_FAILURE;
    }
    uber_node->frequency_list[uber_node->frequency_list_size++] =\
                        (MarkovNodeFrequency) {added_node,1};
    return EXIT_SUCCESS;
}

// Print an allocation error massage, free MNode and return NULL
Node* allocation_error_message( MarkovChain** chain,\
                MarkovNode **markov_node_to_free)
{
    free_markov_node(chain, markov_node_to_free);
    printf(ALLOCATION_ERROR_MASSAGE);
    return NULL;
}

// Create a new database for the markov chain
// @param markov_chain markov chain to create database for
// @return 0 on success, 1 otherwise
int create_database(MarkovChain * markov_chain)
{
    markov_chain->database = malloc(sizeof(LinkedList));
    if (markov_chain->database == NULL)
    {
        allocation_error_message(&markov_chain, NULL);
        return EXIT_FAILURE;
    }
    *(markov_chain->database)= (LinkedList){NULL, NULL, 0};
    return EXIT_SUCCESS;
}

Node* add_to_database(MarkovChain *markov_chain, void *data_ptr)
{
    if (markov_chain == NULL|| data_ptr == NULL|| sizeof(*data_ptr) == 0)
    {
        return NULL;
    }
    // check if the data is already in the database
    Node *new_node = get_node_from_database(markov_chain, data_ptr);
    if (new_node)
    {
        return new_node;
    }
    // Allocate memory for new node, and check if allocation was successful
    MarkovNode* new_markov_node = malloc(sizeof(MarkovNode));
    if(new_markov_node == NULL)
    {
        return allocation_error_message(&markov_chain, NULL);
    }
    *new_markov_node = (MarkovNode) {NULL, NULL, 0};
    // Since the data is not in the database, add it
    new_markov_node->frequency_list = malloc(sizeof(MarkovNodeFrequency));
    if (new_markov_node->frequency_list== NULL)
    {
        return allocation_error_message(&markov_chain, &new_markov_node);
    }
    *new_markov_node->frequency_list = (MarkovNodeFrequency) {NULL, 0};
    // Get the word from the data, and check if it was successful
    new_markov_node->data = markov_chain->copy_func(data_ptr);
    if (!new_markov_node->data)
    {
        return allocation_error_message(&markov_chain, &new_markov_node);
    }
    // Add the new node to the database
    if(markov_chain->database == NULL &&\
        create_database(markov_chain) == EXIT_FAILURE)
    {
        return allocation_error_message(&markov_chain, &new_markov_node);
    }
    if (add(markov_chain->database, new_markov_node) == EXIT_SUCCESS)
    {
        return markov_chain->database->last;
    }
    free_markov_node(&markov_chain, &new_markov_node);
    return NULL;
}
