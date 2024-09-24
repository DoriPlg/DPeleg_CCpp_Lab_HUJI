//
// Created on 2/20/2022.
//

#ifndef USER_H
#define USER_H
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "RecommendationSystem.h"
#include "Movie.h"

class RecommendationSystem;
typedef std::unordered_map<sp_movie, double, hash_func, equal_func> rank_map;
using std::ostream;
using std::string;

class User
{
private:
	std::string _name;
	rank_map _ranks;
	std::shared_ptr<RecommendationSystem> _rs;
public:

	/**
	 * Constructor for the class
	 */
	User(const std::string& name, rank_map ranks,\
			std::shared_ptr<RecommendationSystem> rs);


	/**
	 * a getter for the user's name
	 * @return the username
	 */
	std::string get_name() const { return _name; }

	/**
	 * function for adding a movie to the DB
	 * @param name name of movie
     * @param year year it was made
	 * @param features a vector of the movie's features
	 * @param rate the user rate for this movie
	 */
	void add_movie_to_user(const std::string &name, int year,
                         const std::vector<double> &features,
                         double rate);


    /**
     * a getter for the ranks map
     * @return
     */
    rank_map get_ranks() const { return _ranks; }

	/**
	 * returns a recommendation according to the movie's content
	 * @return recommendation
	 */
	sp_movie get_rs_recommendation_by_content() const;

	/**
	 * returns a recommendation according to the similarity
	 * recommendation method
	 * @param k the number of the most similar movies to calculate by
	 * @return recommendation
	 */
	sp_movie get_rs_recommendation_by_cf(int k) const;

	/**
	 * predicts the score for a given movie
	 * @param name the name of the movie
	 * @param year the year the movie was created
	 * @param k the parameter which represents the number of the most similar
	 * movies to predict the score by
	 * @return predicted score for the given movie
	 */
	double get_rs_prediction_score_for_movie(const std::string& name, 
													int year, int k) const;

	/**
	 * output stream operator
	 * @param os the output stream
	 * @param user the user
	 * @return output stream
	 */
	friend ostream& operator<<(ostream& os, const User& user);

	/**
	 * get the average of the user's ratings
	 * @return the average of the user's ratings
	 */
	double get_average() const;

};



#endif //USER_H
