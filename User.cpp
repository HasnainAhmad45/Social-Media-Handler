#include "User.h"
#include <fstream>
#include <algorithm>
#include <sstream>

User::User(const std::string& username, const std::string& password) 
    : username(username), password(password) {}

const std::string& User::getUsername() const { return username; }
const std::string& User::getPassword() const { return password; }
const std::vector<Post>& User::getPosts() const { return posts; }
std::vector<Post>& User::getPosts() { return posts; }

bool User::hasLikedPost(int postID) const {
    return likedPostIDs.find(postID) != likedPostIDs.end();
}

void User::addLikedPost(int postID) {
    likedPostIDs.insert(postID);
}

void User::removeLikedPost(int postID) {
    likedPostIDs.erase(postID);
}

bool User::likePost(int postID, const std::string& likerUsername) {
    for (auto& post : posts) {
        if (post.getID() == postID) {
            if (post.hasUserLiked(likerUsername)) {
                return false;
            }
            post.addLike(likerUsername);
            return true;
        }
    }
    return false;
}

bool User::addComment(int postID, const std::string& commenter, const std::string& comment) {
    for (auto& post : posts) {
        if (post.getID() == postID) {
            post.addComment(comment);
            return true;
        }
    }
    return false;
}

void User::createPost(const std::string& content) {
    posts.emplace_back(content, username);
}

bool User::deletePost(int postID) {
    auto it = std::find_if(posts.begin(), posts.end(), 
        [postID](const Post& post) { return post.getID() == postID; });
    if (it != posts.end()) {
        posts.erase(it);
        return true;
    }
    return false;
}

bool User::displayPosts() const {
    if (posts.empty()) return false;
    for (const auto& post : posts) {
        post.display();
    }
    return true;
}

void User::serialize(std::ofstream& out) const {
    out << username << "\n" << password << "\n";
    out << posts.size() << "\n";
    for (const auto& post : posts) {
        post.serialize(out);
    }
    out << likedPostIDs.size() << "\n";
    for (int postID : likedPostIDs) {
        out << postID << "\n";
    }
}

void User::deserialize(std::ifstream& in) {
    std::getline(in, username);
    std::getline(in, password);
    int postCount;
    in >> postCount;
    in.ignore();
    posts.clear();
    for (int i = 0; i < postCount; ++i) {
        Post post;
        post.deserialize(in);
        posts.push_back(post);
    }
    int likedCount;
    in >> likedCount;
    in.ignore();
    likedPostIDs.clear();
    for (int i = 0; i < likedCount; ++i) {
        int postID;
        in >> postID;
        in.ignore();
        likedPostIDs.insert(postID);
    }
}