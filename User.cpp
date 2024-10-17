#include "Media.h"

void User::deleteUser(UserManager &manager)
{
    std::cout<<"Invalid command!"<<std::endl;
}

void User::deleteOthersPost(UserManager &manager)
{
    std::cout<<"Invalid command!"<<std::endl;
}

void User::MakeAdmin(UserManager &manager)
{
    std::cout<<"Invalid command!"<<std::endl;
}

int User::getAge()
{
    return age;
}

std::vector<Post> User::Getposts()
{
    return posts;
}

std::string User::getJob()
{
    return job;
}

std::string User::getName()
{
    return name;
}

std::string User::getUsername()
{
    return username;
}

bool User::getIsAdmin()
{
    return isAdmin;
}

void User::displayMenu()
{
     std::cout<<"1. Create a post"<<std::endl
              <<"2. See the ohter users' posts"<<std::endl
              <<"3. list my posts"<<std::endl
              <<"4. Delete post"<<std::endl
              <<"5. list all the people in the community"<<std::endl
              <<"6. search by Username"<<std::endl
              <<"7. My profile!"<<std::endl
              <<"8. Display MENU"<<std::endl
              <<"12. Exit!"<<std::endl;

}

bool User::registerUser()
{

    std::fstream myfile;
    
    bool UsernameExists;
    
    std::cout<<"Please type your name?"<<std::endl;
    std::getline(std::cin>>std::ws, name);
   

    do{
            std::cout<<"Please, type your username"<<std::endl;
            std::cin>>username;

            myfile.open("users.txt", std::ios::in);
            if(!myfile.is_open())
            {
                throw std::runtime_error("Unable to open a file for registration!");
            }

            std::string line;
            std::string username1;
            UsernameExists=false;

            while(std::getline(myfile, line))
            {
                std::istringstream iss(line);

                iss>>username1;

                if(username1==this->username)
                {
                    std::cout<<"This username is already in use! Please, change it"<<std::endl;
                    UsernameExists=true;
                    break;
                }
            }
            
            myfile.close();
    }while(UsernameExists);
 
 
    std::cout<<"Please, type your password!"<<std::endl;
    std::getline(std::cin>>std::ws, password);
    isAdmin=false;
    age=0;
    job='-';

    return true;
}

bool User::login()
{
     std::cout<<"Please, type your username"<<std::endl;
     std::cin>>username;
     std::cout<<"Please, type your password"<<std::endl;
     std::getline(std::cin>>std::ws, password);

     std::fstream myfile("users.txt", std::ios::in);


     if(!myfile.is_open())
     {
         throw std::runtime_error("Unable to open a file for login!");
     }
     std::string line, fileusername, filepassword;
     
     while(std::getline(myfile, line))
     {
        std::istringstream iss(line);

        iss>>fileusername>>filepassword;

        if(fileusername==username)
        {
            if(filepassword==password)
            {
                return true;
            }
            else{
                std::cout<<"Password is incorrect!"<<std::endl;
                myfile.close();
                return false;
            }
        }

     }

     std::cout<<"There is no such username!"<<std::endl;
     myfile.close();
     return false;
    
}



void User::displayallposts()
{
    if(posts.size()==0)
    {
        std::cout<<"There are no posts!"<<std::endl;
    }
    for(int i=0; i<posts.size(); i++)
    {
        posts[i].viewPost(i);
    }
}

void User::addPost()
{
    Post post;
    post.createPost(this);

    posts.push_back(post);
    std::cout<<"Post created successfully!"<<std::endl;
}

void User::deletePost()
{
    if(posts.size()==0)
    {
        std::cout<<"There is no post to delete!"<<std::endl;
    }
   else{ 
        displayallposts();
        int num;
     while(true)
      {
        std::cout<<"Which post do you want to delete (please, type corresponding number?)"<<std::endl;
        std::cout<<"If you want to go back type '-1' !"<<std::endl;
        std::cin>>num;
        if(std::cin.fail())// check if non-integer value is typed. std::cin fails when data type doesn't match expected type
            {
                std::cin.clear();// clears the error flags on cin so it can work again
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Removes bad input from the stream
                std::cout<<"Invalid command, please type corresponding number"<<std::endl;
            }
        else if(num==-1)
        {
            return;
        }  
        else if(num < 1 || num > posts.size())  
        {
            std::cout<<"Invalid command, please type corresponding number"<<std::endl;     
        }
        else{
            posts.erase(posts.begin()+(num-1));
            std::cout<<"The post deleted successfully!"<<std::endl;
            return;
        }
      }  
   }   

}


