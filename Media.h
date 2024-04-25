#ifndef MEDIA_H
#define MEDIA_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

class Post;
class User;
class Comment;
class Admin;

class User{
    protected:
       std::string username;
       std::string name;
       std::string password;
       int userId;
       int age;
       std::string job;
       std::vector<Post> posts;

    public:
        User(){}
        User(std::string username, std::string name, int age, std::string job){
            this->username=username;
            this->name=name;
            this->age=age;
            this->job=job;
        }
        
        
        bool registerUser();
        bool login();
        void Getinfo();
        void setData(int n, int usernum);
        void deletePost();
        virtual void displayMenu();
        std::string getUsername()
        {
            return username;
        }


};

class Admin : public User{

 public:
            Admin(std::string username, std::string name, int age, std::string job);
            Admin();//constructor to make a oridinary user admin of the community
            void addUserAdmin();
            void deleteUser();
            void displayMenu();
};

class Post{
     User author;
     int timestap;
     std::string post;

  public:
      
      void createPost();
      void viewPosts();
      void addComment(const Comment &comment);
      void viewComments();
};

class UserManager{
     User** udata;
     int usersNum;

 public:

     UserManager(){
        udata=nullptr;
        usersNum=0;
     }
     ~UserManager();

    
     void loadFromfile(const std::string & filename);
     void addUser(User *user);
     void loadPosts(User user);
     const User getuser();
     User *CheckIfAdmin(User *user);
     int getUsernum()
     {
        return usersNum;
     }

    
  
};





#endif 

