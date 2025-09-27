#include "SocialNetwork.h"
#include "User.h"
#include <fstream>
#include <algorithm>
#include <sstream>

SocialNetwork::SocialNetwork(const std::string& filename) : dataFile(filename) {
    loadData();
}

void SocialNetwork::loadData() {
    std::ifstream in(dataFile);
    if (!in) return;

    int userCount;
    in >> userCount;
    in.ignore();

    for (int i = 0; i < userCount; ++i) {
        User user;
        user.deserialize(in);
        users.push_back(user);
    }
}
std::string SocialNetwork::getPostByID(int id) {
    for (auto& user : users) {
        for (auto& post : user.getPosts()) {
            if (post.getID() == id) {
                std::ostringstream oss;
                oss << "Post ID: " << post.getID() << "\n"
                    << "Author: " << post.getAuthor() << "\n"
                    << "Content: " << post.getContent() << "\n"
                    << "Likes: " << post.getLikes() << "\n";
                return oss.str();
            }
        }
    }
    return "Post not found.\n";
}
void SocialNetwork::saveData() {
    std::ofstream out(dataFile);
    if (!out) return;

    out << users.size() << "\n";
    for (const auto& user : users) {
        user.serialize(out);
    }
}

User* SocialNetwork::findUser(const std::string& username) {
    auto it = std::find_if(users.begin(), users.end(), 
        [&username](const User& user) { return user.getUsername() == username; });
    return it != users.end() ? &(*it) : nullptr;
}

bool SocialNetwork::registerUser(const std::string& username, const std::string& password) {
    if (username.empty() || password.empty()) return false;
    if (findUser(username)) return false;
    users.emplace_back(username, password);
    saveData();
    return true;
}

bool SocialNetwork::login(const std::string& username, const std::string& password) const {
    auto it = std::find_if(users.begin(), users.end(), 
        [&](const User& user) { return user.getUsername() == username && user.getPassword() == password; });
    return it != users.end();
}

void SocialNetwork::createPost(const std::string& username, const std::string& content) {
    if (User* user = findUser(username)) {
        user->createPost(content);
        saveData();
    }
}

bool SocialNetwork::deletePost(int postID, const std::string& username) {
    if (User* user = findUser(username)) {
        if (user->deletePost(postID)) {
            saveData();
            return true;
        }
    }
    return false;
}

int SocialNetwork::likePost(int postID, const std::string& username) {
    for (auto& user : users) {
        for (auto& post : user.getPosts()) {
            if (post.getID() == postID) {
                if (post.hasUserLiked(username)) {
                    return 0; // Already liked
                }
                post.addLike(username);
                saveData();
                return 1; 
            }
        }
    }
    return -1; 
}

void SocialNetwork::commentOnPost(int postID, const std::string& username, const std::string& comment) {
    for (auto& user : users) {
        for (auto& post : user.getPosts()) {
            if (post.getID() == postID) {
                post.addComment(username + ": " + comment);
                saveData();
                return;
            }
        }
    }
}

bool SocialNetwork::displayAllPosts() const {
    bool hasPosts = false;
    for (const auto& user : users) {
        if (user.displayPosts()) {
            hasPosts = true;
        }
    }
    return hasPosts;
}

bool SocialNetwork::displayUserPosts(const std::string& username) const {
    auto it = std::find_if(users.begin(), users.end(),
        [&username](const User& user) { return user.getUsername() == username; });
    return it != users.end() ? it->displayPosts() : false;
}