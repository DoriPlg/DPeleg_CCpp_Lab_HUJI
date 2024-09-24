#include "User.h"

User::User(const std::string &name, rank_map ranks,\
                            std::shared_ptr<RecommendationSystem> rs):
                            _name(name), _ranks(ranks), _rs(rs)
{

}


void User::add_movie_to_user(const std::string &name, int year,
                         const std::vector<double> &features,
                         double rate)
{
    Movie movie(name, year);
    sp_movie movie_p = std::make_shared<Movie>(movie);
    if (_ranks.find(movie_p) != _ranks.end())
    {
        _ranks[movie_p] = rate;
    }
    else
    {
        _ranks.insert({movie_p, rate});
    }
    _rs->add_movie_to_rs(name, year, features);
}

double User::get_rs_prediction_score_for_movie(const string& name,\
                                        int year, int k) const
{
    Movie movie(name, year);
    sp_movie movie_p = std::make_shared<Movie>(movie);
    return _rs->predict_movie_score(*this, movie_p, k);
}

sp_movie User::get_rs_recommendation_by_content() const
{
    return _rs->recommend_by_content(*this);
}

sp_movie User::get_rs_recommendation_by_cf(int k) const
{
    return _rs->recommend_by_cf(*this, k);
}

ostream& operator<<(ostream& os, const User& user)
{
    os<<"Name: "<<user.get_name()<<std::endl;
    os<< *user._rs;
    os<<std::endl;
    return os;
}

double User::get_average() const
{
    double sum = 0;
    for (auto it = _ranks.begin(); it != _ranks.end(); ++it)
    {
        sum += it->second;
    }
    return sum / _ranks.size();
}
