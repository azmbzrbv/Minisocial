#include "Media.h"

Admin::Admin(User *user)
{  
     username = user->getUsername();
     job= user->getJob();
     name=user->getName();
     age=user->getAge();
     posts=Getposts();
     isAdmin=true;


  
}


Admin:: Admin(std::string username, std::string name, int age, std::string job, bool isAdmin)
{
              this->username=username;
              this->name=name;
              this->age=age;
              this->job=job;
              this->isAdmin=isAdmin;
}

void Admin::MakeAdmin(UserManager &manager) 
{
     while(true)
     {
          std::cout<<"Write the username of the person!"<<std::endl;
          std::cout<<"Write \"Exit\" if you want to go back!"<<std::endl;
          std::string searchname;
          int index=-1;
          std::getline(std::cin>>std::ws, searchname);
          if(searchname=="Exit" || searchname=="exit")
           {
               return;
           }
          
          for(int i=0; i<manager.getUsernum(); i++)
           {
               if(searchname==manager.udata[i]->getUsername())
               {
                         index=i;
                         break;
               }
           }
          
          if(index==-1)
           {
                std::cout<<"Username doesn't exists! Please, try again!"<<std::endl;
           }
          else if(manager.udata[index]->getIsAdmin())
           {
               std::cout<<"This user is already an Admin!"<<std::endl;
           }
          else
           {
            Admin *newadmin=new Admin(manager.udata[index]);
            delete manager.udata[index];
            manager.udata[index]=newadmin;

            try
            {
               manager.UpdateUserData("userdata.txt");
            }
            catch(const std::exception& e)
            {
               std::cerr <<"Exception has occured! "<< e.what() << '\n';
               continue;
            }

            std::cout<<"New admin has been created!"<<std::endl;
            return;
           }
     }
}



void Admin::deleteUser(UserManager &manager)
{
     while(true)
     {
          std::string checkname;
          std::cout<<"Write the username of the person you want to delete!"<<std::endl;
          std::cout<<"Write \"Exit\" if you want to go back!"<<std::endl;
          std::getline(std::cin>>std::ws, checkname);
          int index=-1;
          
          if(checkname=="Exit" || checkname=="exit")
          {
               return;
          }
          else if(checkname==username)
          {
               std::cout<<"You can't delete yourself!"<<std::endl;
               continue;
          }

          for(int i=0; i<manager.usersNum; i++)
          {
               if(checkname==manager.udata[i]->getUsername())
               {
               index=i;
               break;
               }
          }

          if(index==-1)
          {
               std::cout<<"This username doesn't exists"<<std::endl;
               continue;
          }
          else
          {
            try
            {
              manager.removeUser(index);
              manager.UpdateUserData("userdata.txt");
              manager.UpdatePostData("userpost.txt");
              manager.UpdataUsersfile("users.txt");
              std::cout<<"User has been deleted!"<<std::endl;
            }
            catch(const std::exception &e)
            {
               std::cout<<"Exception has occured! "<<e.what()<<std::endl;
               continue;
            }
          }
     }

}

void Admin::deleteOthersPost(UserManager &manager)
{
     while(true)
     {
          std::cout<<"Write the username of the person to delete a post!"<<std::endl;
          std::cout<<"Write \"Exit\" to go back the MENU!"<<std::endl;
          std::string checkname;
          int index=-1;
          std::getline(std::cin>>std::ws, checkname);

          if(checkname=="Exit" && checkname=="exit")
          {
               return;
          }

          for(int i=0; i<manager.usersNum; i++) 
          {
             if(checkname==manager.udata[i]->getUsername())
             {
               index=i;
               break;
             }
          }

          if(index==-1)
          {
               std::cout<<"Username doesn't exists"<<std::endl;
               continue;
          }

          else
          {
               manager.udata[index]->deletePost();
               try
               {
                   manager.UpdatePostData("userpost.txt");
               }
               catch(const std::exception& e)
               {
                    std::cerr << "Exception has occured! " << e.what() << '\n';
               }
               
               
               return;
          }

     }
}

void Admin::displayMenu()
{
     std::cout<<"1. Create a post"<<std::endl
              <<"2. See the other users' posts"<<std::endl
              <<"3. list my posts"<<std::endl
              <<"4. Delete post"<<std::endl
              <<"5. List all the people in the community"<<std::endl
              <<"6. Search by Username"<<std::endl
              <<"7. My profile"<<std::endl
              <<"8. Display MENU!"<<std::endl
              <<"9. Make an admin"<<std::endl
              <<"10. delete user"<<std::endl
              <<"11. Delete others' posts"<<std::endl
              <<"12. Exit!"<<std::endl;

}