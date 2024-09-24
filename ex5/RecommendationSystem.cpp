#include "RecommendationSystem.h"


sp_movie RecommendationSystem::add_movie_to_rs(const std::string& name,
                        int year, const std::vector<double>& features)
{
    Movie movie(name, year);
    sp_movie movie_p = std::make_shared<Movie>(movie);
    _movies[movie]=std::make_pair(movie_p, features);
    return movie_p;
}

std::vector<double> RecommendationSystem::get_user_preferences(
                                                const User& user)
{
    double factor = user.get_average();
    rank_map ranks = user.get_ranks();
    // initialize user preferences to 0
    std::vector<double> user_preferences;
    for(int i = 0; i < (int)_movies.begin()->second.second.size();i++)
    {
        user_preferences.push_back(0);
    }
    // calculate user preferences
    for (auto &movie : ranks)
    {
        double movie_rate = movie.second - factor;
        for (int i = 0; i <(int) user_preferences.size(); i++)
        {
            user_preferences[i] += movie_rate*_movies[*movie.first].second[i];
        }
    }
    return user_preferences;
}

double norm(std::vector<double> vec)
{
    double sum = 0;
    for (double val : vec)
    {
        sum += val * val;
    }
    return sqrt(sum);
}

double get_similarity(  const std::vector<double> vec1,
                        const std::vector<double> vec2)
{
    double sum = 0;
    for (int i = 0; i < (int)vec1.size(); i++)
    {
        sum += vec1[i] * vec2[i];
    }
    return sum / (norm(vec1) * norm(vec2));
}

sp_movie RecommendationSystem::best_match(
             std::vector<double> preferences,
                        movie_data& movies) const
{
    double max = 0;
    sp_movie best_match;
    for (auto &movie : movies)
    {
        double match = get_similarity(preferences, movie.second.second);
        if (match > max || best_match == nullptr)
        {
            max = match;
            best_match = movie.second.first;
        }
    }
    return best_match;
}

sp_movie RecommendationSystem::recommend_by_content(const User& user)
{
    std::vector<double> user_preferences = this->get_user_preferences(user);
    movie_data unseen_movies = _movies;
    for (auto &movie : user.get_ranks())
    {
        unseen_movies.erase(*movie.first);
    }
    return this->best_match(user_preferences, unseen_movies);
    // return this->best_match(user_preferences, unseen_movies);
}

std::vector<sp_movie> RecommendationSystem::get_k_closest_movies(
        const User& user,  sp_movie movie, int k)
{
    std::vector<double> movie_rate = _movies[*movie].second;
    std::vector<sp_movie> closest_movies;
    movie_data movies;
    for (auto &m : user.get_ranks())
    {
        movies[*m.first] = _movies[*m.first];
    }
    for (int i = 0; i < k; i++)
    {
        sp_movie best_match = this->best_match(movie_rate, movies);
        closest_movies.push_back(best_match);
        movies.erase(*best_match);
    }
    return closest_movies;
}

double RecommendationSystem::predict_movie_score(const User& user, 
                                    const sp_movie &movie, int k)
{
    std::vector<sp_movie> closest_movies =\
            this->get_k_closest_movies(user, movie, k);
    double sum = 0;
    double similarity_sum = 0;
    for (int i = 0; i<k; i++)
    {
        sum+= user.get_ranks()[closest_movies[i]] * get_similarity(
                _movies[*closest_movies[i]].second, _movies[*movie].second);
        similarity_sum += get_similarity(_movies[*closest_movies[i]].second,
                                                    _movies[*movie].second);
    }
    return sum / similarity_sum;    
}

sp_movie RecommendationSystem::recommend_by_cf(const User& user, int k)
{
    double max = 0;
    sp_movie best_match;
    for (auto &movie : _movies)
    {
        if (user.get_ranks().find(movie.second.first) ==\
                                            user.get_ranks().end())
        {
            double score = predict_movie_score(user, movie.second.first, k);
            if (score > max || best_match == nullptr)
            {
                max = score;
                best_match = movie.second.first;
            }
        }
    }
    return best_match;
}


sp_movie RecommendationSystem::get_movie(const std::string& name, int year)
{
    Movie movie(name, year); 
    auto it = _movies.find(movie);
    if (it != _movies.end())
    {
        return it->second.first;
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const RecommendationSystem& rs)
{
    for (const auto &movie : rs._movies)
    {
        os << movie.first;
    }   
    return os;
}