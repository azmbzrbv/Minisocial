#include "Media.h"


int main(){
  bool running=true;
  UserManager manager;
  User *user=new User(); 
  std::cout<<"*****Welcome to Minisocial****"<<std::endl;
  manager.loadFromfile("userdata.txt");

 while(running){
  char choice;
  std::cout<<"1. Register"<<std::endl;
  std::cout<<"2. Log in"<< std::endl;
  std::cout<<"3. Exit!"<<std::endl;
  std::cout<<"Enter the corresponding number!"<<std::endl;
  std::cin>>choice;
  if(choice>'3' || choice<'1'){
     std::cout<<"Invalid option, please type again!"<<std::endl;
     std::cin>>choice;
  }
  
if(choice=='1'){
  {
      if(user->registerUser()){
        user->setData(0, manager.getUsernum());/// it wasn't implemented fully. consider making the manager static
        manager.addUser(user);
        std::cout<<"Regisration is successfull!"<<std::endl;
        running=false;
      }
        
      else
        std::cout<<"Something went wrong! Please, try again!"<<std::endl;   
  }  

}
else if(choice=='2'){
   
    if(user->login())
    {
      user=manager.CheckIfAdmin(user); //check if admin by creating the method in manager!
      
      std::cout<<"You have logged in successfully!"<<std::endl;
      running=false;
    }
    else{
      std::cout<<"Plsease, try again!"<<std::endl;
    }
}

else if(choice=='3')
  return 0;
 }

 char choose='99';
 user->displayMenu();

while(choose!='7')
{
  

  
  std::cout<<"Please type a corresponding number!"<<std::endl;
  std::cin>>choose;

  switch (choose)
  {
  case '1': std::cout<<"This function is not ready yet!"<<std::endl; break;

  case '2': std::cout<<"This function is not ready yet!"<<std::endl; break;

  case '3': std::cout<<"This function is not ready yet!"<<std::endl; break;

  case '4': std::cout<<"This function is not ready yet!"<<std::endl; break;

  case '5': std::cout<<"This function is not ready yet!"<<std::endl; break;

  case '6': std::cout<<"This function is not ready yet!"<<std::endl; break;

  case '8': std::cout<<"This function is not ready yet!"<<std::endl; break;

  case '9': std::cout<<"This function is not ready yet!"<<std::endl; break;

  case '10': std::cout<<"This function is not ready yet!"<<std::endl; break;

  default: break;
  }

}

/*Further implementations:
loadposts
userpost.txt*/

// questions to ask:
//what will happen if i make whole class static?
//



     
  



 return 0;


}