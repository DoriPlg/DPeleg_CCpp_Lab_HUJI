//
// Created on 2/20/2022.
//

#ifndef RECOMMENDATIONSYSTEM_H
#define RECOMMENDATIONSYSTEM_H
#include "User.h"
#include "Movie.h"
#include <map>
#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>


using std::ostream;
typedef \
    std::map<const Movie,std::pair< sp_movie,std::vector<double>>> movie_data;
class User;

class RecommendationSystem
{
private:
	movie_data _movies;
/**
 * a function that calculates the user preferences based on the user's ranking
 * @param user user to calculate preferences for
 * @return vector of user preferences
 */
     std::vector<double> get_user_preferences(const User& user);
/**
 * a function that calculates the movie with the highest match to the
 *  given preference vector
 * @param preferences user preferences
 * @return shared pointer to movie in system
 */
     sp_movie best_match(std::vector<double> preferences,
                              movie_data& movies) const;

/**
 * a function that gets the k most similar movies to the given movie
 * @param user user to from whose list to find the movies
 * @param movie movie to find similar movies to
 * @param k number of similar movies to find
 * @return vector of shared pointers to movies in system
 */
     std::vector<sp_movie> get_k_closest_movies(const User& user,
     							sp_movie movie, int k);

public:

	explicit RecommendationSystem():_movies({}) {};


    /**
     * adds a new movie to the system
     * @param name name of movie
     * @param year year it was made
     * @param features features for movie
     * @return shared pointer for movie in system
     */
	sp_movie add_movie_to_rs(const std::string& name,int year,
							const std::vector<double>& features);


    /**
     * a function that calculates the movie with highest score based on
     *  movie features
     * @param ranks user ranking to use for algorithm
     * @return shared pointer to movie in system
     */
	sp_movie recommend_by_content(const User& user);

    /**
     * a function that calculates the movie with highest predicted 
     * score based on ranking of other movies
     * @param ranks user ranking to use for algorithm
     * @param k
     * @return shared pointer to movie in system
     */
	sp_movie recommend_by_cf(const User& user, int k);


    /**
     * Predict a user rating for a movie given argument using item cf
     *  procedure with k most similar movies.
     * @param user_rankings: ranking to use
     * @param movie: movie to predict
     * @param k:
     * @return score based on algorithm as described in pdf
     */
	double predict_movie_score(const User &user, const sp_movie &movie,
												  int k);

	/**
	 * gets a shared pointer to movie in system
	 * @param name name of movie
	 * @param year year movie was made
	 * @return shared pointer to movie in system
	 */
	sp_movie get_movie(const std::string& name, int year);


	friend ostream& operator<<(ostream& os, const RecommendationSystem& rs);

};


#endif //RECOMMENDATIONSYSTEM_H
