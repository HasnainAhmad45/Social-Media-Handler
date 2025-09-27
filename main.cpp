#include "SocialNetwork.h"
#include <iostream>
#include <limits>
#include <iomanip>

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    std::cout << "\033[2J\033[1;1H";
}

void displayBox(const std::string &title)
{
    std::cout << "\n+--------------------------------------+\n";
    std::cout << "|" << std::setw(20 + title.length() / 2) << title
              << std::setw(20 - title.length() / 2) << "|\n";
    std::cout << "+--------------------------------------+\n";
}

void displayMenu(const std::vector<std::string> &options)
{
    for (size_t i = 0; i < options.size(); ++i)
    {
        std::cout << i + 1 << ". " << options[i] << "\n";
    }
    std::cout << "Choice: ";
}

void pressEnterToContinue()
{
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    SocialNetwork network("social_data.txt");
    std::string currentUser;

    while (true)
    {
        clearScreen();

        if (currentUser.empty())
        {
            displayBox("SOCIAL MEDIA SYSTEM");
            std::vector<std::string> options = {
                "Register",
                "Login",
                "View All Posts",
                "Exit"};
            displayMenu(options);

            int choice;
            std::cin >> choice;
            std::cin.ignore();

            switch (choice)
            {
            case 1:
            {
                clearScreen();
                displayBox("REGISTER NEW ACCOUNT");
                std::string username, password;
                std::cout << "Enter username: ";
                std::getline(std::cin, username);
                std::cout << "Enter password: ";
                std::getline(std::cin, password);

                if (network.registerUser(username, password))
                {
                    std::cout << "\nAccount created successfully!\n";
                }
                else
                {
                    std::cout << "\nUsername already exists!\n";
                }
                pressEnterToContinue();
                break;
            }
            case 2:
            {
                clearScreen();
                displayBox("USER LOGIN");
                std::string username, password;
                std::cout << "Username: ";
                std::getline(std::cin, username);
                std::cout << "Password: ";
                std::getline(std::cin, password);

                if (network.login(username, password))
                {
                    currentUser = username;
                    std::cout << "\nLogin successful! Welcome, " << username << "!\n";
                }
                else
                {
                    std::cout << "\nInvalid username or password!\n";
                }
                pressEnterToContinue();
                break;
            }
            case 3:
            {
                clearScreen();
                displayBox("ALL POSTS");
                if (!network.displayAllPosts())
                {
                    std::cout << "\nNo posts available to display.\n";
                }
                pressEnterToContinue();
                break;
            }
            case 4:
                return 0;
            default:
                std::cout << "\nInvalid choice!\n";
                pressEnterToContinue();
            }
        }
        else
        {
            displayBox("MAIN MENU - Welcome, " + currentUser);
            std::vector<std::string> options = {
                "Create New Post",
                "View My Posts",
                "View All Posts",
                "Like a Post",
                "Comment on Post",
                "Delete My Post",
                "Logout"};
            displayMenu(options);

            int choice;
            std::cin >> choice;
            std::cin.ignore();

            switch (choice)
            {
            case 1:
            {
                clearScreen();
                displayBox("CREATE NEW POST");
                std::string content;
                std::cout << "Enter your post content:\n";
                std::getline(std::cin, content);

                network.createPost(currentUser, content);
                std::cout << "\nPost published successfully!\n";
                pressEnterToContinue();
                break;
            }
            case 2:
            {
                clearScreen();
                displayBox("MY POSTS");
                if (!network.displayUserPosts(currentUser))
                {
                    std::cout << "\nYou haven't posted anything yet.\n";
                }
                pressEnterToContinue();
                break;
            }
            case 3:
            {
                clearScreen();
                displayBox("ALL POSTS");
                if (!network.displayAllPosts())
                {
                    std::cout << "\nNo posts available to display.\n";
                }
                pressEnterToContinue();
                break;
            }
            case 4:
            { // Like Post
                clearScreen();
                displayBox("LIKE A POST");
                if (network.displayAllPosts())
                {
                    int postID;
                    std::cout << "Enter Post ID to like: ";
                    while (!(std::cin >> postID))
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter Post ID: ";
                    }
                    int result = network.likePost(postID, currentUser);
                    if (result == 1)
                    {
                        std::cout << "Post liked successfully!\n";
                    }
                    else if (result == 0)
                    {
                        std::cout << "You've already liked this post.\n";
                    }
                    else
                    {
                        std::cout << "Invalid Post ID!\n";
                    }

                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get(); 
                }
                else
                {
                    std::cout << "\nNo posts available to like.\n";
                    pressEnterToContinue();
                }
                break;
            }
            case 5:
            {
                clearScreen();
                displayBox("ADD COMMENT");
                if (network.displayAllPosts())
                {
                    int postID;
                    std::string comment;
                    std::cout << "Enter Post ID to comment on: ";
                    while (!(std::cin >> postID))
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter Post ID: ";
                    }
                    std::cin.ignore();
                    std::cout << "Enter your comment: ";
                    std::getline(std::cin, comment);

                    network.commentOnPost(postID, currentUser, comment);
                    std::cout << "\nComment added successfully!\n";
                }
                else
                {
                    std::cout << "\nNo posts available to comment on.\n";
                }
                pressEnterToContinue();
                break;
            }
            case 6:
            { 
                clearScreen();
                displayBox("DELETE POST");
                if (network.displayUserPosts(currentUser))
                {
                    int postID;
                    std::cout << "Enter Post ID to delete: ";
                    while (!(std::cin >> postID))
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter Post ID: ";
                    }

                    if (network.deletePost(postID, currentUser))
                    {
                        std::cout << "Post deleted successfully!\n";
                    }
                    else
                    {
                        std::cout << "Cannot delete post (invalid ID or not your post)\n";
                    }

                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get(); 
                }
                else
                {
                    std::cout << "\nYou have no posts to delete.\n";
                    pressEnterToContinue();
                }
                break;
            }
            case 7:
                currentUser = "";
                std::cout << "\nLogged out successfully.\n";
                pressEnterToContinue();
                break;
            default:
                std::cout << "\nInvalid choice!\n";
                pressEnterToContinue();
            }
        }
    }

    return 0;
}
