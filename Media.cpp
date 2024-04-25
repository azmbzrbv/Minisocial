#include "Media.h"

Admin::Admin()
{

}

Admin:: Admin(std::string username, std::string name, int age, std::string job)
{
              this->username=username;
              this->name=name;
              this->age=age;
               this->job=job;
}

void Admin::addUserAdmin()
{

}

void Admin::deleteUser()
{

}

void Admin::displayMenu()
{
     std::cout<<"1. Make a post"<<std::endl
              <<"2. See the ohter users' posts"<<std::endl
              <<"3. list my posts"<<std::endl
              <<"4. list my comments"<<std::endl
              <<"5. list all the people in the community"<<std::endl
              <<"6. search by name"<<std::endl
              <<"7. Exit!"<<std::endl
              <<"8. Add user"<<std::endl
              <<"9. delete user"<<std::endl
              <<"10.Make an admin"<<std::endl;
}


void User::Getinfo(){}

 void User::displayMenu()
{
     std::cout<<"1. Make a post"<<std::endl
              <<"2. See the ohter users' posts"<<std::endl
              <<"3. list my posts"<<std::endl
              <<"4. list my comments"<<std::endl
              <<"5. list all the people in the community"<<std::endl
              <<"6. search by name"<<std::endl
              <<"7. Exit!"<<std::endl;

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
                std::cout<<"Unable to open data file"<<std::endl;
                return false;
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
    std::cin>>password;

    myfile.open("users.txt", std::ios::app);
    if(!myfile.is_open())
    {
       std::cout<<"Something went wrong"<<std::endl;
       return false;
    }

    myfile << std::left << std::setw(17) <<username <<password << '\n';

    return true;
}

bool User::login()
{
     std::cout<<"Please, type your username"<<std::endl;
     std::cin>>username;
     std::cout<<"Please, type your password"<<std::endl;
     std::cin>>password;

     std::fstream myfile("users.txt", std::ios::in);


     if(!myfile.is_open())
     {
        std::cout<<"Something went wrong!"<<std::endl;
        return false;
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

void User::setData(int n, int usernum)// if 1 then user can change it himself
{
    if(n==0){
        std::fstream myfile;
        myfile.open("userdata.txt", std::ios::app);
        if(!myfile.is_open())
        {
            std::cout<<"Couln't upload to the file"<<std::endl;
            return;
        }

        myfile<<'\n'<<"User "<<usernum+1<<'\n';
        myfile<<"--Admin:"<<0<<'\n';
        myfile<<"--Name:"<<name<<'\n';
        myfile<<"--Username:"<<username<<'\n';
        myfile<<"--Age:"<<0<<'\n';
        myfile<<"--Occupation"<<'-'<<'\n';

        myfile.close();

    }


    
}
void UserManager::addUser(User *user){
    User** newdata= new User*[usersNum+1];

    for(int i=0; i<usersNum; i++)
    {
        newdata[i]=udata[i];
    }

    newdata[usersNum]=user;

    delete []udata;
    udata=newdata;

    usersNum++; 
}

UserManager::~UserManager(){
 for(int i=0; i<usersNum; i++)
 {
    delete udata[i];
 }

 delete [] udata;
 udata=nullptr;
 usersNum=0;
}

void UserManager::loadFromfile(const std::string& filename)
 {
   std::fstream myfile(filename, std::ios::in);
   if(!myfile.is_open())
   {
    std::cout<<"Error uploading the file"<<std::endl;
    return;
   }

   std::string fileName, fileusername, filejob;
   int fileage;
   bool isAdmin;
   std::string line;
   while(getline(myfile, line))
   {
        std::istringstream iss(line);
        std::string key;

        if(getline(iss, key, ':'))
        {
            std::string value;
            getline(iss, value);
                if(!value.empty() && value[0]==' ')
                {
                    value=value.substr(1);
                }

           if(key.find("Name")!=std::string::npos){//find will return npos if will nof find the name
               fileName = value;
           }else if(key.find("Age")!=std::string::npos){ //consider adding the try catch function whihc is in the plan.txt
               fileage=std::stoi(value);
           }  else if (key.find("Admin") != std::string::npos) {
                isAdmin = (value == "1");
           }else if(key.find("Username")!=std::string::npos){
            fileusername=value;
           }else if (key.find("Occupation") != std::string::npos) {
                filejob = value;
                if(!isAdmin)
                {
                    User *user=new User(fileusername, fileName, fileage, filejob);
                    addUser(user);      
                    //addpost
                }
                else{
                    User *user=new Admin(fileusername, fileName, fileage, filejob);
                    addUser(user);
                    //addposts
                  
                }
               
           }

        }
   }

  myfile.close();
 }

  User *UserManager::CheckIfAdmin(User *user)
  {
         for(int i=0; i<usersNum; i++)
         {
            if(user->getUsername()==udata[i]->getUsername())
            {
                return udata[i];
            }
         }

         return user;
  }