void User::Setdata(const UserManager &manager)
{
   while(true)
    {
      std::cout<<"1.Full Name: "<<name<<std::endl
               <<"2.Username: "<<username<<std::endl
               <<"3.Age: "<<age<<std::endl
               <<"4.Occupation: "<<job<<std::endl
               <<"5.Number of posts: "<<posts.size()<<std::endl
               <<"6.Change password"<<std::endl
               <<std::endl;
      
        int num;
        std::cout<<"Type corresponding section to change it"<<std::endl;
        std::cout<<"Type '7' to go back to a MENU"<<std::endl;
        std::cin>>num;
        if(std::cin.fail())// check if non-integer value is typed. std::cin fails when data type doesn't match expected type
        {
            std::cin.clear();// clears the error flags on cin so it can work again
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Removes bad input from the stream
            std::cout<<"Invalid command"<<std::endl;
        }

        else if(num==1)
        {
            std::cout<<"Please type your New Full Name!"<<std::endl;
            std::getline(std::cin>>std::ws, name);

            try
            {
              manager.UpdateUserData("userdata.txt");
            }
            catch(const std::exception& e)
            {
                std::cerr <<"Exception has occured! "<< e.what() << '\n';
                return;
            }
            
           
            std::cout<<"Name has been updated!"<<std::endl;
        }
        else if(num==2){
           std::cout<<"Please type your new Username!"<<std::endl;
           std::getline(std::cin>>std::ws, username);
           
            try
            {
              manager.UpdatePostData("userpost.txt");
              manager.UpdateUserData("userdata.txt");
              manager.UpdataUsersfile("users.txt");
            }
            catch(const std::exception& e)
            {
                std::cerr <<"Exception has occured! "<< e.what() << '\n';
                return;
            }
            
           std::cout<<"Username has been updated!"<<std::endl;
        }
        else if(num==3)
        {
            int newage;
            std::cout<<"Please enter your new age!"<<std::endl;
            std::cin>>newage;
            if(std::cin.fail())// check if non-integer value is typed. std::cin fails when data type doesn't match expected type
                {
                    std::cin.clear();// clears the error flags on cin so it can work again
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Removes bad input from the stream
                    std::cout<<"Invalid command"<<std::endl;
                    continue;
                }
            age=newage;
           
            try
            {
              manager.UpdateUserData("userdata.txt");
            }
            catch(const std::exception& e)
            {
                std::cerr <<"Exception has occured! "<< e.what() << '\n';
                return;
            }
            
            std::cout<<"Age has been updated!"<<std::endl;  
        }
        else if(num==4)
        {
           std::cout<<"Please type your new Occupation!"<<std::endl;
           std::getline(std::cin>>std::ws, job);
          
            try
            {
              manager.UpdateUserData("userdata.txt");
            }
            catch(const std::exception& e)
            {
                std::cerr <<"Exception has occured! "<< e.what() << '\n';
                return;
            }
            
           std::cout<<"Occupation has been updated!"<<std::endl;
          
        }
        else if(num==5)
        {
            std::cout<<"You can only change it by creating new post!"<<std::endl;
        }
        else if(num==6)
        {
            std::cout<<"Please type your old password!"<<std::endl;
            std::string check;
            std::getline(std::cin>>std::ws, check);

            if(password==check)
            {
               std::cout<<"Please type your new password"<<std::endl;
               std::getline(std::cin>>std::ws, password);
                
                try
                {
                manager.UpdataUsersfile("users.txt");
                }
                catch(const std::exception &e)
                {
                    std::cerr <<"Exception has occured! "<< e.what() << '\n';
                    return;
                }
            
              
               std::cout<<"Password has been updated!"<<std::endl;
            }
            else
            {
                std::cout<<"Wrong password!"<<std::endl;
            }
        }
        else if(num==7)
        {
            return;
        }
        else
        {
            std::cout<<"Invalid command"<<std::endl;
        }


    }
}