#ifndef POST_H
#define POST_H
#include <string>
#include <vector>
#include <algorithm>

class Post {
private:
    static int currentID;
    int postID;
    std::string content;
    std::string author;
    int likes;
    std::vector<std::string> comments;
    std::vector<std::string> likedBy;
public:
    Post(const std::string& content = "", const std::string& author = "");
    int getID() const;
    std::string getContent() const;
    std::string getAuthor() const;
    int getLikes() const;
    bool hasUserLiked(const std::string& username) const;
    void addLike(const std::string& username);
    void addComment(const std::string& comment);
    void display() const;
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);
    static int getNextID();
};

#endif