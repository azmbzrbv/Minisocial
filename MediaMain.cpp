#include "Media.h"


int main(){
  bool running=true;
  UserManager manager;// manager object is created for managing the general application
  User *user=new User(); 
  std::cout<<"*****Welcome to Minisocial****"<<std::endl;

  try
  {
    manager.loadFromfile("userdata.txt");// loading all necessary data from the database
  }
  catch(const std::exception &e)
  {
    std::cerr <<"Exception has occured! "<< e.what() << '\n';
  }
  
 
 while(running){
  int choice;
  std::cout<<"1. Register"<<std::endl;
  std::cout<<"2. Log in"<< std::endl;
  std::cout<<"3. Exit!"<<std::endl;
  std::cout<<"Enter the corresponding number!"<<std::endl;
  std::cin>>choice;
  if(std::cin.fail())// check if non-integer value is typed. std::cin fails when data type doesn't match expected type
  {
    std::cin.clear();// clears the error flags on cin so it can work again
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Removes bad input from the stream
    std::cout<<"Invalid command, please type again!"<<std::endl;
  }

 else if(choice>3 || choice<1){
     std::cout<<"Invalid option, please type again!"<<std::endl;
     std::cin>>choice;
  }
  
else if(choice==1){
  {
    try{
      if(user->registerUser()){
        manager.addUser(user); 
        manager.UpdatePostData("userpost.txt");
        manager.UpdateUserData("userdata.txt");
        manager.UpdataUsersfile("users.txt");
        std::cout<<"Regisration is successfull!"<<std::endl;
        running=false;
      }
        
      else
        std::cout<<"Something went wrong! Please, try again!"<<std::endl;   
    }
    catch(const std::exception &e)
    {
      std::cerr<<"Exception has occured! "<<e.what()<<std::endl;
    }
  }  

}
else if(choice==2){
   try{
        if(user->login())
        {
          User *assignedUser=manager.AssignData(user); 

          if(assignedUser!=user)
          {
            delete user;  // to avoid memery leakage
            user= assignedUser;
          }
          
          std::cout<<"You have logged in successfully!"<<std::endl;
          running=false;
       }else{
          std::cout<<"Please, try again!"<<std::endl;
        }
     }
     catch(const std::exception &e)
     {
      std::cerr<<"Exception occured during login: "<<e.what()<<std::endl;
     }
}

else if(choice==3)
  return 0;
 }

 int choose=99;
 user->displayMenu();

while(choose!=12)
{
  

  
  std::cout<<"Please type a corresponding number from MENU!"<<std::endl;
  std::cin>>choose;

  if(std::cin.fail())// check if non-integer value is typed. std::cin fails when data type doesn't match expected type
  {
    std::cin.clear();// clears the error flags on cin so it can work again
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Removes bad input from the stream
    std::cout<<"Invalid command"<<std::endl;
    continue;
  }

  switch (choose)
  {
  case 1: user->addPost(); 
          try
          {
            manager.UpdatePostData("userpost.txt");
          }
          catch(const std::exception &e)
          {
            std::cerr <<"Exception has occured! "<< e.what() << '\n';
          }
      break;//done 

  case 2: manager.displayOthersposts(); break;// done 

  case 3: user->displayallposts(); break;//done

  case 4: user->deletePost();
          try
          {
            manager.UpdatePostData("userpost.txt");
          }
          catch(const std::exception& e)
          {
             std::cerr <<"Exception has occured! "<< e.what() << '\n';
          }
    break;

  case 5: manager.listUsers(); break;

  case 6: manager.SearchUser(); break;

  case 7: user->Setdata(manager);  break;

  case 8: user->displayMenu(); break;

  case 9: user->MakeAdmin(manager); break;

  case 10: user->deleteUser(manager); break;

  case 11: user->deleteOthersPost(manager); break;
  
  case 12: std::cout<<"Thank you for using Minisocial!"<<std::endl; break;

  default: std::cout<<"Invalid command!"<<std::endl; break;
  }

}


 return 0;


}
