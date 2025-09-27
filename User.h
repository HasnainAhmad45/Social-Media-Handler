#ifndef USER_H
#define USER_H

#include "Post.h"
#include <vector>
#include <string>
#include <unordered_set>

class User {
private:
    std::string username;
    std::string password;
    std::vector<Post> posts;
    std::unordered_set<int> likedPostIDs;
public:
    User(const std::string& username = "", const std::string& password = "");
    const std::string& getUsername() const;
    const std::string& getPassword() const;
    const std::vector<Post>& getPosts() const;
    std::vector<Post>& getPosts();
    bool hasLikedPost(int postID) const;
    void addLikedPost(int postID);
    void removeLikedPost(int postID);
    bool likePost(int postID, const std::string& likerUsername);
    bool addComment(int postID, const std::string& commenter, const std::string& comment);
    void createPost(const std::string& content);
    bool deletePost(int postID);
    bool displayPosts() const;
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);
    
};

#endif