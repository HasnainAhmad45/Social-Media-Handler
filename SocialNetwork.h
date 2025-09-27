#ifndef SOCIAL_NETWORK_H
#define SOCIAL_NETWORK_H

#include "User.h"
#include <vector>
#include <string>

class SocialNetwork {
private:
    std::vector<User> users;
    std::string dataFile;
    void loadData();
    void saveData();
    User* findUser(const std::string& username);
public:
    SocialNetwork(const std::string& filename);
    bool registerUser(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password) const;
    void createPost(const std::string& username, const std::string& content);
    bool deletePost(int postID, const std::string& username);
    int likePost(int postID, const std::string& username);
    void commentOnPost(int postID, const std::string& username, const std::string& comment);
    bool displayAllPosts() const;
    bool displayUserPosts(const std::string& username) const;
    std::string getPostByID(int postID);
};
#endif
