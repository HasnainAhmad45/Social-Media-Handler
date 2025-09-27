#include "Post.h"
#include <fstream>
#include <iostream>
#include <sstream>
int Post::currentID = 0;

Post::Post(const std::string &content, const std::string &author)
    : content(content), author(author), likes(0)
{
    postID = getNextID();
}

int Post::getID() const { return postID; }
std::string Post::getContent() const { return content; }
std::string Post::getAuthor() const { return author; }
int Post::getLikes() const { return likes; }

bool Post::hasUserLiked(const std::string &username) const
{
    return std::find(likedBy.begin(), likedBy.end(), username) != likedBy.end();
}

void Post::addLike(const std::string &username)
{
    if (!hasUserLiked(username))
    {
        likes++;
        likedBy.push_back(username);
    }
}

void Post::addComment(const std::string &comment)
{
    comments.push_back(comment);
}

void Post::display() const
{
    std::cout << "\n=== Post #" << postID << " by " << author << " ===\n";
    std::cout << content << "\n";
    std::cout << "Likes: " << likes << "\n";
    if (!comments.empty())
    {
        std::cout << "Comments: \n";
        for (const auto &comment : comments)
        {
            std::cout << "--> " << comment << "\n";
        }
    }
    std::cout << "====================\n";
}

void Post::serialize(std::ofstream &out) const
{
    out << postID << "\n"
        << content << "\n"
        << author << "\n"
        << likes << "\n";
    out << comments.size() << "\n";
    for (const auto &comment : comments)
    {
        out << comment << "\n";
    }
    out << likedBy.size() << "\n";
    for (const auto &user : likedBy)
    {
        out << user << "\n";
    }
}

void Post::deserialize(std::ifstream &in)
{
    in >> postID;
    in.ignore();
    std::getline(in, content);
    std::getline(in, author);
    in >> likes;
    int commentCount;
    in >> commentCount;
    in.ignore();
    comments.clear();
    for (int i = 0; i < commentCount; ++i)
    {
        std::string comment;
        std::getline(in, comment);
        comments.push_back(comment);
    }
    int likedByCount;
    in >> likedByCount;
    in.ignore();
    likedBy.clear();
    for (int i = 0; i < likedByCount; ++i)
    {
        std::string user;
        std::getline(in, user);
        likedBy.push_back(user);
    }
}

int Post::getNextID() { return ++currentID; }