#ifndef MEDIA_H
#define MEDIA_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <exception>

class Post;
class User;
class Admin;
class UserManager;

class User{
    protected:
       std::string username;
       std::string name;
       std::string password;
       bool isAdmin;
       int age;
       std::string job;
       std::vector<Post> posts;

    public:
        User(){
         isAdmin=false;
        }
        User(std::string username, std::string name, int age, std::string job, bool isAdmin){
            this->username=username;
            this->name=name;
            this->age=age;
            this->job=job;
            this->isAdmin=isAdmin;
        }
        
        
        bool registerUser();//done
        bool login();//done
        void displayallposts();//done
        std::string getUsername();
        std::string getJob();
        std::string getName();
        std::vector<Post> Getposts();
        int getAge();
        void deletePost();//done
        void addPost();// done
        virtual void displayMenu();//done
        virtual void deleteUser(UserManager &manger);
        virtual void  MakeAdmin(UserManager &manager);
        virtual void deleteOthersPost(UserManager &manager);
        void Setdata(const UserManager &manager);//done
        bool getIsAdmin();
   
        
       
       
       friend class UserManager; // 
       

};

class Admin : public User{
   
 public:
            Admin(std::string username, std::string name, int age, std::string job, bool isAdmin);
            Admin(User *user);//constructor to make a oridinary user admin of the community
            void MakeAdmin(UserManager &manager);
            void deleteUser(UserManager &manager);
            void deleteOthersPost(UserManager &manager);
            void displayMenu();


            friend class UserManager;
};

class Post{
     User *author;
     std::string content;
     std::vector<std::string> comments;

  public:
      
      Post(User *user, std::string content, std::vector<std::string> comments){
        author=user;
        this->content=content;
        this->comments=comments;
      }
      
      Post(){}
      
      void createPost(User *user);
      void viewPost(int index);
      void addComment();
      void viewComments();
      std::string getContent();
      int getCommentsSize();
      std::string getCommentContentAt(int index);

};

class UserManager{
     User** udata;//it is just an array which is pointing to pointers(users)
     int usersNum;

 public:

     UserManager(){
        udata=nullptr;
        usersNum=0;
     }
     ~UserManager();
     

     void UploadPosts(User *user);
     void loadFromfile(const std::string & filename);
     void addUser(User *user);
     void SearchUser();
     void listUsers();
     User *AssignData(User *user);
     int getUsernum() const
     {
        return usersNum;
     }
     void UpdatePostData(const std::string &filename) const;
     void UpdateUserData(const std::string &filename) const;
     void UpdataUsersfile(const std::string &filename)const;
     void displayOthersposts();
     void removeUser(int index);
     void Uploadpassword(User *user);

    
     friend class Admin;
};


#endif 

